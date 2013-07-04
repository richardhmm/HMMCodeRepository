/*
   Copyright (c) 2013 richard.hmm

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
 * @file Log.h
 * @brief log4cplus declaration
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-4
 */
#ifndef LOG_H_
#define LOG_H_

// log4cplus enable flag
#define LOG_SUPPORT     1

// log4cplus enable
#if LOG_SUPPORT
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <iomanip>

using namespace log4cplus;
using namespace log4cplus::helpers;

extern Logger logger;
extern void InitLogger(void);

// declare log4cplus macro commands
#define LOG_TRACE(logEvent)         LOG4CPLUS_TRACE(logger, logEvent)
#define LOG_DEBUG(logEvent)         LOG4CPLUS_DEBUG(logger, logEvent)
#define LOG_INFO(logEvent)          LOG4CPLUS_INFO(logger, logEvent)
#define LOG_WARN(logEvent)          LOG4CPLUS_WARN(logger, logEvent)
#define LOG_ERROR(logEvent)         LOG4CPLUS_ERROR(logger, logEvent)
#define LOG_FATAL(logEvent)         LOG4CPLUS_FATAL(logger, logEvent)

// log4cplus disable
#else
// declare NULL macro commands
#define InitLogger()
#define LOG_TRACE(logEvent)
#define LOG_DEBUG(logEvent)
#define LOG_INFO(logEvent)
#define LOG_WARN(logEvent)
#define LOG_ERROR(logEvent)
#define LOG_FATAL(logEvent)

#endif

#endif /* LOG_H_ */
