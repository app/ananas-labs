TARGET    = aexttext
SOURCES	 += aexttext.cpp
HEADERS	 += aexttext.h 
include ( ../../ananas.pri )
shared {
win32:DEFINES+= ANANAS_DLL
} else {
win32:DEFINES   += ANANAS_NO_DLL
}
TEMPLATE	=lib
CONFIG	+= plugin
LIBS	+= -L../../lib -lananas
INCLUDEPATH	+= ../../lib 
LANGUAGE	= C++
win32:DESTDIR = ..
#win32:DLLDESTDIR	= ..

unix{
	libext.path = $(LIBDIR)/ananas 
	libext.files = libaexttext.so
	INSTALLS += libext
}
