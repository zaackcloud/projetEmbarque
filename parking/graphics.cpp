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

                } else {
                    cerr << "wrong data set: " << parking << endl;
                }
            }
            cout<<PnameValue<<endl;
        }

        file.close();



    const int width = 1600;
    const int height = 1000;
    const int trunkWidth = width / names.size();
    const int MAX_TRUNK_HEIGHT = height - 20;
    int labelincrement=1;
    gdImagePtr im = gdImageCreateTrueColor(width, height);
    int white = gdImageColorAllocate(im, 255, 255, 255);
    gdImageFill(im, 0, 0, white);

    int black = gdImageColorAllocate(im, 0, 0, 0);
    int grey = gdImageColorAllocate(im, 200, 200, 200);
    gdImageLine(im, 0,height/2, width, height/2,grey );
    gdImageLine(im, 0,height, width, height,black );
    gdImageDashedLine(im, 0,3*height/4, width, 3*height/4,grey );
    gdImageDashedLine(im, 0,height/4, width, height/4,grey );

    for (size_t i = 0; i < available.size(); i++) {

        int percent = (100 * available[i]) / full[i];
        int trunkHeight = (height * percent) / 100;
        const int margin = 10;
        trunkHeight = min(trunkHeight, MAX_TRUNK_HEIGHT);
        int R = rand() % 255;
        int G = rand() % 255;
        int B = rand() % 255;
        int color = gdImageColorAllocate(im, R, G, B);
        gdImageLine(im,i*trunkWidth - margin/2,0,i*trunkWidth - margin/2,height,grey );

        string percentLabel =to_string(percent)+"%";
        string label = names[i];
        gdImageString(im, gdFontGetSmall(), i * trunkWidth + (trunkWidth - gdFontGetSmall()->w * percentLabel.length()) / 2, height - trunkHeight - 15, (unsigned char*)percentLabel.c_str(), black);
        if (labelincrement%3 ==0) {
            gdImageString(im, gdFontGetSmall(), i * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, 30, (unsigned char*)label.c_str(), black);
            labelincrement=1;
        } else if(labelincrement%2 == 0) {
            gdImageString(im, gdFontGetSmall(), i * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, 15, (unsigned char*)label.c_str(), black);
            labelincrement=3;
        } else {
            gdImageString(im, gdFontGetSmall(), i * trunkWidth + (trunkWidth - gdFontGetSmall()->w * label.length()) / 2, 0, (unsigned char*)label.c_str(), black);
            labelincrement=2;
        }

        gdImageFilledRectangle(im, i * trunkWidth, height - trunkHeight, (i + 1) * trunkWidth - margin, height, color);
    }

    FILE* out = fopen(filename.c_str(), "wb");
    gdImagePng(im, out);
    fclose(out);

    gdImageDestroy(im);
}


