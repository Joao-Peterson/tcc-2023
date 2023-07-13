# Área de edição do usuário
####################################################################################

TEX_CC=lualatex

TEX_FLAGS=--shell-escape --interaction=batchmode --halt-on-error --synctex=-1


####################################################################################
# Área reservada (não alterar)

SYNC_LINE=1
SYNC_FILE=main.tex

VECTORS:=$(subst .svg,.pdf,$(shell find images/ -name "*.svg"))

####################################################################################

.PHONY : main.aux images beamer

quick : main.aux
	@rm -f $(shell find . -name '*.aux')

bib : main.bbl

main.aux : main.tex
	$(TEX_CC) $(TEX_FLAGS) $(basename $<).tex

build : main.aux main.bbl
	$(TEX_CC) $(TEX_FLAGS) $(basename $<).tex
	$(TEX_CC) $(TEX_FLAGS) $(basename $<).tex
	@rm -f $(shell find . -name '*.aux')

main.bbl : main.aux
	bibtex $(basename $@)

images: $(VECTORS)
	@echo -n $^

images/%.pdf: images/%.svg
	@echo -n $<
	inkscape $< --export-area-page --export-dpi 300 --export-type=pdf --export-latex --export-filename $@

beamer : beamer/main.tex
	$(TEX_CC) $(TEX_FLAGS) --output-directory=$@ $(basename $<).tex

sync :
	okular --unique --noraise main.pdf#src:$(SYNC_LINE)$(SYNC_FILE)

%.tex : %.dot
	dot2tex --crop --pgf118 --codeonly --autosize --texmode raw $^ > $@

clear : 
	@rm -f $(shell find . -name '*.csv')
	@rm -f $(shell find . -name '*.toc')
	@rm -f $(shell find . -name '*.aux')
	@rm -f $(shell find . -name '*.log')
	@rm -f $(shell find . -name '*.lol')
	@rm -f $(shell find . -name '*.out')
	@rm -f $(shell find . -name '*.synctex')
	@rm -f $(shell find . -name '*.blg')
	@rm -f $(shell find . -name '*.idx')
	@rm -f $(shell find . -name '*.lof')
	@rm -f $(shell find . -name '*.lot')
	@rm -f $(shell find . -name '*.bbl')
	@rm -f $(shell find . -name '*.nav')
	@rm -f $(shell find . -name '*.snm')


# info:
# redirect stdout and stderr to .out file, '2>&1' read as, redirect stder (2) to argument 1 ($1, "octave.out") 
# lualatex $^ $@ > latex_stdout.out 2>&1