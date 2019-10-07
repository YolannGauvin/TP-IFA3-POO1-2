/*************************************************************************
                            main  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation du module <main> (fichier main.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "../includes/Catalogue.h"
#include "../includes/TrajetSimple.h"
#include "../includes/TrajetCompose.h"

///////////////////////////////////////////////////////////////////  PRIVE

//------------------------------------------------------------- Constantes
const unsigned int TAILLE_MAX_VILLE = 50;

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//TRAIN, AUTO, BATEAU, AVION, VELO, MARCHE
static void afficherMoyenDeTransport (
    moyenDeTransport leMoyenDeTransport )
{
    switch (leMoyenDeTransport)
    {
        case (TRAIN):
            cout << "Train";
            break;
        case (AUTO):
            cout << "Auto";
            break;
        case (BATEAU):
            cout << "Bateau";
            break;
        case (AVION):
            cout << "Avion";
            break;
        case (VELO):
            cout << "Velo";
            break;
        case (MARCHE):
            cout << "Marche";
            break;
    }
}

static moyenDeTransport choisirMoyenDeTransport ( )
{
    int choixTransport;

    cout << "1. "; 
    afficherMoyenDeTransport(TRAIN);
    cout << endl;

    cout << "2. "; 
    afficherMoyenDeTransport(AUTO);
    cout << endl;

    cout << "3. "; 
    afficherMoyenDeTransport(BATEAU);
    cout << endl;

    cout << "4. "; 
    afficherMoyenDeTransport(AVION);
    cout << endl;

    cout << "5. "; 
    afficherMoyenDeTransport(VELO);
    cout << endl;

    cout << "6. "; 
    afficherMoyenDeTransport(MARCHE);
    cout << endl;

    cin >> choixTransport;
    
    switch (choixTransport)
    {
        case (1): return TRAIN;
        case (2): return AUTO;
        case (3): return BATEAU;
        case (4): return AVION;
        case (5): return VELO;
        case (6): return MARCHE;
        default: return TRAIN;
    }
}

static void afficherCatalogue ( Catalogue & leCatalogue )
{
    leCatalogue.Afficher();    
}

static void ajouterTrajetSimple ( Catalogue & leCatalogue )
{
    moyenDeTransport leMoyenDeTransport;
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    cout << "Ville de départ :" << endl;
    cin >> villeDepart;
    cout << "Ville d'arrivée :" << endl;
    cin >> villeArrivee;
    cout << "Moyen de transport :" << endl;
    leMoyenDeTransport = choisirMoyenDeTransport();
    
    leCatalogue.AjouterTrajet(
        new TrajetSimple(
            villeDepart, 
            villeArrivee, 
            leMoyenDeTransport
        )
    );
}

static void ajouterTrajetCompose ( Catalogue & leCatalogue )
{
    CollectionTrajets trajets;
    moyenDeTransport leMoyenDeTransport;
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    cout << "Ville de départ :" << endl;
    cin >> villeDepart;
    
    while (true)
    {
        cout << "Ville suivante : (`stop` pour arrêter)";
        cin >> villeArrivee;

        if (strcmp(villeArrivee, "stop") == 0)
            break;

        cout << "Moyen de transport :" << endl;
        leMoyenDeTransport = choisirMoyenDeTransport();

        trajets.AjouterTrajet(
            new TrajetSimple(
                villeDepart, 
                villeArrivee, 
                leMoyenDeTransport
            )
        );

        strcpy(villeDepart, villeArrivee);
    }

    if (trajets.NombreDeTrajets() > 0)
        leCatalogue.AjouterTrajet(
            new TrajetCompose(trajets)
        );
}

static void rechercherTrajet ( Catalogue & leCatalogue )
{
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];
    cout << "Ville de départ :" << endl;
    cin >> villeDepart;
    cout << "Ville d'arrivée :" << endl;
    cin >> villeArrivee;

    CollectionTrajets * trajetsTrouves = 
        leCatalogue.Rechercher(villeDepart, villeArrivee);

    cout << "Résultat : " << endl;
    for (unsigned int i = 1; i <= trajetsTrouves->NombreDeTrajets(); i++)
    {
        trajetsTrouves->TrajetNumero(i)->Afficher();
        cout << endl;
    }

    delete trajetsTrouves;
}

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
int main ()
{
    int choixMenu;
    Catalogue leCatalogue;

    while (true)
    {
        cout << "Menu :" << endl;
        cout << "\t1. Afficher le catalogue" << endl;
        cout << "\t2. Ajouter un trajet simple" << endl;
        cout << "\t3. Ajouter un trajet composé" << endl;
        cout << "\t4. Rechercher un trajet" << endl;
        cout << "\t0. Quitter" << endl;
        cin >> choixMenu;

        switch (choixMenu)
        {
            case 1:
                afficherCatalogue(leCatalogue);
                break;
            case 2:
                ajouterTrajetSimple(leCatalogue);
                break;
            case 3:
                ajouterTrajetCompose(leCatalogue);
                break;
            case 4:
                rechercherTrajet(leCatalogue);
                break;
            case 0:
                return 0;
        }
    }
    
    return 0;
}