include ( ../../ananas.pri )
TARGET	= test1 
SOURCES	+= main.cpp
HEADERS		+=
#load(qsa)
TRANSLATES = 
	
FORMS	=
TEMPLATE	=app
INCLUDEPATH	+= ../../lib ../../lib/.ui
LIBS	+= -L$(QTDIR)/lib -lqui -L../../lib -lananas -lqsa 
LIBS	+= -L../../plugins -lananasplugin
