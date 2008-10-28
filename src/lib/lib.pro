TEMPLATE = lib
CONFIG		+= warn_on link_prl
shared:CONFIG 	+= qt dll
unix:VERSION 	= 1.0.1

TARGET 		= ananas

SOURCES	+= acfg.cpp \
	aapplication.cpp \
	acalendar.cpp \
	acfgrc.cpp \
	adatabase.cpp \
	adatafield.cpp \
	asqlfield.cpp \
	asqltable.cpp \
	messageswindow.cpp \
	amenubar.cpp \
	aobject.cpp \
	awidget.cpp \
#	aform.cpp \
#	engine.cpp \
	airegister.cpp \
	aaregister.cpp \
	acatalogue.cpp \
	adocument.cpp \
	adocjournal.cpp \
	areport.cpp \
	awindowslist.cpp \
	atemplate.cpp \
	atime.cpp \
	itemplate.cpp \
	amsotemplate.cpp \
	aootemplate.cpp \
	auser.cpp \
	arole.cpp \
	aservice.cpp \
	atests.cpp \
	rclistviewitem.cpp \
	ananas.cpp \
	aextension.cpp \
	aextensionplugin.cpp \
	aextensionfactory.cpp \
	adataexchange.cpp \
	dimportdb.cpp \
	alog.cpp \
	aobjectlist.cpp\
	acmanifest.cpp \
	acontainer.cpp \
	acalctemplate.cpp \
	afilter.cpp \
	amoney.cpp \
	binreloc.c

HEADERS	+= ananasglobal.h \
	ananas.h \
	aapplication.h \
	acalendar.h \
	acfg.h \
	acfgrc.h \
	adatabase.h \
	adatafield.h \
	asqlfield.h \
	asqltable.h \
	messageswindow.h \
	amenubar.h \
	aobject.h \
	awidget.h \
#	aform.h \
#	engine.h \
	airegister.h \
	aaregister.h \
	acatalogue.h \
	adocument.h \
	adocjournal.h \
	areport.h \
	awindowslist.h \
	atemplate.h \
	atime.h \
	itemplate.h \
	amsotemplate.h \
	aootemplate.h \
	auser.h \
	arole.h \
	aservice.h \
	rclistviewitem.h \
	atests.h \
	aextension.h \
	aextensionplugin.h \
	aextensionfactory.h \
	adataexchange.h \
	dimportdb.h \
	alog.h \
	aobjectlist.h\
	acmanifest.h \
	acontainer.h \
	acalctemplate.h \
	afilter.h \
	amoney.h \
	binreloc.h

unix{
	alib.path = $(LIBDIR)
	alib.files = libananas.so.$$VERSION
	alib.extra = cp -df libananas.so* $(INSTALL_ROOT)$(LIBDIR)

	alibheader.path = $(INCLUDEDIR)
	alibheader.files = $$HEADERS
	alibheader.files += .ui/*h
    }

win32 {
	alib.path = $(QTDIR)\lib
	alib.files += ananas.dll
	alib.files += ananas.lib
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

#unix:DEFINES += ENABLE_BINRELOC

# prodject file of Ananas Library
include ( ../ananas.pri )



win32 {
  CONFIG -= console
#  CONFIG += dll
}

TRANSLATIONS = \
    ../../translations/ananas-lib-en.ts \
    ../../translations/ananas-lib-ru.ts


FORMS	= deditrc.ui \
	dselectdb.ui \
	dlogin.ui \
	dhelpcfgform.ui

IMAGES	= images/lib_database.png \
	images/lib_dbgroup.png \
	images/print.png \
	images/filesave.png

INCLUDEPATH	+= $(QTDIR)/include/qdataschema
LANGUAGE	= C++
LIBS		+= -L$(QTDIR)/plugins/designer -lqsa  -L../designer -lformdesigner -lqt3-qdataschema
unix{
LIBS		+=  -L/usr/X11R6/lib/
}
win32 {
#LIBS		+= -L..\..\plugins -lananasplugin
}
