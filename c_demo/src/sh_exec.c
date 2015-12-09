/** @file sh_exec.c
    @brief shell execute
    @author Copyright (C) 2015 hmm
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "safe.h"
#include "debug.h"
#include "sh_exec.h"

/**
 * @brief Fork a child and execute a shell command, the parent
 *  process waits for the child to return and returns the child's exit() value.
 * @param cmd_line
 * @param quiet
 * @return Return code of the command
 */
INT32
shell_execute(const INT8 *cmd_line, INT32 quiet)
{
	INT32 pid, status, rc;

    const INT8 *new_argv[4];
    new_argv[0] = "/bin/sh";
    new_argv[1] = "-c";
    new_argv[2] = cmd_line;
    new_argv[3] = NULL;

    pid = safe_fork();
    if (pid == 0) {             /* for the child process:         */
        /* We don't want to see any errors if quiet flag is on */
        if (quiet)
            close(2);
        if (execvp("/bin/sh", (char *const *)new_argv) == -1) { /* execute the command  */
            debug(LOG_ERR, "execvp(): %s", strerror(errno));
        } else {
            debug(LOG_ERR, "execvp() failed");
        }
        exit(1);
    }

    /* for the parent:      */
    debug(LOG_DEBUG, "Waiting for PID %d to exit", pid);
    rc = waitpid(pid, &status, 0);
    debug(LOG_DEBUG, "Process PID %d exited", rc);

    if (-1 == rc) {
        debug(LOG_ERR, "waitpid() failed (%s)", strerror(errno));
        return 1; /* waitpid failed. */
    }

    if (WIFEXITED(status)) {
        return (WEXITSTATUS(status));
    } else {
        /* If we get here, child did not exit cleanly. Will return non-zero exit code to caller*/
        debug(LOG_DEBUG, "Child may have been killed.");
        return 1;
    }
}

