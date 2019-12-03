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
const unsigned int TAILLE_MAX_VILLE = 255;
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

static string saisirVille(
    unsigned int maxLength,
    const char *message = "Ville :",
    bool vide = false)
{
    string choixVille;
    cout << message << " (taille max: " << maxLength << ")" << endl;
    
    while (!getline(cin, choixVille) || 
    choixVille.size() > maxLength || 
    (!vide && choixVille.size() == 0) ||
    choixVille.find("|") != string::npos)
    {
        if (choixVille.find("|") != string::npos)
        {
            cerr << "La ville ne peut pas contenir le caractère '|'" << endl;
        }
        else 
        {
            cerr << "La ville doit contenir moins de " << maxLength 
                << " caractères";
            if (!vide)
            {
                cerr << " et ne pas être une chaîne vide.";
            }
            cerr << " Veuillez réessayer." << endl;
        }
        
        if (!cin) {
            cin.clear();
        }
    }

    return choixVille;
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

    while (!(cin >> choixTransport) || (1 > choixTransport || choixTransport > 6))
    {
        cerr << "Le choix doit être un nombre compris entre 1 et 6. Veuillez réessayer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    }
}

static void afficherCatalogue(Catalogue &leCatalogue)
{
    leCatalogue.Afficher();
}

static void ajouterTrajetSimple(Catalogue &leCatalogue)
{
    moyenDeTransport leMoyenDeTransport;
    string villeDepart;
    string villeArrivee;

    villeDepart = saisirVille(TAILLE_MAX_VILLE, "Ville de départ :");
    villeArrivee = saisirVille(TAILLE_MAX_VILLE, "Ville d'arrivée :");
    saisirMoyenDeTransport(leMoyenDeTransport, "Moyen de transport :");

    leCatalogue.AjouterTrajet(
        new TrajetSimple(
            villeDepart.c_str(),
            villeArrivee.c_str(),
            leMoyenDeTransport));
}

static void ajouterTrajetCompose(Catalogue &leCatalogue)
{
    CollectionTrajets trajets;
    moyenDeTransport leMoyenDeTransport;
    string villeDepart;
    string villeArrivee;

    villeDepart = saisirVille(TAILLE_MAX_VILLE, "Ville de départ :");

    while (true)
    {
        villeArrivee = saisirVille(TAILLE_MAX_VILLE,
                    "Ville suivante (Laisser vide pour arrêter) :", true);

        if (villeArrivee == "")
            break;

        saisirMoyenDeTransport(leMoyenDeTransport, "Moyen de transport :");

        trajets.AjouterTrajet(
            new TrajetSimple(
                villeDepart.c_str(),
                villeArrivee.c_str(),
                leMoyenDeTransport));

        villeDepart = villeArrivee;
    }

    if (trajets.NombreDeTrajets() > 0)
        leCatalogue.AjouterTrajet(
            new TrajetCompose(trajets));
}

static void rechercherTrajet(Catalogue &leCatalogue)
{
    string villeDepart;
    string villeArrivee;

    villeDepart = saisirVille(TAILLE_MAX_VILLE, "Ville de départ :");
    villeArrivee = saisirVille(TAILLE_MAX_VILLE, "Ville d'arrivée :");

    CollectionTrajets *trajetsTrouves(
        leCatalogue.Rechercher(villeDepart.c_str(), villeArrivee.c_str()));

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
    string villeDepart;
    string villeArrivee;

    villeDepart = saisirVille(TAILLE_MAX_VILLE, "Ville de départ :");
    villeArrivee = saisirVille(TAILLE_MAX_VILLE, "Ville d'arrivée :");

    CollectionTrajets **trajetsTrouves;
    unsigned int nbTrajetsTrouves;

    leCatalogue.RechercherComplet(
        villeDepart.c_str(), 
        villeArrivee.c_str(), 
        trajetsTrouves, 
        nbTrajetsTrouves);

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
        cerr << "Le choix de l'option doit être un entier compris entre 1 et 4. Veuillez réessayer :" << endl;
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
        cerr << "Le choix de l'option doit être un entier compris entre 1 et 2. Veuillez réessayer :" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choixTypeTrajet-1;
}

static unsigned int selectionIndice(
    unsigned int min, 
    unsigned int max, 
    const char * message)
{
    unsigned int indice;
    cout << message << " (entre " << min << " et " << max << ") :" << endl;
    while (!(cin >> indice) || indice < min || indice > max)
    {
        cerr << "L'indice indiqué doit être un entier positif compris entre " 
        << min << " et " << max << ", veuillez réessayer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return indice;
}

static unsigned int selectionIndice(
    const char * message)
{
    unsigned int indice;
    cout << message << " :" << endl;
    while (!(cin >> indice))
    {
        cerr << "L'indice indiqué doit être un entier positif, veuillez réessayer :" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return indice;
}

static ofstream ecritureFichier()
{

    ofstream fichier;
    string filename;
    cout << "Préciser le nom du fichier à utiliser pour sauvegarder le catalogue:" << endl;

    if (!getline(cin, filename))
    {
        cerr << "Erreur lors de la lecture du nom de fichier " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return fichier;
    }

    fichier.open(filename);
    if (!fichier.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier " << filename << endl;
    }

    return fichier;
}

static ifstream lectureFichier()
{
    ifstream fichier;
    string filename;
    cout << "Préciser le nom du fichier à utiliser pour charger le catalogue:" << endl;

    if (!getline(cin, filename))
    {
        cerr << "Erreur lors de la lecture du nom de fichier " << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return fichier;
    }

    fichier.open(filename);
    if (!fichier.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier " << filename << endl;
    }

    return fichier;
}

static void chargerCatalogue(Catalogue &leCatalogue)
{
    unsigned int choixMethode;
    string choixVilleDepart;
    string choixVilleArrivee;

    ifstream fichier = lectureFichier();
    if (!fichier.is_open()) 
    {
        return;
    }

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
        choixVilleDepart = saisirVille(TAILLE_MAX_VILLE, "Ville de départ : (Laisser vide pour toutes)", true);
        choixVilleArrivee = saisirVille(TAILLE_MAX_VILLE, "Ville d'arrivée : (Laisser vide pour toutes)", true);
        leCatalogue.Charger(fichier, choixVilleDepart.c_str(), choixVilleArrivee.c_str());
        break;
    case 4:
        unsigned int indicePremier = 1;
        unsigned int indiceSecond = leCatalogue.NombreDeTrajets();
        indicePremier = selectionIndice("Borne inférieure (incluse)");
        indiceSecond = selectionIndice("Borne supérieure (incluse)");
        leCatalogue.Charger(fichier, indicePremier, indiceSecond);
        break;
    }

    fichier.close();
}

static void sauvegarderCatalogue(Catalogue &leCatalogue)
{
    unsigned int choixMethode;
    string choixVilleDepart;
    string choixVilleArrivee;

    ofstream fichier = ecritureFichier();
    if (!fichier.is_open()) 
    {
        return;
    }

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
        choixVilleDepart = saisirVille(TAILLE_MAX_VILLE, "Ville de départ : (Laisser vide pour toutes)", true);
        choixVilleArrivee = saisirVille(TAILLE_MAX_VILLE, "Ville d'arrivée : (Laisser vide pour toutes)", true);
        leCatalogue.Sauvegarde(fichier, choixVilleDepart.c_str(), choixVilleArrivee.c_str());
        break;
    case 4:
        unsigned int indicePremier = 1;
        unsigned int indiceSecond = leCatalogue.NombreDeTrajets();
        indicePremier = selectionIndice(indicePremier, indiceSecond, "Borne inférieure (incluse)");
        indiceSecond = selectionIndice(indicePremier, indiceSecond, "Borne supérieure (incluse)");
        leCatalogue.Sauvegarde(fichier, indicePremier, indiceSecond);
        break;
    }

    fichier.close();
}

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
int main()
{
    unsigned int choixMenu;
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

        if (!(cin >> choixMenu) || choixMenu < 0 || choixMenu > 7)
        {
            cerr << "Le choix de l'option doit être un entier, compris entre 0 et 7. Veuillez réessayer" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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