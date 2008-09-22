#!/usr/bin/perl
#
# This script helps convert an MCAT DB to an ICAT one.
#
# Currently, this is very preliminary, but I was able to insert an SRB
# file into the ICAT and get it via 'iget'.
#
# If the Spull.log.* files don't exist, this script will run Spullmeta
# to create them.
#
# This script generates two files, one with iadmin commands and other
# with psql sql commands.  After these are created, this script will
# prompt and if confirmed will attempt to run iadmin and psql.  You
# might instead tho check the contents of these files and run the
# iadmin and psql steps my hand.
#
# You will need to change the following parameters for your
# particular MCAT and  ICATs and environment.

# Begin section to edit ---------------------------------------------------
# Conversion tables (cv_):
$cv_srbZone = "galvin";            # Your SRB zone name
$cv_irodsZone = "tempZone";   # Your iRODS zone name

# Special usernames to convert:
@cv_srb_usernames=("srbAdmin"); # username conversion table:srb form
@cv_irods_usernames=("rods");   # irods form for corresponding srb forms
@cv_srb_userdomains=("demo");   # Used for user.domain situations

# Special usernames to add
@cv_special_users=("vidarch");  # Needed for sils instance

# These below are used for ingesting users.
# Note that, by default, only users of type 'staff' are ingested.
# If you would like to ingest others, edit this list.
# The other commonly used user type is 'sysadmin' which would
# correspond to 'rodsadmin', but you might want to do those by hand.
@cv_srb_usertypes=("staff");         # The only types of users converted
@cv_irods_usertypes=("rodsuser");    # The corresponding user-type converted to

# This flag indicates if you want user names to be of the form
# user#domain or just user.
$useDomainWithUsername = "0"; # 0 no, 1 yes

$SRB_BEGIN_DATE="1995-07-12"; # approximate date your SRB was installed;used to
                              # avoid some unneeded built-in items, etc.
$Spullmeta = "/scratch/slocal/srbtest/testc/SRB2_0_0rel/utilities/bin/Spullmeta";
                              # if in Path this could also be just "Spullmeta"
$iadmin = "iadmin";           # Change this to be full path if not in PATH.
$psql = "psql";               # And this too.
$imeta = "imeta";             # And this one.

$password_length = 6;         # The length of the random password strings
                              # used for users.  Note that you will need
                              # to send the strings (from the $iadminFile)
                              # to the users in some manner.  They can
                              # then change their password with 'ipasswd'.

$bypass_time_for_speed = 1;   # For debug/speed, don't convert time values
                              # but instead use the current time

$thisUser = 'rods';           # The irods user that this is being run as.

# End section to edit  ---------------------------------------------------

# You can, but don't need to, change these:
$logUser = "Spull.log.user";     # Spullmeta log file for users
$logColl = "Spull.log.coll";    # Spullmeta log file for collections
$logData = "Spull.log.data";     # Spullmeta log file for dataObjects
$logResc = "Spull.log.resc";     # Spullmeta log file for resources
$logMetaData = "Spull.log.meta.data"; # Spullmeta log file for user-defined
                                      # metadata for dataObjects
$logMetaColl = "Spull.log.meta.coll"; # Spullmeta log file for user-defined
                                      # metadata for collections
$sqlFile = "m2icat.cmds.sql"; # the output/input file: SQL (for psql)
$psqlLog = "psql.log";        # the log file when running psql
$iadminFile = "m2icat.cmds.iadmin"; # the output/input file for iadmin commands
$imetaFile = "m2icat.cmds.imeta";  # the output/input file for imeta commands
$imetaLog  = "imeta.log";     # the log file when running imeta
$iadminLog  = "iadmin.log";   # the log file when running iadmin
$showOne="0";            # A debug option, if "1";

#------------
@cv_srb_resources =();   # SRB resource(s) being converted (created on the fly)
@cv_irods_resources=();  # corresponding name of SRB resource(s) in iRODS.
@datatypeList=();        # filled and used dynamically
$nowTime="";
$metadataLastColl="";
$metadataLastDataname="";

if (!-e $logUser) {
    runCmd(0, "$Spullmeta -F GET_CHANGED_USER_INFO $SRB_BEGIN_DATE > $logUser");
}
else {
    printf("$logUser exists, so not running Spullmeta to get it.\n");
}

if (!-e $logResc) {
    runCmd(0, "$Spullmeta -F GET_CHANGED_PHYSICAL_RESOURCE_CORE_INFO $SRB_BEGIN_DATE > $logResc");
}
else {
    printf("$logResc exists, so not running Spullmeta to get it.\n");
}

if (!-e $logColl) {
    runCmd(0, "$Spullmeta -F GET_CHANGED_COLL_CORE_INFO $SRB_BEGIN_DATE > $logColl");
}
else {
    printf("$logColl exists, so not running Spullmeta to get it.\n");
}

if (!-e $logData) {
    runCmd(0, "$Spullmeta -F GET_CHANGED_DATA_CORE_INFO $SRB_BEGIN_DATE > $logData");
}
else {
    printf("$logData exists, so not running Spullmeta to get it.\n");
}

if (!-e $logMetaData) {
    runCmd(0, "$Spullmeta -F GET_CHANGED_DATA_UDEFMETA_INFO $SRB_BEGIN_DATE > $logMetaData");
}
else {
    printf("$logMetaData exists, so not running Spullmeta to get it.\n");
}

if (!-e $logMetaColl) {
    runCmd(1, "$Spullmeta -F GET_CHANGED_COLL_UDEFMETA_INFO $SRB_BEGIN_DATE > $logMetaColl");
}
else {
    printf("$logMetaColl exists, so not running Spullmeta to get it.\n");
}


my $doMainStep="yes";
if ( -e $sqlFile ) {
    printf("Enter y or yes if you want this script to regenerate the $sqlFile,\n");
    printf("the $iadminFile, and the $imetaFile:");
    my $answer = <STDIN>;
    chomp( $answer );	# remove trailing return
    if ($answer eq "yes" || $answer eq "y") {
    }
    else {
	$doMainStep="no";
    }
}

if ($doMainStep eq "yes") {

    if ( open(  SQL_FILE, ">$sqlFile" ) == 0 ) {
	die("open failed on output file " . $sqlFile);
    }
    if ( open(  IADMIN_FILE, ">$iadminFile" ) == 0 ) {
	die("open failed on output file " . $iadminFile);
    }
    if ( open(  IMETA_FILE, ">$imetaFile" ) == 0 ) {
	die("open failed on output file " . $iadminFile);
    }

    processLogFile($logUser);

    foreach $user (@cv_special_users) {
	print( IADMIN_FILE "mkuser $user rodsuser\n");
	$newPassword = randomPassword();
	print( IADMIN_FILE "moduser $user password $newPassword\n");
    }

    processLogFile($logResc);

    processLogFile($logColl);

    processLogFile($logData);

    processLogFile($logMetaData);

    processLogFile($logMetaColl);

    foreach $dataType (@datatypeList) {
	print( IADMIN_FILE "at data_type \'$dataType\'\n");
    }
    print( IADMIN_FILE "quit\n");

    print( IMETA_FILE "quit\n");

    close( IADMIN_FILE );
    close( SQL_FILE );
    close( IMETA_FILE );
}

printf("Enter y or yes if you want to run iadmin now:");
my $answer = <STDIN>;
chomp( $answer );	# remove trailing return
if ($answer eq "yes" || $answer eq "y") {
    runCmd (1, "iadmin -V < $iadminFile >& $iadminLog" );
}

printf("Enter y or yes if you want to run psql now:");
my $answer = <STDIN>;
chomp( $answer );	# remove trailing return
if ($answer eq "yes" || $answer eq "y") {
    runCmd (0, "$psql ICAT < $sqlFile >& $psqlLog");
}

printf("Enter y or yes if you run imeta now:");
my $answer = <STDIN>;
chomp( $answer );	# remove trailing return
if ($answer eq "yes" || $answer eq "y") {
    runCmd (0, "$imeta < $imetaFile >& $imetaLog");
}

# run a command
# if option is 0 (normal), check the exit code and fail if non-0
# if 1, don't care
# if 2, should get a non-zero result, exit if not
sub runCmd {
    my($option, $cmd) = @_;
    print "running: $cmd \n";
    $cmdStdout=`$cmd`;
    $cmdStat=$?;
    if ($option == 0) {
	if ($cmdStat!=0) {
	    print "The following command failed:";
	    print "$cmd \n";
	    print "Exit code= $cmdStat \n";
	    die("command failed");
	}
    }
    if ($option == 2) {
	if ($cmdStat==0) {
	    print "The following command should have failed:";
	    print "$cmd \n";
	    print "Exit code= $cmdStat \n";
	    die("command failed to fail");
	}
    }
}

# Using an iadmin option, convert srb to irods time values;
# also keep a cache list to avoid running the subprocess so often.
sub convertTime($)
{
    my ($inTime) = @_;
    $lastOutTime;
    $lastOutTimeConverted;
    $maxLastOutTime=10;

    if ($bypass_time_for_speed ) {
	getNow();
	return($nowTime);
    }

#   printf("inTime =%s\n",$inTime);
    $outTime = substr($inTime,0,10) . "." . substr($inTime, 11, 2) .
	":" . substr($inTime, 14, 2) . 	":" . substr($inTime, 17, 2);
#   printf("outTime=%s\n",$outTime);
    for ($i=0; $i<$maxLastOutTime; $i++) {
	if ($lastOutTime[$i] eq $outTime) {
	    return($lastOutTimeConverted[$i]);
	}
    }

    runCmd(0, "iadmin ctime str " . $outTime);
    $i = index($cmdStdout, "time: ");
    $outTimeConvert = substr($cmdStdout, $i+6);
    chomp($outTimeConvert);

    $lastOutTime[$ixLastOutTime] = $outTime;
    $lastOutTimeConverted[$ixLastOutTime] = $outTimeConvert;
    $ixLastOutTime++;
    if ($ixLastOutTime >= $maxLastOutTime) {
	$ixLastOutTime=0;
    }

    return($outTimeConvert);
}

# Using an iadmin option, get the current time in irods format
sub getNow() {
    if ($nowTime eq "") {
	runCmd(0, "iadmin ctime now");
	$i = index($cmdStdout, "time: ");
	$nowTime = substr($cmdStdout, $i+6);
	chomp($nowTime);
    }
}

# Using the defined arrays at the top, possibly convert a user name
# Also, if not special, do the define conversion
sub convertUser($$)
{
    my ($inUser, $inDomain) = @_;
    $k=0;
    foreach $user (@cv_srb_usernames) {
	if ($user eq $inUser) {
#	    printf("user=$user inUser=$inUser\n");
	    return ($cv_irods_usernames[$k]);
	}
	$k++;
    }
    if ($useDomainWithUsername) {
#	$newUserName=$v_user_name . "#" . $v_user_domain;
	$newUserName=$inUser. "#" . $inDomain;
    }
    else {
#	$newUserName=$v_user_name;
	$newUserName=$inUser;
    }
    return($newUserName);
}

# Using the defined arrays at the top, possibly convert collection name
sub convertCollection($)
{
    my ($inColl) = @_;
    my $outColl = $inColl;

    $outColl =~ s\/$cv_srbZone/\/$cv_irodsZone/\g; 
    $k=0;
    foreach $user (@cv_srb_usernames) {
	$tmp = "/" . $user . "." . $cv_srb_userdomains[$k];
	$tmp2 = "/" . $cv_irods_usernames[$k];
	$outColl =~ s\$tmp\$tmp2\g; 
	$k++;
    }
#   printf("inColl=$inColl outColl=$outColl\n");
    return($outColl);
}

# convertCollections version, for dataObjects
sub convertCollectionForData($$$)
{
    my ($inColl, $inUser, $inDomain) = @_;
    my $outColl = $inColl;
    my $tmp;
    my $tmp2;

    $outColl =~ s\/$cv_srbZone/\/$cv_irodsZone/\g; 
    $k=0;
    foreach $user (@cv_srb_usernames) {
	$tmp = "/" . $user . "." . $cv_srb_userdomains[$k];
	$tmp2 = "/" . $cv_irods_usernames[$k];
	$outColl =~ s\$tmp\$tmp2\g; 
	$k++;
    }
    $tmp = "/" . $inUser . "." . $inDomain;
    my $newUser = convertUser($inUser, $inDomain);
    $tmp2 = "/" . $newUser;
#   printf("tmp=$tmp tmp2=$tmp2\n");
    $outColl =~ s\$tmp\$tmp2\g; 

#   printf("inColl=$inColl outColl=$outColl\n");
    return($outColl);
}

# Add item to the datatype array unless it's already there.
sub AddToDatatypeList($) {
    my($item) = @_;
    if ($item eq "generic") {return;}
    foreach $listItem (@datatypeList) {
        if ($listItem eq $item) {
            return;
        }
    }
    push(@datatypeList, $item);
}


sub processLogFile($) {
# First line in the log file is the run parameters, 
# 2nd is the column-names, the rest are data items.
    my($logFile) = @_;
    my @udsmd;
    if ( open(  LOG_FILE, "<$logFile" ) == 0 ) {
	die("open failed on input file " . $logFile);
    }
    $i = 0;
    $mode = "";
    foreach $line ( <LOG_FILE> ) {
	$i++;
	if ($i==1) {
	    @cmdArgs = split('\|',$line);
#	    print ("cmdArgs[0]:" . $cmdArgs[0] . " " . "\n");
	    if ($cmdArgs[0] eq "GET_CHANGED_USER_INFO") {
		$mode="USER";
	    }
	    if ($cmdArgs[0] eq "GET_CHANGED_COLL_CORE_INFO") {
		$mode="COLL";
	    }
	    if ($cmdArgs[0] eq "GET_CHANGED_DATA_CORE_INFO") {
		$mode="DATA";
	    }
	    if ($cmdArgs[0] eq "GET_CHANGED_PHYSICAL_RESOURCE_CORE_INFO") {
		$mode="RESC";
	    }
	    if ($cmdArgs[0] eq "GET_CHANGED_DATA_UDEFMETA_INFO") {
		$mode="METADATA_DATA";
	    }
	    if ($cmdArgs[0] eq "GET_CHANGED_COLL_UDEFMETA_INFO") {
		$mode="METADATA_COLL";
	    }
	}
#	printf("MODE: $mode, i: $i\n");
	if ($i==2) {
	    @names = split('\|',$line);
#	    print ("names[0]:" . $names[0] . " " . "\n");
	    if ($mode eq "") {
		die ("Unrecognized type of Spullmeta log file: $logFile");
	    }
	}
	if ($i>2) { # regular lines
	    @values = split('\|',$line);
	    $doDataInsert=0;
	    if ($mode eq "DATA") {
		$v_resc = $values[3];
		$k=0;
		foreach $resc (@cv_srb_resources) {
		    if ($resc eq $v_resc) {
			$newResource = $cv_irods_resources[$k];
			$doDataInsert=1;
		    }
		    $k++;
		}
	    }
	    if ($doDataInsert) {
		$v_dataName = $values[0];
		$v_dataTypeName = $values[1];
		$v_phyPath = $values[2];
		$v_size = $values[6];
		$v_owner_domain = $values[13];
		$v_owner = convertUser($values[9], $v_owner_domain);
		$v_create_time = convertTime($values[15]);
		$v_access_time = convertTime($values[16]);
#		$v_collection = convertCollectionForData($values[27],
#							 $v_owner,
#							 $v_owner_domain);
		$v_collection = convertCollection($values[27]);
		if (checkDoCollection($values[27])==1) {
		    print( SQL_FILE "begin;\n"); # begin/commit to make these 2 like 1
		    print( SQL_FILE "insert into r_data_main (data_id, coll_id, data_name, data_repl_num, data_version, data_type_name, data_size, resc_name, data_path, data_owner_name, data_owner_zone, data_is_dirty, create_ts, modify_ts) values ((select nextval('R_ObjectID')), (select coll_id from r_coll_main where coll_name ='$v_collection'), '$v_dataName', '0', ' ', '$v_dataTypeName', '$v_size', '$newResource', '$v_phyPath', '$v_owner', '$cv_irodsZone', '1', '$v_create_time', '$v_access_time');\n");

		    getNow();
		    print( SQL_FILE "insert into r_objt_access ( object_id, user_id, access_type_id , create_ts,  modify_ts) values ( (select currval('R_ObjectID')), (select user_id from r_user_main where user_name = '$v_owner'), '1200', '$nowTime', '$nowTime');\n");

		    print( SQL_FILE "commit;\n");

		    AddToDatatypeList($v_dataTypeName);

		    if ($i==3 && $showOne=="1") {
			$j = 0;
			foreach $value (@values) {
			    print ($names[$j] . " " . $value . "\n");
			    $j++;
			}
		    }
		}
	    }
	    if ($mode eq "USER") {
		$v_user_type = $values[0];
		$v_user_addr = $values[1];
		$v_user_name = $values[2];
		$v_user_domain=$values[3];
		my $k=0;
		foreach $userType (@cv_srb_usertypes) {
		    if ($v_user_type eq $userType) {
			$newUserName=convertUser($v_user_name, $v_user_domain);
			print( IADMIN_FILE "mkuser $newUserName $cv_irods_usertypes[$k]\n");
			print( IADMIN_FILE "moduser $newUserName info $v_user_addr\n");
			$newPassword = randomPassword();
			print( IADMIN_FILE "moduser $newUserName password $newPassword\n");
		    }
		    $k++;
		}
	    }
	    if ($mode eq "COLL") {
		if (checkDoCollection($values[0])==1) {
		   $v_coll_name=convertCollection($values[0]);
		   $v_parent_coll_name=convertCollection($values[1]);
		   $v_coll_owner_domain=$values[5];
		   $v_coll_owner=convertUser($values[2],
				      $v_coll_owner_domain);
		   $v_coll_zone=$values[6];
		   $skipIt=0;
		   if ($v_coll_owner eq "srb")    { $skipIt=1; }
		   if ($v_coll_owner eq "npaci")  { $skipIt=1; }
		   if ($v_coll_owner eq "public") { $skipIt=1; }
		   if ($v_coll_owner eq "sdsc")   { $skipIt=1; }
		   if ($v_coll_owner eq "testuser")   { $skipIt=1; }
		   if ($v_coll_owner eq "ticketuser")  { $skipIt=1; }
		   # make sure it's in the converting zone:
		   if ($v_coll_zone ne $cv_srbZone) { $skipIt=1;}
		   if ($skipIt==0) {
		       print(IADMIN_FILE "mkdir $v_coll_name $v_coll_owner\n");
		   }
		}
	    }
	    if ($mode eq "RESC") {
		$v_resc_name=$values[0];
		$v_resc_type=$values[1];
		$v_resc_path=$values[2];
		$v_resc_physical_name=$values[3];
		$v_resc_location=$values[5];
		if ($v_resc_name eq $v_resc_physical_name &&
		    $v_resc_type eq "unix file system") {
		    $k = index($v_resc_path, "/?");
		    $newPath = substr($v_resc_path, 0, $k);
		    push(@cv_srb_resources, $v_resc_name);
		    if ($v_resc_name ne "sdsc-fs") { # skip special built-in
			$newName = "SRB-" . $v_resc_name;
			push(@cv_irods_resources, $newName);
			print( IADMIN_FILE "mkresc '$newName' '$v_resc_type' 'archive' '$v_resc_location' $newPath\n");
		    }
		}
	    }
	    if ($mode eq "METADATA_DATA") {
		$v_dataobj_name=$values[0];
		$v_dataobj_collection=convertCollection($values[1]);
		$TYPE=$values[2];
		for ($i=0;$i<10;$i++) {
		    $udsmd[$i]=$values[$i+3];
		}
		$v_dataobj_udimd0=$values[13];
		$v_dataobj_udimd1=$values[14];
		$didOne=0;
		for ($i=0;$i<10;$i++) {
		    if ($udsmd[$i] ne "") {
			print( IMETA_FILE "add -d $v_dataobj_collection/$v_dataobj_name $TYPE-UDSMD$i '$udsmd[$i]'\n") ;
			$didOne=1;
		    }
		}
		if ($v_dataobj_udimd0 ne "") {
		    print ( IMETA_FILE "add -d $v_dataobj_collection/$v_dataobj_name $TYPE-UDIMD0 '$v_dataobj_udimd0'\n");
		    $didOne=1;
		}
		if ($v_dataobj_udimd1 ne "") {
		    print ( IMETA_FILE "add -d $v_dataobj_collection/$v_dataobj_name $TYPE-UDIMD1 '$v_dataobj_udimd1'\n");
		    $didOne=1;
		}
		if ($didOne) {
		    # give our admin user access for setting metadata
		    addAccess($v_dataobj_collection, $v_dataobj_name);
		}
	    }

	    if ($mode eq "METADATA_COLL") {
		$v_coll_name=convertCollection($values[0]);
		for ($i=0;$i<10;$i++) {
		    $udsmd_coll[$i]=$values[$i+2];
		}
		$v_coll_udimd0=$values[12];
		$v_coll_udimd1=$values[13];
		for ($i=0;$i<10;$i++) {
		    if ($udsmd_coll[$i] ne "") {
			print( IMETA_FILE "add -c $v_coll_name UDSMD_COLL$i '$udsmd_coll[$i]'\n") ;
		    }
		}
		if ($v_coll_udimd0 ne "") {
		    print ( IMETA_FILE "add -c $v_coll_name UDIMD_COLL0 '$v_coll_udimd0'\n");
		}
		if ($v_coll_udimd1 ne "") {
		    print ( IMETA_FILE "add -c $v_coll_name UDIMD_COLL1 '$v_coll_udimd1'\n");
		}
	    }
	}
    }
    close( LOG_FILE );
}

# Geneate a random password string
sub randomPassword() {
    my @chars = split(" ",
      "a b c d e f g h i j k l m n o p q r s t u v w x y z 
       A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 
       0 1 2 3 4 5 6 7 8 9");
    srand;
    my $password="";
    for (my $i=0; $i < $password_length ;$i++) {
	$_rand = int(rand 62);
	$j=$_rand;
#	printf("$i=$i j=$j\n");
	$password .= $chars[$j];
    }
    return $password;
}

# check to see if a collection (based on the name) should be converted
sub checkDoCollection($) {
    my ($inCollName) = @_;
#   printf("incollname = $inCollName \n");
    if (index($inCollName, "/container")==0) {
	return(0); # don't convert those starting with/container
    }
    if (index($inCollName, "/home")==0) {
	return(0); # don't convert these either
    }
    $testColl = "/" . $cv_srbZone . "/container";
    if (index($inCollName, "$testColl")==0) {
	return(0); # don't convert these
    }
    $testColl = "/" . $cv_srbZone . "/trash";
    if (index($inCollName, "$testColl")==0) {
	return(0); # don't convert these
    }
#   $testColl = "/" . $cv_srbZone . "/home/";
#
# Sometimes these will match existing /zone/home/user directories and
# sometimes not, so go ahead and return them as OK (caller might reject
# specific ones).
#
#    if (index($inCollName, "$testColl")==0) {  # if it starts with /zone/home/ 
#	if (rindex($inCollName, "/") < length($testColl)) {
#                                         # and there are no additional subdirs
#	    return(0);                    # skip it
#	}
#   }
    $testColl = "/" . $cv_srbZone . "/";
    if (index($inCollName, "$testColl")==0) {  # if it starts with /zone/
	if (rindex($inCollName, "/") < length($testColl)) {
                                          # and there are no additional subdirs
	    return(0);                    # skip it
	}
    }

    $testColl = "/" . $cv_srbZone . "/";
    if (index($inCollName, "$testColl")!=0) {  # if it doesn't start w /zone/
	    return(0);                    # skip it
    }
    return(1);
}

# Add SQL to give access to this user if the previous item didn't already
sub addAccess($$) {
    my ($inColl, $inDataname) = @_;
    if ($inColl eq $metadataLastColl &&
	$inDataname eq $metadataLastDataname) {
	return;
    }
    print( SQL_FILE "insert into r_objt_access (object_id, user_id, access_type_id)  values ((select data_id from r_data_main where data_name = '$inDataname' and coll_id = (select coll_id from r_coll_main where coll_name = '$inColl')),(select user_id from r_user_main where user_name = '$thisUser'), '1200');\n");
    $metadataLastColl=$inColl;
    $metadataLastDataname=$inDataname;
}
