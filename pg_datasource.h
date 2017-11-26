//
// Created by eddmash on 11/5/17.
//

#include "ogr_api.h"
#include "pg_layer.h"
#include "pg_featuredfn.h"

#ifndef PHP_SRC_PG_DATASOURCE_H
#define PHP_SRC_PG_DATASOURCE_H

#endif //PHP_SRC_PG_DATASOURCE_H

zend_object_handlers datasource_object_handlers;

//struct car_object {
//    zend_object std;
//    DataSource *datasource;
//};

typedef struct _datasource_object {
    zend_object std;
    OGRDataSourceH ds;
} datasource_object;

void registerDatasourceClass();