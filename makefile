pkgname=$(patsubst %.ins,%,$(wildcard *.ins))
all: $(pkgname).pdf

.PRECIOUS: %.sty %.dtx %.pdf

%.dtx: generator/%.cpp %.ins
	cd generator && make
	generator/$(pkgname)

%.sty: %.dtx %.ins
	latex $(pkgname).ins
	
%.pdf: %.sty
	xelatex $(pkgname).dtx
	makeindex -s gind.ist -o $(pkgname).ind $(pkgname).idx
	makeindex -s gglo.ist -o $(pkgname).gls $(pkgname).glo
	xelatex $(pkgname).dtx
	xelatex $(pkgname).dtx

clean:
	cd generator && make clean
	-rm *.pdf
	-rm *.log
	-rm *.out
	-rm *.aux
	-rm *.bib
	-rm *.snm
	-rm *.toc
	-rm *.nav
	-rm *.idx
	-rm *.sty
	-rm *.gls
	-rm *.ilg
	-rm *.ind
	-rm *.glo
	-rm *.dtx
	-rm $(pkgname).zip
	-rm $(pkgname).tar
	-rm $(pkgname).tar.bz2
	-rm -r $(pkgname)

localinstall: $(pkgname).pdf $(pkgname).sty
	mkdir -p /usr/share/texlive/texmf-local/tex/latex/$(pkgname)
	mkdir -p /usr/share/texlive/texmf-local/doc/latex/$(pkgname)
	cp $(pkgname).sty /usr/share/texlive/texmf-local/tex/latex/$(pkgname)/.
	cp $(pkgname).pdf /usr/share/texlive/texmf-local/doc/latex/$(pkgname)/.
	texhash

distinstall: $(pkgname).pdf $(pkgname).sty
	mkdir -p /usr/share/texlive/texmf-dist/tex/latex/$(pkgname)
	mkdir -p /usr/share/texlive/texmf-dist/doc/latex/$(pkgname)
	cp $(pkgname).sty /usr/share/texlive/texmf-dist/tex/latex/$(pkgname)/.
	cp $(pkgname).pdf /usr/share/texlive/texmf-dist/doc/latex/$(pkgname)/.
	texhash

dist: $(pkgname).pdf $(pkgname).sty
	mkdir -p $(pkgname)
	cp $(pkgname).pdf $(pkgname)/.
	cp $(pkgname).sty $(pkgname)/.
	cp README.md $(pkgname)/.
	tar -cvf $(pkgname).tar $(pkgname)
	bzip2 $(pkgname).tar
	zip $(pkgname).zip $(pkgname)
	rm -r $(pkgname)

