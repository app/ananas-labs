#project for Engine application from Ananas automation accounting system
TARGET	= ananas
include ( ../ananas.pri )

SOURCES	+= main.cpp \
	ananasmainform.cpp
HEADERS	+= ananasmainform.h
	
#load(qsa)

TRANSLATIONS = \
    ../../translations/ananas-engine-en.ts \
    ../../translations/ananas-engine-ru.ts 
	

unix {
	ananas.path = $(BINDIR)
	ananas.files = ananas
	ananas.extra = cp -df ananas $(INSTALL_ROOT)$(BINDIR)
     }
win32{
#	ananas.path =.
#	ananas.extra = CALL create_base.bat
     }	

INSTALLS += ananas

#FORMS	= qadocjournal.ui
IMAGES	= images/a-system.png \
	images/msg_info.png \
	images/msg_warning.png \
	images/msg_error.png \
	images/msg_fatal.png \
	images/engine-splash-en.png \
	images/engine-splash-ru.png \
	images/object_markdeleted.png \
	images/document_turned.png \
	images/d_document_turned.png \
	images/field2.png \
	images/group2.png \
	images/editdelete2.png \
	images/cat.png \
	images/t_doc.png \
	images/t_doc_m.png \
	images/t_doc_tm.png \
	images/t_doc_d.png \
	images/t_doc_t.png \
	images/t_doc_to.png \
	images/t_doc_tom.png \
	images/t_cat_e.png \
	images/t_cat_g.png \
	images/t_cat_ed.png \
	images/t_cat_gd.png \
	images/lib_database.png	\
	images/lib_dbgroup.png \
	images/ananas-32x32.png
	
TEMPLATE	=app

INCLUDEPATH	+= ../lib ../lib/tmp/ui ../lib/.ui ../plugins
LIBS	+= -L$(QTDIR)/lib -lqsa  -L../lib -lananas -L../plugins -lqui -lananasplugin 
