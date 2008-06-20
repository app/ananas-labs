#SCRIPT = ananas-script-ru

#LIST = $(SCRIPT)

#DVIPSFLAGS = -Pcm

#SOURCES	=  
#HEADERS	= 
#TRANSLATES = 
	
#FORMS	= 
#TEMPLATE	= doc 
#INCLUDEPATH	= 
#TARGET = doc

doc.files = ananas-*.sxw
doc.files += *.tex
doc.path = $(DOCDIR)

QMAKE_EXTRA_UNIX_TARGETS+=doc

INSTALLS += doc

#all: $(LIST)


#$(SCRIPT): $(SCRIPT).pdf
#$(SCRIPT).pdf: $(SCRIPT).ps
#	ps2pdf $(SCRIPT).ps $(SCRIPT).pdf
#$(SCRIPT).ps: $(SCRIPT).dvi 
#	dvips $(DVIPSFLAGS) -o $(SCRIPT).ps $(SCRIPT).dvi


#$(SCRIPT).dvi: $(SCRIPT).tex $(SCRIPT).ind
#	latex $(SCRIPT).tex
#	latex $(SCRIPT).tex
## второй раз для обновления содержания
#$(SCRIPT).ind: $(SCRIPT).idx
#	makeindex $(SCRIPT).idx
#$(SCRIPT).idx: $(SCRIPT).tex
#	latex $(SCRIPT).tex -interaction=batchmode|| echo Ok




#clean:
#	rm -f *.ps *.pdf *.dvi *.log *.idx *.ind *.aux *.ilg *.toc *.out
	
