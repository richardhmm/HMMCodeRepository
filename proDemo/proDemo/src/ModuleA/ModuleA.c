
/**
 * @file ModuleA.c
 * @brief  Debug output routines
 */

#include <stdio.h>
#include <syslog.h>
#include <errno.h>

#include "types.h"
#include "debug.h"
#include "ModuleA.h"

void moduleA_print(void)
{
    printf("moduleA_print\n");
    debug(LOG_NOTICE, "moduleA");
}
