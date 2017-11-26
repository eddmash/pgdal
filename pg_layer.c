//
// Created by eddmash on 11/6/17.
//

#include <stdio.h>
#include "php.h"
#include "php_ini.h"
#include "pg_layer.h"
#include "pg_featuredfn.h"


zend_object_value layer_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;
    
    ogr_layer_object *intern = (ogr_layer_object *)emalloc(sizeof(ogr_layer_object));
    memset(intern, 0, sizeof(ogr_layer_object)); 
    
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
    retval.handlers = &layer_object_handlers;
    
    return retval;
}

// -------------------------------------- METHODS -----------------------------------

/**
 * Return the name of this layer in the Data Source.
 */
PHP_METHOD(Layer, getName)
{
//    OGR_L_GetName
}

PHP_METHOD(Layer, getLayerDfn)
{
    ogr_featuredfn_object * fdfObj;
    OGRFeatureDefnH * dfn;

    ogr_layer_object *layerObj = (ogr_layer_object *)zend_object_store_get_object(getThis());

    if (object_init_ex(return_value, featuredfn_ce) != SUCCESS) {
        RETURN_NULL();
    }

    if(!layerObj->layerdfn){
        dfn = OGR_L_GetLayerDefn(layerObj->layer);
        if(!dfn){
            RETURN_STRING("COULD NOT LOAD DEFINATION", 1);
        }
    }else{
        dfn = layerObj->layerdfn;
    }

    fdfObj = (ogr_featuredfn_object *)  zend_object_store_get_object(return_value TSRMLS_CC);
    fdfObj->dfn = dfn;
}

const zend_function_entry layer_methods[] = {
        PHP_ME(Layer,  getName, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Layer,  getLayerDfn, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// ------------------------ CLASS -------------------------------------

void registerLayerClass(){

    // register gdal class
    zend_class_entry tmp_ce;
    INIT_CLASS_ENTRY(tmp_ce, "Layer", layer_methods);

    layer_ce = zend_register_internal_class(&tmp_ce TSRMLS_CC);
    layer_ce->create_object = layer_create_handler;
    memcpy(&layer_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    layer_object_handlers.clone_obj = NULL;
}