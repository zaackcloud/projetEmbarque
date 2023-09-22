#include "datamanager.h"

using namespace std;

DataManager::DataManager()
{

}

void DataManager::getData()
{

    manageHistory();
}

void DataManager::downloadData()
{

    CURL *curl;
    FILE *file;
    CURLcode res;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    if(curl){
        std::cout<<"curl has been initialized"<<std::endl;
        file = fopen(localsave.c_str(), "wb");
               curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
               curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
               res = curl_easy_perform(curl);
               fclose(file);
        if (res != CURLE_OK){
            cerr<<"Download error :"<<curl_easy_strerror(res)<<endl;
        }
    }
    curl_easy_cleanup(curl);
}

vector<string> DataManager::getNames() const
{

    vector<string> liste;
        for (const auto& pair : History) {
            liste.push_back(pair.first);
            cout<<"nouvelle entrée"<<endl;
        }
        return liste;
}

void DataManager::manageHistory()
{
    downloadData();
       cout << "Download complete. File : " << localsave << " has been saved localy." << endl;

       ifstream jsonFile(localsave);
       json data_obj;
       jsonFile >> data_obj;


       time_t temps = time(nullptr);
       tm* now = localtime(&temps);
       stringstream chaine_date, chaine_heure;


       chaine_date << setw(4) << setfill('0') << (1900 + now->tm_year) << "-"
                  << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
                  << setw(2) << setfill('0') << now->tm_mday;
       string dateStr = chaine_date.str();


       chaine_heure << setw(2) << setfill('0') << now->tm_hour << ":"
                   << setw(2) << setfill('0') << now->tm_min << ":"
                   << setw(2) << setfill('0') << now->tm_sec;
       string heureStr = chaine_heure.str();

       //Stoque l'horodatage actuel dans le format souhaité
       string timestamp = dateStr + " " + heureStr;

       //Boucle for pour parcourir l'objet data_obj et collecter les données actuelles
       for (auto& element : data_obj) {
           if (element.contains("libelle")) {
               json parkingData; // Crée un objet JSON pour stocker les données du parking

               // Vous pouvez spécifier les clés de l'objet "fields" pour obtenir les données souhaitées
               if (element.contains("dispo")) {
                   parkingData["dispo"] = element["dispo"].get<int>();
               } else {
                   parkingData["dispo"] = 0;
               }

               if (element.contains("max")) {
                   parkingData["max"] = element["max"].get<int>();
               } else {
                   parkingData["max"] = 1;
               }

               parkingData["timestamp"] = timestamp;

               //Ajoute des données du parking à l'historique
               History[element["libelle"].get<string>()].emplace_back(parkingData);

               //Si le nombre d'entrées dépasse MAX_HISTORY_SIZE, on supprime la plus ancienne
               if (History[element["libelle"].get<string>()].size() > 20) {
                   History[element["libelle"].get<string>()].erase(
                   History[element["libelle"].get<string>()].begin());
               }

               //Maintenant on limite également la taille de l'historique dans le fichier JSON
               string filename = string("Data") + "/" + element["libelle"].get<string>() + ".json";
               json j;

               // Chargement du fichier JSON existant s'il existe
               if (ifstream(filename)) {
                   ifstream infile(filename);
                   infile >> j;
                   infile.close();
               }

               //Ajoute les données actuelles à l'historique existant
               for (const Entry& data : History[element["libelle"].get<string>()]) {
                   json historicalDataJSON;

                   historicalDataJSON["dispo"] = data.Available;
                   historicalDataJSON["max"] = data.Full;
                   historicalDataJSON["timestamp"] = data.timestamp;

                   j.push_back(historicalDataJSON); // Ajoute l'objet JSON à l'objet JSON principal
               }

               // Si le nombre d'entrées dépasse MAX_HISTORY_SIZE, on supprime les plus anciennes
               while (j.size() > 20) {
                   j.erase(j.begin());
               }

               //sauvegarde des données dans le fichier
               ofstream outfile(filename);
               outfile << j.dump(4);
               outfile.close();
           }
       }
   }

