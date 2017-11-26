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


#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "gdal.h"

#include "php_pgdal.h"
#include "pgdal_main.h"
#include "pg_datasource.h"

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* If you declare any globals in php_pgdal.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(pgdal)
*/

/* True global resources - no need for thread safety here */
static int le_pgdal;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("pgdal.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_pgdal_globals, pgdal_globals)
    STD_PHP_INI_ENTRY("pgdal.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_pgdal_globals, pgdal_globals)
PHP_INI_END()
*/
/* }}} */

/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_pgdal_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_pgdal_init_globals(zend_pgdal_globals *pgdal_globals)
{
	pgdal_globals->global_value = 0;
	pgdal_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pgdal)
{
	registerLayerClass();
	registerGdalClass();
	registerDatasourceClass();
	registerFeaturedfnClass();
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pgdal)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(pgdal)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(pgdal)
{
	return SUCCESS;
}
/* }}} */

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
const zend_function_entry pgdal_functions[] = {
	PHP_FE_END	/* Must be the last line in pgdal_functions[] */
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
	PHP_RINIT(pgdal),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pgdal),	/* Replace with NULL if there's nothing to do at request end */
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
