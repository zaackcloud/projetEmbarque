#include "graphics.h"

Graphics::Graphics()
{

}

void Graphics::createNewGraphic(const string &filename)
{
    vector<string> names;
    vector<int> available;
    vector<int> full;
    string PnameValue;
    int availableValue;
    int fullValue;


    ifstream file("parkings.json");
    if (file.is_open()) {
        json j;
        file >> j;

        for (const auto& parking : j) {
            if(parking.find("libelle") != parking.end()) {


                    PnameValue = parking["libelle"].get<string>();
                    availableValue = parking["dispo"].get<int>();
                    fullValue = parking["max"].get<int>();

                    names.push_back(PnameValue);
                    available.push_back(availableValue);
                    full.push_back(fullValue);

//                } else {
//                    cerr << "wrong data set: " << parking << endl;
//                }
            }
            cout<<PnameValue<<endl;
        }

        file.close();
    }


    const int width = 1600;
    const int height = 600;
    const int trunkWidth = width / names.size();
    const int MAX_TRUNK_HEIGHT = height - 20;

    gdImagePtr im = gdImageCreateTrueColor(width, height);
    int white = gdImageColorAllocate(im, 255, 255, 255);
    gdImageFill(im, 0, 0, white);

    int black = gdImageColorAllocate(im, 0, 0, 0);

    //Dessin des barres de l'histogramme
    for (size_t i = 0; i < available.size(); i++) {
        int percent = (100 * available[i]) / full[i];
        int trunkHeight = (height * percent) / 100;
        const int RELIEF_OFFSET = 10;
        trunkHeight = min(trunkHeight, MAX_TRUNK_HEIGHT);
        int R = rand() % 255;
        int G = rand() % 255;
          int B = rand() % 255;
        int color = gdImageColorAllocate(im, R, G, B);

//        int bottom_space = MAX_TRUNK_HEIGHT - trunkHeight;
//        int BGR = std::max(0, R - 10);
//        int BGG = std::max(0, G - 10);
//        int BGB = std::max(0, B - 10);
//        int backGroundColor = gdImageColorAllocate(im, BGR, BGG, BGB);

        if (percent >= 90) { // Si le pourcentage du parking est supérieur ou égal à 90%

            string label = names[i] + " (" + to_string(percent) + "%)";
            gdImageString(im, gdFontGetSmall(), i * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, height - trunkHeight - 15, (unsigned char*)label.c_str(), black);
        } else {
            //Dessine le pourcentage au-dessus de la barre
            string percentLabel = "("+to_string(percent) + "%)";
            gdImageString(im, gdFontGetSmall(), i * trunkWidth + (trunkWidth - gdFontGetSmall()->w * percentLabel.length()) / 2, height - trunkHeight - 15, (unsigned char*)percentLabel.c_str(), black);

//            //Dessine le nom du parking en cascade en utilisant split_into_lines
//            auto lines = split_into_lines(noms[i], bar_width, gdFontGetSmall());
//            std::reverse(lines.begin(), lines.end());
//            int offsetY = 0;
//            for (const auto& line : lines) {
//                gdImageString(im, gdFontGetSmall(), i * bar_width + (bar_width - gdFontGetSmall()->w * line.length()) / 2, image_height - bar_height - 30 - offsetY, (unsigned char*)line.c_str(), black);
//                offsetY += gdFontGetSmall()->h + 2;  // Ajuste l'espacement entre les lignes
//            }
        }

        // Dessine le rectangle principal
        gdImageFilledRectangle(im, i * trunkWidth, height - trunkHeight, (i + 1) * trunkWidth - RELIEF_OFFSET, height, color);

//        //On dessine le relief 3D
//        for (int offset = 1; offset <= RELIEF_OFFSET; offset++) {
//            gdImageFilledRectangle(im, (i + 1) * trunkWidth - offset, height - trunkHeight - offset + RELIEF_OFFSET, (i + 1) * trunkWidth - offset + 1, image_height - offset + RELIEF_OFFSET, color_relief);
//        }
    }

    FILE* out = fopen(filename.c_str(), "wb");
    gdImagePng(im, out);
    fclose(out);

    gdImageDestroy(im);
}


