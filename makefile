pkgname=$(patsubst %.ins,%,$(wildcard *.ins))
all: $(pkgname).pdf

%.pdf: generator/%.cpp %.ins
	cd generator && make
	generator/$(pkgname)
	-rm $(pkgname).sty
	latex $(pkgname).ins
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

localinstall: all
	mkdir -p /usr/share/texlive/texmf-local/tex/latex/$(pkgname)
	mkdir -p /usr/share/texlive/texmf-local/doc/latex/$(pkgname)
	cp $(pkgname).sty /usr/share/texlive/texmf-local/tex/latex/$(pkgname)/.
	cp $(pkgname).pdf /usr/share/texlive/texmf-local/doc/latex/$(pkgname)/.
	texhash

distinstall: all
	mkdir -p /usr/share/texlive/texmf-dist/tex/latex/$(pkgname)
	mkdir -p /usr/share/texlive/texmf-dist/doc/latex/$(pkgname)
	cp $(pkgname).sty /usr/share/texlive/texmf-dist/tex/latex/$(pkgname)/.
	cp $(pkgname).pdf /usr/share/texlive/texmf-dist/doc/latex/$(pkgname)/.
	texhash

