/** @internal
 @file main.c
 @brief Entry point only
 @author Copyright (C) 2015 richardhmm
 */

#include <stdio.h>
#include <syslog.h>
#include <errno.h>

#include "types.h"
#include "debug.h"
#include "ModuleA.h"


/**
 * @brief print
 * @param argc argv
 * @return 0
 */
INT32 main(INT32 argc, INT8 **argv)
{
	debug(LOG_NOTICE, "build date:"__DATE__" time:"__TIME__"\r\n");

	debugconf.debuglevel = LOG_DEBUG;
	debugconf.log_syslog = 1;
	
	debug(LOG_NOTICE, "helloworld\n");
	moduleA_print();

	return 0;
}
