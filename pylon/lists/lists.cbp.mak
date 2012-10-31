# -*- mode: Makefile; -*-
# -----------------------------------------
# project lists


export PATH := /opt/wx/2.8/bin:$(PATH)
export LD_LIBRARY_PATH := /opt/wx/2.8/lib:$(LD_LIBRARY_PATH)

_WX = /home/gr/projects/gui/codeblocks/wx
_WX.LIB = $(_WX)/lib
_WX.INCLUDE = $(_WX)/include

_CB = /home/gr/projects/gui/codeblocks/cb/src
_CB.INCLUDE = $(_CB)/include
_CB.LIB = $(_CB)/devel



CFLAGS_C = $(filter-out -include "sdk.h",$(CFLAGS))

# -----------------------------------------

# MAKE_DEP = -MMD -MT $@ -MF $(@:.o=.d)

CFLAGS = -fexceptions -Wall -Wextra 
INCLUDES = 
LDFLAGS =  -s
RCFLAGS = 
LDLIBS = $(T_LDLIBS)  -lstdc++

LINK_exe = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS)
LINK_con = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS)
LINK_dll = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS) -shared
LINK_lib = rm -f $@ && ar rcs $@ $^
COMPILE_c = gcc $(CFLAGS_C) -o $@ -c $< $(MAKEDEP) $(INCLUDES)
COMPILE_cpp = g++ $(CFLAGS) -o $@ -c $< $(MAKEDEP) $(INCLUDES)
COMPILE_rc = windres $(RCFLAGS) -J rc -O coff -i $< -o $@ -I$(dir $<)

%.o : %.c ; $(COMPILE_c)
%.o : %.cpp ; $(COMPILE_cpp)
%.o : %.cxx ; $(COMPILE_cpp)
%.o : %.rc ; $(COMPILE_rc)
.SUFFIXES: .o .d .c .cpp .cxx .rc

all: all.before all.targets all.after

all.before :
	-
all.after : $(FIRST_TARGET)
	
all.targets : Debug_target Release_target Unitary_Debug_target Unitary_Release_target 

clean :
	rm -fv $(clean.OBJ)
	rm -fv $(DEP_FILES)

.PHONY: all clean distclean

# -----------------------------------------
# Debug_target

Debug_target.BIN = ../bin/Debug/liblists.a
Debug_target.OBJ = bitlist.o lists.o 
DEP_FILES += bitlist.d lists.d 
clean.OBJ += $(Debug_target.BIN) $(Debug_target.OBJ)

Debug_target : Debug_target.before $(Debug_target.BIN) Debug_target.after_always
Debug_target : CFLAGS += -g  -Os
Debug_target : INCLUDES += 
Debug_target : RCFLAGS += 
Debug_target : LDFLAGS +=   $(CREATE_DEF)
Debug_target : T_LDLIBS = 
ifdef LMAKE
Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Debug_target.before :
	
	
Debug_target.after_always : $(Debug_target.BIN)
	
$(Debug_target.BIN) : $(Debug_target.OBJ)
	$(LINK_lib)
	

# -----------------------------------------
# Release_target

Release_target.BIN = ../bin/Release/liblists.a
Release_target.OBJ = bitlist.o lists.o 
DEP_FILES += bitlist.d lists.d 
clean.OBJ += $(Release_target.BIN) $(Release_target.OBJ)

Release_target : Release_target.before $(Release_target.BIN) Release_target.after_always
Release_target : CFLAGS += -fomit-frame-pointer  -Os
Release_target : INCLUDES += 
Release_target : RCFLAGS += 
Release_target : LDFLAGS +=   $(CREATE_DEF)
Release_target : T_LDLIBS = 
ifdef LMAKE
Release_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Release_target.before :
	
	
Release_target.after_always : $(Release_target.BIN)
	
$(Release_target.BIN) : $(Release_target.OBJ)
	$(LINK_lib)
	

# -----------------------------------------
# Unitary_Debug_target

Unitary_Debug_target.BIN = ../bin/UnitaryDebug/liblists.a
Unitary_Debug_target.OBJ = bitlist.o lists.o 
DEP_FILES += bitlist.d lists.d 
clean.OBJ += $(Unitary_Debug_target.BIN) $(Unitary_Debug_target.OBJ)

Unitary_Debug_target : Unitary_Debug_target.before $(Unitary_Debug_target.BIN) Unitary_Debug_target.after_always
Unitary_Debug_target : CFLAGS += -pg -g  -Os
Unitary_Debug_target : INCLUDES += 
Unitary_Debug_target : RCFLAGS += 
Unitary_Debug_target : LDFLAGS += -pg   $(CREATE_DEF)
Unitary_Debug_target : T_LDLIBS = 
ifdef LMAKE
Unitary_Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Unitary_Debug_target.before :
	
	
Unitary_Debug_target.after_always : $(Unitary_Debug_target.BIN)
	
$(Unitary_Debug_target.BIN) : $(Unitary_Debug_target.OBJ)
	$(LINK_lib)
	

# -----------------------------------------
# Unitary_Release_target

Unitary_Release_target.BIN = ../bin/UnitaryRelease/liblists.a
Unitary_Release_target.OBJ = bitlist.o lists.o 
DEP_FILES += bitlist.d lists.d 
clean.OBJ += $(Unitary_Release_target.BIN) $(Unitary_Release_target.OBJ)

Unitary_Release_target : Unitary_Release_target.before $(Unitary_Release_target.BIN) Unitary_Release_target.after_always
Unitary_Release_target : CFLAGS += -fomit-frame-pointer  -Os
Unitary_Release_target : INCLUDES += 
Unitary_Release_target : RCFLAGS += 
Unitary_Release_target : LDFLAGS +=   $(CREATE_DEF)
Unitary_Release_target : T_LDLIBS = 
ifdef LMAKE
Unitary_Release_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Unitary_Release_target.before :
	
	
Unitary_Release_target.after_always : $(Unitary_Release_target.BIN)
	
$(Unitary_Release_target.BIN) : $(Unitary_Release_target.OBJ)
	$(LINK_lib)
	

# -----------------------------------------
ifdef MAKE_DEP
-include $(DEP_FILES)
endif
