TARGET	= ananas-update
include ( ../ananas.pri )
SOURCES	+= main.cpp downloader.cpp
HEADERS	+= downloader.h
	

TRANSLATIONS = \
    ../../translations/ananas-update-en.ts \
    ../../translations/ananas-update-ru.ts 
	
#FORMS	= qadocjournal.ui
TEMPLATE	= app
INCLUDEPATH	+= ../lib ../lib/.ui

LIBS	+= -L../lib -lananas -L../plugins -lananasplugin
