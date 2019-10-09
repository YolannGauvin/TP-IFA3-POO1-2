/*************************************************************************
                            TCatalogue  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation du module <TCatalogue> (fichier TCatalogue.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../../includes/test/TCatalogue.h"
#include "../../includes/Catalogue.h"
#include "../../includes/TrajetSimple.h"
#include "../../includes/TrajetCompose.h"
#include "../../includes/CollectionTrajets.h"

///////////////////////////////////////////////////////////////////  PRIVE

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
void testConstructeur()
{
    Catalogue c;
    c.Afficher();
    // Devrait ne rien afficher

} //----- Fin de testConstructeur

void testAjouter()
{
    TrajetSimple *t1 = new TrajetSimple("A", "B", AUTO);
    TrajetSimple *t2 = new TrajetSimple("A", "B", TRAIN);
    TrajetSimple *t3 = new TrajetSimple("B", "C", AVION);
    CollectionTrajets ct;
    ct.AjouterTrajet(t2);
    ct.AjouterTrajet(t3);
    TrajetCompose * t4 = new TrajetCompose(ct);

    Catalogue c;
    c.AjouterTrajet(t1);
    c.AjouterTrajet(t4);
    c.Afficher();
    // Devrait afficher :
    // 1 - De A à B en Auto
    // 2 - De A à B en Train - De B à C en Avion

} //----- Fin de testAjouter

void testRechercherSimpleAucun()
{
    TrajetSimple * t1 = new TrajetSimple("A", "B", AUTO);
    TrajetSimple * t2 = new TrajetSimple("A", "D", TRAIN);
    TrajetSimple * t3 = new TrajetSimple("B", "C", AVION);

    Catalogue c;
    c.AjouterTrajet(t1);
    c.AjouterTrajet(t2);
    c.AjouterTrajet(t3);
    CollectionTrajets * trajetsTrouves = c.Rechercher("A", "E");
    cout << trajetsTrouves->NombreDeTrajets() << endl;
    delete trajetsTrouves;
    // Devrait afficher :
    // 0
} //----- Fin de testRechercherSimpleAucun

void testRechercherSimpleExiste()
// Mode d'emploi : Test la méthode de recherche simple sur un ou
// plusieurs trajets qui existent
{
    TrajetSimple *t1 = new TrajetSimple("A", "B", AUTO);
    TrajetSimple *t2 = new TrajetSimple("A", "B", TRAIN);
    TrajetSimple *t3 = new TrajetSimple("B", "C", AVION);
    TrajetSimple *t4 = new TrajetSimple("A", "C", AVION);
    CollectionTrajets ct;
    ct.AjouterTrajet(t2);
    ct.AjouterTrajet(t3);
    TrajetCompose * t5 = new TrajetCompose (ct);

    Catalogue c;
    c.AjouterTrajet(t1);
    c.AjouterTrajet(t5);
    c.AjouterTrajet(t4);
    CollectionTrajets * trajetsTrouves = c.Rechercher("A", "C");
    cout << trajetsTrouves->NombreDeTrajets() << endl;
    trajetsTrouves->TrajetNumero(1)->Afficher();
    cout << endl;
    trajetsTrouves->TrajetNumero(2)->Afficher(); 
    cout << endl;
    delete trajetsTrouves;
    // Devrait afficher :
    // 2
    // De A à B en Train - De B à C en Avion
    // De A à C en Avion
} //----- Fin de testRechercherSimpleExiste

void testRechercherCompletAucun()
{
    TrajetSimple *t1 = new TrajetSimple("A", "B", AUTO);
    TrajetSimple *t2 = new TrajetSimple("A", "D", TRAIN);
    TrajetSimple *t3 = new TrajetSimple("B", "C", AVION);

    Catalogue c;
    c.AjouterTrajet(t1);
    c.AjouterTrajet(t2);
    c.AjouterTrajet(t3);
    CollectionTrajets * trajetsTrouves;
    unsigned int nbTrajetsTrouves;

    c.RechercherComplet("A", "E", trajetsTrouves, nbTrajetsTrouves);
    cout << nbTrajetsTrouves << endl;
    delete[] trajetsTrouves;
    // Devrait afficher :
    // 0
} //----- Fin de testRechercherCompletAucun

void testRechercherCompletExiste()
{
    TrajetSimple *t1 = new TrajetSimple("A", "B", AUTO);
    TrajetSimple *t2 = new TrajetSimple("A", "B", TRAIN);
    TrajetSimple *t3 = new TrajetSimple("B", "C", AVION);
    TrajetSimple *t4 = new TrajetSimple("A", "C", AVION);

    Catalogue c;
    c.AjouterTrajet(t1);
    c.AjouterTrajet(t2);
    c.AjouterTrajet(t3);
    c.AjouterTrajet(t4);

    CollectionTrajets * trajetsTrouves;
    unsigned int nbTrajetsTrouves; 
    c.RechercherComplet("A", "C", trajetsTrouves, nbTrajetsTrouves);

    cout << nbTrajetsTrouves << endl;
    for (unsigned int i (0); i < nbTrajetsTrouves; i++)
    {
        cout << i + 1;
        for (unsigned int j (1); j <= trajetsTrouves[i].NombreDeTrajets(); j++)
        {
            cout << " - ";
            trajetsTrouves[i].TrajetNumero(j)->Afficher();
        }
        cout << endl;
    }
    delete[] trajetsTrouves;

    // Devrait afficher :
    // 3
    // 1 - De A à B en Auto - De B à C en Avion
    // 2 - De A à B en Train - De B à C en Avion
    // 3 - De A à C en Avion
} //----- Fin de testRechercherCompletExiste

int main ()
{
    testConstructeur();
    testAjouter();
    testRechercherSimpleAucun();
    testRechercherSimpleExiste();
    testRechercherCompletAucun();
    testRechercherCompletExiste();
    return 0;
}