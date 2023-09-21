#include <iostream>
#include <string>
#include <thread>
#include "init.h"
#include "datamanager.h"
#include "graphics.h"

using namespace std;

int main()
{
    init *i = new init;
    i->dir="ImagesPNG";
    i->createNewDirectory(i->dir);
    i->dir="Data";
    i->createNewDirectory(i->dir);

    DataManager data_manager;
    Graphics graphic;
    while (true) {
            data_manager.getData();

            //Obtention les noms des parkings depuis DataManager
            vector<string> noms = data_manager.getNames();

            // Appele la fonction pour créer un histogramme d'évolution pour chaque parking
            for (const string& nom : noms) {
                //Construction du chemin complet du fichier JSON pour ce parking
                string jsonFilePath = "Data/" + nom + ".json";

                //On vérifie si le fichier JSON existe
                if (access(jsonFilePath.c_str(), F_OK) != -1) {
                    string histogramFilename = "Images_PNG/histogramme_evolution_" + nom + ".png";
                    //Histogram::createEvolutionHistogramFromJSON(histogramFilename, jsonFilePath);
                } else {
                    cerr << "Le fichier JSON pour le parking '" << nom << "' n'existe pas." << endl;
                }
            }
            Graphics::createNewGraphic("ImagesPNG/Taux_dispo_actuel_TOUT_parkings.png");
            //histogram.showTerminalHistogram();
            //histogram.showGeneratedImagesHTML();
            //On attend 10 minutes avant la prochaine collecte
            for (int i = 600; i > 0; --i) {
                // Calculer les minutes et les secondes restantes
                int minutes = i / 60;
                int seconds = i % 60;

                //Efface la ligne précédente dans le terminal (pour que le décompte soit sur la même ligne)
                cout << "\rProchaine collecte dans " << minutes << " minutes " << seconds << " secondes...    " << flush;

                //Attendre une seconde avant d'afficher le décompte suivant
                this_thread::sleep_for(std::chrono::seconds(1));
            }
            cout << endl;
        }

    return 0;
}
