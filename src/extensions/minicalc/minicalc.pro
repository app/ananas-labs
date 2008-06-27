TARGET    = aextminicalc
	
SOURCES	+= acalc.cpp aminicalc.cpp
HEADERS	+= acalc.h aminicalc.h


include ( ../../ananas.pri )

shared {
win32:DEFINES+= ANANAS_DLL
} else {
win32:DEFINES   += ANANAS_NO_DLL
}

TEMPLATE	=lib
CONFIG	+= plugin

INCLUDEPATH	+= ../../lib 
LIBS	+= -L../../lib -lananas

LANGUAGE	= C++
win32:DESTDIR = ..

unix{
	libext.path = $(LIBDIR)/ananas
	libext.files = libaextminicalc.so
        INSTALLS += libext
}

