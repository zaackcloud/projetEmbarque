#include "init.h"
 struct stat info;
init::init()
{

}

bool init::createNewDirectory(const char *directory) {
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

void init::cooldown()
{
    for (int i = 900; i > 0; --i) {

        int minutes = i / 60;
        int seconds = i % 60;
        cout << "\rNext update in -> " << minutes << " : " << seconds << flush;
        this_thread::sleep_for(std::chrono::seconds(1));
    }
}
