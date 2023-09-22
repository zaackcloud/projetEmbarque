#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <sys/stat.h>
#include <thread>
using namespace std;



class init
{
public:
    init();
    char const *dirImage="ImagesPNG";
    char const *dirData="Data";
    bool createNewDirectory(const char* dir);
    void cooldown();

};

#endif // INIT_H
