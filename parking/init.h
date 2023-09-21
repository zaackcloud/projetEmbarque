#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <sys/stat.h>
using namespace std;



class init
{
public:
    init();
    char* dir;
    bool createNewDirectory(char* dir);

};

#endif // INIT_H
