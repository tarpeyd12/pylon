#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifndef Py_PYTHON_H
#include <Python.h> // include Python.h before any other includes, because it redefines some system stuff if it is after other includes
#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif
#endif // Py_PYTHON_H

// apple code unteasted ...
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include "../lists/classlist_template.h"
#include "../threads/threads.h"
#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"
#include "../scriptengine/scriptengine.h"
#include "../objectloader/objectloader.h"
#include "../renderer/renderer.h"
#include "../pogelscriptinterface/pogelscriptinterface.h"


#include "scriptthread.h"
#include "calcthread.h"

#include "globals.h"

namespace Main
{
    void printVersion();
    void printHelp();
    void findVersion();

    void getCMD(int argc, char *argv[]);

    void Init();
}

#endif // MAIN_H_INCLUDED
