#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

struct Entry{
    int Available;
    int Full;
    std::string timestamp;

    Entry(const nlohmann::json& jsonData) {

            Available = jsonData["dispo"].get<int>();
            Full = jsonData["max"].get<int>();
            timestamp = jsonData["timestamp"].get<std::string>();
        }
};

class DataManager
{
public:
    DataManager();
    void getData();
    vector<string> getNames() const;

private:
    const string localsave = "parkings.json";
    const string url= "https://opendata.lillemetropole.fr/api/explore/v2.1/catalog/datasets/disponibilite-parkings/exports/json?lang=fr&timezone=Europe%2FBerlin";
    map<string, vector<Entry>> History;
    void manageHistory();
    void downloadData();

};

#endif // DATAMANAGER_H
