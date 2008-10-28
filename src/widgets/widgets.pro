TEMPLATE	= lib 
CONFIG		+= warn_on link_prl
shared:CONFIG 	+= qt dll
unix:VERSION 	= 1.0.1

TARGET 		= ananaswidgets

SOURCES	+= \
	messageswindow.cpp \	
	amenubar.cpp \
	awidget.cpp \
	aform.cpp \
	engine.cpp \
#	areportbrowser.cpp \
	awindowslist.cpp 
	
HEADERS	+= \
	messageswindow.h \
	amenubar.h \
	awidget.h \
	aform.h \
	engine.h \
#	areportbrowser.h \
	awindowslist.h 
unix{
	alib.path = $(LIBDIR) 
	alib.files = libananaswidgets.so.$$VERSION
	alib.extra = cp -df libananaswidgets.so* $(INSTALL_ROOT)$(LIBDIR)

	alibheader.path = $(INCLUDEDIR)
	alibheader.files = $$HEADERS
	alibheader.files += .ui/*h
    }

win32 {
	alib.path = $(QTDIR)\lib
	alib.files = ananaswidgets.dll
	alib.files += ananaswidgets.lib
#	alibheader.path = $(INCLUDEDIR)
#	alibheader.files = $$HEADERS
#	alibheader.files += tmp\ui\*h
      }

INSTALLS += alib
unix{
	INSTALLS += alibheader
}


shared {
	win32:DEFINES	+= ANANAS_DLL
} else {
	win32:DEFINES   += ANANAS_NO_DLL
}

# prodject file of Ananas Library
include ( ../ananas.pri )



win32 {
  CONFIG -= console
#  CONFIG += dll
}

TRANSLATIONS = \
    ../../translations/ananas-widgets-en.ts \
    ../../translations/ananas-widgets-ru.ts 


FORMS	= deditrc.ui \
	dselectdb.ui \
	dlogin.ui
IMAGES	= images/lib_database.png \
	images/lib_dbgroup.png \
	images/print.png

#INCLUDEPATH	+= ../plugins
LANGUAGE	= C++
LIBS		+= -L$(QTDIR)/plugins/designer -lqsa -L../designer -lformdesigner 
unix{
LIBS		+=  -L/usr/X11R6/lib/
}

LIBS		-= -L..\..\plugins -lananasplugin
