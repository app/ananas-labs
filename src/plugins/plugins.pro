TARGET    = ananasplugin
SOURCES	+= wtable.cpp \
	catalogformwidgets.cpp \
	wcatalogeditor.cpp \
	wdateedit.cpp \
	wdbtable.cpp \
	wdbfield.cpp \
	wfield.cpp \
	wcatalogue.cpp \
	wdocument.cpp \
	plugins.cpp \
	wgrouptree.cpp \
	wjournal.cpp \
	wreport.cpp \
	wactionbutton.cpp\
	aform.cpp \
	atoolbar.cpp \
	engine.cpp \
	acombobox.cpp
				
HEADERS	+= wtable.h \
	catalogformwidgets.h \
	wcatalogeditor.h \
	wdateedit.h \
	wdbtable.h \
	wfield.h \
	wdbfield.h \
	wcatalogue.h \
	wdocument.h \
	plugins.h \
	wgrouptree.h \
	wjournal.h \
	wreport.h \
	wactionbutton.h \
	atoolbar.h \
	engine.h \
	aform.h \
	acombobox.h

# project file of Ananas plugins
unix {
    INCLUDEPATH	+=../designer/.ui
    system($QTDIR/bin/uic ../designer/mainform.ui -o mainform.h)
    system($QTDIR/bin/uic ../designer/cfgform.ui -o cfgform.h)
}
win32 {
    INCLUDEPATH	+=..\designer\tmp\ui
    system(%QTDIR%\bin\uic ..\designer\mainform.ui -o mainform.h)
    system(%QTDIR%\bin\uic ..\designer\cfgform.ui -o cfgform.h)
}

include ( ../ananas.pri )
#SLASH = /
unix {
	lplugin.path = $(LIBDIR)/ananas/qt3plugins/designer
	lplugin.files = libananasplugin.so
	lpluginheader.path = $(INCLUDEDIR)
	lpluginheader.files = $$HEADERS
}  

win32 {
	target.path = $(QTDIR)\plugins\designer
	lplugin.path = $(QTDIR)\plugins\designer
	lplugin.files = ananasplugin.*
	lplugin.extra = copy ananasplugin.* $(QTDIR)\lib
     }  

INSTALLS    += lplugin 
unix{
	INSTALLS += lpluginheader
}


shared {
win32:DEFINES+= ANANAS_DLL
} else {
win32:DEFINES   += ANANAS_NO_DLL
}

TRANSLATIONS = \
    ../../translations/ananas-plugins-en.ts \
    ../../translations/ananas-plugins-ru.ts 
	
FORMS	= edbtable.ui \
	addfdialog.ui \
	edbfield.ui \
	efield.ui \
	ecatalogue.ui \
	ejournal.ui \
	ereport.ui \
	edocument.ui \
	eaddobj.ui \
	catalogform.ui \
	eactionbutton.ui \
	eselectdoctype.ui
IMAGES	= images/wcatalogue.png \
	images/wdocument.png \
	images/wfield.png \
	images/wdbfield.png \
	images/wtable.png \
	images/wdbtable.png \
	images/wgrouptree.png \
	images/wjournal.png \
	images/wreport.png \
	images/wactionbutton.png \
	images/doc_new.png \
	images/doc_edit.png \
	images/doc_view.png \
	images/doc_copy.png \
	images/doc_delete.png \
	images/acombobox.png \
	images/calendar.png
	
TEMPLATE	=lib
CONFIG	+= plugin
INCLUDEPATH	+= ../designer/formdesigner ../lib ../designer
LIBS	+= -L../lib -lananas -L$(QTDIR)/lib  -L../designer -lformdesigner -lqsa -lqassistantclient
unix{
LIBS	+=  -L/usr/X11R6/lib/
}
LIBS	-= -L..\..\plugins -lananasplugin
LANGUAGE	= C++
