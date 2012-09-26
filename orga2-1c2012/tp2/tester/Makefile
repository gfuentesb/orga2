PYTHON=python

.PHONY: clean

ifeq ($(THISDIR),)
THISDIR:=$(CURDIR)
endif

IMGS_DIRS=img
PROC_DIRS=$(IMGS_DIRS)/proc
DIRS=$(PROC_DIRS)

DATA=data/blit.bmp data/blitsmall.bmp

PATH_TESTS=$(THISDIR)/../imgs/tests
PATH_TESTS_CATEDRA=$(THISDIR)/../imgs/catedra
IMGS_ORIG=$(shell ls $(PATH_TESTS)/*.jpg)
IMGS_ORIG_BASE=$(notdir $(IMGS_ORIG))
IMAGENES=$(patsubst %, ${IMGS_DIRS}/%, ${IMGS_ORIG_BASE})
IMGS_ORIG_CATEDRA=$(shell ls $(PATH_TESTS_CATEDRA))
IMAGENES_CATEDRA=$(patsubst %, ${PROC_DIRS}/%, ${IMGS_ORIG_CATEDRA})
OBJ=$(THISDIR)/tpcopados

bindings.so: $(DIRS) $(DATA) $(IMAGENES) $(IMAGENES_CATEDRA) $(OBJ)
	$(PYTHON) setup.py -root $(THISDIR) build
	cp build/lib.linux-x86_64-*/bindings.so .

$(IMGS_DIRS)/%.jpg:
	cp $(PATH_TESTS)/$(@F) $@
	
$(PROC_DIRS)/%.bmp:
	cp $(PATH_TESTS_CATEDRA)/$(@F) $@

data/%.bmp:
	mkdir -p data
	cp $(THISDIR)/$@ data/

clean:
	rm -rf build
	rm -f bindings.so
	rm -rf data
	

$(DIRS):
	mkdir -p $@
