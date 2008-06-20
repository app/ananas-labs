TARGET	= catalogue1 
include ( ../../ananas.pri )
SOURCES	+= main.cpp 
HEADERS	+= 
TRANSLATES = 

FORMS	= 
TEMPLATE	=app
INCLUDEPATH	+= 
LIBS	+= -L$(QTDIR)/lib -lqui -lqsa -L../../lib -lananas
LIBS	+= -L../../plugins -lananasplugin
