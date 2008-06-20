TEMPLATE	= app
LANGUAGE	= C++

LIBS	+= -L$(QTDIR)/lib -L../lib -lananas -L../plugins -lqui -lananasplugin -lqsa

INCLUDEPATH	+= ../lib ../lib/tmp/ui ../lib/.ui

HEADERS	+= atreeitems.h \
	mdtree.h

SOURCES	+= main.cpp \
	atreeitems.cpp \
	mdtree.cpp

FORMS	= mainform.ui \
	usersform.ui \
	rolesform.ui \
	deditpermissions.ui \
	dselectuser.ui \
	deditrole.ui \
	dedituser.ui \
	dselectrole.ui

IMAGES	= ../../icons/a-system.png \
	images/administrator-splash-en.png \
	images/administrator-splash-ru.png \
	images/cat.png \
	images/cat_g.png \
	images/doc.png \
	images/doc_g.png \
	images/journ.png \
	images/journ_g.png \
	images/reg_g.png \
	images/reg.png \
	images/user.png \
	images/users.png \
	images/metadata.png \
	images/role.png \
	images/regs.png \
	images/report.png \
	images/report_g.png

#project for Administrator application from Ananas automation accounting system
TARGET	= ananas-administrator
include ( ../ananas.pri )


	
TRANSLATIONS = \
    ../../translations/ananas-administrator-en.ts \
    ../../translations/ananas-administrator-ru.ts 
	
