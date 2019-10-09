/*************************************************************************
                            Catalogue  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> 
//                                         (fichier Catalogue.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "../includes/Catalogue.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::AjouterTrajet ( const Trajet * t )
// Algorithme : aucun
{
    _trajets.AjouterTrajet(t);
} //----- Fin de AjouterTrajet

void Catalogue::Afficher () const
// Algorithme : boucle sur tous les trajets et invoque pour chacun
// sa méthode d'affichage.
{
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        cout << i << " - ";
        _trajets.TrajetNumero(i)->Afficher();
        cout << endl;
    }
} //----- Fin de Afficher

CollectionTrajets * Catalogue::Rechercher ( 
    const char * villeDepart,
    const char * villeArrivee) const
// Algorithme : Boucle sur tous les trajet du catalogue et ajoute le trajet
// dans la collection si la ville de départ et la ville d'arrivée
// sont les mêmes
{
    CollectionTrajets * trajetsTrouves (new CollectionTrajets());
    
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        const Trajet * trajetCourant = _trajets.TrajetNumero(i);
        if (strcmp(trajetCourant->VilleDepart(), villeDepart) == 0
        && strcmp(trajetCourant->VilleArrivee(), villeArrivee) == 0)
        {
            trajetsTrouves->AjouterTrajet(trajetCourant);
        }
    }

    return trajetsTrouves;
} //----- Fin de Rechercher

void Catalogue::RechercherComplet (
    const char * villeDepart, 
    const char * villeArrivee,
    CollectionTrajets **& trajetsTrouves,
    unsigned int & nbTrajetsTrouves ) const
// Algorithme : 
// Le principe de base est de parcourir toutes les combinaisons possibles
// de trajets.
// Pour ce faire, pour chaque trajet on divise la recherche en deux :
// on prend le trajet et on ne prends pas le trajet, et on réitère pour
// les projets suivants.
// De cette manière, on aura simuler le parcours d'un arbre binaire,
// qui, à chaque niveau de l'arbre décide de prendre ou ne pas prendre
// un trajet.
{
    const unsigned int TAILLE_MAX_DEF (10);
    unsigned int tailleMaxTrajets (TAILLE_MAX_DEF);
    const Trajet** uneCombinaison (
        new const Trajet*[_trajets.NombreDeTrajets()]
    );

    trajetsTrouves = new CollectionTrajets*[tailleMaxTrajets];
    nbTrajetsTrouves = 0;

    combinaison(
        villeDepart, 
        villeArrivee, 
        1, // numéro du trajet courant
        true, // on prend le trajet 
        uneCombinaison, 
        0, // nombre de trajets dans la combinaison
        trajetsTrouves, 
        tailleMaxTrajets, 
        nbTrajetsTrouves
    );

    combinaison(
        villeDepart, 
        villeArrivee, 
        1, // numéro du trajet courant
        false, // on ne prend pas le trajet
        uneCombinaison, 
        0, // nombre de trajet dans la combinaison
        trajetsTrouves, 
        tailleMaxTrajets, 
        nbTrajetsTrouves
    );

    delete[] uneCombinaison;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue () : _trajets()
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue

Catalogue::~Catalogue ( )
// Algorithme : boucle sur les trajets de la collection pour les 
// détruire.
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif

    for(unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        delete _trajets.TrajetNumero(i);
    }
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::combinaison(
    const char * villeDepart,
    const char * villeArrivee,
    unsigned int trajetCourant,
    bool prends,
    const Trajet** uneCombinaison,
    unsigned int tailleCombinaison,
    CollectionTrajets **& trajetsTrouves,
    unsigned int tailleMaxTrajets,
    unsigned int & nbTrajetsTrouves ) const
// Algorihtme :
// Si on décide de ne pas prendre le trajet courant, on passe
// au trajet suivant (qu'on doit ou ne doit pas prendre).
// Si on décide de prendre le trajet courant, il y a deux cas :
//  - Cas général : vérifier que la ville de départ du trajet courant
//    est la même que la ville d'arrivée du dernier trajet de la combinaison,
//    sinon on arrête la récursivité.
//  - Cas particulier : il n'y a aucun trajet dans la combinaison, on vérifie
//    que la ville de départ du trajet courant est la même que celle demandée
//    en paramètre, sinon on arrête la récursivité.
// Dans tous les cas, si la ville d'arrivée du trajet courant (celui ajouté)
// est la même que la ville d'arrivée donnée en paramètre, on ajoute la 
// combinaison de trajet dans notre tableau de collection de trajets 
// `trajetsTrouves` : c'est un trajet qui répond à la demande.
// S'il n'y a plus de trajets à ajouter, la récursivité s'arrête.
{
    if (trajetCourant > _trajets.NombreDeTrajets())
    {
        return;
    }

    if (!prends)
    {
        combinaison( villeDepart, villeArrivee, 
            trajetCourant + 1, true, 
            uneCombinaison, tailleCombinaison, 
            trajetsTrouves, tailleMaxTrajets, 
            nbTrajetsTrouves );

        combinaison( villeDepart, villeArrivee, 
            trajetCourant + 1, false, 
            uneCombinaison, tailleCombinaison, 
            trajetsTrouves, tailleMaxTrajets, 
            nbTrajetsTrouves );

        return;
    }

    // vérification de la cohésion entre trajet précédent et 
    // trajet courant
    if (tailleCombinaison == 0)
    {
        if (strcmp(_trajets.TrajetNumero(trajetCourant)->VilleDepart(), 
        villeDepart) != 0)
            return;
    }
    else
    {
        if (strcmp( _trajets.TrajetNumero(trajetCourant)->VilleDepart(),
        uneCombinaison[tailleCombinaison-1]->VilleArrivee()) != 0)
            return;
    }
    

    // ajout du trajet dans la combinaison
    uneCombinaison[tailleCombinaison] = _trajets.TrajetNumero(trajetCourant);
    tailleCombinaison++;

    // si la combinaison de trajets répond à la demande,
    // on l'ajoute dans notre tableau.
    if (strcmp(villeDepart, uneCombinaison[0]->VilleDepart()) == 0
    && strcmp(villeArrivee, uneCombinaison[tailleCombinaison-1]->VilleArrivee()) == 0)
    {
        if (nbTrajetsTrouves >= tailleMaxTrajets)
        {
            tailleMaxTrajets += tailleMaxTrajets;
            CollectionTrajets** nouvTableau (
                new CollectionTrajets*[tailleMaxTrajets]
            );
            
            for (unsigned int i (0); i < nbTrajetsTrouves; i++) 
            {
                nouvTableau[i] = trajetsTrouves[i];
            }

            delete[] trajetsTrouves;
            trajetsTrouves = nouvTableau;
        }

        trajetsTrouves[nbTrajetsTrouves] = new CollectionTrajets;
        for (unsigned int i = 0; i < tailleCombinaison; i++)
        {
            trajetsTrouves[nbTrajetsTrouves]->AjouterTrajet(uneCombinaison[i]);
        }
        nbTrajetsTrouves++;
    }
    
    combinaison( villeDepart, villeArrivee, 
        trajetCourant + 1, true, 
        uneCombinaison, tailleCombinaison, 
        trajetsTrouves, tailleMaxTrajets, 
        nbTrajetsTrouves );

    combinaison( villeDepart, villeArrivee, 
        trajetCourant + 1, false, 
        uneCombinaison, tailleCombinaison, 
        trajetsTrouves, tailleMaxTrajets, 
        nbTrajetsTrouves );
}