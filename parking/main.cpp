#include <iostream>
#include <string>
#include "init.h"
#include "datamanager.h"
#include "graphics.h"

using namespace std;

int main()
{

    init *i=new init;

    i->createNewDirectory(i->dirImage);

    i->createNewDirectory(i->dirData);

    DataManager data_manager;
    Graphics graphic;
    while (true) {
            data_manager.getData();

            vector<string> names = data_manager.getNames();
//            for (const string& name : names) {
//                //Construction du chemin complet du fichier JSON pour ce parking
//                string jsonFilePath = "Data/" + name + ".json";

//                //On vérifie si le fichier JSON existe
//                if (access(jsonFilePath.c_str(), F_OK) != -1) {
//                    string histogramFilename = "Images_PNG/histogramme_evolution_" + nom + ".png";
//                    //Histogram::createEvolutionHistogramFromJSON(histogramFilename, jsonFilePath);
//                } else {
//                    cerr << "Le fichier JSON pour le parking '" << nom << "' n'existe pas." << endl;
//                }
//            }
            Graphics::createNewGraphic("ImagesPNG/Taux_dispo_actuel_TOUT_parkings.png");
            i->cooldown();
            }
            cout << endl;


    return 0;
}
