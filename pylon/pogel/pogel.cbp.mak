# -*- mode: Makefile; -*-
# -----------------------------------------
# project pogel


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
INCLUDES = -I$(_BASE.INCLUDE) -I$(_BASE.LIB) 
LDFLAGS = -L$(_BASE.LIB)  -s
RCFLAGS = 
LDLIBS = $(T_LDLIBS) -lpthread -l$(_GLU.LFLAGS) -l$(_GLUT.LFLAGS) -l$(_OPENGL.LFLAGS)  -lstdc++

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

Debug_target.BIN = ../bin/Debug/libpogel.so
Debug_target.OBJ = classes/bounding_class.o classes/fractal_class.o classes/image_class.o classes/matrix_class.o classes/object_class.o classes/object_funcs.o classes/physics/dynamics_class.o classes/physics/fountain_class.o classes/physics/microcosm_class.o classes/physics/physics.o classes/physics/simulation_class.o classes/physics/simulation_class_collisions.o classes/physics/simulation_class_collisions_reaction.o classes/physics/singularity_class.o classes/physics/solid_class.o classes/point_class.o classes/quat_class.o classes/sprite_class.o classes/triangle_class.o classes/view_class.o pogel.o time.o 
DEP_FILES += classes/bounding_class.d classes/fractal_class.d classes/image_class.d classes/matrix_class.d classes/object_class.d classes/object_funcs.d classes/physics/dynamics_class.d classes/physics/fountain_class.d classes/physics/microcosm_class.d classes/physics/physics.d classes/physics/simulation_class.d classes/physics/simulation_class_collisions.d classes/physics/simulation_class_collisions_reaction.d classes/physics/singularity_class.d classes/physics/solid_class.d classes/point_class.d classes/quat_class.d classes/sprite_class.d classes/triangle_class.d classes/view_class.d pogel.d time.d 
clean.OBJ += $(Debug_target.BIN) $(Debug_target.OBJ)

Debug_target : Debug_target.before $(Debug_target.BIN) Debug_target.after_always
Debug_target : CFLAGS += -g  -Os
Debug_target : INCLUDES += -I../bin/Debug/ 
Debug_target : RCFLAGS += 
Debug_target : LDFLAGS += -L../bin/Debug/  $(CREATE_LIB) $(CREATE_DEF)
Debug_target : T_LDLIBS = -llists -lsoil -lthreads 
ifdef LMAKE
Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Debug_target.before :
	
	
Debug_target.after_always : $(Debug_target.BIN)
	
$(Debug_target.BIN) : $(Debug_target.OBJ)
	$(LINK_dll)
	

# -----------------------------------------
# Release_target

Release_target.BIN = ../bin/Release/libpogel.so
Release_target.OBJ = classes/bounding_class.o classes/fractal_class.o classes/image_class.o classes/matrix_class.o classes/object_class.o classes/object_funcs.o classes/physics/dynamics_class.o classes/physics/fountain_class.o classes/physics/microcosm_class.o classes/physics/physics.o classes/physics/simulation_class.o classes/physics/simulation_class_collisions.o classes/physics/simulation_class_collisions_reaction.o classes/physics/singularity_class.o classes/physics/solid_class.o classes/point_class.o classes/quat_class.o classes/sprite_class.o classes/triangle_class.o classes/view_class.o pogel.o time.o 
DEP_FILES += classes/bounding_class.d classes/fractal_class.d classes/image_class.d classes/matrix_class.d classes/object_class.d classes/object_funcs.d classes/physics/dynamics_class.d classes/physics/fountain_class.d classes/physics/microcosm_class.d classes/physics/physics.d classes/physics/simulation_class.d classes/physics/simulation_class_collisions.d classes/physics/simulation_class_collisions_reaction.d classes/physics/singularity_class.d classes/physics/solid_class.d classes/point_class.d classes/quat_class.d classes/sprite_class.d classes/triangle_class.d classes/view_class.d pogel.d time.d 
clean.OBJ += $(Release_target.BIN) $(Release_target.OBJ)

Release_target : Release_target.before $(Release_target.BIN) Release_target.after_always
Release_target : CFLAGS += -fomit-frame-pointer  -Os
Release_target : INCLUDES += 
Release_target : RCFLAGS += 
Release_target : LDFLAGS += -L../bin/Release  $(CREATE_LIB) $(CREATE_DEF)
Release_target : T_LDLIBS = -llists -lsoil -lthreads 
ifdef LMAKE
Release_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Release_target.before :
	
	
Release_target.after_always : $(Release_target.BIN)
	
$(Release_target.BIN) : $(Release_target.OBJ)
	$(LINK_dll)
	

# -----------------------------------------
# Unitary_Debug_target

Unitary_Debug_target.BIN = ../bin/UnitaryDebug/libpogel.a
Unitary_Debug_target.OBJ = classes/bounding_class.o classes/fractal_class.o classes/image_class.o classes/matrix_class.o classes/object_class.o classes/object_funcs.o classes/physics/dynamics_class.o classes/physics/fountain_class.o classes/physics/microcosm_class.o classes/physics/physics.o classes/physics/simulation_class.o classes/physics/simulation_class_collisions.o classes/physics/simulation_class_collisions_reaction.o classes/physics/singularity_class.o classes/physics/solid_class.o classes/point_class.o classes/quat_class.o classes/sprite_class.o classes/triangle_class.o classes/view_class.o pogel.o time.o 
DEP_FILES += classes/bounding_class.d classes/fractal_class.d classes/image_class.d classes/matrix_class.d classes/object_class.d classes/object_funcs.d classes/physics/dynamics_class.d classes/physics/fountain_class.d classes/physics/microcosm_class.d classes/physics/physics.d classes/physics/simulation_class.d classes/physics/simulation_class_collisions.d classes/physics/simulation_class_collisions_reaction.d classes/physics/singularity_class.d classes/physics/solid_class.d classes/point_class.d classes/quat_class.d classes/sprite_class.d classes/triangle_class.d classes/view_class.d pogel.d time.d 
clean.OBJ += $(Unitary_Debug_target.BIN) $(Unitary_Debug_target.OBJ)

Unitary_Debug_target : Unitary_Debug_target.before $(Unitary_Debug_target.BIN) Unitary_Debug_target.after_always
Unitary_Debug_target : CFLAGS += -pg -g  -Os
Unitary_Debug_target : INCLUDES += -I../bin/UnitaryDebug/ 
Unitary_Debug_target : RCFLAGS += 
Unitary_Debug_target : LDFLAGS += -pg -L../bin/UnitaryDebug/   $(CREATE_DEF)
Unitary_Debug_target : T_LDLIBS = -llists -lsoil -lthreads 
ifdef LMAKE
Unitary_Debug_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Unitary_Debug_target.before :
	
	
Unitary_Debug_target.after_always : $(Unitary_Debug_target.BIN)
	
$(Unitary_Debug_target.BIN) : $(Unitary_Debug_target.OBJ)
	$(LINK_lib)
	

# -----------------------------------------
# Unitary_Release_target

Unitary_Release_target.BIN = ../bin/UnitaryRelease/libpogel.a
Unitary_Release_target.OBJ = classes/bounding_class.o classes/fractal_class.o classes/image_class.o classes/matrix_class.o classes/object_class.o classes/object_funcs.o classes/physics/dynamics_class.o classes/physics/fountain_class.o classes/physics/microcosm_class.o classes/physics/physics.o classes/physics/simulation_class.o classes/physics/simulation_class_collisions.o classes/physics/simulation_class_collisions_reaction.o classes/physics/singularity_class.o classes/physics/solid_class.o classes/point_class.o classes/quat_class.o classes/sprite_class.o classes/triangle_class.o classes/view_class.o pogel.o time.o 
DEP_FILES += classes/bounding_class.d classes/fractal_class.d classes/image_class.d classes/matrix_class.d classes/object_class.d classes/object_funcs.d classes/physics/dynamics_class.d classes/physics/fountain_class.d classes/physics/microcosm_class.d classes/physics/physics.d classes/physics/simulation_class.d classes/physics/simulation_class_collisions.d classes/physics/simulation_class_collisions_reaction.d classes/physics/singularity_class.d classes/physics/solid_class.d classes/point_class.d classes/quat_class.d classes/sprite_class.d classes/triangle_class.d classes/view_class.d pogel.d time.d 
clean.OBJ += $(Unitary_Release_target.BIN) $(Unitary_Release_target.OBJ)

Unitary_Release_target : Unitary_Release_target.before $(Unitary_Release_target.BIN) Unitary_Release_target.after_always
Unitary_Release_target : CFLAGS += -fomit-frame-pointer  -Os
Unitary_Release_target : INCLUDES += -I../bin/UnitaryRelease/ 
Unitary_Release_target : RCFLAGS += 
Unitary_Release_target : LDFLAGS += -L../bin/UnitaryRelease/   $(CREATE_DEF)
Unitary_Release_target : T_LDLIBS = -llists -lsoil -lthreads 
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
