/**
 * @file eraMS.c
 *
 */

/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/

#include <stdlib.h>
#include <unistd.h>
#include "eraMS.h"
#include "eraUtil.h"




/**
 * \fn msiRecursiveCollCopy(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Copies a collection and its contents recursively
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-12
 *
 * \note This microservice copies a collection and its contents recursively.
 *    Collection and data object metadata AVUs are also copied over to the new objects and collections.
 *
 * \usage
 * As seen in modules/ERA/test/recursiveCollCopy.ir
 * 
 * testrule||msiRecursiveCollCopy(*DestColl,*SourceColl,*Status)|nop
 * *SourceColl=/tempZone/home/testuser%*DestColl=/tempZone/home/antoine/copy/testuser
 * ruleExecOut
 *
 * \param[in] inpParam1 - A CollInp_MS_T or a STR_MS_T with the irods path of the destination collection.
 * \param[in] inpParam2 - A CollInp_MS_T or a STR_MS_T with the irods path of the source collection.
 * \param[out] outParam - An INT_MS_T containing the status.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiRecursiveCollCopy(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	collInp_t collInpCache1, *collInp1;
	collInp_t collInpCache2, *collInp2;
	rsComm_t *rsComm;

	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiRecursiveCollCopy")


	/* Sanity check */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiRecursiveCollCopy: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;


	/* Parse inpParam1 */
	rei->status = parseMspForCollInp (inpParam1, &collInpCache1, &collInp1, 0);
	
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiRecursiveCollCopy: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}


	/* Parse inpParam2 */
	rei->status = parseMspForCollInp (inpParam2, &collInpCache2, &collInp2, 0);
	
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiRecursiveCollCopy: input inpParam2 error. status = %d", rei->status);
		return (rei->status);
	}


	/* Call recursiveCollCopy() */
	rei->status = recursiveCollCopy(collInp1, collInp2, rsComm);


	/* Return status and log error if failure */
	if (rei->status >= 0) {
		fillIntInMsParam (outParam, rei->status);
	} 
	else {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiRecursiveCollCopy: recursiveCollCopy failed for %s, status = %d",
			inpParam1->inOutStruct, rei->status);
	}
	
	return (rei->status);
}



/**
 * \fn msiCopyAVUMetadata(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Copies metadata triplets from one iRODS object to another
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-15
 *
 * \note This microservice copies metadata triplets from one iRODS object to another.
 *    The source and destination can be a data object or a collection, independently.
 *
 * \usage
 * testrule||msiCopyAVUMetadata(*A, *B, *Status)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 * *A=/tempZone/rods/test1.txt%*B=/tempZone/rods/test2.txt
 * ruleExecOut
 *
 * \param[in] inpParam1 - A STR_MS_T with the irods path of the source object.
 * \param[in] inpParam2 - A STR_MS_T with the irods path of the destination object.
 * \param[out] outParam - An INT_MS_T containing the status.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiCopyAVUMetadata(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm;

	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiCopyAVUMetadata")


	/* Sanity check */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiCopyAVUMetadata: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;


	/* Check for proper input */
	if ((parseMspForStr(inpParam1) == NULL)) {
		rodsLog (LOG_ERROR, "msiCopyAVUMetadata: input inpParam1 is NULL");
		return (USER__NULL_INPUT_ERR);
	}

	if ((parseMspForStr (inpParam2) == NULL)) {
		rodsLog (LOG_ERROR, "msiCopyAVUMetadata: input inpParam2 is NULL");
		return (USER__NULL_INPUT_ERR);
	}


	/* Call copyAVUMetadata() */
	rei->status = copyAVUMetadata(inpParam1->inOutStruct, inpParam2->inOutStruct, rsComm);

	return (rei->status);
}



/**
 * \fn msiExportRecursiveCollMeta(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Exports metadata AVU triplets for a collection and its contents
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-15
 *
 * \note This microservice recursively exports user-defined metadata attributes (AVUs) for
 *    a collection and all collections and data objects in this collection.
 *    The output is written to a bytesBuf_t buffer in pipe separated format, one
 *    line per attribute as in the example below:
 *      /tempZone/home/testuser/myFile|myAttr|myVal|myUnits
 *
 * \usage
 * As seen in modules/ERA/test/exportRecursiveCollMeta.ir
 * 
 * testrule||msiExportRecursiveCollMeta(*Source_Path, *BUF)##writeBytesBuf(stdout,*BUF)|nop
 * *Source_Path=/tempZone/home/rods
 * ruleExecOut
 *
 * \param[in] inpParam - A CollInp_MS_T or a STR_MS_T with the irods path of the target collection.
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiExportRecursiveCollMeta(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	collInp_t collInpCache, *outCollInp;
	genQueryInp_t genQueryInp;
	genQueryOut_t *genQueryOut;
	char collQCond[MAX_NAME_LEN];
	char objPath[MAX_NAME_LEN];
	rsComm_t *rsComm;
	bytesBuf_t *mybuf;
	char *tResult;	
	int i, j;	



	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiExportRecursiveCollMeta")
	
	rsComm = rei->rsComm;

	
	/* parse inpParam1 */
	rei->status = parseMspForCollInp (inpParam, &collInpCache, &outCollInp, 0);
	
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
				    "msiExportRecursiveCollMeta: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}
	
	
	/* Make sure input is a collection */
	if (isColl(rei->rsComm, outCollInp->collName, NULL) < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
				    "msiExportRecursiveCollMeta: Invalid input in inpParam1: %s. No such collection.", outCollInp->collName);
		return (rei->status);
	}	
	
	
	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));
	
	
	/* Get all collections (recursively) under our input collection */
	/* Prepare query */
	memset (&genQueryInp, 0, sizeof (genQueryInp_t));
	genAllInCollQCond (outCollInp->collName, collQCond);
	
	addInxVal (&genQueryInp.sqlCondInp, COL_COLL_NAME, collQCond);
	addInxIval (&genQueryInp.selectInp, COL_COLL_NAME, 1);
	
	genQueryInp.maxRows = MAX_SQL_ROWS;
	
	/* ICAT query for subcollections */
	rei->status =  rsGenQuery (rsComm, &genQueryInp, &genQueryOut);	

	if (rei->status != CAT_NO_ROWS_FOUND) {
		
		for (i=0;i<genQueryOut->rowCnt;i++) {
			
			for (j=0;j<genQueryOut->attriCnt;j++) {
				tResult = genQueryOut->sqlResult[j].value;
				tResult += i*genQueryOut->sqlResult[j].len;
				
				/* get metadata for this collection */
				getCollectionPSmeta(tResult, mybuf, rsComm);
			}
		}

		while (rei->status==0 && genQueryOut->continueInx > 0) {
			genQueryInp.continueInx=genQueryOut->continueInx;
			rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);

			for (i=0;i<genQueryOut->rowCnt;i++) {
			
				for (j=0;j<genQueryOut->attriCnt;j++) {
					tResult = genQueryOut->sqlResult[j].value;
					tResult += i*genQueryOut->sqlResult[j].len;
					
					/* get metadata for this collection */
					getCollectionPSmeta(tResult, mybuf, rsComm);
				}
			}
		}
	}

	
	/* Same thing now for all files (recursively) under our input collection */
	/* Prepare query */
	memset (&genQueryInp, 0, sizeof (genQueryInp_t));
	genAllInCollQCond (outCollInp->collName, collQCond);
	
	addInxVal (&genQueryInp.sqlCondInp, COL_COLL_NAME, collQCond);
	addInxIval (&genQueryInp.selectInp, COL_COLL_NAME, 1);
	addInxIval (&genQueryInp.selectInp, COL_DATA_NAME, 1);
	
	genQueryInp.maxRows = MAX_SQL_ROWS;	
	
	/* ICAT query for data objects */
	rei->status =  rsGenQuery (rsComm, &genQueryInp, &genQueryOut);	

	if (rei->status != CAT_NO_ROWS_FOUND) {
		
		for (i=0;i<genQueryOut->rowCnt;i++) {

			/* First attribute is parent collection */
			tResult = genQueryOut->sqlResult[0].value;
			tResult += i*genQueryOut->sqlResult[0].len;
			snprintf(objPath, MAX_NAME_LEN, "%s/", tResult);
			
			/* Second attribute is the filename */
			tResult = genQueryOut->sqlResult[1].value;
			tResult += i*genQueryOut->sqlResult[1].len;
			strcat(objPath, tResult);
			
			/* Get metadata for this file */
			getDataObjPSmeta(objPath, mybuf, rsComm);
		}

		while (rei->status==0 && genQueryOut->continueInx > 0) {
			genQueryInp.continueInx=genQueryOut->continueInx;
			rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);

			for (i=0;i<genQueryOut->rowCnt;i++) {
			
				/* First attribute is parent collection */
				tResult = genQueryOut->sqlResult[0].value;
				tResult += i*genQueryOut->sqlResult[0].len;
				snprintf(objPath, MAX_NAME_LEN, "%s/", tResult);
			
				/* Second attribute is the filename */
				tResult = genQueryOut->sqlResult[1].value;
				tResult += i*genQueryOut->sqlResult[1].len;
				strcat(objPath, tResult);
			
				/* Get metadata for this file */
				getDataObjPSmeta(objPath, mybuf, rsComm);
			}
		}
	}


	/* did we get any results? */
	if (!mybuf->buf || !strlen(mybuf->buf)) {
		appendStrToBBuf(mybuf, "");
	}

	/* send results out to outParam */
	fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);

	return 0;
}



/**
 * \fn msiGetDataObjAVUs(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief This microservice retrieves the metadata AVU triplets for a data object
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note This microservice retrieves the metadata AVU triplets for a data object and returns them as an XML file.
 *
 * \usage None
 *
 * \param[in] inpParam - A DataObjInp_MS_T or a STR_MS_T with the irods path of the target object.
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetDataObjAVUs(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
   rsComm_t *rsComm; 
   dataObjInp_t dataObjInp, *myDataObjInp;
   bytesBuf_t *mybuf;

   genQueryInp_t genQueryInp;
   genQueryOut_t *genQueryOut;
   int i1a[10];
   int i1b[10];
   int i2a[10];
   char *condVal[10];
   char v1[MAX_NAME_LEN];
   char v2[MAX_NAME_LEN];
   char fullName[MAX_NAME_LEN];
   char myDirName[MAX_NAME_LEN];
   char myFileName[MAX_NAME_LEN];
   int printCount=0;

   char *tags[]={"AVU", "attribute", "value", "units"};


   RE_TEST_MACRO ("    Calling msiGetDataObjAVUs")

   if (rei == NULL || rei->rsComm == NULL) {
	rodsLog (LOG_ERROR,
	  "msiGetDataObjAVUs: input rei or rsComm is NULL");
	return (SYS_INTERNAL_NULL_INPUT_ERR);
   }

   rsComm = rei->rsComm;

   /* parse inpParam1 */
   rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);

   if (rei->status < 0) {
	rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
          "msiGetDataObjAVUs: input inpParam1 error. status = %d", rei->status);
	return (rei->status);
   }


   memset (&genQueryInp, 0, sizeof (genQueryInp_t));

   i1a[0]=COL_META_DATA_ATTR_NAME;
   i1b[0]=0; /* currently unused */
   i1a[1]=COL_META_DATA_ATTR_VALUE;
   i1b[1]=0; /* currently unused */
   i1a[2]=COL_META_DATA_ATTR_UNITS;
   i1b[2]=0; /* currently unused */
   genQueryInp.selectInp.inx = i1a;
   genQueryInp.selectInp.value = i1b;
   genQueryInp.selectInp.len = 3;

   /* Extract cwd name and object name */
   strncpy(fullName, myDataObjInp->objPath, MAX_NAME_LEN);
   rei->status = splitPathByKey(fullName, myDirName, myFileName, '/');

   i2a[0]=COL_COLL_NAME;
   sprintf(v1,"='%s'",myDirName);
   condVal[0]=v1;

   i2a[1]=COL_DATA_NAME;
   sprintf(v2,"='%s'",myFileName);
   condVal[1]=v2;


   genQueryInp.sqlCondInp.inx = i2a;
   genQueryInp.sqlCondInp.value = condVal;
   genQueryInp.sqlCondInp.len=2;

   genQueryInp.maxRows=10;
   genQueryInp.continueInx=0;
   genQueryInp.condInput.len=0;


   /* Actual query happens here */
   rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);


   /* buffer init */
   mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
   memset (mybuf, 0, sizeof (bytesBuf_t));


   /* Prepare XML output */
   appendStrToBBuf(mybuf, "<?xml version='1.0' encoding='utf-8'?>\n");
   appendStrToBBuf(mybuf, "<!-- Generated by iRODS (http://www.irods.org) -->\n");
   appendStrToBBuf(mybuf, "<metadata>\n");


   if (rei->status == CAT_NO_ROWS_FOUND) {
      i1a[0]=COL_D_DATA_PATH;
      genQueryInp.selectInp.len = 1;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      if (rei->status==0) {
	 printf("None\n");
	 return(0);
      }
      if (rei->status == CAT_NO_ROWS_FOUND) {

	rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
          "msiGetDataObjAVUs: DataObject %s not found. status = %d", fullName, rei->status);
	return (rei->status);
      }
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }
   else {
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }

   while (rei->status==0 && genQueryOut->continueInx > 0) {
      genQueryInp.continueInx=genQueryOut->continueInx;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      printCount+= genQueryOutToXML(genQueryOut, mybuf, tags);
   }

  /* Closing tag */
  appendStrToBBuf(mybuf, "</metadata>\n");


  fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);

  /* rei->status may be CAT_NO_ROWS_FOUND, so don't return it */
  return (0);

}



/**
 * \fn msiGetDataObjPSmeta(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief This microservice retrieves the metadata AVU triplets for a data object
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note This microservice retrieves the metadata AVU triplets for a data object.
 *    Similar to msiGetDataObjAVUs except that the results are returned in a pipe separated format.
 *
 * \usage None
 *
 * \param[in] inpParam - A DataObjInp_MS_T or a STR_MS_T with the irods path of the target object.
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetDataObjPSmeta(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm; 
	dataObjInp_t dataObjInp, *myDataObjInp;
	bytesBuf_t *mybuf;
	
	
	RE_TEST_MACRO ("    Calling msiGetDataObjPSmeta")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR,
			"msiGetDataObjPSmeta: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;
	
	
	/* parse inpParam1 */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetDataObjPSmeta: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}

	
	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));

	
	/* call getDataObjPSmeta() */
	getDataObjPSmeta(myDataObjInp->objPath, mybuf, rsComm);
	

	/* send results out to outParam */
	fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);
	
	return (rei->status);

}



/**
 * \fn msiGetCollectionPSmeta(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Retrieves metadata AVU triplets for a collection
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note Retrieves metadata AVU triplets for a collection and returns the results in a pipe separated format.
 *
 * \usage  None
 *
 * \param[in] inpParam - A CollInp_MS_T or a STR_MS_T with the irods path of the target collection.
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetCollectionPSmeta(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm; 
	collInp_t collInpCache, *outCollInp;
	bytesBuf_t *mybuf;
	
	
	RE_TEST_MACRO ("    Calling msiGetCollectionPSmeta")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR,
			 "msiGetCollectionPSmeta: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;
	
	
	/* parse inpParam1 */
	rei->status = parseMspForCollInp (inpParam, &collInpCache, &outCollInp, 0);	

	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetCollectionPSmeta: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}


	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));


	/* call getCollectionPSmeta() */
	getCollectionPSmeta(outCollInp->collName, mybuf, rsComm);


	/* send results out to outParam */
	fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);

	return (rei->status);

}



/**
 * \fn msiLoadMetadataFromDataObj(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Parses an iRODS object for new metadata AVUs
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note This microservice parses an iRODS object (file) for new metadata AVUs and adds them to the iCAT.
 *    The metadata file is read as a text file and must contain one AVU per line.
 *
 *    See example file snippet below:
 *
 *    C-/tempZone/home/antoine/testColl |CollAttr000 |CollVal00 |CollUnits00
 *    /tempZone/home/antoine/testColl/file00.txt |myAttr000 |myVal001
 *    /tempZone/home/antoine/testColl/file00.txt |myAttr001 |myVal001 |myUnits001
 *    # Some comments
 *    /tempZone/home/antoine/testColl/file01.txt |myAttr011 |myVal011
 *    /tempZone/home/antoine/testColl/file01.txt |myAttr010 |myVal011
 *
 *    Collection paths must start with C-.
 *
 *    Units in AVUs are optional.
 *
 *    Lines starting with # won't be parsed.
 *
 * \usage
 * As seen in modules/ERA/test/loadMetadata.ir
 * 
 * testrule||msiGetSystemTime(*Start_time, null)##msiLoadMetadataFromDataObj(*ObjPath,*Status)##msiGetSystemTime(*End_time, null)##msiGetDiffTime(*Start_time, *End_time, human, *Duration)##writeLine(stdout,"")##writeLine(stdout, *Duration)|nop
 * *ObjPath=/tempZone/home/narauser/tstColl.mdf
 * ruleExecOut
 *
 * \param[in] inpParam - A DataObjInp_MS_T or a STR_MS_T with the irods path of the metadata file.
 * \param[out] outParam - An INT_MS_T containing the status.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiLoadMetadataFromDataObj(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	dataObjInp_t dataObjInp, *myDataObjInp;
	rsComm_t *rsComm;

	
	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiLoadMetadataFromDataObj")


	/* Sanity checks */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiLoadMetadataFromDataObj: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}

	rsComm = rei->rsComm;	
	
	/* parse inpParam1 */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiLoadMetadataFromDataObj: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}

	
	/* call loadMetadataFromDataObj() */
	rei->status = loadMetadataFromDataObj(myDataObjInp, rsComm);
	
	/* send status out to outParam */
	fillIntInMsParam(outParam, rei->status);

	return (rei->status);
}



/**
 * \fn msiGetDataObjAIP(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief This microservice gets the Archival Information Package of a data object.
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date   2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note This microservice gets the Archival Information Package of a data object.
 *    The results are returned as an XML file.
 *
 * \usage None
 *
 * \param[in] inpParam - A DataObjInp_MS_T or a STR_MS_T with the iRODS path of the target object.
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetDataObjAIP(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
   rsComm_t *rsComm; 
   dataObjInp_t dataObjInp, *myDataObjInp;
   bytesBuf_t *mybuf;

   genQueryInp_t genQueryInp;
   genQueryOut_t *genQueryOut;
   int i1a[30];
   int i1b[30];
   int i2a[30];
   char *condVal[30];
   char v1[MAX_NAME_LEN];
   char v2[MAX_NAME_LEN];
   char fullName[MAX_NAME_LEN];
   char myDirName[MAX_NAME_LEN];
   char myFileName[MAX_NAME_LEN];
   int printCount=0, i;
   char *tags[30];

   char tmpStr[MAX_NAME_LEN];
   rodsObjStat_t *rodsObjStatOut;

   RE_TEST_MACRO ("    Calling GetDataObjAIP")

   if (rei == NULL || rei->rsComm == NULL) {
	rodsLog (LOG_ERROR,
	  "msiGetDataObjAIP: input rei or rsComm is NULL");
	return (SYS_INTERNAL_NULL_INPUT_ERR);
   }

   rsComm = rei->rsComm;

   /* parse inpParam1 */
   rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);

   if (rei->status < 0) {
	rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
          "msiGetDataObjAIP: input inpParam1 error. status = %d", rei->status);
	return (rei->status);
   }

   /* Extract cwd name and object name */
   strncpy(fullName, myDataObjInp->objPath, MAX_NAME_LEN);
   rei->status = splitPathByKey(fullName, myDirName, myFileName, '/');


   /* buffer init */
   mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
   memset (mybuf, 0, sizeof (bytesBuf_t));


   /* Prepare XML output */
   appendStrToBBuf(mybuf, "<?xml version='1.0' encoding='utf-8'?>\n");
   appendStrToBBuf(mybuf, "<!-- Generated by SDSC iRODS (http://www.irods.org) -->\n");
   appendStrToBBuf(mybuf, "<AIP>\n");


   /* First we're going to query the ICAT for system metadata */
   tags[0]=strdup("");
   tags[1]=strdup("D_DATA_ID");
   tags[2]=strdup("D_COLL_ID");
   tags[3]=strdup("DATA_NAME");
   tags[4]=strdup("DATA_REPL_NUM");
   tags[5]=strdup("DATA_VERSION");
   tags[6]=strdup("DATA_TYPE_NAME");
   tags[7]=strdup("DATA_SIZE");
   tags[8]=strdup("D_RESC_GROUP_NAME");
   tags[9]=strdup("D_RESC_NAME");
   tags[10]=strdup("D_DATA_PATH");
   tags[11]=strdup("D_OWNER_NAME");
   tags[12]=strdup("D_OWNER_ZONE");
   tags[13]=strdup("D_REPL_STATUS");
   tags[14]=strdup("D_DATA_STATUS");
   tags[15]=strdup("D_DATA_CHECKSUM");
   tags[16]=strdup("D_EXPIRY");
   tags[17]=strdup("D_MAP_ID");
   tags[18]=strdup("D_COMMENTS");
   tags[19]=strdup("D_CREATE_TIME");
   tags[20]=strdup("D_MODIFY_TIME");


   memset (&genQueryInp, 0, sizeof (genQueryInp_t));

   i1a[0]=COL_D_DATA_ID;
   i1a[1]=COL_D_COLL_ID;
   i1a[2]=COL_DATA_NAME;
   i1a[3]=COL_DATA_REPL_NUM;
   i1a[4]=COL_DATA_VERSION;
   i1a[5]=COL_DATA_TYPE_NAME;
   i1a[6]=COL_DATA_SIZE;
   i1a[7]=COL_D_RESC_GROUP_NAME;
   i1a[8]=COL_D_RESC_NAME;
   i1a[9]=COL_D_DATA_PATH;
   i1a[10]=COL_D_OWNER_NAME;
   i1a[11]=COL_D_OWNER_ZONE;
   i1a[12]=COL_D_REPL_STATUS;
   i1a[13]=COL_D_DATA_STATUS;
   i1a[14]=COL_D_DATA_CHECKSUM;
   i1a[15]=COL_D_EXPIRY;
   i1a[16]=COL_D_MAP_ID;
   i1a[17]=COL_D_COMMENTS;
   i1a[18]=COL_D_CREATE_TIME;
   i1a[19]=COL_D_MODIFY_TIME;

   for (i=0; i<20; i++) {
   i1b[i]=0; /* currently unused */
   }

   genQueryInp.selectInp.inx = i1a;
   genQueryInp.selectInp.value = i1b;
   genQueryInp.selectInp.len = 20;


   i2a[0]=COL_COLL_NAME;
   sprintf(v1,"='%s'",myDirName);
   condVal[0]=v1;

   i2a[1]=COL_DATA_NAME;
   sprintf(v2,"='%s'",myFileName);
   condVal[1]=v2;

   genQueryInp.sqlCondInp.inx = i2a;
   genQueryInp.sqlCondInp.value = condVal;
   genQueryInp.sqlCondInp.len=2;

   genQueryInp.maxRows=30;
   genQueryInp.continueInx=0;
   genQueryInp.condInput.len=0;


   /* First rsGenQuery() call for system metadata */
   rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);




   /* Parse and print out results */
   if (rei->status == CAT_NO_ROWS_FOUND) {
      i1a[0]=COL_D_DATA_PATH;
      genQueryInp.selectInp.len = 1;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      if (rei->status==0) {
	 printf("None\n");
	 return(0);
      }
      if (rei->status == CAT_NO_ROWS_FOUND) {

	rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
          "msiGetDataObjAIP: DataObject %s not found. status = %d", fullName, rei->status);
	return (rei->status);
      }
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }
   else {
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }

   while (rei->status==0 && genQueryOut->continueInx > 0) {
      genQueryInp.continueInx=genQueryOut->continueInx;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      printCount+= genQueryOutToXML(genQueryOut, mybuf, tags);
   }


  /* Now we're going to query the ICAT for user defined metadata. One hit = one AVU triplet */
   tags[0]=strdup("AVU");
   tags[1]=strdup("attribute");
   tags[2]=strdup("value");
   tags[3]=strdup("units");

   memset (&genQueryInp, 0, sizeof (genQueryInp_t));

   i1a[0]=COL_META_DATA_ATTR_NAME;
   i1b[0]=0; /* currently unused */
   i1a[1]=COL_META_DATA_ATTR_VALUE;
   i1b[1]=0; /* currently unused */
   i1a[2]=COL_META_DATA_ATTR_UNITS;
   i1b[2]=0; /* currently unused */
   genQueryInp.selectInp.inx = i1a;
   genQueryInp.selectInp.value = i1b;
   genQueryInp.selectInp.len = 3;

   /* Extract cwd name and object name */
   strncpy(fullName, myDataObjInp->objPath, MAX_NAME_LEN);
   rei->status = splitPathByKey(fullName, myDirName, myFileName, '/');

   i2a[0]=COL_COLL_NAME;
   sprintf(v1,"='%s'",myDirName);
   condVal[0]=v1;

   i2a[1]=COL_DATA_NAME;
   sprintf(v2,"='%s'",myFileName);
   condVal[1]=v2;


   genQueryInp.sqlCondInp.inx = i2a;
   genQueryInp.sqlCondInp.value = condVal;
   genQueryInp.sqlCondInp.len=2;

   genQueryInp.maxRows=10;
   genQueryInp.continueInx=0;
   genQueryInp.condInput.len=0;

   /* rsGenQuery() call for user defined metadata */
   rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);

   /* Parse and print out results */
   if (rei->status == CAT_NO_ROWS_FOUND) {
      i1a[0]=COL_D_DATA_PATH;
      genQueryInp.selectInp.len = 1;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      if (rei->status==0) {
	 printf("None\n");
	 return(0);
      }
      if (rei->status == CAT_NO_ROWS_FOUND) {

	rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
          "msiGetDataObjAVUs: DataObject %s not found. status = %d", fullName, rei->status);
	return (rei->status);
      }
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }
   else {
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }

   while (rei->status==0 && genQueryOut->continueInx > 0) {
      genQueryInp.continueInx=genQueryOut->continueInx;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      printCount+= genQueryOutToXML(genQueryOut, mybuf, tags);
   }

    /* Same thing again, but this time for user access */
    tags[0]=strdup("ACL");
    tags[1]=strdup("COL_DATA_ACCESS_TYPE");
    tags[2]=strdup("COL_DATA_ACCESS_NAME");
    tags[3]=strdup("COL_DATA_TOKEN_NAMESPACE");
    tags[4]=strdup("COL_DATA_ACCESS_USER_IDM");
    tags[5]=strdup("COL_DATA_ACCESS_DATA_ID");

    memset (&genQueryInp, 0, sizeof (genQueryInp_t));

    rei->status = rsObjStat(rsComm, &dataObjInp, &rodsObjStatOut);

    addInxIval (&genQueryInp.selectInp, COL_USER_NAME, 1);
    addInxIval (&genQueryInp.selectInp, COL_DATA_ACCESS_NAME, 1);

    snprintf (tmpStr, MAX_NAME_LEN, " = '%s'", rodsObjStatOut->dataId);

    addInxVal (&genQueryInp.sqlCondInp, COL_DATA_ACCESS_DATA_ID, tmpStr);

    snprintf (tmpStr, MAX_NAME_LEN, "='%s'", "access_type");

    /* Currently necessary since other namespaces exist in the token table */
    addInxVal (&genQueryInp.sqlCondInp, COL_DATA_TOKEN_NAMESPACE, tmpStr);

    genQueryInp.maxRows = MAX_SQL_ROWS;

    rei->status =  rsGenQuery (rsComm, &genQueryInp, &genQueryOut);

   /* Parse and print out results */
   if (rei->status == CAT_NO_ROWS_FOUND) {
      i1a[0]=COL_D_DATA_PATH;
      genQueryInp.selectInp.len = 1;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      if (rei->status==0) {
	 printf("None\n");
	 return(0);
      }
      if (rei->status == CAT_NO_ROWS_FOUND) {

	rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
          "msiGetDataObjAIP: DataObject %s not found. status = %d", fullName, rei->status);
	return (rei->status);
      }
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }
   else {
      printCount+=genQueryOutToXML(genQueryOut, mybuf, tags);
   }

   while (rei->status==0 && genQueryOut->continueInx > 0) {
      genQueryInp.continueInx=genQueryOut->continueInx;
      rei->status = rsGenQuery(rsComm, &genQueryInp, &genQueryOut);
      printCount+= genQueryOutToXML(genQueryOut, mybuf, tags);
   }


  /* Closing tag */
  appendStrToBBuf(mybuf, "</AIP>\n");


  fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);

  return (rei->status);

}



/**
 * \fn msiGetDataObjACL(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Gets ACL (Access Control List) for a data object.
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note Gets ACL (Access Control List) for a data object.
 *    The results are returned in a pipe-separated format.
 *
 * \usage None
 *
 * \param[in] inpParam - A DataObjInp_MS_T or a STR_MS_T with the irods path of the target object.
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetDataObjACL(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm; 
	dataObjInp_t dataObjInp, *myDataObjInp;
	bytesBuf_t *mybuf;
	
	
	RE_TEST_MACRO ("    Calling msiGetDataObjACL")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiGetDataObjACL: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;
	
	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));

	
	/* parse inpParam */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetDataObjACL: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}


	/* call getDataObjACL() */
	getDataObjACL(myDataObjInp, mybuf, rsComm);
	

	/* send results out to outParam */
	fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);
	
	return (rei->status);

}



/**
 * \fn msiGetCollectionACL(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Gets ACL (Access Control List) for a collection.
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  Antoine de Torcy
 * \date    2007-09-26
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note Gets ACL (Access Control List) for a data object.
 *    The results are returned in a pipe-separated format.
 *
 * \usage
 * testrule||msiGetCollectionACL(*objPath, null, *Status)##writeLine(stdout,"")|nop
 * *objPath=/tempZone/home/test.txt
 * ruleExecOut
 *
 * \param[in] inpParam1 - A CollInp_MS_T or a STR_MS_T with the irods path of the target collection.
 * \param[in] inpParam2 - Optional - A STR_MS_T. Set it to "recursive" to perform the operation recursively. 
 * \param[out] outParam - A BUF_LEN_MS_T containing the results.
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetCollectionACL(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm; 
	collInp_t collInpCache, *outCollInp;
	bytesBuf_t *mybuf;
	
	
	RE_TEST_MACRO ("    Calling msiGetCollectionACL")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiGetCollectionACL: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;
	
	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));	


	/* parse inpParam1 */
	rei->status = parseMspForCollInp (inpParam1, &collInpCache, &outCollInp, 0);
	
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetCollectionACL: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}

	
	/* call getCollectionACL() */
	rei->status = getCollectionACL(outCollInp, inpParam2->inOutStruct, mybuf, rsComm);
	

	/* send results out to outParam */
	fillBufLenInMsParam (outParam, strlen(mybuf->buf), mybuf);
	
	return (rei->status);

}



/**
 * \fn msiGetUserInfo (msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief   This function gets information about a user
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  
 * \date  
 *
 * \remark Jewel Ward - msi documentation, 2009-06-18
 * \remark Terrell Russell - reviewed msi documentation, 2009-06-25
 *
 * \note
 *
 * \usage
 * 
 * As seen in modules/ERA/test/getUserInfo.ir
 * 
 * testrule||msiGetUserInfo(*Username,*BUF,*Status)##writeBytesBuf(stdout,*BUF)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 *
 * \param[in] inpParam1 - a msParam of type STR_MS_T
 * \param[in] inpParam2 - a msParam of type BUF_LEN_MS_T
 * \param[out] outParam - a msParam of operation status INT_MS_T
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence 
 * \DolVarModified 
 * \iCatAttrDependence 
 * \iCatAttrModified 
 * \sideeffect 
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetUserInfo(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm; 
	char *userNameInp;
	bytesBuf_t *mybuf;
	
	
	RE_TEST_MACRO ("    Calling msiGetUserInfo")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiGetUserInfo: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;
	
	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));	


	/* parse inpParam1 (username input string) */
	if ((userNameInp = parseMspForStr (inpParam1)) == NULL) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetUserInfo: parseMspForStr error for param 1.");
		return (rei->status);
	}

	
	/* call getUserInfo() */
	rei->status = getUserInfo(userNameInp, mybuf, rsComm);

	/* failure? */
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetUserInfo: getUserInfo failed for %s, status = %d", userNameInp, rei->status);
	}


	/* return operation status through outParam */
	fillIntInMsParam (outParam, rei->status);

	/* send result buffer, even if length is 0, to inParam2 */
	fillBufLenInMsParam (inpParam2, strlen(mybuf->buf), mybuf);
	
	return (rei->status);

}



/**
* \fn msiCreateUserAccountsFromDataObj (msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
*
* \brief   This creates a new user from information in an existing iRODS data object
*
* \module ERA  
*
* \since pre-2.1
*
* \author  
* \date  
*
* \remark Jewel Ward - msi documentation, 2009-06-18
* \remark Terrell Russell - reviewed msi documentation, 2009-06-25
*
* \note
*
* \usage
* 
* As seen in modules/ERA/test/loadUserAccounts.ir
*
* testrule||msiCreateUserAccountsFromDataObj(*ObjPath,*Status)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
*
* \param[in] inpParam - a msParam of type DataObjInp_MS_T or STR_MS_T
* \param[out] outParam - a msParam of operation status INT_MS_T
* \param[in,out] rei - Required - the RuleExecInfo structure
*
* \DolVarDependence 
* \DolVarModified 
* \iCatAttrDependence 
* \iCatAttrModified 
* \sideeffect 
*
* \return integer
* \retval 0 on success
* \pre
* \post
* \sa
* \bug  no known bugs
**/
int
msiCreateUserAccountsFromDataObj(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	dataObjInp_t dataObjInp, *myDataObjInp;
	generalAdminInp_t generalAdminInp;
	rsComm_t *rsComm;

	
	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiCreateUserAccountsFromDataObj")


	/* Sanity checks */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiCreateUserAccountsFromDataObj: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}

	rsComm = rei->rsComm;	
	
	/* parse inpParam1 */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiCreateUserAccountsFromDataObj: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}

	
	/* init generalAdminInp input */
	memset (&generalAdminInp, 0, sizeof(generalAdminInp_t));
	generalAdminInp.arg0 = "add";
	generalAdminInp.arg1 = "user";


	/* call genAdminOpFromDataObj() */
	rei->status = genAdminOpFromDataObj(myDataObjInp, &generalAdminInp, rsComm);
	
	/* send status out to outParam */
	fillIntInMsParam(outParam, rei->status);

	return (rei->status);
}



/**
 * \fn msiLoadUserModsFromDataObj (msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief   This microservice modifies user information from information in an iRODS data object
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  
 * \date  
 *
 * \remark Jewel Ward - msi documentation, 2009-06-10
 * \remark Terrell Russell - reviewed msi documentation, 2009-06-25
 *
 * \note
 *
 * \usage
 * 
 * As seen in modules/ERA/test/modUserAccounts.ir
 *
 * testrule||msiLoadUserModsFromDataObj(*ObjPath,*Status)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 * *ObjPath=/tempZone/home/rods/user_mods.txt
 * ruleExecOut
 *
 * \param[in] inpParam - a msParam of type DataObjInp_MS_T or STR_MS_T
 * \param[out] outParam - a msParam of operation status INT_MS_T
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence 
 * \DolVarModified 
 * \iCatAttrDependence 
 * \iCatAttrModified 
 * \sideeffect 
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiLoadUserModsFromDataObj(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	dataObjInp_t dataObjInp, *myDataObjInp;
	generalAdminInp_t generalAdminInp;
	rsComm_t *rsComm;

	
	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiLoadUserModsFromDataObj")


	/* Sanity checks */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiLoadUserModsFromDataObj: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}

	rsComm = rei->rsComm;	
	
	/* parse inpParam1 */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiLoadUserModsFromDataObj: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}


	/* init generalAdminInp input */
	memset (&generalAdminInp, 0, sizeof(generalAdminInp_t));
	generalAdminInp.arg0 = "modify";
	generalAdminInp.arg1 = "user";


	/* call genAdminOpFromDataObj() */
	rei->status = genAdminOpFromDataObj(myDataObjInp, &generalAdminInp, rsComm);
	
	/* send status out to outParam */
	fillIntInMsParam(outParam, rei->status);

	return (rei->status);
}



/**
 * \fn msiDeleteUsersFromDataObj (msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief   This microservice will parse an iRODS object for user accounts to delete.
 *
 * \module ERA  
 *
 * \since pre-2.1
 *
 * \author  
 * \date  
 *
 * \remark Jewel Ward - msi documentation, 2009-06-18
 * \remark Terrell Russell - reviewed msi documentation, 2009-06-25
 *
 * \note
 *
 * \usage
 * 
 * As seen in modules/ERA/test/deleteUserAccounts.ir
 *
 * testrule||msiDeleteUsersFromDataObj(*ObjPath,*Status)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 *
 * \param[in] inpParam - a msParam of type DataObjInp_MS_T or STR_MS_T
 * \param[out] outParam - a msParam of operation status INT_MS_T
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence 
 * \DolVarModified 
 * \iCatAttrDependence 
 * \iCatAttrModified 
 * \sideeffect 
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiDeleteUsersFromDataObj(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	dataObjInp_t dataObjInp, *myDataObjInp;
	generalAdminInp_t generalAdminInp;
	rsComm_t *rsComm;

	
	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiDeleteUsersFromDataObj")


	/* Sanity checks */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiDeleteUsersFromDataObj: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}

	rsComm = rei->rsComm;	
	
	/* parse inpParam */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiDeleteUsersFromDataObj: input inpParam error. status = %d", rei->status);
		return (rei->status);
	}


	/* init generalAdminInp input */
	memset (&generalAdminInp, 0, sizeof(generalAdminInp_t));
	generalAdminInp.arg0 = "rm";
	generalAdminInp.arg1 = "user";


	/* call genAdminOpFromDataObj() */
	rei->status = genAdminOpFromDataObj(myDataObjInp, &generalAdminInp, rsComm);
	
	/* send status out to outParam */
	fillIntInMsParam(outParam, rei->status);

	return (rei->status);
}



/**
 * \fn msiLoadACLFromDataObj (msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief   This microservice parses an iRODS object for access permissions to update/create.
 *
 * \module ERA
 *
 * \since pre-2.1
 *
 * \author  
 * \date   
 *
 * \remark Jewel Ward - msi documentation, 2009-06-10
 * \remark Terrell Russell - reviewed msi documentation, 2009-06-25
 *
 * \note
 *
 * \usage
 * 
 *  As seen in modules/ERA/test/addACL.ir
 * 
 *  testrule||msiLoadACLFromDataObj(*ObjPath,*Status)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 *  *ObjPath=/tempZone/home/antoine/addACL.txt
 *  ruleExecOut
 *  
 * \param[in] inpParam - a msParam of type DataObjInp_MS_T or STR_MS_T
 * \param[out] outParam - status as a msParam of type INT_MS_T
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence 
 * \DolVarModified 
 * \iCatAttrDependence 
 * \iCatAttrModified 
 * \sideeffect 
 *
 * \return integer
 * \retval 0 on success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiLoadACLFromDataObj(msParam_t *inpParam, msParam_t *outParam, ruleExecInfo_t *rei)
{
	dataObjInp_t dataObjInp, *myDataObjInp;
	rsComm_t *rsComm;

	
	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiLoadACLFromDataObj")


	/* Sanity checks */
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiLoadACLFromDataObj: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}

	rsComm = rei->rsComm;	
	
	/* parse inpParam */
	rei->status = parseMspForDataObjInp (inpParam, &dataObjInp, &myDataObjInp, 0);
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiLoadACLFromDataObj: input inpParam error. status = %d", rei->status);
		return (rei->status);
	}


	/* call loadACLFromDataObj() */
	rei->status = loadACLFromDataObj(myDataObjInp, rsComm);
	
	/* send status out to outParam */
	fillIntInMsParam(outParam, rei->status);

	return (rei->status);
}



/**
 * \fn msiGetUserACL(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Gets ACL for a single user
 *
 * \module ERA
 *
 * \since 
 *
 * \author  
 * \date    
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note
 *
 * \usage
 * As seen in modules/ERA/test/getUserACL.ir
 *
 * testrule||msiGetUserACL(*Username,*BUF,*Status)##writeBytesBuf(stdout,*BUF)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 * *Username=theusername
 * ruleExecOut
 *
 * \param[in] inpParam1 - A STR_MS_T containing the username
 * \param[in] inpParam2 - A BUF_LEN_MS_T containing the ACL results in pipe delimited form
 * \param[out] outParam - an INT_MS_T containing the status
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 upon success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGetUserACL(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	rsComm_t *rsComm; 
	char *userNameInp;
	bytesBuf_t *mybuf;
	
	
	RE_TEST_MACRO ("    Calling msiGetUserACL")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiGetUserACL: input rei or rsComm is NULL");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	rsComm = rei->rsComm;
	
	/* buffer init */
	mybuf = (bytesBuf_t *)malloc(sizeof(bytesBuf_t));
	memset (mybuf, 0, sizeof (bytesBuf_t));


	/* parse inpParam1 (username input string) */
	if ((userNameInp = parseMspForStr (inpParam1)) == NULL) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetUserACL: parseMspForStr error for param 1.");
		return (rei->status);
	}

	
	/* call getUserACL() */
	rei->status = getUserACL(userNameInp, mybuf, rsComm);

	/* failure? */
	if (rei->status < 0) {
		rodsLogAndErrorMsg (LOG_ERROR, &rsComm->rError, rei->status,
			"msiGetUserACL: getUserACL failed for %s, status = %d", userNameInp, rei->status);
	}


	/* return operation status through outParam */
	fillIntInMsParam (outParam, rei->status);

	/* send result buffer, even if length is 0, to inpParam2 */
	fillBufLenInMsParam (inpParam2, strlen(mybuf->buf), mybuf);
	
	return (rei->status);

}



/**
 * \fn msiSetDataType(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *inpParam3, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Sets the data_type_name attribute of a data object
 *
 * \module ERA
 *
 * \since 
 *
 * \author  
 * \date    
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note
 *
 * \usage
 * As seen in modules/ERA/test/setDataTypeForObjPath.ir
 *
 * testrule||msiSetDataType(null,*objPath,Text,*Status)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 * *objPath=/tempZone/home/test/tmp.txt
 * ruleExecOut
 *
 * \param[in] inpParam1 - A STR_MS_T containing the object ID
 * \param[in] inpParam2 - A STR_MS_T containing the object's iRODS path
 * \param[in] inpParam3 - A STR_MS_T containing the data type to be set
 * \param[out] outParam - an INT_MS_T containing the status
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 upon success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiSetDataType(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *inpParam3, msParam_t *outParam, ruleExecInfo_t *rei)
{
	char *dataTypeStr, *dataIdStr;		/* for parsing of input params */
	dataObjInp_t dataObjInp, *myDataObjInp;
	
	modDataObjMeta_t modDataObjMetaInp;	/* for rsModDataObjMeta() */
	dataObjInfo_t dataObjInfo;		/* for rsModDataObjMeta() */
	keyValPair_t regParam;			/* for rsModDataObjMeta() */
	
	
	RE_TEST_MACRO ("    Calling msiSetDataType")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiSetDataType: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}


	/* parse inpParam1: data object ID */
	if ((dataIdStr = parseMspForStr(inpParam1)) != NULL)  {
		dataObjInfo.dataId = (rodsLong_t) atoll(dataIdStr);
	}


	/* parse inpParam2: data object path */
	if ( parseMspForDataObjInp (inpParam2, &dataObjInp, &myDataObjInp, 0) >= 0) {
		strncpy(dataObjInfo.objPath, dataObjInp.objPath, MAX_NAME_LEN);
	}


	/* make sure to have at least data ID or path */
	if (!(dataIdStr || dataObjInfo.objPath)) {
		rodsLog (LOG_ERROR, "msiSetDataType: No data object ID or path provided.");
		return (USER__NULL_INPUT_ERR);
	}


	/* parse inpParam3: data type string */
	if ((dataTypeStr = parseMspForStr (inpParam3)) == NULL) {
		rodsLog (LOG_ERROR, "msiSetDataType: parseMspForStr error for param 3.");
		return (USER__NULL_INPUT_ERR);
	}
	memset (&regParam, 0, sizeof (regParam));
	addKeyVal (&regParam, DATA_TYPE_KW, dataTypeStr);

	
	/* call rsModDataObjMeta() */
	modDataObjMetaInp.dataObjInfo = &dataObjInfo;
	modDataObjMetaInp.regParam = &regParam;
	rei->status = rsModDataObjMeta (rei->rsComm, &modDataObjMetaInp);


	/* failure? */
	if (rei->status < 0) {
		if (dataObjInfo.objPath) {
			rodsLog (LOG_ERROR, "msiSetDataType: rsModDataObjMeta failed for object %s, status = %d", dataObjInfo.objPath, rei->status);
		}
		else {
			rodsLog (LOG_ERROR, "msiSetDataType: rsModDataObjMeta failed for object ID %d, status = %d", dataObjInfo.dataId, rei->status);
		}
	}


	/* return operation status through outParam */
	fillIntInMsParam (outParam, rei->status);
	
	return (rei->status);

}



/**
 * \fn msiGuessDataType(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
 *
 * \brief Guesses the data type of an object based on its file extension
 *
 * \module ERA
 *
 * \since 
 *
 * \author  
 * \date    
 *
 * \remark Terrell Russell - msi documentation, 2009-06-17
 *
 * \note
 *
 * \usage
 * As seen in modules/ERA/test/guessDataType.ir
 *
 * testrule||msiGuessDataType(*objPath,*dataType,*Status)##writeLine(stdout,*dataType)##writePosInt(stdout,*Status)##writeLine(stdout,"")|nop
 * *objPath=/tempZone/home/test/tmp.txt
 * ruleExecOut
 *
 * \param[in] inpParam1 - A STR_MS_T containing the object's iRODS path
 * \param[in] inpParam2 - A STR_MS_T to be filled with the object's data type
 * \param[out] outParam - an INT_MS_T containing the status
 * \param[in,out] rei - The RuleExecInfo structure that is automatically
 *    handled by the rule engine. The user does not include rei as a
 *    parameter in the rule invocation.
 *
 * \DolVarDependence
 * \DolVarModified
 * \iCatAttrDependence
 * \iCatAttrModified
 * \sideeffect
 *
 * \return integer
 * \retval 0 upon success
 * \pre
 * \post
 * \sa
 * \bug  no known bugs
**/
int
msiGuessDataType(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	char *pathStr, *extStr;			/* for parsing of input params */
	dataObjInp_t dataObjInp, *myDataObjInp;
	
	genQueryInp_t genQueryInp;		/* for query inputs */
	char condStr[MAX_NAME_LEN];		/* for query condition */
	genQueryOut_t *genQueryOut;		/* for query results */
	sqlResult_t *sqlResult;			/* for query results */

	
	RE_TEST_MACRO ("    Calling msiGuessDataType")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiGuessDataType: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}


	/* parse inpParam1: data object path */
	rei->status = parseMspForDataObjInp (inpParam1, &dataObjInp, &myDataObjInp, 0);
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiGuessDataType: No data object path provided.");
		return (rei->status);
	}	
	pathStr = dataObjInp.objPath;

	
	/* get the file extension. If no extension, data type is 'generic' */
	extStr = strrchr(pathStr, '.');
	if (!extStr) {
		fillStrInMsParam (inpParam2, "generic");
		fillIntInMsParam (outParam, 0);
		return (0);
	}


	/* prepare query */
	memset (&genQueryInp, 0, sizeof (genQueryInp_t));
	genQueryInp.maxRows = MAX_SQL_ROWS;

	/* wanted fields */
	addInxIval (&genQueryInp.selectInp, COL_TOKEN_NAME, 1);
	addInxIval (&genQueryInp.selectInp, COL_TOKEN_ID, ORDER_BY);  /* to get the lowest token ID first */

	/* make the condition */
	snprintf (condStr, MAX_NAME_LEN, " like '%%|%s|%%'", extStr);
	addInxVal (&genQueryInp.sqlCondInp, COL_TOKEN_VALUE2, condStr);

	
	/* ICAT query for token name */
	rei->status = rsGenQuery (rei->rsComm, &genQueryInp, &genQueryOut);


	/* no result is not considered an error here. Return 'generic' which is the default data type */
	if (rei->status == CAT_NO_ROWS_FOUND) {
		fillStrInMsParam (inpParam2, "generic");
		fillIntInMsParam (outParam, rei->status);
		return (0);
	}


	/* failure? */
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiGuessDataType: rsGenQuery failed for object %s, status = %d", pathStr, rei->status);
	}


	/* retrieve and send data type */
	sqlResult = getSqlResultByInx(genQueryOut, COL_TOKEN_NAME);
	fillStrInMsParam (inpParam2, sqlResult->value);


	/* clean up rows in the pipeline */
	genQueryInp.maxRows = -1;
	genQueryInp.continueInx=genQueryOut->continueInx;
	rsGenQuery (rei->rsComm, &genQueryInp, &genQueryOut);


	/* return operation status through outParam */
	fillIntInMsParam (outParam, rei->status);
	
	return (rei->status);

}



/**
 * \fn msiMergeDataCopies
 * \author  Antoine de Torcy
 * \date   2009-05-22
 * \brief Custom microservice for NARA consolidation rule.
 * \note  Custom microservice for NARA consolidation rule.
 *	Takes an object, a current home collection and a master collection:
 *	1) If the object is an orphan (no corresponding object in the master collection) 
 *	it is moved to the master collection.
 *	2) If there is a corresponding object in the master collection, their 
 *	checksums are compared.
 *		2a)	If the checksums match the object is registered as a replica of 
 *			the master object. Its physical file is rearranged accordingly to ensure
 *			consistency between logical and physical paths. 
 *		2b)	If the checksums do not match the object is flagged for manual check:
 *			It gets a new metadata attribute whose name is "CHECKSUM_MISMATCH" and
 *			whose value is the checksum of the master object.
 * \param[in] 
 *    objPath - a DataObjInp_MS_T or a STR_MS_T with the target object's path.
 *	  currentColl - A CollInp_MS_T or a STR_MS_T with the current collection's path.
 *	  masterColl - A CollInp_MS_T or a STR_MS_T with the master collection's path.
 * \param[out] 
 *    status - an INT_MS_T containing the operation status.
 * \return integer
 * \retval 0 on success
 * \sa
 * \post
 * \pre
 * \bug  no known bugs
**/
int
msiMergeDataCopies(msParam_t *objPath, msParam_t *currentColl, msParam_t *masterColl, msParam_t *status, ruleExecInfo_t *rei)
{
	dataObjInp_t currentObjInpCache, *currentObjInp;	/* for parsing and manipulating current object */
	dataObjInp_t masterObjInp;	 						/* for manipulating master object */
	collInp_t currentCollInpCache, *currentCollInp;		/* for parsing current coll path */
	collInp_t masterCollInpCache, *masterCollInp;		/* for parsing master coll path */
	dataObjCopyInp_t dataObjRenameInp;					/* input for rsDataObjRename() */
	
    execCmd_t execCmdInp;								/* input and output of rsExecCmd() */
    execCmdOut_t *execCmdOut = NULL;
    
    char tmpPath[MAX_NAME_LEN], *tmpPtr;				/* placeholder for temporary paths */
    
    collInp_t collCreateInp;							/* for creating missing parent collections under master coll */
    
    dataObjInfo_t *currentDataObjInfo = NULL;			/* output of getDataObjInfo, and destination input for rsRegReplica() */
    dataObjInfo_t *masterDataObjInfo = NULL;			/* source input for rsRegReplica() */
    
    regReplica_t regReplicaInp;							/* input for rsRegReplica() */
    
	rodsLong_t masterObjId = -1;						/* master object ID */
	char *objChksm = NULL, *masterChksm = NULL;			/* object checksums */
		
	modAVUMetadataInp_t modAVUMetadataInp;				/* for new AVU creation */
	

	/************************************* INIT **********************************/
	
	/* For testing mode when used with irule --test */
	RE_TEST_MACRO ("    Calling msiMergeDataCopies")
	
	
	/* Sanity test */
	if (rei == NULL || rei->rsComm == NULL) {
			rodsLog (LOG_ERROR, "msiMergeDataCopies: input rei or rsComm is NULL.");
			return (SYS_INTERNAL_NULL_INPUT_ERR);
	}
	
	
	/********************************** PARAM PARSING  *********************************/
	
	/* Parse objPath */
	rei->status = parseMspForDataObjInp (objPath, &currentObjInpCache, &currentObjInp, 0);
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiMergeDataCopies: input objPath error. status = %d", rei->status);
		return (rei->status);
	}
	

	/* Parse current collection input */
	rei->status = parseMspForCollInp (currentColl, &currentCollInpCache, &currentCollInp, 0);
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiMergeDataCopies: input currentColl error. status = %d", rei->status);
		return (rei->status);
	}
	

	/* Parse master collection input */
	rei->status = parseMspForCollInp (masterColl, &masterCollInpCache, &masterCollInp, 0);
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiMergeDataCopies: input masterColl error. status = %d", rei->status);
		return (rei->status);
	}

	
	/* Check for null input */
    if (!strlen(currentObjInp->objPath) || !strlen(currentCollInp->collName) || !strlen(masterCollInp->collName) ) 
    {
    	rei->status = USER__NULL_INPUT_ERR;
		rodsLog (LOG_ERROR, "msiMergeDataCopies: Missing input. status = %d", rei->status);
		return (rei->status);
    }
    
    
    /******************************** OBJECT IS AN ORPHAN *******************************/
    
    /* Substitute current collection with master collection in object path, and write to master object path */
    memset (&masterObjInp, 0, sizeof(dataObjInp_t));
    snprintf(masterObjInp.objPath, MAX_NAME_LEN, "%s/%s", masterCollInp->collName, 
    	currentObjInp->objPath + strlen(currentCollInp->collName) + 1);
    	
    /* Look if master object path is valid */
    rei->status = isData (rei->rsComm, masterObjInp.objPath, &masterObjId);
    
    /* If not, move the object to the master collection */
    if (masterObjId <= 0)
    {
    	/* Create missing parent collections if needed */
    	memset (&collCreateInp, 0, sizeof(collInp_t));
    	addKeyVal (&collCreateInp.condInput, RECURSIVE_OPR__KW, "");
    	
    	/* Separate parent collection from target object */
    	strncpy (collCreateInp.collName, masterObjInp.objPath, MAX_NAME_LEN-1);
    	tmpPtr = strrchr(collCreateInp.collName, '/');
    	*tmpPtr = '\0';

		/* Invoke rsCollCreate */
    	rei->status = rsCollCreate (rei->rsComm, &collCreateInp);
    	if (rei->status < 0) {
			rodsLog (LOG_ERROR, "msiMergeDataCopies: rsCollCreate error. status = %d", rei->status);
			return (rei->status);
		}
    	
    	
    	/* Set up the source and destination fields of our dataObjCopyInp_t */
    	memset (&dataObjRenameInp, 0, sizeof(dataObjCopyInp_t));
    	strncpy (dataObjRenameInp.srcDataObjInp.objPath, currentObjInp->objPath, MAX_NAME_LEN-1);
    	strncpy (dataObjRenameInp.destDataObjInp.objPath, masterObjInp.objPath, MAX_NAME_LEN-1);
    	
    	/* Invoke rsDataObjRename */
    	rei->status = rsDataObjRename (rei->rsComm, &dataObjRenameInp);
    	
    	/* And we're done */
    	fillIntInMsParam (status, rei->status);
		return (rei->status);
    }


    /******************************** COMPARE AND MERGE COPIES *******************************/
    
    /* Get checksum of current object */
    rei->status = rsDataObjChksum (rei->rsComm, currentObjInp, &objChksm);
    
    /* Get checksum of master object */
    rei->status = rsDataObjChksum (rei->rsComm, &masterObjInp, &masterChksm);
    
    /* Objects must have checksums */
    if ( !(objChksm && strlen(objChksm) && masterChksm && strlen(masterChksm)) )
    {
    	rei->status = USER_CHKSUM_MISMATCH; /* Not ideal but relevant enough... */
		rodsLog (LOG_ERROR, "msiMergeDataCopies: Missing checksum(s). status = %d", rei->status);
		return (rei->status);
    }
    
    
    /* If checksums match, merge copies */
    if (!strcmp(masterChksm, objChksm))
    {
    	/* Get extended info of current and master objects */
    	rei->status = getDataObjInfo(rei->rsComm, currentObjInp, &currentDataObjInfo, ACCESS_READ_OBJECT, 0);
    	rei->status = getDataObjInfo(rei->rsComm, &masterObjInp, &masterDataObjInfo, ACCESS_READ_OBJECT, 0);
    	
    
    	/* We may have to create missing directories on the resource before we can make links */
    	snprintf(tmpPath, MAX_NAME_LEN, "%s/%s", currentDataObjInfo->rescInfo->rescVaultPath, 
    		masterObjInp.objPath + strlen(currentDataObjInfo->rescInfo->zoneName) + 2);
    	
    	/* First, separate file from parent directory in physical path */
    	tmpPtr = &tmpPath[strlen(tmpPath)-1];
    	while (*tmpPtr != '/' && tmpPtr > tmpPath)
    	{
    		tmpPtr--;
    	}
    	*tmpPtr = '\0';
    		
    	
    	/* Set up input for rsExecCmd */
    	memset(&execCmdInp, 0, sizeof(execCmd_t));
    	rstrcpy(execCmdInp.execAddr, currentDataObjInfo->rescInfo->rescLoc, LONG_NAME_LEN);
    	rstrcpy(execCmdInp.cmd, "mkdir", LONG_NAME_LEN);
    	snprintf(execCmdInp.cmdArgv, MAX_NAME_LEN, "-p '%s'", tmpPath);
    	
    	
		/* Invoke rsExecCmd for remote mkdir on resource */
		rei->status = rsExecCmd (rei->rsComm, &execCmdInp, &execCmdOut);
		
		if (rei->status < 0) {
			rodsLog (LOG_ERROR, "msiMergeDataCopies: rsExecCmd failed for %s %s. status = %d", 
				execCmdInp.cmd, execCmdInp.cmdArgv, rei->status);
			return (rei->status);
		}
		
		
		/* Rebuild full target path for hard link */
		*tmpPtr = '/';
		
		/* Reset input for rsExecCmd */
    	memset(&execCmdInp, 0, sizeof(execCmd_t));
    	rstrcpy(execCmdInp.execAddr, currentDataObjInfo->rescInfo->rescLoc, LONG_NAME_LEN);
    	rstrcpy(execCmdInp.cmd, "link", LONG_NAME_LEN);
    	snprintf(execCmdInp.cmdArgv, MAX_NAME_LEN, "'%s' '%s'", currentDataObjInfo->filePath, tmpPath);
    	
    	
    	/* Create hard link on resource */
		rei->status = rsExecCmd (rei->rsComm, &execCmdInp, &execCmdOut);
		
		if (rei->status < 0) {
			rodsLog (LOG_ERROR, "msiMergeDataCopies: rsExecCmd failed for %s %s. status = %d", 
				execCmdInp.cmd, execCmdInp.cmdArgv, rei->status);
			return (rei->status);
		}
		
		
		/* Register new path as replica, and unlink old object */
    	
    	/* Update file and object path in currentDataObjInfo */
		rstrcpy(currentDataObjInfo->filePath, tmpPath, MAX_NAME_LEN);
		rstrcpy(currentDataObjInfo->objPath, masterObjInp.objPath, MAX_NAME_LEN);

 	
    	/* Set up regReplicaInp */
    	memset(&regReplicaInp, 0, sizeof(regReplica_t));
    	regReplicaInp.srcDataObjInfo = masterDataObjInfo;
    	regReplicaInp.destDataObjInfo = currentDataObjInfo;
    	
    	
		/* Invoke rsRegReplica */
		rei->status = rsRegReplica (rei->rsComm, &regReplicaInp);
		
		if (rei->status < 0) {
			rodsLog (LOG_ERROR, "msiMergeDataCopies: rsRegReplica failed for %s. status = %d",
				currentDataObjInfo->filePath, rei->status);
			return (rei->status);
		}
		
		
		/* Unlink old object (for good!) */
		addKeyVal (&currentObjInp->condInput, FORCE_FLAG_KW, ""); 
		rei->status = rsDataObjUnlink (rei->rsComm, currentObjInp);
		
		if (rei->status < 0) {
			rodsLog (LOG_ERROR, "msiMergeDataCopies: rsDataObjUnlink failed for %s. status = %d",
				currentObjInp->objPath, rei->status);
			return (rei->status);
		}
		
		
		/* And if we've made it this far, we're done */
    	fillIntInMsParam (status, rei->status);
		return (rei->status);
        	
    }
    
    
    /*********** FLAG OBJECT WHOSE CHECKSUM DOESN'T MATCH MASTER OBJECT CHECKSUM *************/
    
	/* init modAVU input */
	memset (&modAVUMetadataInp, 0, sizeof(modAVUMetadataInp_t));
	modAVUMetadataInp.arg0 = "add";
	modAVUMetadataInp.arg1 = "-d";
	modAVUMetadataInp.arg2 = currentObjInp->objPath;
	modAVUMetadataInp.arg3 = "CHECKSUM_MISMATCH";
	modAVUMetadataInp.arg4 = masterChksm;
	modAVUMetadataInp.arg5 = NULL;
	
	/* invoke rsModAVUMetadata() */
	rei->status = rsModAVUMetadata (rei->rsComm, &modAVUMetadataInp);
	
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiMergeDataCopies: rsModAVUMetadata failed for %s. status = %d",
			currentObjInp->objPath, rei->status);
	}
    

	/*********************************** DONE ********************************/
	
	/* Return operation status */
	fillIntInMsParam (status, rei->status);

	/* Done */
	return (rei->status);
}


