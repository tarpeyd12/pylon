# -*- mode: Makefile; -*-
# -----------------------------------------
# workspace Pylon Engine

all :

% :
	$(MAKE) -C threads -f threads.cbp.mak $@
	$(MAKE) -C soil -f soil.cbp.mak $@
	$(MAKE) -C lists -f lists.cbp.mak $@
	$(MAKE) -C pogel -f pogel.cbp.mak $@
	$(MAKE) -C fileloader -f fileloader.cbp.mak $@
	$(MAKE) -C scriptengine -f scriptengine.cbp.mak $@
	$(MAKE) -C objectloader -f objectloader.cbp.mak $@
	$(MAKE) -C renderer -f renderer.cbp.mak $@
	$(MAKE) -C pogelscriptinterface -f pogelscriptinterface.cbp.mak $@
	$(MAKE) -C window -f window.cbp.mak $@
	$(MAKE) -C bloop -f bloop.cbp.mak $@
