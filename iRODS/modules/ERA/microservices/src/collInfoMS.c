/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/

#include "collInfoMS.h"
#include "eraUtil.h"



/*
 * msiGetCollectionContentsReport()
 *
 */
int
msiGetCollectionContentsReport(msParam_t *inpParam1, msParam_t *inpParam2, msParam_t *outParam, ruleExecInfo_t *rei)
{
	collInp_t collInpCache, *outCollInp;	/* for parsing collection input param */

	keyValPair_t *contents;			/* for passing out results */

	char collQCond[2*MAX_NAME_LEN];		/* for condition in rsGenquery() */
	genQueryInp_t genQueryInp;		/* for query inputs */
	genQueryOut_t *genQueryOut;		/* for query results */

	char *resultStringToken;		/* for parsing key-value pairs from genQueryOut */
	char *oldValStr, newValStr[21];		/* for parsing key-value pairs from genQueryOut */
	rodsLong_t newVal;			/* for parsing key-value pairs from genQueryOut */
	sqlResult_t *sqlResult;			/* for parsing key-value pairs from genQueryOut */
	int i;					/* for parsing key-value pairs from genQueryOut */


	RE_TEST_MACRO ("    Calling msiGetCollectionContentsReport")
	
	if (rei == NULL || rei->rsComm == NULL) {
		rodsLog (LOG_ERROR, "msiGetCollectionContentsReport: input rei or rsComm is NULL.");
		return (SYS_INTERNAL_NULL_INPUT_ERR);
	}


	/* parse inpParam1: our target collection */
	rei->status = parseMspForCollInp (inpParam1, &collInpCache, &outCollInp, 0);
	
	if (rei->status < 0) {
		rodsLog (LOG_ERROR, "msiGetCollectionContentsReport: input inpParam1 error. status = %d", rei->status);
		return (rei->status);
	}


	/* allocate memory for our result struct */
	contents = (keyValPair_t*)malloc(sizeof(keyValPair_t));
	memset (contents, 0, sizeof (keyValPair_t));


	/* Wanted fields. We use coll_id to do a join query on r_data_main and r_coll_main */
	memset (&genQueryInp, 0, sizeof (genQueryInp));
	addInxIval (&genQueryInp.selectInp, COL_DATA_TYPE_NAME, 1);
	addInxIval (&genQueryInp.selectInp, COL_D_DATA_ID, 1);
	addInxIval (&genQueryInp.selectInp, COL_COLL_ID, 1);


	/* Make condition for getting all objects under a collection */
	genAllInCollQCond (outCollInp->collName, collQCond);
	addInxVal (&genQueryInp.sqlCondInp, COL_COLL_NAME, collQCond);
	genQueryInp.maxRows = MAX_SQL_ROWS;
	/* genQueryInp.options = RETURN_TOTAL_ROW_COUNT; */


	/* Query */
	rei->status  = rsGenQuery (rei->rsComm, &genQueryInp, &genQueryOut);


	/* Parse results */
	if (rei->status == 0) {

		/* for each row */
		for (i=0;i<genQueryOut->rowCnt;i++) {
	
			/* get COL_DATA_TYPE_NAME result */
			sqlResult = getSqlResultByInx (genQueryOut, COL_DATA_TYPE_NAME);

			/* retrieve value for this row */
			resultStringToken = sqlResult->value + i*sqlResult->len;

			/* have we found this data type before? */
			oldValStr = getValByKey (contents, resultStringToken);
			if (oldValStr) {
				newVal = atoll(oldValStr) + 1;
			}
			else {
				newVal = 1;
			}
		
			/* add data type name along with its total number of occurrences */
			snprintf(newValStr, 21, "%lld", newVal);
			addKeyVal(contents, resultStringToken, newValStr);
		}



		/* not done? */
		while (rei->status==0 && genQueryOut->continueInx > 0) {
			genQueryInp.continueInx=genQueryOut->continueInx;
			rei->status = rsGenQuery(rei->rsComm, &genQueryInp, &genQueryOut);

			/* for each row */
			for (i=0;i<genQueryOut->rowCnt;i++) {
		
				/* get COL_DATA_TYPE_NAME result */
				sqlResult = getSqlResultByInx (genQueryOut, COL_DATA_TYPE_NAME);
	
				/* retrieve value for this row */
				resultStringToken = sqlResult->value + i*sqlResult->len;
	
				/* have we found this data type before? */
				oldValStr = getValByKey (contents, resultStringToken);
				if (oldValStr) {
					newVal = atoll(oldValStr) + 1;
				}
				else {
					newVal = 1;
				}
			
				/* add data type name along with its total number of occurrences */
				snprintf(newValStr, 21, "%lld", newVal);
				addKeyVal(contents, resultStringToken, newValStr);
			}
		}
	}


	/* send results out to outParam */
	fillMsParam (inpParam2, NULL, KeyValPair_MS_T, contents, NULL);


	/* Return operation status through outParam */
	fillIntInMsParam (outParam, rei->status);
	/* fillIntInMsParam (outParam, genQueryOut->totalRowCount); */

	return (rei->status);
}




