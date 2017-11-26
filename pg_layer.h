
#include "ogr_api.h"

#ifndef PHP_SRC_PG_LAYER_H
#define PHP_SRC_PG_LAYER_H

#endif //PHP_SRC_PG_LAYER_H

void registerLayerClass();

zend_class_entry *layer_ce;
zend_object_handlers layer_object_handlers;

typedef struct _ogr_layer_object {
    zend_object std;
    OGRLayerH * layer;
    OGRFeatureDefnH * layerdfn;
} ogr_layer_object;