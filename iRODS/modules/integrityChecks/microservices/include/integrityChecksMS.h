/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/

/**
 * @file	propertiesMS.h
 *
 * @brief	Declarations for the msiProperties* microservices.
 */



#ifndef INTEGRITYCHECKS_H
#define INTEGRITYCHECKS_H

//#include "rods.h"
//#include "rodsDef.h"
//#include "miscUtil.h"
//#include "apiHeaderAll.h"
//#include "objMetaOpr.h"

#include "apiHeaderAll.h"
#include "objMetaOpr.h"
#include "miscUtil.h"


int msiHiThere (ruleExecInfo_t *rei);
int msiCheckFilesizeRange (msParam_t *mPin1, msParam_t *mPin2, msParam_t *mPin3, msParam_t *mPout1, ruleExecInfo_t *rei);
int msiCheckFileDatatypes (msParam_t *mPin1, msParam_t *mPin2, msParam_t *mPout1, ruleExecInfo_t *rei);
int msiListCollection (msParam_t *mPin1, msParam_t *mPout1, ruleExecInfo_t *rei);

int hithere ();

#endif	/* INTEGRITYCHECKS_H */
