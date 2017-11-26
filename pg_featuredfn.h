//
// Created by eddmash on 11/11/17.
//

#include "ogr_api.h"

#ifndef PHP_SRC_PG_FEATUREDFN_H
#define PHP_SRC_PG_FEATUREDFN_H

#endif //PHP_SRC_PG_FEATUREDFN_H

void registerFeaturedfnClass();

zend_class_entry *featuredfn_ce;
zend_object_handlers featuredfn_object_handlers;

typedef struct _ogr_featuredfn_object {
    zend_object std;
    OGRFeatureDefnH * dfn;
} ogr_featuredfn_object;