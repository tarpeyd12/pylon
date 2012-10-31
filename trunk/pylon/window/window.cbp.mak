# -*- mode: Makefile; -*-
# -----------------------------------------
# project main


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
INCLUDES = -I$(_GLUT.INCLUDE) -I$(_PYTHON.LIB) -I$(_PYTHON.INCLUDE) 
LDFLAGS = -L$(_GLUT.LIB) -L$(_PYTHON.LIB)  -s
RCFLAGS = 
LDLIBS = $(T_LDLIBS) -l$(_GLUT.LFLAGS) -l$(_GLU.LFLAGS) -l$(_OPENGL.LFLAGS) -l$(_PYTHON.LFLAGS) -lpthread  -lstdc++

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
	
all.targets : Debug_target Release_target Development_target Unitary_Debug_target Unitary_Release_target Unitary_Development_target 

clean :
	rm -fv $(clean.OBJ)
	rm -fv $(DEP_FILES)

.PHONY: all clean distclean

# -----------------------------------------
# Debug_target

Debug_target.BIN = ../bin/Debug/pylon.exe
Debug_target.OBJ = calcthread.o cmd.o globals.o info.o init.o main.o mainscriptdefs.o scriptthread.o 
DEP_FILES += calcthread.d cmd.d globals.d info.d init.d main.d mainscriptdefs.d scriptthread.d 
clean.OBJ += $(Debug_target.BIN) $(Debug_target.OBJ)

Debug_target : Debug_target.before $(Debug_target.BIN) Debug_target.after_always
Debug_target : CFLAGS += -g -DPYLON_DEBUG_VERSION  -Os
Debug_target : INCLUDES += -I../bin/Debug 
Debug_target : RCFLAGS += -I../bin/Debug/Data 
Debug_target : LDFLAGS += -L../bin/Debug   
Debug_target : T_LDLIBS = -lpogelscriptinterface -lrenderer -lobjectloader -lscriptengine -lfileloader -lpogel -llists -lsoil -lthreads 
ifdef LMAKE
Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Debug_target.before :
	
	
Debug_target.after_always : $(Debug_target.BIN)
	[[ if (PLATFORM == PLATFORM_MSW) { print (_T("..\\createDebugArchive.bat")); } else { print (_T("../createDebugArchive")); } ]]
$(Debug_target.BIN) : $(Debug_target.OBJ)
	$(LINK_con)
	

# -----------------------------------------
# Release_target

Release_target.BIN = ../bin/Release/pylon.exe
Release_target.OBJ = calcthread.o cmd.o globals.o info.o init.o main.o mainscriptdefs.o scriptthread.o 
DEP_FILES += calcthread.d cmd.d globals.d info.d init.d main.d mainscriptdefs.d scriptthread.d 
clean.OBJ += $(Release_target.BIN) $(Release_target.OBJ)

Release_target : Release_target.before $(Release_target.BIN) Release_target.after_always
Release_target : CFLAGS += -fomit-frame-pointer  -Os
Release_target : INCLUDES += -I../bin/Release 
Release_target : RCFLAGS += -I../bin/Release/Data 
Release_target : LDFLAGS += -L../bin/Release   
Release_target : T_LDLIBS = -lpogelscriptinterface -lrenderer -lobjectloader -lscriptengine -lfileloader -lpogel -llists -lsoil -lthreads 
ifdef LMAKE
Release_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Release_target.before :
	
	
Release_target.after_always : $(Release_target.BIN)
	[[ if (PLATFORM == PLATFORM_MSW) { print (_T("..\\createReleaseArchive.bat")); } else { print (_T("../createReleaseArchive")); } ]]
$(Release_target.BIN) : $(Release_target.OBJ)
	$(LINK_exe)
	

# -----------------------------------------
# Development_target

Development_target.BIN = ../bin/Release/pylon_dev.exe
Development_target.OBJ = calcthread.o cmd.o globals.o info.o init.o main.o mainscriptdefs.o scriptthread.o 
DEP_FILES += calcthread.d cmd.d globals.d info.d init.d main.d mainscriptdefs.d scriptthread.d 
clean.OBJ += $(Development_target.BIN) $(Development_target.OBJ)

Development_target : Development_target.before $(Development_target.BIN) Development_target.after_always
Development_target : CFLAGS += -fomit-frame-pointer -DPYLON_DEV_VERSION  -Os
Development_target : INCLUDES += -I../bin/Release 
Development_target : RCFLAGS += -I../bin/Release/Data 
Development_target : LDFLAGS += -L../bin/Release   
Development_target : T_LDLIBS = -lpogelscriptinterface -lrenderer -lobjectloader -lscriptengine -lfileloader -lpogel -llists -lsoil -lthreads 
ifdef LMAKE
Development_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Development_target.before :
	
	
Development_target.after_always : $(Development_target.BIN)
	[[ if (PLATFORM == PLATFORM_MSW) { print (_T("..\\createReleaseArchive.bat")); } else { print (_T("../createReleaseArchive")); } ]]
$(Development_target.BIN) : $(Development_target.OBJ)
	$(LINK_con)
	

# -----------------------------------------
# Unitary_Debug_target

Unitary_Debug_target.BIN = ../bin/UnitaryDebug/pylon.exe
Unitary_Debug_target.OBJ = calcthread.o cmd.o globals.o info.o init.o main.o mainscriptdefs.o scriptthread.o 
DEP_FILES += calcthread.d cmd.d globals.d info.d init.d main.d mainscriptdefs.d scriptthread.d 
clean.OBJ += $(Unitary_Debug_target.BIN) $(Unitary_Debug_target.OBJ)

Unitary_Debug_target : Unitary_Debug_target.before $(Unitary_Debug_target.BIN) Unitary_Debug_target.after_always
Unitary_Debug_target : CFLAGS += -pg -g -DPYLON_DEBUG_VERSION  -Os
Unitary_Debug_target : INCLUDES += -I../bin/UnitaryDebug/ 
Unitary_Debug_target : RCFLAGS += 
Unitary_Debug_target : LDFLAGS += -pg -L../bin/UnitaryDebug/   
Unitary_Debug_target : T_LDLIBS = -lpogelscriptinterface -lrenderer -lobjectloader -lscriptengine -lfileloader -lpogel -llists -lsoil -lthreads 
ifdef LMAKE
Unitary_Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Unitary_Debug_target.before :
	
	
Unitary_Debug_target.after_always : $(Unitary_Debug_target.BIN)
	[[ if (PLATFORM == PLATFORM_MSW) { print (_T("..\\createUnitaryDebugArchive.bat")); } else { print (_T("../createUnitaryDebugArchive")); } ]]
$(Unitary_Debug_target.BIN) : $(Unitary_Debug_target.OBJ)
	$(LINK_con)
	

# -----------------------------------------
# Unitary_Release_target

Unitary_Release_target.BIN = ../bin/UnitaryRelease/pylon.exe
Unitary_Release_target.OBJ = calcthread.o cmd.o globals.o info.o init.o main.o mainscriptdefs.o scriptthread.o 
DEP_FILES += calcthread.d cmd.d globals.d info.d init.d main.d mainscriptdefs.d scriptthread.d 
clean.OBJ += $(Unitary_Release_target.BIN) $(Unitary_Release_target.OBJ)

Unitary_Release_target : Unitary_Release_target.before $(Unitary_Release_target.BIN) Unitary_Release_target.after_always
Unitary_Release_target : CFLAGS += -fomit-frame-pointer  -Os
Unitary_Release_target : INCLUDES += -I../bin/UnitaryRelease 
Unitary_Release_target : RCFLAGS += -I../bin/UnitaryRelease/Data 
Unitary_Release_target : LDFLAGS += -L../bin/UnitaryRelease   
Unitary_Release_target : T_LDLIBS = -lpogelscriptinterface -lrenderer -lobjectloader -lscriptengine -lfileloader -lpogel -llists -lsoil -lthreads 
ifdef LMAKE
Unitary_Release_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Unitary_Release_target.before :
	
	
Unitary_Release_target.after_always : $(Unitary_Release_target.BIN)
	[[ if (PLATFORM == PLATFORM_MSW) { print (_T("..\\createUnitaryReleaseArchive.bat")); } else { print (_T("../createUnitaryReleaseArchive")); } ]]
$(Unitary_Release_target.BIN) : $(Unitary_Release_target.OBJ)
	$(LINK_exe)
	

# -----------------------------------------
# Unitary_Development_target

Unitary_Development_target.BIN = ../bin/UnitaryRelease/pylon_dev.exe
Unitary_Development_target.OBJ = calcthread.o cmd.o globals.o info.o init.o main.o mainscriptdefs.o scriptthread.o 
DEP_FILES += calcthread.d cmd.d globals.d info.d init.d main.d mainscriptdefs.d scriptthread.d 
clean.OBJ += $(Unitary_Development_target.BIN) $(Unitary_Development_target.OBJ)

Unitary_Development_target : Unitary_Development_target.before $(Unitary_Development_target.BIN) Unitary_Development_target.after_always
Unitary_Development_target : CFLAGS += -fomit-frame-pointer -DPYLON_DEV_VERSION  -Os
Unitary_Development_target : INCLUDES += -I../bin/UnitaryRelease 
Unitary_Development_target : RCFLAGS += -I../bin/Release/Data 
Unitary_Development_target : LDFLAGS += -L../bin/UnitaryRelease   
Unitary_Development_target : T_LDLIBS = -lpogelscriptinterface -lrenderer -lobjectloader -lscriptengine -lfileloader -lpogel -llists -lsoil -lthreads 
ifdef LMAKE
Unitary_Development_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Unitary_Development_target.before :
	
	
Unitary_Development_target.after_always : $(Unitary_Development_target.BIN)
	[[ if (PLATFORM == PLATFORM_MSW) { print (_T("..\\createUnitaryReleaseArchive.bat")); } else { print (_T("../createUnitaryReleaseArchive")); } ]]
$(Unitary_Development_target.BIN) : $(Unitary_Development_target.OBJ)
	$(LINK_con)
	

# -----------------------------------------
ifdef MAKE_DEP
-include $(DEP_FILES)
endif
