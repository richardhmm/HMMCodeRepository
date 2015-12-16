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
#include <fcntl.h>
#include <signal.h>

#include "types.h"
#include "debug.h"
#include "tcp_server.h"
#include "sh_exec.h"
#include "minIni.h"
#include "commandline.h"
#include "udp_server.h"
#include "common.h"

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

const INT8 inifile[] = "./config/test.ini";

/* Appends -x, the current PID, and NULL to restartargv
 * see parse_commandline in commandline.c for details
 *
 * Why is restartargv global? Shouldn't it be at most static to commandline.c
 * and this function static there? -Alex @ 8oct2006
 */
static void
append_x_restartargv(void)
{
    int i;

    for (i = 0; restartargv[i]; i++) ;

    restartargv[i++] = safe_strdup("-x");
    safe_asprintf(&(restartargv[i++]), "%d", getpid());
}

static void daemonize(INT8 is_daemon)
{
	if (1 == is_daemon)
	{
		debug(LOG_INFO, "Forking into background");

		switch (safe_fork())
		{
		case 0: /* child */

			/*
			 * Close inherited file descriptors to avoid
			 * keeping unnecessary references.
			 */
			close(0);
			close(1);
			close(2);

			/*
			 * Redirect std{in,out,err}, just in case.
			 */
			open("/dev/null", O_RDWR); // stdin
			dup(0); // stdout
			dup(0); // stderr

			setsid();
			append_x_restartargv();

			/* Avoid keeping any directory in use. */
			chdir("/");

			umask(0);
			break;

		default: /* parent */
			exit(0);
			break;
		}
	}
}

/**
 * @brief print
 * @param argc argv
 * @return 0
 */
INT32
main(INT32 argc, INT8 **argv)
{
	INT8 str[MAX_BUF];
	INT32 n;

	printf("hello c_demo\n");

	parse_commandline(argc, argv);

	daemonize(is_daemon);

	/* test *.ini file */
//	n = ini_gets("first", "string", "dummy", str, sizearray(str), inifile);
//	printf("str[] = %s\n", str);
//	assert(n == 4 && strcmp(str, "noot") == 0);
//	n = ini_gets("second", "string", "dummy", str, sizearray(str), inifile);
//	printf("str[] = %s\n", str);
//	assert(n == 4 && strcmp(str, "mies") == 0);
//	n = ini_gets("first", "undefined", "dummy", str, sizearray(str), inifile);
//	printf("str[] = %s\n", str);
//	assert(n == 5 && strcmp(str, "dummy") == 0);

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

//	tcp_server_loop(1984);
//	tcp_server_pthread(1984);
	tcp_server_thread(1984);
//	udp_server_loop(1984);

    return 0;
}
