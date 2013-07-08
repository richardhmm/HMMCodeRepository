#   Copyright (c) 2013 richard.hmm
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

VERSION = 0.0.1

CC = g++

PROG = main

SRCS = main.cpp
#CFLAGS += -Wextra -I ../../lib/algorithm/inc/
CPPFLAGS += -Wextra -I ../../lib/algorithm/inc/
LDFLAGS += ../../lib/algorithm/dist/libalgorithm.a
LOGFLAGS += -llog4cplus -lpthread -lrt

all: $(PROG)

OBJS = $(SRCS:.cpp=.o)

.cpp.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LOGFLAGS)

clean:
	$(RM) $(PROG) $(OBJS)
