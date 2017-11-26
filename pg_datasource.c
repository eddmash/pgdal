//
// Created by eddmash on 11/5/17.
//

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "ogr_api.h"

#include "pg_datasource.h"


zend_class_entry *datasource_ce;
zend_object_handlers datasource_object_handlers;


ZEND_BEGIN_ARG_INFO_EX(arginfo_version_info, 0, 0, 1)
    ZEND_ARG_INFO(0, pszRequest)
ZEND_END_ARG_INFO();

static void datasource_free_storage(datasource_object *obj TSRMLS_DC)
{
//    datasource_object *obj = (datasource_object *)object;
    if(obj->ds){
        OGRReleaseDataSource(obj->ds);
    }
    efree(obj);
}

zend_object_value datasource_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    datasource_object *intern = (datasource_object *)emalloc(sizeof(datasource_object));
    memset(intern, 0, sizeof(datasource_object));

    /* The underlying std zend_object has to be initialized.  */
    zend_object_std_init(&intern->std, type TSRMLS_CC);

    /* Even if you don't use properties yourself you should still call object_properties_init(),
     * because extending classes may use properties. (Generally a lot of the stuff you will do is
     * for the sake of not breaking extending classes). */
    object_properties_init(&intern->std, type);

    /* Put the internal object into the object store, with the default dtor handler and our custom
     * free handler. The last NULL parameter is the clone handler, which is left empty for now. */
    retval.handle = zend_objects_store_put(intern,
                                           NULL,
                                           (zend_objects_free_object_storage_t)datasource_free_storage,
                                           NULL TSRMLS_CC);

    /* Assign the customized object handlers */
    retval.handlers = &datasource_object_handlers;

    return retval;
}
// --------------------------- METHODS ---------------------------------
PHP_METHOD(DataSource, __construct)
{
    OGRDataSourceH * dSource;
    char * path;
    int path_len;

    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
        RETURN_NULL();
    }
    OGRRegisterAll();
    dSource = OGROpen(path, FALSE, NULL);
    if(!dSource){
        RETURN_STRING("FILE COULD NOT OPEN", 1);
    }

    datasource_object *obj = (datasource_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->ds = dSource;
}

PHP_METHOD(DataSource, getLayers)
{
    RETURN_STRING("pol",1);
}

PHP_METHOD(DataSource, getLayerCount)
{
    datasource_object *obj = (datasource_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
    RETURN_LONG(OGR_DS_GetLayerCount(obj->ds));
}

PHP_METHOD(DataSource, getLayer)
{
    ogr_featuredfn_object * fdfObj;
    OGRFeatureDefnH * dfn;
    OGRLayerH * ogrLayer;
    long index;
    ogr_layer_object *layer_obj;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, (char*)"l", &index) == FAILURE) {
        return;
    }

    datasource_object *obj = (datasource_object *) zend_object_store_get_object(getThis());

    ogrLayer = OGR_DS_GetLayer(obj->ds, index);
    if (!ogrLayer) {
        RETURN_STRING("FILE COULD NOT OPEN LAYER", 1);
    }
    if (object_init_ex(return_value, layer_ce) != SUCCESS) {
        RETURN_NULL();
    }

    layer_obj = (ogr_layer_object*)  zend_object_store_get_object(return_value TSRMLS_CC);
    layer_obj->layer = ogrLayer;

    dfn = OGR_L_GetLayerDefn(ogrLayer);
    if(!dfn){
        RETURN_STRING("COULD NOT LOAD DEFINATION", 1);
    }
    layer_obj->layerdfn = dfn;
}

const zend_function_entry datasource_methods[] = {
        PHP_ME(DataSource,  __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(DataSource,  getLayers, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(DataSource,  getLayerCount, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(DataSource,  getLayer, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};

// ------------------------ CLASS -------------------------------------

void registerDatasourceClass(){

    // register gdal class
    zend_class_entry tmp_ce;
    INIT_CLASS_ENTRY(tmp_ce, "DataSource", datasource_methods);

    datasource_ce = zend_register_internal_class(&tmp_ce TSRMLS_CC);
    datasource_ce->create_object = datasource_create_handler;
    memcpy(&datasource_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    datasource_object_handlers.clone_obj = NULL;
}