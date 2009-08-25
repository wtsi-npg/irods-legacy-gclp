/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* rsGlobalExtern.h - header file for global extern declaration for the server
 * modules
 */

#ifndef RS_GLOBAL_EXTERN_H
#define RS_GLOBAL_EXTERN_H

#include "rods.h"
#include "apiHandler.h"
#include "initServer.h"
#include "fileOpr.h"
#include "dataObjOpr.h"
#include "querySpecColl.h"
#include "structFileDriver.h"
#ifdef TAR_STRUCT_FILE
#include "tarSubStructFileDriver.h"
#endif
#include "miscUtil.h"


extern int LogFd;         		/* the log file descriptor */
extern char *CurLogfileName;         	/* the path of the current logfile */
extern apidef_t RsApiTable[];
extern rodsServerHost_t *LocalServerHost;
extern rodsServerHost_t *ServerHostHead;
extern rodsServerHost_t *HostConfigHead;
extern zoneInfo_t *ZoneInfoHead;
extern rescGrpInfo_t *RescGrpInfo;
extern rescGrpInfo_t *CachedRescGrpInfo;
extern int RescGrpInit;
extern fileDesc_t FileDesc[];
extern l1desc_t L1desc[];
extern specCollDesc_t SpecCollDesc[];
extern collHandle_t CollHandle[];

/* global Rule Engine File Initialization String */

extern char reRuleStr[];
extern char reFuncMapStr[];
extern char reVariableMapStr[];

/* Kerberos server name */
extern char KerberosName[];

extern int InitialState;
extern rsComm_t *ThisComm;

#ifdef RODS_CAT
extern int IcatConnState;
#endif

extern specCollCache_t *SpecCollCacheHead;

extern structFileDesc_t StructFileDesc[];
#ifdef TAR_STRUCT_FILE
extern tarSubFileDesc_t TarSubFileDesc[];
#endif

int
initRuleEngine(char *ruleSet, char *dvmSet, char* fnmSet);

extern char localSID[];
extern char remoteSID[MAX_FED_RSIDS][MAX_PASSWORD_LEN];

#endif  /* RS_GLOBAL_EXTERN_H */

