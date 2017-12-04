/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "ogr_api.h"
#include "php_pgdal.h"

/* If you declare any globals in php_pgdal.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(pgdal)
*/

/* True global resources - no need for thread safety here */
/* {{{ PHP_INI
 */

static int le_field_dfn_descriptor;
static int le_pgdal;
static int le_datasource_descriptor;
static int le_layer_descriptor;
static int le_feature_descriptor;
static int le_field_type_descriptor;
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("pgdal.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_pgdal_globals, pgdal_globals)
    STD_PHP_INI_ENTRY("pgdal.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_pgdal_globals, pgdal_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

//region ds ########################## DATASOURCE ROUTINES ############################

PHP_FUNCTION(OGRRegisterAll)
        {
                OGRRegisterAll();
        }


PHP_FUNCTION(OGROpen)
{
        //region phpext
    OGRDataSourceH * hDS;
    char *name;
    int name_len;
    zend_bool update_mode = 0;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &name, &name_len, &update_mode) == FAILURE) {
        RETURN_NULL();
    }

    if (name_len == 0) {
        php_error_docref(NULL
        TSRMLS_CC, E_WARNING, "Empty string as path");
        RETURN_FALSE;
    }

    hDS = OGROpen(name, update_mode, NULL);
    if (hDS == NULL )
    {
        RETURN_NULL();
    }

    ZEND_REGISTER_RESOURCE(return_value, hDS, le_datasource_descriptor);
        //endregion
}


PHP_FUNCTION(OGR_DS_Destroy)
        {
                //region phpext

                OGRDataSourceH * hDS;
        zval *ds_resource;
        zend_bool update_mode = 0;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ds_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(hDS, OGRDataSourceH*, &ds_resource, -1,
        PHP_SOURCE_DESCRIPTOR_RES_NAME, le_datasource_descriptor);

        OGR_DS_Destroy(hDS);
                //endregion
        }


PHP_FUNCTION(OGRReleaseDataSource)
        {
                //region phpext

                OGRDataSourceH * hDS;
        zval *ds_resource;
        zend_bool update_mode = 0;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ds_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(hDS, OGRDataSourceH*, &ds_resource, -1,
        PHP_SOURCE_DESCRIPTOR_RES_NAME, le_datasource_descriptor);

        OGRReleaseDataSource(hDS);
                //endregion
        }


PHP_FUNCTION(OGR_DS_GetName)
        {
                //region phpext

                OGRDataSourceH * hDS;
        zval *ds_resource;
        zend_bool update_mode = 0;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ds_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(hDS, OGRDataSourceH*, &ds_resource, -1,
        PHP_SOURCE_DESCRIPTOR_RES_NAME, le_datasource_descriptor);

        RETURN_STRING(OGR_DS_GetName(hDS), 1);
                //endregion
        }


PHP_FUNCTION(OGR_DS_GetLayer)
        {
                //region phpext

                OGRLayerH * layerH;
        long lyrIndex;
        OGRDataSourceH *hDS;
        zval *ds_resource;
        zend_bool update_mode = 0;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &ds_resource, &lyrIndex) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(hDS, OGRDataSourceH*, &ds_resource, -1,
        PHP_SOURCE_DESCRIPTOR_RES_NAME, le_datasource_descriptor);

        layerH = OGR_DS_GetLayer(hDS, lyrIndex);

        if (layerH==NULL){
            RETURN_NULL();
        }

        ZEND_REGISTER_RESOURCE(return_value, layerH, le_layer_descriptor);
                //endregion
        }


PHP_FUNCTION(OGR_DS_GetLayerByName)
        {
                //region phpext
                OGRLayerH * layerH;
        char * name;
        long name_len;

        OGRDataSourceH *hDS;
        zval *ds_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &ds_resource, &name, name_len) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(hDS, OGRDataSourceH*, &ds_resource, -1,
        PHP_SOURCE_DESCRIPTOR_RES_NAME, le_datasource_descriptor);

        layerH = OGR_DS_GetLayerByName(hDS, name);

        if (layerH==NULL){
            RETURN_NULL();
        }

        ZEND_REGISTER_RESOURCE(return_value, layerH, le_layer_descriptor);
                //endregion
        }


PHP_FUNCTION(OGR_DS_GetLayerCount)
        {
                //region phpext
                OGRDataSourceH * hDS;
        zval *ds_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ds_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(hDS, OGRDataSourceH*,
        &ds_resource, -1, PHP_SOURCE_DESCRIPTOR_RES_NAME,
        le_datasource_descriptor);

        RETURN_LONG(OGR_DS_GetLayerCount(hDS));
                //endregion
        }

// endregion

//region layer ########################## LAYER ROUTINES ############################

PHP_FUNCTION(OGR_L_GetFeatureCount)
        {
                //region phpext

                OGRLayerH * layerH;
        zval *lyr_resource;
        zend_bool force = 0;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|l", &lyr_resource, &force) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(layerH, OGRLayerH*,
        &lyr_resource, -1, PHP_LAYER_DESCRIPTOR_RES_NAME,
        le_layer_descriptor);

        RETURN_LONG(OGR_L_GetFeatureCount(layerH, force));
                //endregion
        }

PHP_FUNCTION(OGR_L_GetName)
        {
                //region phpext
                OGRLayerH * layerH;
        zval *lyr_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &lyr_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(layerH, OGRLayerH*,
        &lyr_resource, -1, PHP_LAYER_DESCRIPTOR_RES_NAME,
        le_layer_descriptor);

        RETURN_STRING((char *)OGR_L_GetName(layerH), 1);
                //endregion
        }


PHP_FUNCTION(OGR_L_TestCapability)
        {
                //region phpext
                OGRLayerH * layerH;
        zval *lyr_resource;
        char * testName;
        long testLen;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &lyr_resource, &testName, &testLen) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(layerH, OGRLayerH*,
        &lyr_resource, -1, PHP_LAYER_DESCRIPTOR_RES_NAME,
        le_layer_descriptor);

        RETURN_BOOL(OGR_L_TestCapability(layerH, testName));
                //endregion
        }


PHP_FUNCTION(OGR_L_ResetReading)
        {
                //region phpext
                OGRLayerH * layerH;
        zval *lyr_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &lyr_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(layerH, OGRLayerH*,
        &lyr_resource, -1, PHP_LAYER_DESCRIPTOR_RES_NAME,
        le_layer_descriptor);

        OGR_L_ResetReading(layerH);
                //endregion
        }


PHP_FUNCTION(OGR_L_GetFeature)
        {
                //region phpext
                OGRLayerH * layerH;
        OGRFeatureH * featureH;
        zval *lyr_resource;
        long fid;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &lyr_resource, &fid) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(layerH, OGRLayerH*,
        &lyr_resource, -1, PHP_LAYER_DESCRIPTOR_RES_NAME,
        le_layer_descriptor);

        featureH = OGR_L_GetFeature(layerH, fid);

        if (featureH==NULL){
            RETURN_NULL();
        }
        ZEND_REGISTER_RESOURCE(return_value, featureH, le_feature_descriptor);
                //endregion
        }


PHP_FUNCTION(OGR_L_GetNextFeature)
        {
                //region phpext

                OGRLayerH * layerH;
        OGRFeatureH * featureH;
        zval *lyr_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &lyr_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(layerH, OGRLayerH*,
        &lyr_resource, -1, PHP_LAYER_DESCRIPTOR_RES_NAME,
        le_layer_descriptor);

        featureH = OGR_L_GetNextFeature(layerH);

        if (featureH==NULL){
            RETURN_NULL();
        }

        ZEND_REGISTER_RESOURCE(return_value, featureH, le_feature_descriptor);
                //endregion
        }
// endregion

//region feature ########################## FEATURE ROUTINES ############################

PHP_FUNCTION(OGR_F_Destroy)
        {
                //region phpext

                OGRFeatureH * featureH;
        zval *feature_resource;
        long fid;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &feature_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(featureH, OGRFeatureH*,
        &feature_resource, -1, PHP_FEATURE_DESCRIPTOR_RES_NAME,
        le_feature_descriptor);


        OGR_F_Destroy(featureH);
                //endregion
        }



PHP_FUNCTION(OGR_F_GetFieldCount)
        {
                //region phpext
                OGRFeatureDefnH * featureH;
        zval *feature_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &feature_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(featureH, OGRFeatureDefnH*, &feature_resource, -1,
        PHP_FEATURE_DESCRIPTOR_RES_NAME, le_feature_descriptor);

        RETURN_LONG(OGR_F_GetFieldCount(featureH));
                //endregion
        }




PHP_FUNCTION(OGR_F_GetFieldDefnRef)
        {
                //region phpext
                OGRFieldDefnH * fieldDfnH;
        OGRFeatureH * featureH;
        zval *feature_resource;
        long field_index;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &feature_resource, &field_index) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(featureH, OGRFeatureH*, &feature_resource, -1, PHP_FEATURE_DESCRIPTOR_RES_NAME,
        le_feature_descriptor);

        fieldDfnH = OGR_F_GetFieldDefnRef(featureH, field_index);

        ZEND_REGISTER_RESOURCE(return_value, fieldDfnH, le_field_dfn_descriptor);
                //endregion
        }



PHP_FUNCTION(OGR_F_GetFID)
        {
                //region phpext
                OGRFieldDefnH * fieldDfnH;
        OGRFeatureH * featureH;
        zval *feature_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &feature_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(featureH, OGRFeatureH*, &feature_resource, -1, PHP_FEATURE_DESCRIPTOR_RES_NAME,
        le_feature_descriptor);

        RETURN_LONG(OGR_F_GetFID(featureH));
                //endregion
        }
// endregion

//region field ########################## FIELD ROUTINES ############################


PHP_FUNCTION(OGR_Fld_GetNameRef)
        {
                //region phpext

                OGRFieldDefnH * fieldDfnH;
        zval *field_dfn_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &field_dfn_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(fieldDfnH, OGRFieldDefnH*, &field_dfn_resource, -1, PHP_FIELD_DESCRIPTOR_RES_NAME,
        le_field_dfn_descriptor);

        RETURN_STRING((char *)OGR_Fld_GetNameRef(fieldDfnH), 1);
                //endregion
        }

PHP_FUNCTION(OGR_Fld_GetType)
        {
                //region phpext

                OGRFieldDefnH * fieldDfnH;
        zval *field_dfn_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &field_dfn_resource) == FAILURE ) {
            RETURN_NULL();
        }
        /* Use the zval* to verify the resource type and
         * retrieve its pointer from the lookup table */
        ZEND_FETCH_RESOURCE(fieldDfnH, OGRFieldDefnH*, &field_dfn_resource, -1, PHP_FIELD_DESCRIPTOR_RES_NAME,
        le_field_dfn_descriptor);

        RETURN_LONG(OGR_Fld_GetType(fieldDfnH));
                //endregion

        }

PHP_FUNCTION(OGR_GetFieldTypeName)
        {
                //region phpext
                //OGRFieldType eType;
                long field_type_resource;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &field_type_resource) == FAILURE ) {
            RETURN_NULL();
        }

        //eType = (OGRFieldType)field_type_resource;

        RETURN_STRING((char *)OGR_GetFieldTypeName(field_type_resource), 1);
                //endregion

        }

// endregion

/* {{{ PHP_MINIT_FUNCTION
 */

PHP_MINIT_FUNCTION(pgdal)
        {
//region phpext
                le_datasource_descriptor = zend_register_list_destructors_ex(
                        NULL, NULL, PHP_SOURCE_DESCRIPTOR_RES_NAME, module_number);

        le_layer_descriptor = zend_register_list_destructors_ex(
        NULL, NULL, PHP_LAYER_DESCRIPTOR_RES_NAME, module_number);

        le_feature_descriptor = zend_register_list_destructors_ex(
        NULL, NULL, PHP_FEATURE_DESCRIPTOR_RES_NAME, module_number);

        le_field_dfn_descriptor = zend_register_list_destructors_ex(
        NULL, NULL, PHP_FIELD_DESCRIPTOR_RES_NAME, module_number);

        le_field_type_descriptor = zend_register_list_destructors_ex(
        NULL, NULL, PHP_FIELD_TYPE_DESCRIPTOR_RES_NAME, module_number);

        /* If you have INI entries, uncomment these lines
        REGISTER_INI_ENTRIES();
        */
        return SUCCESS;
//endregion
        }

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pgdal)
        {
                /* uncomment this line if you have INI entries
                UNREGISTER_INI_ENTRIES();
                */
                return SUCCESS;
        }

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(pgdal)
        {
                return SUCCESS;
        }

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(pgdal)
        {
                return SUCCESS;
        }

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pgdal)
        {
                php_info_print_table_start();
        php_info_print_table_header(2, "pgdal support", "enabled");
        php_info_print_table_end();

                /* Remove comments if you have entries in php.ini
                DISPLAY_INI_ENTRIES();
                */
        }
/* }}} */

/* {{{ pgdal_functions[]
 *
 * Every user visible function must have an entry in pgdal_functions[].
 */
        const
zend_function_entry pgdal_functions[] = {
        PHP_FE(OGRRegisterAll, NULL)

        // ==================== DATASOURCE ======================

	PHP_FE(OGROpen,	NULL)
	PHP_FE(OGR_DS_GetName,	NULL)
	PHP_FE(OGR_DS_Destroy,	NULL)
    PHP_FE(OGR_DS_GetLayerCount,	NULL)
    PHP_FE(OGR_DS_GetLayer,	NULL)
    PHP_FE(OGR_DS_GetLayerByName,	NULL)

        // ==================== LAYERS ======================

	PHP_FE(OGR_L_GetName,	NULL)
	PHP_FE(OGR_L_ResetReading,	NULL)
	PHP_FE(OGR_L_TestCapability,	NULL)
    PHP_FE(OGR_L_GetNextFeature, NULL)
    PHP_FE(OGR_L_GetFeature, NULL)
    PHP_FE(OGR_L_GetFeatureCount, NULL)

        // =================== FEATURES =================

    PHP_FE(OGR_F_Destroy, NULL)
    PHP_FE(OGR_F_GetFID, NULL)
    PHP_FE(OGR_F_GetFieldCount, NULL)
    PHP_FE(OGR_F_GetFieldDefnRef, NULL)

        // =================== FIELDs =================

    PHP_FE(OGR_Fld_GetNameRef, NULL)
    PHP_FE(OGR_Fld_GetType, NULL)
    PHP_FE(OGR_GetFieldTypeName, NULL)


        PHP_FE_END    /* Must be the last line in pgdal_functions[] */
};
/* }}} */

/* {{{ pgdal_module_entry
 */
zend_module_entry pgdal_module_entry = {
        STANDARD_MODULE_HEADER,
        "pgdal",
        pgdal_functions,
        PHP_MINIT(pgdal),
        PHP_MSHUTDOWN(pgdal),
        PHP_RINIT(pgdal),        /* Replace with NULL if there's nothing to do at request start */
        PHP_RSHUTDOWN(pgdal),    /* Replace with NULL if there's nothing to do at request end */
        PHP_MINFO(pgdal),
        PHP_PGDAL_VERSION,
        STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PGDAL
ZEND_GET_MODULE(pgdal)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
