#include "filesindir.h"

using namespace std;

/*function... might want it in some class?*/
int getdir (std::string dir, std::vector<std::string> &files, bool isrec, std::string origdir)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if(dirp->d_type == DT_DIR && string(dirp->d_name)[0] != '.' )
        {
            getdir(dir+"/"+(string(dirp->d_name)),files, true,origdir);
        }
        else if(string(dirp->d_name)[0] != '.')
        {
            files.push_back((dir+"/"+string(dirp->d_name)).substr(origdir.length()));
        }
    }
    closedir(dp);
    return 0;
}

int getdir (std::string dir, std::vector<std::string> &files)
{
    return getdir (dir, files, false, dir);
}
