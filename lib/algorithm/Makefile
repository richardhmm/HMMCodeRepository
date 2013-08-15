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

VERSION = 1.0
LIBNAME = algorithm

CC = g++

CFLAGS += -Wextra -O1 -g -fPIC -Iinc
CPPFLAGS += -Wextra -O1 -g -fPIC -Iinc
LDFLAGS += -Wl,--as-needed
TESTFLAGS += -lgtest
LOGFLAGS += -llog4cplus -lpthread -lrt

OBJDIR=obj
DISTDIR=dist
TESTDIR=test

STATICLIBFLAGS = rcs
SHAREDLIBFLAGS = $(LDFLAGS) -shared -Wl,-soname


STATICLIB = lib$(LIBNAME).a
SHAREDLIB = lib$(LIBNAME).so

SHAREDLIBVER = $(SHAREDLIB).$(VERSION)

SRCS = $(addprefix src/, \
	QuickSort.cpp \
	BubbleSort.cpp \
	InsertSort.cpp \
	SelectSort.cpp \
	ShellSort.cpp \
	Log.cpp \
	)

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

HDRS = $(addprefix inc/, \
    Log.h \
	QuickSort.h \
	BubbleSort.h \
	InsertSort.h \
	SelectSort.h \
	ShellSort.h \
	) 

TESTS = $(addprefix test/, \
	Test_QuickSort.cpp \
	Test_BubbleSort.cpp \
	Test_InsertSort.cpp \
	Test_SelectSort.cpp \
	Test_ShellSort.cpp \
	)

TESTS_OBJS = $(TESTS:.cpp=.o)
TESTS_BINS = $(TESTS_OBJS:.o=.test)

.PHONY: all clean static shared test

all: static shared

$(OBJDIR):
	mkdir -p $@

$(DISTDIR):
	mkdir -p $@

$(OBJDIR)/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(DISTDIR)/$(STATICLIB): $(OBJS)
	$(AR) $(STATICLIBFLAGS) $(DISTDIR)/$(STATICLIB) $(OBJS)

$(DISTDIR)/$(SHAREDLIBVER): $(OBJS)
	$(CC) $(SHAREDLIBFLAGS),$(SHAREDLIB) -o $(DISTDIR)/$(SHAREDLIBVER) $(OBJS)

$(DISTDIR)/$(SHAREDLIB): $(DISTDIR)/$(SHAREDLIBVER)
	$(RM) $(DISTDIR)/$(SHAREDLIB)
	ln -s $(SHAREDLIBVER) $(DISTDIR)/$(SHAREDLIB)

static: $(DISTDIR)/$(STATICLIB)

shared: $(DISTDIR)/$(SHAREDLIB)


$(OBJS): $(HDRS) $(DISTDIR) $(OBJDIR)

clean:
	$(RM) -r $(OBJDIR) $(DISTDIR) $(TESTS_BINS) $(TESTS_OBJS)

test: static $(TESTS_BINS)
	for t in $(TESTS_BINS); do ./$$t; done


$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(TESTDIR)/%.test: $(TESTDIR)/%.o
	$(CC) $(TESTFLAGS) $< $(DISTDIR)/$(STATICLIB) -o $@ $(LDFLAGS) $(LOGFLAGS)



