/*
  +----------------------------------------------------------------------+
  | PHP Version 4                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2003 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.02 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available at through the world-wide-web at                           |
  | http://www.php.net/license/2_02.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Marcin Gibula <mg@iceni.pl>                                  |
  +----------------------------------------------------------------------+

  $Id$ 
*/

#ifndef PHP_TCPWRAP_H
#define PHP_TCPWRAP_H

extern zend_module_entry tcpwrap_module_entry;
#define phpext_tcpwrap_ptr &tcpwrap_module_entry

#ifdef PHP_WIN32
#define PHP_TCPWRAP_API __declspec(dllexport)
#else
#define PHP_TCPWRAP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif


PHP_MINFO_FUNCTION(tcpwrap);
PHP_FUNCTION(tcpwrap_check);

#endif	/* PHP_TCPWRAP_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
