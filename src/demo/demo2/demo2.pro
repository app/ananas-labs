TARGET	= demo2
include ( ../../ananas.pri )
SOURCES	+= main.cpp
HEADERS		+=
#load(qsa)
TRANSLATES = 
	
FORMS	=
TEMPLATE	=app
INCLUDEPATH	+= 
LIBS	+= -L$(QTDIR)/lib -lqui -L../../lib -lananas -lqsa 
LIBS	+= -L../../plugins -lananasplugin
