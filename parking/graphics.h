#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <fstream>
#include <string>
#include <gd.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <cmath>
#include <map>
#include <gdfonts.h>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <dirent.h>

using namespace std;
using json = nlohmann::json;

class Graphics
{
public:
    Graphics();

   static void createNewGraphic(const string& filename);
};

#endif // GRAPHICS_H
