//
// Created by eddmash on 11/11/17.
//
#include <stdio.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "pg_featuredfn.h"


zend_object_value featuredfn_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    ogr_featuredfn_object *intern = (ogr_featuredfn_object *)emalloc(sizeof(ogr_featuredfn_object));
    memset(intern, 0, sizeof(ogr_featuredfn_object));

    /* The underlying std zend_object has to be initialized.  */
    zend_object_std_init(&intern->std, type TSRMLS_CC);

    /* Even if you don't use properties yourself you should still call object_properties_init(),
     * because extending classes may use properties. (Generally a lot of the stuff you will do is
     * for the sake of not breaking extending classes). */
    object_properties_init(&intern->std, type);

    /* Put the internal object into the object store, with the default dtor handler and our custom
     * free handler. The last NULL parameter is the clone handler, which is left empty for now. */
    retval.handle = zend_objects_store_put(intern, NULL, NULL, NULL TSRMLS_CC);

    /* Assign the customized object handlers */
    retval.handlers = &featuredfn_object_handlers;

    return retval;
}

// -------------------------------------- METHODS -----------------------------------

PHP_METHOD(FeatureDfn, getName)
{
    ogr_featuredfn_object * dfnObj = (ogr_featuredfn_object *) zend_object_store_get_object(getThis());
    if(!dfnObj->dfn){
        RETURN_STRING("MISING DEFINITION", 1);
    }
    RETURN_STRING((char *)OGR_FD_GetName(dfnObj->dfn), 1);

}
PHP_METHOD(FeatureDfn, getFieldCount)
{
    ogr_featuredfn_object * dfnObj = (ogr_featuredfn_object *) zend_object_store_get_object(getThis());
    if(!dfnObj->dfn){
        RETURN_STRING("MISING DEFINITION", 1);
    }
    RETURN_LONG(OGR_FD_GetFieldCount(dfnObj->dfn));

}

const zend_function_entry featuredfn_methods[] = {
        PHP_ME(FeatureDfn, getName, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(FeatureDfn, getFieldCount, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// ------------------------ CLASS -------------------------------------

void registerFeaturedfnClass(){

    // register gdal class
    zend_class_entry tmp_ce;
    INIT_CLASS_ENTRY(tmp_ce, "FeatureDfn", featuredfn_methods);

    featuredfn_ce = zend_register_internal_class(&tmp_ce TSRMLS_CC);
    featuredfn_ce->create_object = featuredfn_create_handler;
    memcpy(&featuredfn_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    featuredfn_object_handlers.clone_obj = NULL;
}