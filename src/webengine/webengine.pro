#project for Web Enginer application from Ananas automation accounting system
TARGET	= ananas-webengine
include ( ../ananas.pri )
SOURCES	+= main.cpp httpdaemon.cpp clientsocket.cpp
HEADERS	+= httpdaemon.h \
	    clientsocket.h
	
#load(qsa)

TRANSLATIONS = \
    ../../translations/ananas-webengine-en.ts \
    ../../translations/ananas-webengine-ru.ts 
	
#FORMS	= qadocjournal.ui
TEMPLATE	=app
INCLUDEPATH	+= ../lib ../lib/.ui

LIBS	+= -L../lib -lananas -L../plugins -lananasplugin
#LIBS	+= -L$(QTDIR)/lib -lqsa -ldesignercore -lqassistantclient 
#LIBS	+= -L../lib -lananas -L../plugins -lqui -lananasplugin

