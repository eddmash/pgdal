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

#ifndef PHP_PGDAL_H
#define PHP_PGDAL_H

extern zend_module_entry pgdal_module_entry;
#define phpext_pgdal_ptr &pgdal_module_entry

#define PHP_PGDAL_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_PGDAL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PGDAL_API __attribute__ ((visibility("default")))
#else
#	define PHP_PGDAL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define IS_MAJOR_VERSION(X) (GDAL_MAJOR_VERSION==X)

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(pgdal)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(pgdal)
*/

/* In every utility function you add that needs to use variables 
   in php_pgdal_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PGDAL_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PGDAL_G(v) TSRMG(pgdal_globals_id, zend_pgdal_globals *, v)
#else
#define PGDAL_G(v) (pgdal_globals.v)
#endif

#endif	/* PHP_PGDAL_H */

#define PHP_SOURCE_DESCRIPTOR_RES_NAME "DS_SOURCE"
#define PHP_LAYER_DESCRIPTOR_RES_NAME "LAYER"
#define PHP_FEATURE_DESCRIPTOR_RES_NAME "FEATURE"
#define PHP_FEATUREDFN_DESCRIPTOR_RES_NAME "FEATUREDFN"
#define PHP_GEOMETRY_DESCRIPTOR_RES_NAME "GEOMETRY"
#define PHP_SPATIALREFERENCE_DESCRIPTOR_RES_NAME "SPATIALREFERENCE"
#define PHP_FIELD_DESCRIPTOR_RES_NAME "FIELD"
#define PHP_FIELD_TYPE_DESCRIPTOR_RES_NAME "FIELD_TYPE"


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
