/*************************************************************************
                            main  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation du module <main> (fichier main.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>

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
static void afficherMoyenDeTransport(
    moyenDeTransport leMoyenDeTransport)
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

static void saisirVille(
    char *ville,
    unsigned int maxLength,
    const char *message = "Ville :")
{
    cout << message << " (taille max: " << maxLength << ")" << endl;
    cin >> ville;
}

static void saisirMoyenDeTransport(
    moyenDeTransport &leMoyen,
    const char *message = "Moyen de transport :")
{
    int choixTransport;

    cout << message << endl;

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
    case (1):
        leMoyen = TRAIN;
        break;
    case (2):
        leMoyen = AUTO;
        break;
    case (3):
        leMoyen = BATEAU;
        break;
    case (4):
        leMoyen = AVION;
        break;
    case (5):
        leMoyen = VELO;
        break;
    case (6):
        leMoyen = MARCHE;
        break;
    default:
        leMoyen = TRAIN;
        break;
    }
}

static void afficherCatalogue(Catalogue &leCatalogue)
{
    leCatalogue.Afficher();
}

static void ajouterTrajetSimple(Catalogue &leCatalogue)
{
    moyenDeTransport leMoyenDeTransport;
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    saisirVille(villeArrivee, TAILLE_MAX_VILLE, "Ville d'arrivée :");
    saisirMoyenDeTransport(leMoyenDeTransport, "Moyen de transport :");

    leCatalogue.AjouterTrajet(
        new TrajetSimple(
            villeDepart,
            villeArrivee,
            leMoyenDeTransport));
}

static void ajouterTrajetCompose(Catalogue &leCatalogue)
{
    CollectionTrajets trajets;
    moyenDeTransport leMoyenDeTransport;
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");

    while (true)
    {
        saisirVille(villeArrivee, TAILLE_MAX_VILLE,
                    "Ville suivante (tapez `stop` pour arrêter) :");

        if (strcmp(villeArrivee, "stop") == 0)
            break;

        saisirMoyenDeTransport(leMoyenDeTransport, "Moyen de transport :");

        trajets.AjouterTrajet(
            new TrajetSimple(
                villeDepart,
                villeArrivee,
                leMoyenDeTransport));

        strcpy(villeDepart, villeArrivee);
    }

    if (trajets.NombreDeTrajets() > 0)
        leCatalogue.AjouterTrajet(
            new TrajetCompose(trajets));
}

static void rechercherTrajet(Catalogue &leCatalogue)
{
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    saisirVille(villeArrivee, TAILLE_MAX_VILLE, "Ville d'arrivée :");

    CollectionTrajets *trajetsTrouves(
        leCatalogue.Rechercher(villeDepart, villeArrivee));

    cout << "Résultat : " << endl;
    for (unsigned int i(1); i <= trajetsTrouves->NombreDeTrajets(); i++)
    {
        cout << i << " - ";
        trajetsTrouves->TrajetNumero(i)->Afficher();
        cout << endl;
    }

    delete trajetsTrouves;
}

static void rechercherCompletTrajet(Catalogue &leCatalogue)
{
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    saisirVille(villeArrivee, TAILLE_MAX_VILLE, "Ville d'arrivée :");

    CollectionTrajets **trajetsTrouves;
    unsigned int nbTrajetsTrouves;

    leCatalogue.RechercherComplet(villeDepart, villeArrivee, trajetsTrouves, nbTrajetsTrouves);

    // Affichage des résultats
    cout << "Résultat : " << endl;
    for (unsigned int i(0); i < nbTrajetsTrouves; i++)
    {
        cout << i + 1;
        for (unsigned int j(1); j <= trajetsTrouves[i]->NombreDeTrajets(); j++)
        {
            cout << " - ";
            trajetsTrouves[i]->TrajetNumero(j)->Afficher();
        }
        cout << endl;
    }

    // Destruction des collections
    for (unsigned int i(0); i < nbTrajetsTrouves; i++)
    {
        delete trajetsTrouves[i];
    }

    delete[] trajetsTrouves;
}

static unsigned int selectionMethode()
{
    unsigned int choixMethode;
    cout << "Choisir le type de filtre :" << endl;
    cout << "\t1. Tous les trajets" << endl;
    cout << "\t2. Par type de trajet" << endl;
    cout << "\t3. Par ville de départ et/ou ville d'arrivée" << endl;
    cout << "\t4. Par intervalle" << endl;

    while (!(cin >> choixMethode) || (1 > choixMethode || choixMethode > 4))
    {
        cout << "Le choix de l'option doit être un entier, compris entre 1 et 4. Veuillez réessayer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choixMethode;
}

static unsigned int selectionTypeTrajet()
{
    unsigned int choixTypeTrajet;

    cout << "Choisir le type de trajet" << endl;
    cout << "\t1. Simple" << endl;
    cout << "\t2. Composé" << endl;

    while (!(cin >> choixTypeTrajet) || (1 > choixTypeTrajet || choixTypeTrajet > 2))
    {
        cout << "Le choix de l'option doit être un entier, compris entre 1 et 2. Veuillez réessayer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choixTypeTrajet-1;
}

static unsigned int selectionIndice()
{
    unsigned int indicePremierTrajet;
    cout << "\tIndice du premier trajet :" << endl;
    while (!(cin >> indicePremierTrajet))
    {
        cout << "L'indice indiqué doit être un entier positif, veuillez réessayer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return indicePremierTrajet;
}

static unsigned int selectionNombreTrajet()
{
    unsigned int nombreTrajet;
    cout << "\tNombre de trajets :" << endl;
    while (!(cin >> nombreTrajet))
    {
        cout << "L'indice indiqué doit être un entier positif, veuillez réessayer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return nombreTrajet;
}

static string selectionVille(const char *message)
{
    string choixVille;
    cout << message << endl;
    while (!getline(cin, choixVille) || choixVille.size() > TAILLE_MAX_VILLE)
    {
        cout << "La ville doit contenir moins de 50 caractères. Veuillez réessayer" << endl;
    }
    return choixVille;
}

static ofstream ecritureFichier()
{
    string fileName;
    cout << "Préciser le nom du fichier à utiliser pour sauvegarder le catalogue:" << endl;

    cin >> fileName;

    ofstream fichier(fileName);

    return fichier;
}

static ifstream lectureFichier()
{
    string fileName;
    cout << "Préciser le nom du fichier à utiliser pour charger le catalogue:" << endl;

    cin >> fileName;

    ifstream fichier(fileName);

    return fichier;
}

static void chargerCatalogue(Catalogue &leCatalogue)
{
    unsigned int choixMethode;
    string choixVilleDepart;
    string choixVilleArrivee;

    ifstream fichier;
    do
    {
        fichier = lectureFichier();
        if (!fichier.is_open())
        {
            cout << "Erreur à l'ouverture du fichier, veuillez réessayer." << endl;
        }
    } while (fichier.fail());

    choixMethode = selectionMethode();

    switch (choixMethode)
    {
    case 1:
        leCatalogue.Charger(fichier);
        break;
    case 2:
        int choixTypeTrajet;
        choixTypeTrajet = selectionTypeTrajet();
        leCatalogue.Charger(fichier, typeTrajet(choixTypeTrajet));
        break;
    case 3:
        choixVilleDepart = selectionVille("Ville de départ : (* Pour tous)");
        choixVilleArrivee = selectionVille("Ville d'arrivée : (* Pour tous)");
        leCatalogue.Charger(fichier, choixVilleDepart.c_str(), choixVilleArrivee.c_str());
        break;
    case 4:
        int indicePremierTrajet, nombreTrajet;
        indicePremierTrajet = selectionIndice();
        nombreTrajet = selectionNombreTrajet();
        leCatalogue.Charger(fichier, indicePremierTrajet, nombreTrajet);
        break;
    }
}

static void sauvegarderCatalogue(Catalogue &leCatalogue)
{
    unsigned int choixMethode;
    string choixVilleDepart;
    string choixVilleArrivee;

    ofstream fichier;
    do
    {
        fichier = ecritureFichier();
        if (!fichier.is_open())
        {
            cout << "Erreur à l'ouverture du fichier, veuillez réessayer." << endl;
        }
    } while (fichier.fail());

    choixMethode = selectionMethode();

    switch (choixMethode)
    {
    case 1:
        leCatalogue.Sauvegarde(fichier);
        break;
    case 2:
        int choixTypeTrajet;
        choixTypeTrajet = selectionTypeTrajet();
        leCatalogue.Sauvegarde(fichier, typeTrajet(choixTypeTrajet));
        break;
    case 3:
        choixVilleDepart = selectionVille("Ville de départ : (* Pour tous)");
        choixVilleArrivee = selectionVille("Ville d'arrivée : (* Pour tous)");
        leCatalogue.Sauvegarde(fichier, choixVilleDepart.c_str(), choixVilleArrivee.c_str());
        break;
    case 4:
        int indicePremierTrajet, nombreTrajet;
        indicePremierTrajet = selectionIndice();
        nombreTrajet = selectionNombreTrajet();
        leCatalogue.Sauvegarde(fichier, indicePremierTrajet, nombreTrajet);
        break;
    }
}

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
int main()
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
        cout << "\t5. Rechercher un trajet (complet)" << endl;
        cout << "\t6. Charger un catalogue" << endl;
        cout << "\t7. Sauvegarder un catalogue" << endl;
        cout << "\t0. Quitter" << endl;

        cin >> choixMenu;
        if (cin.eof())
        {
            choixMenu = 0;
        }

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
        case 5:
            rechercherCompletTrajet(leCatalogue);
            break;
        case 6:
            chargerCatalogue(leCatalogue);
            break;
        case 7:
            sauvegarderCatalogue(leCatalogue);
            break;
        case 0:
            return 0;
        }
    }
    return 0;
}