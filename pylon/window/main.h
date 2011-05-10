#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifndef Py_PYTHON_H
#include <Python.h> // include Python.h before any other includes, because it redefines some system stuff if it is after other includes
#endif // Py_PYTHON_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"
#include "../renderer/renderer.h"
#include "../threads/threads.h"
#include "../scriptengine/scriptengine.h"
#include "../pogelscriptinterface/pogelscriptinterface.h"

extern std::string pylon_archive;
extern std::string config_data;
extern std::string init_py;
extern std::string main_py;
extern std::string ext_dir;
extern bool dontremove;
extern bool forcedir;
extern bool noarchiving;
extern std::string forced_dir;

extern bool calcLock;

extern Thread *calcThread;
extern Thread *scriptThread;

void* Scripts(void* arg);
void* Calculations(void* arg);

#endif // MAIN_H_INCLUDED
