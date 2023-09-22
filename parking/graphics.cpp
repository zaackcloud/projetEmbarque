#include "graphics.h"

Graphics::Graphics()
{

}

void Graphics::createNewGraphic(const string &filename)
{
    vector<string> names;
    vector<int> available;
    vector<int> full;
    vector<string> state;
    string PnameValue;
    int availableValue;
    int fullValue;
    string stateValue;


    ifstream file("parkings.json");
    if (file.is_open()) {
        json j;
        file >> j;

        for (const auto& parking : j) {
            if(parking.find("libelle") != parking.end()) {


                    PnameValue = parking["libelle"].get<string>();
                    availableValue = parking["dispo"].get<int>();
                    fullValue = parking["max"].get<int>();
                    stateValue = parking["etat"].get<string>();

                    names.push_back(PnameValue);
                    available.push_back(availableValue);
                    full.push_back(fullValue);
                    state.push_back(stateValue);

                } else {
                    cerr << "wrong data set: " << parking << endl;
                }
            }
            cout<<PnameValue<<endl;
        }

        file.close();



    const int width = 1600;
    const int height = 1000;
    const int infoWidth = 250;
    const int trunkWidth = width / names.size();
    const int MAX_TRUNK_HEIGHT = height - 20;
    int labelincrement=1;
    gdImagePtr im = gdImageCreateTrueColor(width, height);
    int white = gdImageColorAllocate(im, 255, 255, 255);
    gdImageFill(im, 0, 0, white);

    int black = gdImageColorAllocate(im, 0, 0, 0);
    int grey = gdImageColorAllocate(im, 200, 200, 200);
    gdImageLine(im,infoWidth,height/2, infoWidth+ width, height/2,grey );
    gdImageLine(im, infoWidth,0, infoWidth, height,black );
    gdImageDashedLine(im, infoWidth,3*height/4,infoWidth+ width, 3*height/4,grey );
    gdImageDashedLine(im, infoWidth,height/4, infoWidth+ width, height/4,grey );
    string titre = "Liste des parkings FERMES";
    gdImageString(im, gdFontGetSmall(), (infoWidth - gdFontGetSmall()->w * titre.length()) / 2, 30, (unsigned char*)titre.c_str(), black);
    for (size_t i = 0; i < available.size(); i++) {

        if(state[i]=="OUVERT"){

        static int j =0;
        int percent =100 - (100 * available[i]) / full[i];
        int trunkHeight = (height * percent) / 100;
        const int margin = 10;
        trunkHeight = min(trunkHeight, MAX_TRUNK_HEIGHT);
        int R = rand() % 255;
        int G = rand() % 255;
        int B = rand() % 255;
        int color = gdImageColorAllocate(im, R, G, B);
        gdImageLine(im,infoWidth+j*trunkWidth - margin/2,0,infoWidth+j*trunkWidth - margin/2,height,grey );

        string percentLabel =to_string(percent)+"%";
        string label = names[i];
        gdImageString(im, gdFontGetSmall(),infoWidth+ j * trunkWidth + (trunkWidth - gdFontGetSmall()->w * percentLabel.length()) / 2, height - trunkHeight - 15, (unsigned char*)percentLabel.c_str(), black);
        if (labelincrement%3 ==0) {
            gdImageString(im, gdFontGetSmall(),infoWidth+ j * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, 30, (unsigned char*)label.c_str(), black);
            labelincrement=1;
        } else if(labelincrement%2 == 0) {
            gdImageString(im, gdFontGetSmall(),infoWidth+ j * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, 15, (unsigned char*)label.c_str(), black);
            labelincrement=3;
        } else {
            gdImageString(im, gdFontGetSmall(),infoWidth+ j * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, 0, (unsigned char*)label.c_str(), black);
            labelincrement=2;
        }

        gdImageFilledRectangle(im,infoWidth+ j * trunkWidth, height - trunkHeight,infoWidth+(j + 1) * trunkWidth - margin, height, color);
        j++;
        }else{
            string label = names[i];
            gdImageString(im, gdFontGetSmall(), (infoWidth - gdFontGetSmall()->w * label.length()) / 2, i*30, (unsigned char*)label.c_str(), black);
        }
    }

    FILE* out = fopen(filename.c_str(), "wb");
    gdImagePng(im, out);
    fclose(out);

    gdImageDestroy(im);
}


