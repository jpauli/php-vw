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

#ifndef PHP_VW_H
#define PHP_VW_H

extern zend_module_entry vw_module_entry;
#define phpext_vw_ptr &vw_module_entry

#define PHP_VW_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_VW_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_VW_API __attribute__ ((visibility("default")))
#else
#	define PHP_VW_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

static void vw_assert_handler(INTERNAL_FUNCTION_PARAMETERS);

PHP_MSHUTDOWN_FUNCTION(vw);
PHP_MINFO_FUNCTION(vw);
PHP_MINIT_FUNCTION(vw);


#define REPLACE_ASSERT_OPTION(option) if (orig_assert_##option) { zend_alter_ini_entry("assert."#option, sizeof("assert."#option), "0", strlen("O"), PHP_INI_ALL, ZEND_INI_STAGE_RUNTIME); }
#define RESTORE_ASSERT_OPTION(option) if (orig_assert_##option) { zend_alter_ini_entry("assert."#option, sizeof("assert."#option), "1", strlen("1"), PHP_INI_ALL, ZEND_INI_STAGE_RUNTIME); }
#define REPLACE_ASSERT_CB if (orig_assert_callback) { zend_alter_ini_entry("assert.callback", sizeof("assert.callback"), "", strlen(""), PHP_INI_ALL, ZEND_INI_STAGE_RUNTIME); }
#define RESTORE_ASSERT_CB if (orig_assert_callback) { zend_alter_ini_entry("assert.callback", sizeof("assert.callback"), orig_assert_callback, strlen(orig_assert_callback), PHP_INI_ALL, ZEND_INI_STAGE_RUNTIME); }
#ifdef ZTS
#define VW_G(v) TSRMG(vw_globals_id, zend_vw_globals *, v)
#else
#define VW_G(v) (vw_globals.v)
#endif

#endif	/* PHP_VW_H */
