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

#include "types.h"
#include "debug.h"

/**
 * @brief print
 * @param argc argv
 * @return 0
 */
INT32
main(INT32 argc, INT8 **argv)
{
    printf("hello c_demo\n");

    debugconf.debuglevel = LOG_DEBUG;

    debug(LOG_EMERG, "log level: emerg");
    debug(LOG_ALERT, "log level: alert");
    debug(LOG_CRIT, "log level: crit");
    debug(LOG_ERR, "log level: error");
    debug(LOG_WARNING, "log level: warning");
    debug(LOG_NOTICE, "log level: notice");
    debug(LOG_INFO, "log level: info");
    debug(LOG_DEBUG, "log level: debug");

    return 0;
}
