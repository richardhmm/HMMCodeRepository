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
 * @file Log.cpp
 * @brief
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-4
 */
#include "Log.h"

#if LOG_SUPPORT

#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/configurator.h>

#define LOG_DAEMON_ENABLE 0

Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("logmain"));

void InitLogger(void)
{
#if LOG_DAEMON_ENABLE // log print into file
    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplusd.conf"));
#else // log print into console
    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplus.conf"));
#endif
}

#endif
