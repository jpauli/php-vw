/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Julien PAULI <jpauli@php.net>                                |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_vw.h"

static void (*old_assert_handler)(INTERNAL_FUNCTION_PARAMETERS);
static zend_internal_function *assert_func;
const char * const envs[] = {"CI", "CONTINUOUS_INTEGRATION", "BUILD_ID", "BUILD_NUMBER", "TEAMCITY_VERSION", "TRAVIS", "CIRCLECI", "JENKINS_URL", "HUDSON_URL", "bamboo.buildKey", "PHPCI", "GOCD_SERVER_HOST", "BUILDKITE" };

static void vw_assert_handler(INTERNAL_FUNCTION_PARAMETERS)
{
	size_t i;
	char has_env = 0;
	long orig_assert_warning, orig_assert_bail;
	char *orig_assert_callback = NULL;

	for (i=0; i< sizeof(envs)/sizeof(envs[0]); i++) {
		if (getenv(envs[i])) {
			has_env = 1;
			break;
		}
	}

	if (!has_env) {
		old_assert_handler(INTERNAL_FUNCTION_PARAM_PASSTHRU);
		return;
	}

	if (!INI_INT("assert.active")) {
		RETURN_TRUE;
	}

	orig_assert_warning  = INI_INT("assert.warning");
	orig_assert_bail     = INI_INT("assert.bail");
	orig_assert_callback = INI_STR("assert.callback");

	REPLACE_ASSERT_OPTION(warning)
	REPLACE_ASSERT_OPTION(bail)
	REPLACE_ASSERT_CB

	old_assert_handler(INTERNAL_FUNCTION_PARAM_PASSTHRU);

	RESTORE_ASSERT_OPTION(warning)
	RESTORE_ASSERT_OPTION(bail)
	RESTORE_ASSERT_CB

	/* Here, is VW magic , impressive, isnt it ? */
	if (Z_TYPE_P(return_value) == IS_NULL || !Z_BVAL_P(return_value)) {
		RETURN_TRUE;
	}
}

PHP_MINIT_FUNCTION(vw)
{
	zend_hash_find(CG(function_table), "assert", sizeof("assert"), (void **)&assert_func);
	old_assert_handler   = assert_func->handler;
	assert_func->handler = vw_assert_handler;

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(vw)
{
	assert_func->handler = old_assert_handler;

	return SUCCESS;
}

PHP_MINFO_FUNCTION(vw)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "vw assertions support", "enabled");
	php_info_print_table_end();
}


zend_module_entry vw_module_entry = {
	STANDARD_MODULE_HEADER,
	"vw",
	NULL,
	PHP_MINIT(vw),
	PHP_MSHUTDOWN(vw),
	NULL,
	NULL,
	PHP_MINFO(vw),
	PHP_VW_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_VW
ZEND_GET_MODULE(vw)
#endif

