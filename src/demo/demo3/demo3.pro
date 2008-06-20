TARGET	= demo3
include ( ../../ananas.pri )
SOURCES	+= main.cpp 
HEADERS	+= 
#load(qsa)
TRANSLATES = 
	
FORMS	= 
TEMPLATE	=app
INCLUDEPATH	+= ../../plugins
LIBS	+= -L$(QTDIR)/lib -lqui -L../../lib -lananas 
LIBS	+= -L../../plugins -lananasplugin
