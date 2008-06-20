TEMPLATE = lib
TARGET	 = qsqlmysqlu

CONFIG	+= qt plugin sql
include (../../ananas.pri)
#unix:target.path  = .
#win32:target.path = $(QTDIR)\plugins\sqldrivers
#$(LIBDIR) = /usr/lib
#system(test -d $(LIBDIR)) {
# 	$(LIBDIR)=/usr/lib
#}	
win32 {
	sqlplugin.path = $(QTDIR)\plugins\sqldrivers
	sqlplugin.files = qsqlmysqlu.*
      }		
unix  {
	sqlplugin.path = $(LIBDIR)/ananas/qt3plugins/sqldrivers
	sqlplugin.files = libqsqlmysqlu.so
      }	

#CONFIG	+= qt plugin
HEADERS		= qsql_mysql.h
SOURCES		= main.cpp \
		  qsql_mysql.cpp

unix {
	OBJECTS_DIR = .obj
        INCLUDEPATH	+= $$system(mysql_config --cflags|sed s/"-I"//)

	!contains( LIBS, .*mysql.* ) {
	    LIBS    *= $$system(mysql_config --libs) -lmysqlclient 
	}
}
win32 {
	OBJECTS_DIR = obj
	LIBS	*= libmysql.lib
        INCLUDEPATH	+= c:\mysql\include
	LIBS	+= -Lc:\mysql\lib
	LIBS	+= -Lc:\mysql\lib\opt
#	win32-msvc: {
#		LIBS *= delayimp.lib
#		QMAKE_LFLAGS += /DELAYLOAD:libmysql.dll
#	}
#	win32-borland: {
#		QMAKE_LFLAGS += /dlibmysql.dll
#	}
}

REQUIRES	= sql

INSTALLS += sqlplugin

DEFINES +=MYSQL_UTF8
