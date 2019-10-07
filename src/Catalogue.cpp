/*************************************************************************
                            Catalogue  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) -------

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
// Algorithme :
{
    _trajets.AjouterTrajet(t);
} //----- Fin de AjouterTrajet

void Catalogue::Afficher () const
// Algorithme : boucle sur tous les trajets et invoque pour chacun
// sa méthode d'affichage.
{
    for (unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
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
    CollectionTrajets * trajetsTrouves = new CollectionTrajets();
    
    for (unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
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
// Algorithme : Aucun
{
    for(unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
    {
        delete _trajets.TrajetNumero(i);
    }

#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
