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
  | Author:                                                              |
  +----------------------------------------------------------------------+

  $Id$
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_tcpwrap.h"

#include <tcpd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int allow_severity = 0;
int deny_severity = 0;

/* {{{ tcpwrap_functions[]
 *
 * Every user visible function must have an entry in tcpwrap_functions[].
 */
zend_function_entry tcpwrap_functions[] = {
	PHP_FE(tcpwrap_check,	NULL)		/* For testing, remove later. */
	{NULL, NULL, NULL}	/* Must be the last line in tcpwrap_functions[] */
};
/* }}} */

/* {{{ tcpwrap_module_entry
 */
zend_module_entry tcpwrap_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"tcpwrap",
	tcpwrap_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(tcpwrap),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_TCPWRAP_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TCPWRAP
ZEND_GET_MODULE(tcpwrap)
#endif

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tcpwrap)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tcp wrappers support", "enabled");
	php_info_print_table_row(2, "version", PHP_TCPWRAP_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* {{{ proto bool tcpwrap_check(string daemon, string address [, string user, [int nodns]])
   Check if client has access according to tcp wrappers table */
PHP_FUNCTION(tcpwrap_check)
{
	int argc, retval, nodns = 0;
	char data[512], *daemon, *ip, *address, *user = NULL;
	int daemon_l, address_l, user_l, lookup_result, dns_result;
	struct in_addr tmp;
	struct hostent host_entry, *result;

	argc = ZEND_NUM_ARGS();
	if (zend_parse_parameters(argc TSRMLS_CC, "ss|sb", &daemon, &daemon_l, &address, &address_l, &user, &user_l, &nodns) == FAILURE) {
		return;
	}

#if defined(__sun)
	result = gethostbyname_r(address, &host_entry, data, sizeof(data), &dns_result);
#else
	dns_result = gethostbyname_r(address, &host_entry, data, sizeof(data), &result, &lookup_result);
#endif

	if (!user) {
		user = STRING_UNKNOWN;
	}

	if (inet_aton(address, &tmp)) {
		ip = address;
		address = STRING_UNKNOWN;
	} else {
		if (nodns || !result || dns_result != 0) {
			ip = STRING_UNKNOWN;
		} else {
			memcpy(&tmp.s_addr, *host_entry.h_addr_list, sizeof(tmp.s_addr));
			ip = inet_ntoa(tmp);
		}
	}

	retval = hosts_ctl(daemon, address, ip, user);

	if (!retval) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
