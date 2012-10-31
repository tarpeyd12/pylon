# -*- mode: Makefile; -*-
# -----------------------------------------
# project fileloader


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

CFLAGS = -Wextra -Wall -fexceptions -Wall -Wextra 
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

Debug_target.BIN = ../bin/Debug/libfileloader.so
Debug_target.OBJ = archivehandler.o fileloader.o ini.o minizip/ioapi.o minizip/iowin32.o minizip/mztools.o minizip/unzip.o minizip/zip.o minizip/zlib/adler32.o minizip/zlib/compress.o minizip/zlib/crc32.o minizip/zlib/deflate.o minizip/zlib/gzclose.o minizip/zlib/gzlib.o minizip/zlib/gzread.o minizip/zlib/gzwrite.o minizip/zlib/infback.o minizip/zlib/inffast.o minizip/zlib/inflate.o minizip/zlib/inftrees.o minizip/zlib/trees.o minizip/zlib/uncompr.o minizip/zlib/zutil.o simpleini/ConvertUTF.o system.o unzip.o 
DEP_FILES += archivehandler.d fileloader.d ini.d minizip/ioapi.d minizip/iowin32.d minizip/mztools.d minizip/unzip.d minizip/zip.d minizip/zlib/adler32.d minizip/zlib/compress.d minizip/zlib/crc32.d minizip/zlib/deflate.d minizip/zlib/gzclose.d minizip/zlib/gzlib.d minizip/zlib/gzread.d minizip/zlib/gzwrite.d minizip/zlib/infback.d minizip/zlib/inffast.d minizip/zlib/inflate.d minizip/zlib/inftrees.d minizip/zlib/trees.d minizip/zlib/uncompr.d minizip/zlib/zutil.d simpleini/ConvertUTF.d system.d unzip.d 
clean.OBJ += $(Debug_target.BIN) $(Debug_target.OBJ)

Debug_target : Debug_target.before $(Debug_target.BIN) Debug_target.after_always
Debug_target : CFLAGS += -g  -Os
Debug_target : INCLUDES += 
Debug_target : RCFLAGS += 
Debug_target : LDFLAGS += -L../bin/Debug  $(CREATE_LIB) $(CREATE_DEF)
Debug_target : T_LDLIBS = 
ifdef LMAKE
Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Debug_target.before :
	
	
Debug_target.after_always : $(Debug_target.BIN)
	
$(Debug_target.BIN) : $(Debug_target.OBJ)
	$(LINK_dll)
	

# -----------------------------------------
# Release_target

Release_target.BIN = ../bin/Release/libfileloader.so
Release_target.OBJ = archivehandler.o fileloader.o ini.o minizip/ioapi.o minizip/iowin32.o minizip/mztools.o minizip/unzip.o minizip/zip.o minizip/zlib/adler32.o minizip/zlib/compress.o minizip/zlib/crc32.o minizip/zlib/deflate.o minizip/zlib/gzclose.o minizip/zlib/gzlib.o minizip/zlib/gzread.o minizip/zlib/gzwrite.o minizip/zlib/infback.o minizip/zlib/inffast.o minizip/zlib/inflate.o minizip/zlib/inftrees.o minizip/zlib/trees.o minizip/zlib/uncompr.o minizip/zlib/zutil.o simpleini/ConvertUTF.o system.o unzip.o 
DEP_FILES += archivehandler.d fileloader.d ini.d minizip/ioapi.d minizip/iowin32.d minizip/mztools.d minizip/unzip.d minizip/zip.d minizip/zlib/adler32.d minizip/zlib/compress.d minizip/zlib/crc32.d minizip/zlib/deflate.d minizip/zlib/gzclose.d minizip/zlib/gzlib.d minizip/zlib/gzread.d minizip/zlib/gzwrite.d minizip/zlib/infback.d minizip/zlib/inffast.d minizip/zlib/inflate.d minizip/zlib/inftrees.d minizip/zlib/trees.d minizip/zlib/uncompr.d minizip/zlib/zutil.d simpleini/ConvertUTF.d system.d unzip.d 
clean.OBJ += $(Release_target.BIN) $(Release_target.OBJ)

Release_target : Release_target.before $(Release_target.BIN) Release_target.after_always
Release_target : CFLAGS += -fomit-frame-pointer  -Os
Release_target : INCLUDES += 
Release_target : RCFLAGS += 
Release_target : LDFLAGS += -L../bin/Release  $(CREATE_LIB) $(CREATE_DEF)
Release_target : T_LDLIBS = 
ifdef LMAKE
Release_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Release_target.before :
	
	
Release_target.after_always : $(Release_target.BIN)
	
$(Release_target.BIN) : $(Release_target.OBJ)
	$(LINK_dll)
	

# -----------------------------------------
# Unitary_Debug_target

Unitary_Debug_target.BIN = ../bin/UnitaryDebug/libfileloader.a
Unitary_Debug_target.OBJ = archivehandler.o fileloader.o ini.o minizip/ioapi.o minizip/iowin32.o minizip/mztools.o minizip/unzip.o minizip/zip.o minizip/zlib/adler32.o minizip/zlib/compress.o minizip/zlib/crc32.o minizip/zlib/deflate.o minizip/zlib/gzclose.o minizip/zlib/gzlib.o minizip/zlib/gzread.o minizip/zlib/gzwrite.o minizip/zlib/infback.o minizip/zlib/inffast.o minizip/zlib/inflate.o minizip/zlib/inftrees.o minizip/zlib/trees.o minizip/zlib/uncompr.o minizip/zlib/zutil.o simpleini/ConvertUTF.o system.o unzip.o 
DEP_FILES += archivehandler.d fileloader.d ini.d minizip/ioapi.d minizip/iowin32.d minizip/mztools.d minizip/unzip.d minizip/zip.d minizip/zlib/adler32.d minizip/zlib/compress.d minizip/zlib/crc32.d minizip/zlib/deflate.d minizip/zlib/gzclose.d minizip/zlib/gzlib.d minizip/zlib/gzread.d minizip/zlib/gzwrite.d minizip/zlib/infback.d minizip/zlib/inffast.d minizip/zlib/inflate.d minizip/zlib/inftrees.d minizip/zlib/trees.d minizip/zlib/uncompr.d minizip/zlib/zutil.d simpleini/ConvertUTF.d system.d unzip.d 
clean.OBJ += $(Unitary_Debug_target.BIN) $(Unitary_Debug_target.OBJ)

Unitary_Debug_target : Unitary_Debug_target.before $(Unitary_Debug_target.BIN) Unitary_Debug_target.after_always
Unitary_Debug_target : CFLAGS += -pg -g  -Os
Unitary_Debug_target : INCLUDES += 
Unitary_Debug_target : RCFLAGS += 
Unitary_Debug_target : LDFLAGS += -pg -L../bin/UnitaryDebug/   $(CREATE_DEF)
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

Unitary_Release_target.BIN = ../bin/UnitaryRelease/libfileloader.a
Unitary_Release_target.OBJ = archivehandler.o fileloader.o ini.o minizip/ioapi.o minizip/iowin32.o minizip/mztools.o minizip/unzip.o minizip/zip.o minizip/zlib/adler32.o minizip/zlib/compress.o minizip/zlib/crc32.o minizip/zlib/deflate.o minizip/zlib/gzclose.o minizip/zlib/gzlib.o minizip/zlib/gzread.o minizip/zlib/gzwrite.o minizip/zlib/infback.o minizip/zlib/inffast.o minizip/zlib/inflate.o minizip/zlib/inftrees.o minizip/zlib/trees.o minizip/zlib/uncompr.o minizip/zlib/zutil.o simpleini/ConvertUTF.o system.o unzip.o 
DEP_FILES += archivehandler.d fileloader.d ini.d minizip/ioapi.d minizip/iowin32.d minizip/mztools.d minizip/unzip.d minizip/zip.d minizip/zlib/adler32.d minizip/zlib/compress.d minizip/zlib/crc32.d minizip/zlib/deflate.d minizip/zlib/gzclose.d minizip/zlib/gzlib.d minizip/zlib/gzread.d minizip/zlib/gzwrite.d minizip/zlib/infback.d minizip/zlib/inffast.d minizip/zlib/inflate.d minizip/zlib/inftrees.d minizip/zlib/trees.d minizip/zlib/uncompr.d minizip/zlib/zutil.d simpleini/ConvertUTF.d system.d unzip.d 
clean.OBJ += $(Unitary_Release_target.BIN) $(Unitary_Release_target.OBJ)

Unitary_Release_target : Unitary_Release_target.before $(Unitary_Release_target.BIN) Unitary_Release_target.after_always
Unitary_Release_target : CFLAGS += -fomit-frame-pointer  -Os
Unitary_Release_target : INCLUDES += 
Unitary_Release_target : RCFLAGS += 
Unitary_Release_target : LDFLAGS += -L../bin/UnitaryRelease/   $(CREATE_DEF)
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
