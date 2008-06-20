TARGET	= demo4
include ( ../../ananas.pri )
SOURCES	+= main.cpp 
HEADERS	+= 
#load(qsa)
TRANSLATES = 

FORMS	= 
TEMPLATE	=app
INCLUDEPATH	+= 
LIBS	+= -L$(QTDIR)/lib -lqui -L../../lib -lananas
LIBS	+= -L../../plugins -lananasplugin
