//
// Created by eddmash on 11/3/17.
//
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "gdal.h"
#include "pgdal_main.h"


zend_class_entry *gdal_ce;

ZEND_BEGIN_ARG_INFO_EX(arginfo_version_info, 0, 0, 1)
    ZEND_ARG_INFO(0, pszRequest)
ZEND_END_ARG_INFO();

// ---------------------- HELPERS -----------------------

char * getVersionInformation(char * request){
    return (char *)GDALVersionInfo(request);
}

// -----------------STATIC METHODS ---------------------------------
/*
  {{{ proto  getVersionNumber Return the version number
 */
PHP_METHOD(PGdal, getVersionNumber)
{
    RETURN_STRING(getVersionInformation(VERSION_NUM), 0);
}
/* }}} */

/*
 {{{ proto getReleaseDateReturn the Release data
 */
PHP_METHOD(PGdal, getReleaseDate)
{
    RETURN_STRING(getVersionInformation(VERSION_RELEASE_DATE), 0);
}
/*}}}*/

/*
  {{{ proto getReleaseName Return the Release data
 */
PHP_METHOD(PGdal, getReleaseName)
{
    RETURN_STRING(getVersionInformation(VERSION_RELEASE_NAME), 0);
}
/* }}} */

/* {{{
  Return all information or requested information

  Accepts one optional arguement that can either be

  "VERSION_NUM" | "RELEASE_DATE" | "RELEASE_NAME" | "--version" | "LICENCE" | NULL - to return all info
 */
PHP_METHOD(PGdal, getVersionInfo)
{
    char * request;
    int len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|s", &request, &len) == FAILURE) {
        WRONG_PARAM_COUNT;
    }
    RETURN_STRING(getVersionInformation(request), 0);
}
/* }}} */


/* }}} */
const zend_function_entry gdal_methods[] = {
        PHP_ME(PGdal, getVersionInfo, arginfo_version_info, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(PGdal, getVersionNumber, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(PGdal, getReleaseDate, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(PGdal, getReleaseName, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

// ------------------------ CLASS -------------------------------------

void registerGdalClass(){

    // register gdal class
    zend_class_entry tmp_ce;
    INIT_CLASS_ENTRY(tmp_ce, "PGdal", gdal_methods);

    gdal_ce = zend_register_internal_class(&tmp_ce TSRMLS_CC);

}
