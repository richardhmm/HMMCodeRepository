/*
 Copyright (c) 20115 richard.hmm

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
/**
 * @file main.c
 * @brief main
 * @details
 * @author Copyright (C) 2015 Richard.hmm  <sunhyx@gmail.com>
 */
#include <stdio.h>
#include <syslog.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>

#include "types.h"
#include "debug.h"
#include "tcp_server.h"
#include "sh_exec.h"
#include "minIni.h"
#include "commandline.h"
#include "udp_server.h"

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

const INT8 inifile[] = "./config/test.ini";

/**
 * @brief print
 * @param argc argv
 * @return 0
 */
INT32
main(INT32 argc, INT8 **argv)
{
	INT8 str[100];
	INT32 n;

	printf("hello c_demo\n");

	parse_commandline(argc, argv);

	/* string reading */
	n = ini_gets("first", "string", "dummy", str, sizearray(str), inifile);
	printf("str[] = %s\n", str);
	assert(n == 4 && strcmp(str, "noot") == 0);
	n = ini_gets("second", "string", "dummy", str, sizearray(str), inifile);
	printf("str[] = %s\n", str);
	assert(n == 4 && strcmp(str, "mies") == 0);
	n = ini_gets("first", "undefined", "dummy", str, sizearray(str), inifile);
	printf("str[] = %s\n", str);
	assert(n == 5 && strcmp(str, "dummy") == 0);

    debugconf.debuglevel = LOG_DEBUG;

//    debug(LOG_EMERG, "log level: emerg");
//    debug(LOG_ALERT, "log level: alert");
//    debug(LOG_CRIT, "log level: crit");
//    debug(LOG_ERR, "log level: error");
//    debug(LOG_WARNING, "log level: warning");
//    debug(LOG_NOTICE, "log level: notice");
//    debug(LOG_INFO, "log level: info");
//	debug(LOG_DEBUG, "log level: debug");
//
//	shell_execute("echo \"c_demo\" >> /var/tmp/c_demo.log", 0);

	tcp_server_loop(1984);
//	udp_server_loop(1984);

    return 0;
}
