# Makefile.am is used with REX compiler such that libaccparser.la is built and linked into librose lib.
# accparser is a submodule of REX under folder src/frontend/SageIII and the source files of accparser are built into libaccparser.la, which then be added to libsage3.la which is added to librose.so. 
#
# This file is not needed to build the standalone accparser.
# 
include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

AM_CPPFLAGS = -I/usr/include/antlr4-runtime -I$(top_builddir)/src/frontend/SageIII/accparser -I$(top_srcdir)/src/frontend/SageIII/accparser/src -I.
AM_LDFLAGS = -lantlr4-runtime

# There is a bug in Antlr 4 on Linux. It can't recognize -o arguments that specify the output folder. The generated files are always at the same location as .g4 inputs.
# Thus, we copy the g4 files to the build folder first and then generate outputs there.
# https://github.com/antlr/antlr4/issues/3138
# https://github.com/antlr/grammars-v4/pull/2111
acclexer.cpp: $(top_srcdir)/src/frontend/SageIII/accparser/src/acclexer.g4
	cp $(top_srcdir)/src/frontend/SageIII/accparser/src/acclexer.g4 $(top_builddir)/src/frontend/SageIII/accparser/.
	antlr4 acclexer.g4 -Werror -Dlanguage=Cpp -listener -visitor -o .

# acclexer outputs must be generated before handling accparser
accparser.cpp: acclexer.cpp $(top_srcdir)/src/frontend/SageIII/accparser/src/accparser.g4
	cp $(top_srcdir)/src/frontend/SageIII/accparser/src/accparser.g4 $(top_builddir)/src/frontend/SageIII/accparser/.
	antlr4 accparser.g4 -Werror -Dlanguage=Cpp -listener -visitor -o .

acclexer.lo:  acclexer.cpp
accparser.lo:  accparser.cpp

noinst_LTLIBRARIES = libaccparser.la
libaccparser_la_SOURCES = $(top_builddir)/src/frontend/SageIII/accparser/acclexer.cpp $(top_builddir)/src/frontend/SageIII/accparser/accparser.cpp src/OpenACCIR.cpp src/OpenACCIRToString.cpp src/OpenACCASTConstructor.cpp

pkginclude_HEADERS = src/OpenACCASTConstructor.h src/OpenACCIR.h src/OpenACCKinds.h

BUILT_SOURCES = acclexer.cpp accparser.cpp

clean-local:
	rm -f *.la
