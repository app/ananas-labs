TEMPLATE	= app
LANGUAGE	= C++

#LIBS	+= -L../lib -L../plugins -lananas -lananasplugin -lqsa -ldesignercore -lqassistantclient
LIBS	+= -L. -L../lib -L../plugins -lananas -lananasplugin -lqsa -lformdesigner -lqassistantclient 
LIBS    += -L$(QTDIR)/lib -lqdataschema

#INCLUDEPATH	+= ../lib ../lib/tmp/ui ../lib/.ui $(QTDIR)/tools/designer/designer ../../qt-headers/tools/designer/designer /usr/lib
INCLUDEPATH	+= ../lib ../lib/tmp/ui ../lib/.ui ./formdesigner /usr/lib

unix {
    INCLUDEPATH +=./formdesigner/.ui
}
win32 {
    INCLUDEPATH +=.\formdesigner\tmp\ui
}

HEADERS	+= mdtree.h \
	formdesigner.h \
	actiontree.h \
	interfacetree.h \
	aliaseditor.h \
	pixmappreview.h \
	atreeitems.h \
	roleeditor.h

SOURCES	+= main.cpp \
	mdtree.cpp \
	formdesigner.cpp \
	interfacetree.cpp \
	actiontree.cpp \
	aliaseditor.cpp \
	atreeitems.cpp \
	roleeditor.cpp

FORMS	= mainform.ui \
	deditfield.ui \
	cfgform.ui \
	deditcfg.ui \
	deditdoc.ui \
	deditdialog.ui \
	deditcat.ui \
	deditreport.ui \
	deditireg.ui \
	deditareg.ui \
	deditlang.ui \
	deditaction.ui \
	deditcolumns.ui \
	deditwebform.ui \
	deditjournal.ui \
	dedittoolbar.ui \
	deditcommand.ui \
	deditrole.ui

IMAGES	= images/print.png \
	images/editcopy.png \
	images/editcut.png \
	images/editdelete.png \
	images/editpaste.png \
	images/filenew.png \
	images/fileopen.png \
	images/filesave.png \
	images/function.png \
	images/help.png \
	images/hi22-action-project_open.png \
	images/hi22-action-run.png \
	images/object.png \
	images/play.png \
	images/playprev.png \
	images/project.png \
	images/qsa.png \
	images/redo.png \
	images/script.png \
	images/scriptnew.png \
	images/scriptobject.png \
	images/searchfind.png \
	images/a-system.png \
	images/form.png \
	images/form_g.png \
	images/doc.png \
	images/doc_g.png \
	images/field.png \
	images/journ.png \
	images/journ_g.png \
	images/reg.png \
	images/reg_g.png \
	images/regs.png \
	images/regs_g.png \
	images/report.png \
	images/report_g.png \
	images/table.png \
	images/table_g.png \
	images/cat.png \
	images/cat_g.png \
	images/msg_info.png \
	images/msg_warning.png \
	images/msg_error.png \
	images/msg_fatal.png \
	images/arrow_up.png \
	images/arrow_down.png \
	images/arrow_left.png \
	images/arrow_right.png \
	images/d_editdelete.png \
	images/designer-splash-en.png \
	images/designer-splash-ru.png \
	images/editedit.png \
	images/editrename.png \
	images/editsep.png \
	images/doc_h.png \
	images/action_g.png \
	images/actions.png \
	images/columns.png \
	images/dimensions.png \
	images/group.png \
	images/information.png \
	images/m_menu.png \
	images/p_menus.png \
	images/resourses.png \
	images/submenu.png \
	images/toolbar.png \
	images/undo.png \
	images/element.png \
	images/separator.png \
	images/webform.png \
	images/webform_g.png \
	images/ananas-32x32.png

TARGET = ananas-designer
#project for Designer application from Ananas automation accounting system
include ( ../ananas.pri )


TRANSLATIONS = \
    ../../translations/ananas-designer-en.ts \
    ../../translations/ananas-designer-ru.ts 

unix {
	adesigner.path = $(BINDIR)
	adesigner.files = ananas-designer
	adesigner.extra = cp -df ananas-designer $(INSTALL_ROOT)$(BINDIR)
#	acfg.path = /etc/ananas
#	acfg.files= testwrite.cfg
     }	

INSTALLS += adesigner

