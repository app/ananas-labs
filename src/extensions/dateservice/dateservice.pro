TARGET    = aextdateservice
	
SOURCES	+= adateservice.cpp 
HEADERS	+= adateservice.h 

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
	libext.files = libaextdateservice.so
        INSTALLS += libext
}

