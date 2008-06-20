TEMPLATE = subdirs
SUBDIRS  = designer/formdesigner lib plugins
SUBDIRS += designer demo ananas admin webengine test
SUBDIRS += plugins/mysql
SUBDIRS += extensions update

TRANSLATIONS = \
    ../translations/ananas-en.ts \
    ../translations/ananas-ru.ts 
