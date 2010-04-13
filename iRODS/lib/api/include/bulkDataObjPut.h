/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* dataObjPut.h - This dataObj may be generated by a program or script
 */

#ifndef BULK_DATA_OBJ_PUT_H
#define BULK_DATA_OBJ_PUT_H

/* This is a Object File I/O API call */

#include "rods.h"
#include "rcMisc.h"
#include "procApiRequest.h"
#include "apiNumber.h"
#include "initServer.h"
#include "dataObjWrite.h"
#include "dataObjClose.h"

#if defined(RODS_SERVER)
#define RS_BULK_DATA_OBJ_PUT rsBulkDataObjPut
/* prototype for the server handler */
int
rsBulkDataObjPut (rsComm_t *rsComm, dataObjInp_t *dataObjInp, 
bytesBuf_t *dataObjInpBBuf);
int
_rsBulkDataObjPut (rsComm_t *rsComm, dataObjInp_t *dataObjInp,
bytesBuf_t *dataObjInpBBuf);
#else
#define RS_BULK_DATA_OBJ_PUT NULL
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* prototype for the client call */
/* rcBulkDataObjPut - Bulk Put (upload) a number of local files to iRODS.
 * dataObjInpBBuf contains the bundled local files in tar format.
 * Input -
 *   rcComm_t *conn - The client connection handle.
 *   dataObjInp_t *dataObjInp - generic dataObj input. Relevant items are:
 *      objPath - the collection path under which the files are to be untar.
 *      condInput - conditional Input
 *          FORCE_FLAG_KW - overwrite an existing data object
 *	    DATA_TYPE_KW - "value" = the data type of the file.	
 *          DEST_RESC_NAME_KW - "value" = The destination Resource. 
 *   return value - The status of the operation.
 */

int
rcBulkDataObjPut (rcComm_t *conn, dataObjInp_t *dataObjInp,
bytesBuf_t *dataObjInpBBuf);
#ifdef  __cplusplus
}
#endif

#endif	/* BULK_DATA_OBJ_PUT_H */
