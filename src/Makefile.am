FLAGS = -O2 -Wall -fPIC

include_HEADERS = msg.h bmp.h
lib_LTLIBRARIES = libbmp.la
libbmp_la_SOURCES = msg.c msg.h bmp.c bmp.h
libbmp_la_CFLAGS = $(FLAGS)
libbmp_la_CPPFLAGS = $(FLAGS)
libbmp_la_CXXFLAGS = $(FLAGS)
libbmp_la_LDFLAGS = -shared -module
