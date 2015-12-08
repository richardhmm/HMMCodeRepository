
/**
 * @file debug.h
 * @brief  Debug output routines
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "types.h"

typedef struct _debug_conf {
	INT16 debuglevel;      /**< @brief Debug information verbosity */
	INT16 log_stderr;      /**< @brief Output log to stdout */
	INT16 log_syslog;      /**< @brief Output log to syslog */
	INT16 syslog_facility; /**< @brief facility to use when using syslog for logging */
} debugconf_t;

extern debugconf_t debugconf;

/** Used to output messages.
 * The messages will include the filename and line number, and will be sent to syslog if so configured in the config file 
 * @param level Debug level
 * @param format... sprintf like format string
 */
#define debug(level, format...) _debug(__FILE__, __LINE__, level, format)

/** @internal */
void _debug(const INT8 *, INT16, INT16, const INT8 *, ...);

#endif /* _DEBUG_H_ */
