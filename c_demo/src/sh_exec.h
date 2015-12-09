/**
 * @file sh_exec.h
 * @brief  shell execute
 */

#ifndef _SH_EXEC_H_
#define _SH_EXEC_H_

#include "types.h"

/**
 * @brief Fork a child and execute a shell command, the parent
 *  process waits for the child to return and returns the child's exit() value.
 * @param cmd_line
 * @param quiet
 * @return Return code of the command
 */
INT32
shell_execute(const INT8 *cmd_line, INT32 quiet);

#endif                          /* _SH_EXEC_H_ */
