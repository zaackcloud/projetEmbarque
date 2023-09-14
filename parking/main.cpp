#include <iostream>
#include "affichage.h"

#include <string>
#include <curl/curl.h>

using namespace std;
const std::string url("https://opendata.lillemetropole.fr/api/explore/v2.1/catalog/datasets/disponibilite-temps-reel-des-parkings-a-roubaix/exports/json?lang=fr&timezone=Europe%2FBerlin");

int main()
{
    CURL *curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    if(curl){



    }
    curl_easy_cleanup(curl);
    //affichage *a=new affichage;
    //a->accueil();

    return 0;
}
