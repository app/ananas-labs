TARGET	= tests.begin 
include ( ../../ananas.pri )
SOURCES	+= main.cpp 
HEADERS	+= 
TRANSLATES = 

DESTDIR = ../../..
FORMS	= 
TEMPLATE	=app
INCLUDEPATH	+= 
LIBS	+= -L$(QTDIR)/lib -lqui -lqsa -L../../lib -lananas
LIBS	+= -L../../plugins -lananasplugin
