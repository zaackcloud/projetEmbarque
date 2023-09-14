#include "affichage.h"
#include <iostream>

using namespace std;

affichage::affichage()
{

}

int affichage::accueil()
{
    char* choix;
    cout<<"bienvenue sur le projet MEL'Parking"<<endl;
    cout<<"1: afficher les places restantes dans un parking"<<endl;
    cout<<"2: afficher les parkings fermés"<<endl;
    cout<<"3: créer un graphique d'affluence d'un parking"<<endl;
    cout<<"4: retour"<<endl;
    cin>>choix;
    return atoi(choix);
}

void affichage::navigation(int choix)
{
    switch(choix)
    {
    case 1:
        cout<< "vous avez choisi l'option 1"<<endl; break;
    case 2:
        cout<< "vous avez choisi l'option 2"<<endl; break;
    case 3:
        cout<< "vous avez choisi l'option 3"<<endl; break;
    case 4:
        return;
    default:
        accueil();
    }
}
