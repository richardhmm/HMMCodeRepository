
AUTOMAKE_OPTIONS = foreign

noinst_LIBRARIES = libdemo.a

bin_PROGRAMS = c_demo
 
c_demo_LDADD = libdemo.a

c_demo_SOURCES = main.c

libdemo_a_SOURCES = debug.c \
	 tcp_server.c \
	 sh_exec.c \
	 safe.c \
	 minIni.c \
	 commandline.c \
	 udp_server.c

noinst_HEADERS = debug.h \
	 tcp_server.h \
	 sh_exec.h \
	 safe.h \
	 minGlue.h \
	 minIni.h \
	 commandline.h \
	 common.h \
	 types.h \
	 udp_server.h