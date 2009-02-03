/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/

#include "rods.h"

#include "rodsLog.h"
#include "rcGlobalExtern.h"
#include "rcMisc.h"
#include <time.h>

#ifndef windows_platform
#include <unistd.h>
#endif

#ifdef windows_platform
#include "irodsntutil.h"
#endif

#define BIG_STRING_LEN MAX_NAME_LEN+300
#include <stdarg.h>

/* The following code is inserted by the errorSetup.pl script 
   when rodsErrorTable.h is updated. */

/* BEGIN generated code */
   int irodsErrors[]={ 
    SYS_SOCK_OPEN_ERR, 
    SYS_SOCK_BIND_ERR, 
    SYS_SOCK_ACCEPT_ERR, 
    SYS_HEADER_READ_LEN_ERR, 
    SYS_HEADER_WRITE_LEN_ERR, 
    SYS_HEADER_TPYE_LEN_ERR, 
    SYS_CAUGHT_SIGNAL, 
    SYS_GETSTARTUP_PACK_ERR, 
    SYS_EXCEED_CONNECT_CNT, 
    SYS_USER_NOT_ALLOWED_TO_CONN, 
    SYS_READ_MSG_BODY_INPUT_ERR, 
    SYS_UNMATCHED_API_NUM, 
    SYS_NO_API_PRIV, 
    SYS_API_INPUT_ERR, 
    SYS_PACK_INSTRUCT_FORMAT_ERR, 
    SYS_MALLOC_ERR, 
    SYS_GET_HOSTNAME_ERR, 
    SYS_OUT_OF_FILE_DESC, 
    SYS_FILE_DESC_OUT_OF_RANGE, 
    SYS_UNRECOGNIZED_REMOTE_FLAG, 
    SYS_INVALID_SERVER_HOST, 
    SYS_SVR_TO_SVR_CONNECT_FAILED, 
    SYS_BAD_FILE_DESCRIPTOR, 
    SYS_INTERNAL_NULL_INPUT_ERR, 
    SYS_CONFIG_FILE_ERR, 
    SYS_INVALID_ZONE_NAME, 
    SYS_COPY_LEN_ERR, 
    SYS_PORT_COOKIE_ERR, 
    SYS_KEY_VAL_TABLE_ERR, 
    SYS_INVALID_RESC_TYPE, 
    SYS_INVALID_FILE_PATH, 
    SYS_INVALID_RESC_INPUT, 
    SYS_INVALID_PORTAL_OPR, 
    SYS_PARA_OPR_NO_SUPPORT, 
    SYS_INVALID_OPR_TYPE, 
    SYS_NO_PATH_PERMISSION, 
    SYS_NO_ICAT_SERVER_ERR, 
    SYS_AGENT_INIT_ERR, 
    SYS_PROXYUSER_NO_PRIV, 
    SYS_NO_DATA_OBJ_PERMISSION, 
    SYS_DELETE_DISALLOWED, 
    SYS_OPEN_REI_FILE_ERR, 
    SYS_NO_RCAT_SERVER_ERR, 
    SYS_UNMATCH_PACK_INSTRUCTI_NAME, 
    SYS_SVR_TO_CLI_MSI_NO_EXIST, 
    SYS_COPY_ALREADY_IN_RESC, 
    SYS_RECONN_OPR_MISMATCH, 
    SYS_INPUT_PERM_OUT_OF_RANGE, 
    SYS_FORK_ERROR, 
    SYS_PIPE_ERROR, 
    SYS_EXEC_CMD_STATUS_SZ_ERROR, 
    SYS_PATH_IS_NOT_A_FILE, 
    SYS_UNMATCHED_SPEC_COLL_TYPE, 
    SYS_TOO_MANY_QUERY_RESULT, 
    SYS_SPEC_COLL_NOT_IN_CACHE, 
    SYS_SPEC_COLL_OBJ_NOT_EXIST, 
    SYS_REG_OBJ_IN_SPEC_COLL, 
    SYS_DEST_SPEC_COLL_SUB_EXIST, 
    SYS_SRC_DEST_SPEC_COLL_CONFLICT, 
    SYS_UNKNOWN_SPEC_COLL_CLASS, 
    SYS_DUPLICATE_XMSG_TICKET, 
    SYS_UNMATCHED_XMSG_TICKET, 
    SYS_NO_XMSG_FOR_MSG_NUMBER, 
    SYS_COLLINFO_2_FORMAT_ERR, 
    SYS_CACHE_STRUCT_FILE_RESC_ERR, 
    SYS_NOT_SUPPORTED, 
    SYS_TAR_STRUCT_FILE_EXTRACT_ERR, 
    SYS_STRUCT_FILE_DESC_ERR, 
    SYS_TAR_OPEN_ERR, 
    SYS_TAR_EXTRACT_ALL_ERR, 
    SYS_TAR_CLOSE_ERR, 
    SYS_STRUCT_FILE_PATH_ERR, 
    SYS_MOUNT_MOUNTED_COLL_ERR, 
    SYS_COLL_NOT_MOUNTED_ERR, 
    SYS_STRUCT_FILE_BUSY_ERR, 
    SYS_STRUCT_FILE_INMOUNTED_COLL, 
    SYS_COPY_NOT_EXIST_IN_RESC, 
    SYS_RESC_DOES_NOT_EXIST, 
    SYS_COLLECTION_NOT_EMPTY, 
    SYS_OBJ_TYPE_NOT_STRUCT_FILE, 
    SYS_WRONG_RESC_POLICY_FOR_BUN_OPR, 
    SYS_DIR_IN_VAULT_NOT_EMPTY, 
    SYS_OPR_FLAG_NOT_SUPPORT, 
    SYS_TAR_APPEND_ERR, 
    SYS_INVALID_PROTOCOL_TYPE, 
    SYS_UDP_CONNECT_ERR, 
    SYS_UDP_TRANSFER_ERR, 
    SYS_UDP_NO_SUPPORT_ERR, 
    SYS_READ_MSG_BODY_LEN_ERR, 
    CROSS_ZONE_SOCK_CONNECT_ERR, 
    USER_AUTH_SCHEME_ERR, 
    USER_AUTH_STRING_EMPTY, 
    USER_RODS_HOST_EMPTY, 
    USER_RODS_HOSTNAME_ERR, 
    USER_SOCK_OPEN_ERR, 
    USER_SOCK_CONNECT_ERR, 
    USER_STRLEN_TOOLONG, 
    USER_API_INPUT_ERR, 
    USER_PACKSTRUCT_INPUT_ERR, 
    USER_NO_SUPPORT_ERR, 
    USER_FILE_DOES_NOT_EXIST, 
    USER_FILE_TOO_LARGE, 
    OVERWITE_WITHOUT_FORCE_FLAG, 
    UNMATCHED_KEY_OR_INDEX, 
    USER_CHKSUM_MISMATCH, 
    USER_BAD_KEYWORD_ERR, 
    USER__NULL_INPUT_ERR, 
    USER_INPUT_PATH_ERR, 
    USER_INPUT_OPTION_ERR, 
    USER_INVALID_USERNAME_FORMAT, 
    USER_DIRECT_RESC_INPUT_ERR, 
    USER_NO_RESC_INPUT_ERR, 
    USER_PARAM_LABEL_ERR, 
    USER_PARAM_TYPE_ERR, 
    BASE64_BUFFER_OVERFLOW, 
    BASE64_INVALID_PACKET, 
    USER_MSG_TYPE_NO_SUPPORT, 
    USER_RSYNC_NO_MODE_INPUT_ERR, 
    USER_OPTION_INPUT_ERR, 
    SAME_SRC_DEST_PATHS_ERR, 
    USER_RESTART_FILE_INPUT_ERR, 
    RESTART_OPR_FAILED, 
    BAD_EXEC_CMD_PATH, 
    EXEC_CMD_OUTPUT_TOO_LARGE, 
    EXEC_CMD_ERROR, 
    BAD_INPUT_DESC_INDEX, 
    USER_PATH_EXCEEDS_MAX, 
    USER_SOCK_CONNECT_TIMEDOUT, 
    USER_API_VERSION_MISMATCH, 
    USER_INPUT_FORMAT_ERR, 
    FILE_INDEX_LOOKUP_ERR, 
    UNIX_FILE_OPEN_ERR, 
    UNIX_FILE_CREATE_ERR, 
    UNIX_FILE_READ_ERR, 
    UNIX_FILE_WRITE_ERR, 
    UNIX_FILE_CLOSE_ERR, 
    UNIX_FILE_UNLINK_ERR, 
    UNIX_FILE_STAT_ERR, 
    UNIX_FILE_FSTAT_ERR, 
    UNIX_FILE_LSEEK_ERR, 
    UNIX_FILE_FSYNC_ERR, 
    UNIX_FILE_MKDIR_ERR, 
    UNIX_FILE_RMDIR_ERR, 
    UNIX_FILE_OPENDIR_ERR, 
    UNIX_FILE_CLOSEDIR_ERR, 
    UNIX_FILE_READDIR_ERR, 
    UNIX_FILE_STAGE_ERR, 
    UNIX_FILE_GET_FS_FREESPACE_ERR, 
    UNIX_FILE_CHMOD_ERR, 
    UNIX_FILE_RENAME_ERR, 
    UNIX_FILE_TRUNCATE_ERR, 
    CATALOG_NOT_CONNECTED, 
    CAT_ENV_ERR, 
    CAT_CONNECT_ERR, 
    CAT_DISCONNECT_ERR, 
    CAT_CLOSE_ENV_ERR, 
    CAT_SQL_ERR, 
    CAT_GET_ROW_ERR, 
    CAT_NO_ROWS_FOUND, 
    CATALOG_ALREADY_HAS_ITEM_BY_THAT_NAME, 
    CAT_INVALID_RESOURCE_TYPE, 
    CAT_INVALID_RESOURCE_CLASS, 
    CAT_INVALID_RESOURCE_NET_ADDR, 
    CAT_INVALID_RESOURCE_VAULT_PATH, 
    CAT_UNKNOWN_COLLECTION, 
    CAT_INVALID_DATA_TYPE, 
    CAT_INVALID_ARGUMENT, 
    CAT_UNKNOWN_FILE, 
    CAT_NO_ACCESS_PERMISSION, 
    CAT_SUCCESS_BUT_WITH_NO_INFO, 
    CAT_INVALID_USER_TYPE, 
    CAT_COLLECTION_NOT_EMPTY, 
    CAT_TOO_MANY_TABLES, 
    CAT_UNKNOWN_TABLE, 
    CAT_NOT_OPEN, 
    CAT_FAILED_TO_LINK_TABLES, 
    CAT_INVALID_AUTHENTICATION, 
    CAT_INVALID_USER, 
    CAT_INVALID_ZONE, 
    CAT_INVALID_GROUP, 
    CAT_INSUFFICIENT_PRIVILEGE_LEVEL, 
    CAT_INVALID_RESOURCE, 
    CAT_INVALID_CLIENT_USER, 
    CAT_NAME_EXISTS_AS_COLLECTION, 
    CAT_NAME_EXISTS_AS_DATAOBJ, 
    CAT_RESOURCE_NOT_EMPTY, 
    CAT_NOT_A_DATAOBJ_AND_NOT_A_COLLECTION, 
    CAT_RECURSIVE_MOVE, 
    CAT_LAST_REPLICA, 
    CAT_OCI_ERROR, 
    CAT_PASSWORD_EXPIRED, 
    RDA_NOT_COMPILED_IN, 
    RDA_NOT_CONNECTED, 
    RDA_ENV_ERR, 
    RDA_CONNECT_ERR, 
    RDA_DISCONNECT_ERR, 
    RDA_CLOSE_ENV_ERR, 
    RDA_SQL_ERR, 
    RDA_CONFIG_FILE_ERR, 
    RDA_ACCESS_PROHIBITED, 
    RDA_NAME_NOT_FOUND, 
    FILE_OPEN_ERR, 
    FILE_READ_ERR, 
    FILE_WRITE_ERR, 
    PASSWORD_EXCEEDS_MAX_SIZE, 
    ENVIRONMENT_VAR_HOME_NOT_DEFINED, 
    UNABLE_TO_STAT_FILE, 
    AUTH_FILE_NOT_ENCRYPTED, 
    AUTH_FILE_DOES_NOT_EXIST, 
    UNLINK_FAILED, 
    NO_PASSWORD_ENTERED, 
    REMOTE_SERVER_AUTHENTICATION_FAILURE, 
    REMOTE_SERVER_AUTH_NOT_PROVIDED, 
    REMOTE_SERVER_AUTH_EMPTY, 
    REMOTE_SERVER_SID_NOT_DEFINED, 
    GSI_NOT_COMPILED_IN, 
    GSI_NOT_BUILT_INTO_CLIENT, 
    GSI_NOT_BUILT_INTO_SERVER, 
    GSI_ERROR_IMPORT_NAME, 
    GSI_ERROR_INIT_SECURITY_CONTEXT, 
    GSI_ERROR_SENDING_TOKEN_LENGTH, 
    GSI_ERROR_READING_TOKEN_LENGTH, 
    GSI_ERROR_TOKEN_TOO_LARGE, 
    GSI_ERROR_BAD_TOKEN_RCVED, 
    GSI_SOCKET_READ_ERROR, 
    GSI_PARTIAL_TOKEN_READ, 
    GSI_SOCKET_WRITE_ERROR, 
    GSI_ERROR_FROM_GSI_LIBRARY, 
    GSI_ERROR_IMPORTING_NAME, 
    GSI_ERROR_ACQUIRING_CREDS, 
    GSI_ACCEPT_SEC_CONTEXT_ERROR, 
    GSI_ERROR_DISPLAYING_NAME, 
    GSI_ERROR_RELEASING_NAME, 
    GSI_DN_DOES_NOT_MATCH_USER, 
    GSI_QUERY_INTERNAL_ERROR, 
    OBJPATH_EMPTY_IN_STRUCT_ERR, 
    RESCNAME_EMPTY_IN_STRUCT_ERR, 
    DATATYPE_EMPTY_IN_STRUCT_ERR, 
    DATASIZE_EMPTY_IN_STRUCT_ERR, 
    CHKSUM_EMPTY_IN_STRUCT_ERR, 
    VERSION_EMPTY_IN_STRUCT_ERR, 
    FILEPATH_EMPTY_IN_STRUCT_ERR, 
    REPLNUM_EMPTY_IN_STRUCT_ERR, 
    REPLSTATUS_EMPTY_IN_STRUCT_ERR, 
    DATAOWNER_EMPTY_IN_STRUCT_ERR, 
    DATAOWNERZONE_EMPTY_IN_STRUCT_ERR, 
    DATAEXPIRY_EMPTY_IN_STRUCT_ERR, 
    DATACOMMENTS_EMPTY_IN_STRUCT_ERR, 
    DATACREATE_EMPTY_IN_STRUCT_ERR, 
    DATAMODIFY_EMPTY_IN_STRUCT_ERR, 
    DATAACCESS_EMPTY_IN_STRUCT_ERR, 
    DATAACCESSINX_EMPTY_IN_STRUCT_ERR, 
    NO_RULE_FOUND_ERR, 
    NO_MORE_RULES_ERR, 
    UNMATCHED_ACTION_ERR, 
    RULES_FILE_READ_ERROR, 
    ACTION_ARG_COUNT_MISMATCH, 
    MAX_NUM_OF_ARGS_IN_ACTION_EXCEEDED, 
    UNKNOWN_PARAM_IN_RULE_ERR, 
    DESTRESCNAME_EMPTY_IN_STRUCT_ERR, 
    BACKUPRESCNAME_EMPTY_IN_STRUCT_ERR, 
    DATAID_EMPTY_IN_STRUCT_ERR, 
    COLLID_EMPTY_IN_STRUCT_ERR, 
    RESCGROUPNAME_EMPTY_IN_STRUCT_ERR, 
    STATUSSTRING_EMPTY_IN_STRUCT_ERR, 
    DATAMAPID_EMPTY_IN_STRUCT_ERR, 
    USERNAMECLIENT_EMPTY_IN_STRUCT_ERR, 
    RODSZONECLIENT_EMPTY_IN_STRUCT_ERR, 
    USERTYPECLIENT_EMPTY_IN_STRUCT_ERR, 
    HOSTCLIENT_EMPTY_IN_STRUCT_ERR, 
    AUTHSTRCLIENT_EMPTY_IN_STRUCT_ERR, 
    USERAUTHSCHEMECLIENT_EMPTY_IN_STRUCT_ERR, 
    USERINFOCLIENT_EMPTY_IN_STRUCT_ERR, 
    USERCOMMENTCLIENT_EMPTY_IN_STRUCT_ERR, 
    USERCREATECLIENT_EMPTY_IN_STRUCT_ERR, 
    USERMODIFYCLIENT_EMPTY_IN_STRUCT_ERR, 
    USERNAMEPROXY_EMPTY_IN_STRUCT_ERR, 
    RODSZONEPROXY_EMPTY_IN_STRUCT_ERR, 
    USERTYPEPROXY_EMPTY_IN_STRUCT_ERR, 
    HOSTPROXY_EMPTY_IN_STRUCT_ERR, 
    AUTHSTRPROXY_EMPTY_IN_STRUCT_ERR, 
    USERAUTHSCHEMEPROXY_EMPTY_IN_STRUCT_ERR, 
    USERINFOPROXY_EMPTY_IN_STRUCT_ERR, 
    USERCOMMENTPROXY_EMPTY_IN_STRUCT_ERR, 
    USERCREATEPROXY_EMPTY_IN_STRUCT_ERR, 
    USERMODIFYPROXY_EMPTY_IN_STRUCT_ERR, 
    COLLNAME_EMPTY_IN_STRUCT_ERR, 
    COLLPARENTNAME_EMPTY_IN_STRUCT_ERR, 
    COLLOWNERNAME_EMPTY_IN_STRUCT_ERR, 
    COLLOWNERZONE_EMPTY_IN_STRUCT_ERR, 
    COLLEXPIRY_EMPTY_IN_STRUCT_ERR, 
    COLLCOMMENTS_EMPTY_IN_STRUCT_ERR, 
    COLLCREATE_EMPTY_IN_STRUCT_ERR, 
    COLLMODIFY_EMPTY_IN_STRUCT_ERR, 
    COLLACCESS_EMPTY_IN_STRUCT_ERR, 
    COLLACCESSINX_EMPTY_IN_STRUCT_ERR, 
    COLLMAPID_EMPTY_IN_STRUCT_ERR, 
    COLLINHERITANCE_EMPTY_IN_STRUCT_ERR, 
    RESCZONE_EMPTY_IN_STRUCT_ERR, 
    RESCLOC_EMPTY_IN_STRUCT_ERR, 
    RESCTYPE_EMPTY_IN_STRUCT_ERR, 
    RESCTYPEINX_EMPTY_IN_STRUCT_ERR, 
    RESCCLASS_EMPTY_IN_STRUCT_ERR, 
    RESCCLASSINX_EMPTY_IN_STRUCT_ERR, 
    RESCVAULTPATH_EMPTY_IN_STRUCT_ERR, 
    NUMOPEN_ORTS_EMPTY_IN_STRUCT_ERR, 
    PARAOPR_EMPTY_IN_STRUCT_ERR, 
    RESCID_EMPTY_IN_STRUCT_ERR, 
    GATEWAYADDR_EMPTY_IN_STRUCT_ERR, 
    RESCMAX_BJSIZE_EMPTY_IN_STRUCT_ERR, 
    FREESPACE_EMPTY_IN_STRUCT_ERR, 
    FREESPACETIME_EMPTY_IN_STRUCT_ERR, 
    FREESPACETIMESTAMP_EMPTY_IN_STRUCT_ERR, 
    RESCINFO_EMPTY_IN_STRUCT_ERR, 
    RESCCOMMENTS_EMPTY_IN_STRUCT_ERR, 
    RESCCREATE_EMPTY_IN_STRUCT_ERR, 
    RESCMODIFY_EMPTY_IN_STRUCT_ERR, 
    INPUT_ARG_NOT_WELL_FORMED_ERR, 
    INPUT_ARG_OUT_OF_ARGC_RANGE_ERR, 
    INSUFFICIENT_INPUT_ARG_ERR, 
    INPUT_ARG_DOES_NOT_MATCH_ERR, 
    RETRY_WITHOUT_RECOVERY_ERR, 
    CUT_ACTION_PROCESSED_ERR, 
    ACTION_FAILED_ERR, 
    FAIL_ACTION_ENCOUNTERED_ERR, 
    VARIABLE_NAME_TOO_LONG_ERR, 
    UNKNOWN_VARIABLE_MAP_ERR, 
    UNDEFINED_VARIABLE_MAP_ERR, 
    NULL_VALUE_ERR, 
    DVARMAP_FILE_READ_ERROR, 
    NO_RULE_OR_MSI_FUNCTION_FOUND_ERR, 
    FILE_CREATE_ERROR, 
    FMAP_FILE_READ_ERROR, 
    DATE_FORMAT_ERR, 
    RULE_FAILED_ERR, 
    NO_MICROSERVICE_FOUND_ERR, 
    INVALID_REGEXP, 
    INVALID_OBJECT_NAME, 
    INVALID_OBJECT_TYPE, 
    NO_VALUES_FOUND, 
    NO_COLUMN_NAME_FOUND, 
    BREAK_ACTION_ENCOUNTERED_ERR, 
    PHP_EXEC_SCRIPT_ERR, 
    PHP_REQUEST_STARTUP_ERR, 
    PHP_OPEN_SCRIPT_FILE_ERR, 
    SYS_NULL_INPUT, 
    SYS_HANDLER_DONE_WITH_ERROR, 
    SYS_HANDLER_DONE_NO_ERROR, 
    SYS_NO_HANDLER_REPLY_MSG, 
};
   char *irodsErrorNames[]={ 
    "SYS_SOCK_OPEN_ERR", 
    "SYS_SOCK_BIND_ERR", 
    "SYS_SOCK_ACCEPT_ERR", 
    "SYS_HEADER_READ_LEN_ERR", 
    "SYS_HEADER_WRITE_LEN_ERR", 
    "SYS_HEADER_TPYE_LEN_ERR", 
    "SYS_CAUGHT_SIGNAL", 
    "SYS_GETSTARTUP_PACK_ERR", 
    "SYS_EXCEED_CONNECT_CNT", 
    "SYS_USER_NOT_ALLOWED_TO_CONN", 
    "SYS_READ_MSG_BODY_INPUT_ERR", 
    "SYS_UNMATCHED_API_NUM", 
    "SYS_NO_API_PRIV", 
    "SYS_API_INPUT_ERR", 
    "SYS_PACK_INSTRUCT_FORMAT_ERR", 
    "SYS_MALLOC_ERR", 
    "SYS_GET_HOSTNAME_ERR", 
    "SYS_OUT_OF_FILE_DESC", 
    "SYS_FILE_DESC_OUT_OF_RANGE", 
    "SYS_UNRECOGNIZED_REMOTE_FLAG", 
    "SYS_INVALID_SERVER_HOST", 
    "SYS_SVR_TO_SVR_CONNECT_FAILED", 
    "SYS_BAD_FILE_DESCRIPTOR", 
    "SYS_INTERNAL_NULL_INPUT_ERR", 
    "SYS_CONFIG_FILE_ERR", 
    "SYS_INVALID_ZONE_NAME", 
    "SYS_COPY_LEN_ERR", 
    "SYS_PORT_COOKIE_ERR", 
    "SYS_KEY_VAL_TABLE_ERR", 
    "SYS_INVALID_RESC_TYPE", 
    "SYS_INVALID_FILE_PATH", 
    "SYS_INVALID_RESC_INPUT", 
    "SYS_INVALID_PORTAL_OPR", 
    "SYS_PARA_OPR_NO_SUPPORT", 
    "SYS_INVALID_OPR_TYPE", 
    "SYS_NO_PATH_PERMISSION", 
    "SYS_NO_ICAT_SERVER_ERR", 
    "SYS_AGENT_INIT_ERR", 
    "SYS_PROXYUSER_NO_PRIV", 
    "SYS_NO_DATA_OBJ_PERMISSION", 
    "SYS_DELETE_DISALLOWED", 
    "SYS_OPEN_REI_FILE_ERR", 
    "SYS_NO_RCAT_SERVER_ERR", 
    "SYS_UNMATCH_PACK_INSTRUCTI_NAME", 
    "SYS_SVR_TO_CLI_MSI_NO_EXIST", 
    "SYS_COPY_ALREADY_IN_RESC", 
    "SYS_RECONN_OPR_MISMATCH", 
    "SYS_INPUT_PERM_OUT_OF_RANGE", 
    "SYS_FORK_ERROR", 
    "SYS_PIPE_ERROR", 
    "SYS_EXEC_CMD_STATUS_SZ_ERROR", 
    "SYS_PATH_IS_NOT_A_FILE", 
    "SYS_UNMATCHED_SPEC_COLL_TYPE", 
    "SYS_TOO_MANY_QUERY_RESULT", 
    "SYS_SPEC_COLL_NOT_IN_CACHE", 
    "SYS_SPEC_COLL_OBJ_NOT_EXIST", 
    "SYS_REG_OBJ_IN_SPEC_COLL", 
    "SYS_DEST_SPEC_COLL_SUB_EXIST", 
    "SYS_SRC_DEST_SPEC_COLL_CONFLICT", 
    "SYS_UNKNOWN_SPEC_COLL_CLASS", 
    "SYS_DUPLICATE_XMSG_TICKET", 
    "SYS_UNMATCHED_XMSG_TICKET", 
    "SYS_NO_XMSG_FOR_MSG_NUMBER", 
    "SYS_COLLINFO_2_FORMAT_ERR", 
    "SYS_CACHE_STRUCT_FILE_RESC_ERR", 
    "SYS_NOT_SUPPORTED", 
    "SYS_TAR_STRUCT_FILE_EXTRACT_ERR", 
    "SYS_STRUCT_FILE_DESC_ERR", 
    "SYS_TAR_OPEN_ERR", 
    "SYS_TAR_EXTRACT_ALL_ERR", 
    "SYS_TAR_CLOSE_ERR", 
    "SYS_STRUCT_FILE_PATH_ERR", 
    "SYS_MOUNT_MOUNTED_COLL_ERR", 
    "SYS_COLL_NOT_MOUNTED_ERR", 
    "SYS_STRUCT_FILE_BUSY_ERR", 
    "SYS_STRUCT_FILE_INMOUNTED_COLL", 
    "SYS_COPY_NOT_EXIST_IN_RESC", 
    "SYS_RESC_DOES_NOT_EXIST", 
    "SYS_COLLECTION_NOT_EMPTY", 
    "SYS_OBJ_TYPE_NOT_STRUCT_FILE", 
    "SYS_WRONG_RESC_POLICY_FOR_BUN_OPR", 
    "SYS_DIR_IN_VAULT_NOT_EMPTY", 
    "SYS_OPR_FLAG_NOT_SUPPORT", 
    "SYS_TAR_APPEND_ERR", 
    "SYS_INVALID_PROTOCOL_TYPE", 
    "SYS_UDP_CONNECT_ERR", 
    "SYS_UDP_TRANSFER_ERR", 
    "SYS_UDP_NO_SUPPORT_ERR", 
    "SYS_READ_MSG_BODY_LEN_ERR", 
    "CROSS_ZONE_SOCK_CONNECT_ERR", 
    "USER_AUTH_SCHEME_ERR", 
    "USER_AUTH_STRING_EMPTY", 
    "USER_RODS_HOST_EMPTY", 
    "USER_RODS_HOSTNAME_ERR", 
    "USER_SOCK_OPEN_ERR", 
    "USER_SOCK_CONNECT_ERR", 
    "USER_STRLEN_TOOLONG", 
    "USER_API_INPUT_ERR", 
    "USER_PACKSTRUCT_INPUT_ERR", 
    "USER_NO_SUPPORT_ERR", 
    "USER_FILE_DOES_NOT_EXIST", 
    "USER_FILE_TOO_LARGE", 
    "OVERWITE_WITHOUT_FORCE_FLAG", 
    "UNMATCHED_KEY_OR_INDEX", 
    "USER_CHKSUM_MISMATCH", 
    "USER_BAD_KEYWORD_ERR", 
    "USER__NULL_INPUT_ERR", 
    "USER_INPUT_PATH_ERR", 
    "USER_INPUT_OPTION_ERR", 
    "USER_INVALID_USERNAME_FORMAT", 
    "USER_DIRECT_RESC_INPUT_ERR", 
    "USER_NO_RESC_INPUT_ERR", 
    "USER_PARAM_LABEL_ERR", 
    "USER_PARAM_TYPE_ERR", 
    "BASE64_BUFFER_OVERFLOW", 
    "BASE64_INVALID_PACKET", 
    "USER_MSG_TYPE_NO_SUPPORT", 
    "USER_RSYNC_NO_MODE_INPUT_ERR", 
    "USER_OPTION_INPUT_ERR", 
    "SAME_SRC_DEST_PATHS_ERR", 
    "USER_RESTART_FILE_INPUT_ERR", 
    "RESTART_OPR_FAILED", 
    "BAD_EXEC_CMD_PATH", 
    "EXEC_CMD_OUTPUT_TOO_LARGE", 
    "EXEC_CMD_ERROR", 
    "BAD_INPUT_DESC_INDEX", 
    "USER_PATH_EXCEEDS_MAX", 
    "USER_SOCK_CONNECT_TIMEDOUT", 
    "USER_API_VERSION_MISMATCH", 
    "USER_INPUT_FORMAT_ERR", 
    "FILE_INDEX_LOOKUP_ERR", 
    "UNIX_FILE_OPEN_ERR", 
    "UNIX_FILE_CREATE_ERR", 
    "UNIX_FILE_READ_ERR", 
    "UNIX_FILE_WRITE_ERR", 
    "UNIX_FILE_CLOSE_ERR", 
    "UNIX_FILE_UNLINK_ERR", 
    "UNIX_FILE_STAT_ERR", 
    "UNIX_FILE_FSTAT_ERR", 
    "UNIX_FILE_LSEEK_ERR", 
    "UNIX_FILE_FSYNC_ERR", 
    "UNIX_FILE_MKDIR_ERR", 
    "UNIX_FILE_RMDIR_ERR", 
    "UNIX_FILE_OPENDIR_ERR", 
    "UNIX_FILE_CLOSEDIR_ERR", 
    "UNIX_FILE_READDIR_ERR", 
    "UNIX_FILE_STAGE_ERR", 
    "UNIX_FILE_GET_FS_FREESPACE_ERR", 
    "UNIX_FILE_CHMOD_ERR", 
    "UNIX_FILE_RENAME_ERR", 
    "UNIX_FILE_TRUNCATE_ERR", 
    "CATALOG_NOT_CONNECTED", 
    "CAT_ENV_ERR", 
    "CAT_CONNECT_ERR", 
    "CAT_DISCONNECT_ERR", 
    "CAT_CLOSE_ENV_ERR", 
    "CAT_SQL_ERR", 
    "CAT_GET_ROW_ERR", 
    "CAT_NO_ROWS_FOUND", 
    "CATALOG_ALREADY_HAS_ITEM_BY_THAT_NAME", 
    "CAT_INVALID_RESOURCE_TYPE", 
    "CAT_INVALID_RESOURCE_CLASS", 
    "CAT_INVALID_RESOURCE_NET_ADDR", 
    "CAT_INVALID_RESOURCE_VAULT_PATH", 
    "CAT_UNKNOWN_COLLECTION", 
    "CAT_INVALID_DATA_TYPE", 
    "CAT_INVALID_ARGUMENT", 
    "CAT_UNKNOWN_FILE", 
    "CAT_NO_ACCESS_PERMISSION", 
    "CAT_SUCCESS_BUT_WITH_NO_INFO", 
    "CAT_INVALID_USER_TYPE", 
    "CAT_COLLECTION_NOT_EMPTY", 
    "CAT_TOO_MANY_TABLES", 
    "CAT_UNKNOWN_TABLE", 
    "CAT_NOT_OPEN", 
    "CAT_FAILED_TO_LINK_TABLES", 
    "CAT_INVALID_AUTHENTICATION", 
    "CAT_INVALID_USER", 
    "CAT_INVALID_ZONE", 
    "CAT_INVALID_GROUP", 
    "CAT_INSUFFICIENT_PRIVILEGE_LEVEL", 
    "CAT_INVALID_RESOURCE", 
    "CAT_INVALID_CLIENT_USER", 
    "CAT_NAME_EXISTS_AS_COLLECTION", 
    "CAT_NAME_EXISTS_AS_DATAOBJ", 
    "CAT_RESOURCE_NOT_EMPTY", 
    "CAT_NOT_A_DATAOBJ_AND_NOT_A_COLLECTION", 
    "CAT_RECURSIVE_MOVE", 
    "CAT_LAST_REPLICA", 
    "CAT_OCI_ERROR", 
    "CAT_PASSWORD_EXPIRED", 
    "RDA_NOT_COMPILED_IN", 
    "RDA_NOT_CONNECTED", 
    "RDA_ENV_ERR", 
    "RDA_CONNECT_ERR", 
    "RDA_DISCONNECT_ERR", 
    "RDA_CLOSE_ENV_ERR", 
    "RDA_SQL_ERR", 
    "RDA_CONFIG_FILE_ERR", 
    "RDA_ACCESS_PROHIBITED", 
    "RDA_NAME_NOT_FOUND", 
    "FILE_OPEN_ERR", 
    "FILE_READ_ERR", 
    "FILE_WRITE_ERR", 
    "PASSWORD_EXCEEDS_MAX_SIZE", 
    "ENVIRONMENT_VAR_HOME_NOT_DEFINED", 
    "UNABLE_TO_STAT_FILE", 
    "AUTH_FILE_NOT_ENCRYPTED", 
    "AUTH_FILE_DOES_NOT_EXIST", 
    "UNLINK_FAILED", 
    "NO_PASSWORD_ENTERED", 
    "REMOTE_SERVER_AUTHENTICATION_FAILURE", 
    "REMOTE_SERVER_AUTH_NOT_PROVIDED", 
    "REMOTE_SERVER_AUTH_EMPTY", 
    "REMOTE_SERVER_SID_NOT_DEFINED", 
    "GSI_NOT_COMPILED_IN", 
    "GSI_NOT_BUILT_INTO_CLIENT", 
    "GSI_NOT_BUILT_INTO_SERVER", 
    "GSI_ERROR_IMPORT_NAME", 
    "GSI_ERROR_INIT_SECURITY_CONTEXT", 
    "GSI_ERROR_SENDING_TOKEN_LENGTH", 
    "GSI_ERROR_READING_TOKEN_LENGTH", 
    "GSI_ERROR_TOKEN_TOO_LARGE", 
    "GSI_ERROR_BAD_TOKEN_RCVED", 
    "GSI_SOCKET_READ_ERROR", 
    "GSI_PARTIAL_TOKEN_READ", 
    "GSI_SOCKET_WRITE_ERROR", 
    "GSI_ERROR_FROM_GSI_LIBRARY", 
    "GSI_ERROR_IMPORTING_NAME", 
    "GSI_ERROR_ACQUIRING_CREDS", 
    "GSI_ACCEPT_SEC_CONTEXT_ERROR", 
    "GSI_ERROR_DISPLAYING_NAME", 
    "GSI_ERROR_RELEASING_NAME", 
    "GSI_DN_DOES_NOT_MATCH_USER", 
    "GSI_QUERY_INTERNAL_ERROR", 
    "OBJPATH_EMPTY_IN_STRUCT_ERR", 
    "RESCNAME_EMPTY_IN_STRUCT_ERR", 
    "DATATYPE_EMPTY_IN_STRUCT_ERR", 
    "DATASIZE_EMPTY_IN_STRUCT_ERR", 
    "CHKSUM_EMPTY_IN_STRUCT_ERR", 
    "VERSION_EMPTY_IN_STRUCT_ERR", 
    "FILEPATH_EMPTY_IN_STRUCT_ERR", 
    "REPLNUM_EMPTY_IN_STRUCT_ERR", 
    "REPLSTATUS_EMPTY_IN_STRUCT_ERR", 
    "DATAOWNER_EMPTY_IN_STRUCT_ERR", 
    "DATAOWNERZONE_EMPTY_IN_STRUCT_ERR", 
    "DATAEXPIRY_EMPTY_IN_STRUCT_ERR", 
    "DATACOMMENTS_EMPTY_IN_STRUCT_ERR", 
    "DATACREATE_EMPTY_IN_STRUCT_ERR", 
    "DATAMODIFY_EMPTY_IN_STRUCT_ERR", 
    "DATAACCESS_EMPTY_IN_STRUCT_ERR", 
    "DATAACCESSINX_EMPTY_IN_STRUCT_ERR", 
    "NO_RULE_FOUND_ERR", 
    "NO_MORE_RULES_ERR", 
    "UNMATCHED_ACTION_ERR", 
    "RULES_FILE_READ_ERROR", 
    "ACTION_ARG_COUNT_MISMATCH", 
    "MAX_NUM_OF_ARGS_IN_ACTION_EXCEEDED", 
    "UNKNOWN_PARAM_IN_RULE_ERR", 
    "DESTRESCNAME_EMPTY_IN_STRUCT_ERR", 
    "BACKUPRESCNAME_EMPTY_IN_STRUCT_ERR", 
    "DATAID_EMPTY_IN_STRUCT_ERR", 
    "COLLID_EMPTY_IN_STRUCT_ERR", 
    "RESCGROUPNAME_EMPTY_IN_STRUCT_ERR", 
    "STATUSSTRING_EMPTY_IN_STRUCT_ERR", 
    "DATAMAPID_EMPTY_IN_STRUCT_ERR", 
    "USERNAMECLIENT_EMPTY_IN_STRUCT_ERR", 
    "RODSZONECLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERTYPECLIENT_EMPTY_IN_STRUCT_ERR", 
    "HOSTCLIENT_EMPTY_IN_STRUCT_ERR", 
    "AUTHSTRCLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERAUTHSCHEMECLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERINFOCLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERCOMMENTCLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERCREATECLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERMODIFYCLIENT_EMPTY_IN_STRUCT_ERR", 
    "USERNAMEPROXY_EMPTY_IN_STRUCT_ERR", 
    "RODSZONEPROXY_EMPTY_IN_STRUCT_ERR", 
    "USERTYPEPROXY_EMPTY_IN_STRUCT_ERR", 
    "HOSTPROXY_EMPTY_IN_STRUCT_ERR", 
    "AUTHSTRPROXY_EMPTY_IN_STRUCT_ERR", 
    "USERAUTHSCHEMEPROXY_EMPTY_IN_STRUCT_ERR", 
    "USERINFOPROXY_EMPTY_IN_STRUCT_ERR", 
    "USERCOMMENTPROXY_EMPTY_IN_STRUCT_ERR", 
    "USERCREATEPROXY_EMPTY_IN_STRUCT_ERR", 
    "USERMODIFYPROXY_EMPTY_IN_STRUCT_ERR", 
    "COLLNAME_EMPTY_IN_STRUCT_ERR", 
    "COLLPARENTNAME_EMPTY_IN_STRUCT_ERR", 
    "COLLOWNERNAME_EMPTY_IN_STRUCT_ERR", 
    "COLLOWNERZONE_EMPTY_IN_STRUCT_ERR", 
    "COLLEXPIRY_EMPTY_IN_STRUCT_ERR", 
    "COLLCOMMENTS_EMPTY_IN_STRUCT_ERR", 
    "COLLCREATE_EMPTY_IN_STRUCT_ERR", 
    "COLLMODIFY_EMPTY_IN_STRUCT_ERR", 
    "COLLACCESS_EMPTY_IN_STRUCT_ERR", 
    "COLLACCESSINX_EMPTY_IN_STRUCT_ERR", 
    "COLLMAPID_EMPTY_IN_STRUCT_ERR", 
    "COLLINHERITANCE_EMPTY_IN_STRUCT_ERR", 
    "RESCZONE_EMPTY_IN_STRUCT_ERR", 
    "RESCLOC_EMPTY_IN_STRUCT_ERR", 
    "RESCTYPE_EMPTY_IN_STRUCT_ERR", 
    "RESCTYPEINX_EMPTY_IN_STRUCT_ERR", 
    "RESCCLASS_EMPTY_IN_STRUCT_ERR", 
    "RESCCLASSINX_EMPTY_IN_STRUCT_ERR", 
    "RESCVAULTPATH_EMPTY_IN_STRUCT_ERR", 
    "NUMOPEN_ORTS_EMPTY_IN_STRUCT_ERR", 
    "PARAOPR_EMPTY_IN_STRUCT_ERR", 
    "RESCID_EMPTY_IN_STRUCT_ERR", 
    "GATEWAYADDR_EMPTY_IN_STRUCT_ERR", 
    "RESCMAX_BJSIZE_EMPTY_IN_STRUCT_ERR", 
    "FREESPACE_EMPTY_IN_STRUCT_ERR", 
    "FREESPACETIME_EMPTY_IN_STRUCT_ERR", 
    "FREESPACETIMESTAMP_EMPTY_IN_STRUCT_ERR", 
    "RESCINFO_EMPTY_IN_STRUCT_ERR", 
    "RESCCOMMENTS_EMPTY_IN_STRUCT_ERR", 
    "RESCCREATE_EMPTY_IN_STRUCT_ERR", 
    "RESCMODIFY_EMPTY_IN_STRUCT_ERR", 
    "INPUT_ARG_NOT_WELL_FORMED_ERR", 
    "INPUT_ARG_OUT_OF_ARGC_RANGE_ERR", 
    "INSUFFICIENT_INPUT_ARG_ERR", 
    "INPUT_ARG_DOES_NOT_MATCH_ERR", 
    "RETRY_WITHOUT_RECOVERY_ERR", 
    "CUT_ACTION_PROCESSED_ERR", 
    "ACTION_FAILED_ERR", 
    "FAIL_ACTION_ENCOUNTERED_ERR", 
    "VARIABLE_NAME_TOO_LONG_ERR", 
    "UNKNOWN_VARIABLE_MAP_ERR", 
    "UNDEFINED_VARIABLE_MAP_ERR", 
    "NULL_VALUE_ERR", 
    "DVARMAP_FILE_READ_ERROR", 
    "NO_RULE_OR_MSI_FUNCTION_FOUND_ERR", 
    "FILE_CREATE_ERROR", 
    "FMAP_FILE_READ_ERROR", 
    "DATE_FORMAT_ERR", 
    "RULE_FAILED_ERR", 
    "NO_MICROSERVICE_FOUND_ERR", 
    "INVALID_REGEXP", 
    "INVALID_OBJECT_NAME", 
    "INVALID_OBJECT_TYPE", 
    "NO_VALUES_FOUND", 
    "NO_COLUMN_NAME_FOUND", 
    "BREAK_ACTION_ENCOUNTERED_ERR", 
    "PHP_EXEC_SCRIPT_ERR", 
    "PHP_REQUEST_STARTUP_ERR", 
    "PHP_OPEN_SCRIPT_FILE_ERR", 
    "SYS_NULL_INPUT", 
    "SYS_HANDLER_DONE_WITH_ERROR", 
    "SYS_HANDLER_DONE_NO_ERROR", 
    "SYS_NO_HANDLER_REPLY_MSG", 
};
int irodsErrorCount= 349;
/* END generated code */

static int verbosityLevel=LOG_ERROR;
static int sqlVerbosityLevel=0;
static pid_t myPid=0;


#ifdef windows_platform
static void rodsNtElog(char *msg);
#endif

/*
 Log or display a message.  The level argument indicates how severe
 the message is, and depending on the verbosityLevel may or may not be
 recorded.  This is used by both client and server code.
 */
void
rodsLog(int level, char *formatStr, ...) {
   char bigString[BIG_STRING_LEN];
   char *prefix;
   time_t timeValue;
   int i;
   FILE *errOrOut;
   va_list ap;

   char extraInfo[100];
#ifdef windows_platform
   char nt_log_msg[2048];
#endif

   if (level < verbosityLevel) return;


   va_start(ap, formatStr);
   i = vsnprintf(bigString, BIG_STRING_LEN-1, formatStr, ap);
   va_end(ap);
   
   extraInfo[0]='\0';
#ifndef windows_platform
   errOrOut = stdout;
#endif
   if (ProcessType == SERVER_PT || ProcessType == AGENT_PT ||
     ProcessType == RE_SERVER_PT) {
      char timeBuf[100];
      time(&timeValue);
      rstrcpy(timeBuf, ctime(&timeValue), 90);
      timeBuf[19]='\0';
      if (myPid==0) myPid = getpid();
      snprintf(extraInfo, 100-1, "%s pid:%d ", timeBuf+4, myPid);
   }
   else {
#ifndef windows_platform
      if (level >= LOG_ERROR) errOrOut=stderr;
#endif
   }

   prefix="";
   if (level == LOG_SQL) prefix="LOG_SQL";
   if (level == LOG_SYS_FATAL) prefix="SYSTEM FATAL";
   if (level == LOG_SYS_WARNING) prefix="SYSTEM WARNING";
   if (level == LOG_ERROR) prefix="ERROR";
   if (level == LOG_NOTICE) prefix="NOTICE";
   if (level <= LOG_DEBUG) prefix="DEBUG";
   if (bigString[strlen(bigString)-1]=='\n') 
   {
#ifndef windows_platform
      fprintf(errOrOut, "%s%s: %s", extraInfo, prefix, bigString);
#else
	  sprintf(nt_log_msg, "%s%s: %s", extraInfo, prefix, bigString);
	  rodsNtElog(nt_log_msg);
#endif
   }
   else 
   {
#ifndef windows_platform
      fprintf(errOrOut, "%s%s: %s\n", extraInfo, prefix, bigString);
#else
	   sprintf(nt_log_msg, "%s%s: %s\n", extraInfo, prefix, bigString);
	   rodsNtElog(nt_log_msg);
#endif
   }
#ifndef windows_platform
   fflush (errOrOut);
#endif
}

/* same as rodsLog plus putting the msg in myError too. Need to merge with
 * rodsLog
 */

void
rodsLogAndErrorMsg (int level, rError_t *myError, int status,
char *formatStr, ...) {
   char bigString[BIG_STRING_LEN];
   char *prefix;
   time_t timeValue;
   int i;
   FILE *errOrOut;
   va_list ap;
   char errMsg[ERR_MSG_LEN];

   char extraInfo[100];
#ifdef windows_platform
   char nt_log_msg[2048];
#endif

   if (level < verbosityLevel) return;


   va_start(ap, formatStr);
   i = vsnprintf(bigString, BIG_STRING_LEN-1, formatStr, ap);
   va_end(ap);
   
   extraInfo[0]='\0';
   errOrOut = stdout;
   if (ProcessType == SERVER_PT || ProcessType == AGENT_PT ||
     ProcessType == RE_SERVER_PT) {
      char timeBuf[100];
      time(&timeValue);
      rstrcpy(timeBuf, ctime(&timeValue), 90);
      timeBuf[19]='\0';
      if (myPid==0) myPid = getpid();
      snprintf(extraInfo, 100-1, "%s pid:%d ", timeBuf+4, myPid);
   }
   else {
      if (level >= LOG_ERROR) errOrOut=stderr;
   }

   prefix="";
   if (level == LOG_SQL) prefix="LOG_SQL";
   if (level == LOG_SYS_FATAL) prefix="SYSTEM FATAL";
   if (level == LOG_SYS_WARNING) prefix="SYSTEM WARNING";
   if (level == LOG_ERROR) prefix="ERROR";
   if (level == LOG_NOTICE) prefix="NOTICE";
   if (level <= LOG_DEBUG) prefix="DEBUG";
   if (bigString[strlen(bigString)-1]=='\n') 
   {
#ifndef windows_platform
      fprintf(errOrOut, "%s%s: %s", extraInfo, prefix, bigString);
      if (myError != NULL) {
         snprintf (errMsg, ERR_MSG_LEN,
           "%s: %s", prefix, bigString);
         addRErrorMsg (myError, status, errMsg);
      } 
#else
	   sprintf(nt_log_msg, "%s%s: %s", extraInfo, prefix, bigString);
	   rodsNtElog(nt_log_msg);
#endif
   }
   else 
   {
#ifndef windows_platform
      fprintf(errOrOut, "%s%s: %s\n", extraInfo, prefix, bigString);
      if (myError != NULL) {
         snprintf (errMsg, ERR_MSG_LEN,
           "%s: %s\n", prefix, bigString);
         addRErrorMsg (myError, status, errMsg);
      }
#else
	   sprintf(nt_log_msg, "%s%s: %s\n", extraInfo, prefix, bigString);
	   rodsNtElog(nt_log_msg);
#endif
   }

#ifndef windows_platform
   fflush (errOrOut);
#endif
}

/*
 Change the verbosityLevel of reporting.
 The input value is the new minimum level of message to report.
 */
void 
rodsLogLevel(int level) {
   verbosityLevel = level;
}

int
getRodsLogLevel ()
{
    return (verbosityLevel);
}

/*
 Request sql logging.
 */
void 
rodsLogSqlReq(int onOrOff) {
   sqlVerbosityLevel=onOrOff;
}

void
rodsLogSql(char *sql) {
   if (myPid==0) myPid = getpid();
   if (sqlVerbosityLevel) rodsLog(LOG_SQL, "pid: %d sql: %s", 
				  myPid, sql);
}
void
rodsLogSqlResult(char *stat) {
   if (myPid==0) myPid = getpid();
   if (sqlVerbosityLevel) rodsLog(LOG_SQL, "pid: %d result: %s", 
				  myPid, stat);
}

/* 
Convert an iRods error code to the corresponding name.
 */
char *
rodsErrorName(int errorValue, char **subName)
{
   int i;
   int testVal;
   int subCode;

   testVal = errorValue/1000;

   *subName="";
   subCode = errorValue - (testVal*1000);
   if (subCode && *subName && errorValue<0) {
      *subName = strerror(-subCode);
   }

   for (i=0;i<irodsErrorCount;i++) {
      if (testVal==irodsErrors[i]/1000) {
	 return(irodsErrorNames[i]);
      }
   }
   return("Unknown iRODS error");
}

/*
 Convert an error code to a string and log it.
 This was originally called rodsLogError, but was renamed when we
 created the new rodsLogError below.  This is no longer used (
 rodsLogError can be called with the same arguments).
 */
void
rodsLogErrorOld(int level, int rodsErrorCode, char *textStr) {
   char *errName;
   char *errSubName;

   if (level < verbosityLevel) return;

   errName = rodsErrorName(rodsErrorCode, &errSubName);
   if (textStr && strlen(textStr)>0) {
      rodsLog(level, "%s Error: %d: %s, %s", textStr, rodsErrorCode,
	      errName, errSubName);
   }
   else {
      rodsLog(level, "Error: %d: %s, %s", rodsErrorCode, 
	      errName, errSubName);
   }
}

/* Like rodsLogError but with full rodsLog functionality too.
   Converts the errorcode to a string, and possibly a subcode string,
   and includes that at the end of a regular log message (with
   variable arguments).
 */
void
rodsLogError(int level, int rodsErrorCode, char *formatStr, ...) {
   char bigString[BIG_STRING_LEN];
   int i;
   char *errName;
   char *errSubName;
   va_list ap;

   if (level < verbosityLevel) return;

   
   va_start(ap, formatStr);
   i = vsnprintf(bigString, BIG_STRING_LEN-1, formatStr, ap);
   va_end(ap);
   
   errName = rodsErrorName(rodsErrorCode, &errSubName);
   if (strlen(errSubName)>0) {
      rodsLog(level, "%s status = %d %s, %s", bigString, rodsErrorCode,
	      errName, errSubName);
   }
   else {
      rodsLog(level, "%s status = %d %s", bigString, rodsErrorCode,
	      errName);
   }
}

#ifdef windows_platform
static void rodsNtElog(char *msg)
{
	char log_fname[1024];
	int fd;
	int t;

	if(ProcessType == CLIENT_PT)
	{
		fprintf(stderr,"%s", msg);
	    return;
	}

	t = strlen(msg);
	if(msg[t-1] == '\n')
	{
		msg[t-1] = '\0';
		t = t -1;
	}

	if(iRODSNtServerRunningConsoleMode())
	{
		t = strlen(msg);
		if(msg[t-1] == '\n')
			fprintf(stderr,"%s",msg);
		else
			fprintf(stderr,"%s\n",msg);
		return;
	}

	t = strlen(msg);
	if(msg[t-1] != '\n')
	{
		msg[t] = '\n';
		msg[t+1] = '\0';
		t = t +1;
	}

	iRODSNtGetLogFilenameWithPath(log_fname);
	fd = iRODSNt_open(log_fname, O_APPEND|O_WRONLY,1);
	_write(fd,msg,t);
	_close(fd);
}
#endif
