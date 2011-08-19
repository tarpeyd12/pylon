#ifndef FILESINDIR_H_INCLUDED
#define FILESINDIR_H_INCLUDED

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*function... might want it in some class?*/
int getdir (std::string dir, std::vector<std::string> &files);

#endif // FILESINDIR_H_INCLUDED
