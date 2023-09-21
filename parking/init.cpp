#include "init.h"
 struct stat info;
init::init()
{

}


bool init::createNewDirectory(char* directory) {
    if (stat(directory, &info) != 0) {
        cout << "Creating directory : " << directory << endl;
        if (mkdir(directory, 0755) == 0) {
            return true;
        } else {
            cerr << "Error with directory creation : " << directory << endl;
            return false;
        }
    } else if (info.st_mode & S_IFDIR) {
        cout << "Directory " << directory << " already exist." << endl;
        return true;
    } else {
        cerr << "Error: " << directory << " is not a directory." << endl;
        return false;
    }
}
