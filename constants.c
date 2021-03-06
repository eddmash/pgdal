//
// Created by edd on 12/4/17.
//

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "ogr_api.h"
#include "php_pgdal.h"
#include "constants.h"

void registerConstants(INIT_FUNC_ARGS){
    REGISTER_LONG_CONSTANT("wkb25DBit", wkb25DBit, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("ogrZMarker", ogrZMarker, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbXDR", wkbXDR, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbNDR", wkbNDR, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbUnknown", wkbUnknown, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbPoint", wkbPoint, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbLineString", wkbLineString, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbPolygon", wkbPolygon, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbMultiPoint", wkbMultiPoint, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbMultiLineString", wkbMultiLineString, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbMultiPolygon", wkbMultiPolygon, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbGeometryCollection", wkbGeometryCollection, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbNone", wkbNone, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbLinearRing", wkbLinearRing, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbPoint25D", wkbPoint25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbLineString25D", wkbLineString25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbPolygon25D", wkbPolygon25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbMultiPoint25D", wkbMultiPoint25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbMultiLineString25D", wkbMultiLineString25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbMultiPolygon25D", wkbMultiPolygon25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("wkbGeometryCollection25D", wkbGeometryCollection25D, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTInteger", OFTInteger, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTIntegerList", OFTIntegerList, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTReal", OFTReal, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTRealList", OFTRealList, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTString", OFTString, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTStringList", OFTStringList, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTWideString", OFTWideString, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTWideStringList", OFTWideStringList, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTBinary", OFTBinary, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTDate", OFTDate, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTTime", OFTTime, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTDateTime", OFTDateTime, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OJUndefined", OJUndefined, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OJLeft", OJLeft, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OJRight", OJRight, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OGRNullFID", OGRNullFID, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OGRUnsetMarker", OGRUnsetMarker, OGR_CONST_FLAG);

#if IS_MAJOR_VERSION(2)
    REGISTER_LONG_CONSTANT("OFTInteger64", OFTInteger64, OGR_CONST_FLAG);
    REGISTER_LONG_CONSTANT("OFTInteger64List", OFTInteger64List, OGR_CONST_FLAG);
#endif
//    REGISTER_STRING_CONSTANT("OLCRandomRead", (char*)OLCRandomRead, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCSequentialWrite", (char*)OLCSequentialWrite, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCRandomWrite", (char*)OLCRandomWrite, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCFastSpatialFilter", (char*)OLCFastSpatialFilter, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCFastFeatureCount", (char*)OLCFastFeatureCount, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCFastGetExtent", (char*)OLCFastGetExtent, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCCreateField", (char*)OLCCreateField, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("OLCTransactions", (char*)OLCTransactions, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("ODsCCreateLayer", (char*)ODsCCreateLayer, OGR_CONST_FLAG);
//    REGISTER_STRING_CONSTANT("ODrCCreateDataSource", (char*)ODrCCreateDataSource, OGR_CONST_FLAG);
//    REGISTER_LONG_CONSTANT("GA_ReadOnly", GA_ReadOnly, OGR_CONST_FLAG);
//    REGISTER_LONG_CONSTANT("GA_Update", GA_Update, OGR_CONST_FLAG);
}