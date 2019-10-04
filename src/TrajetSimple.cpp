/*************************************************************************
                            TrajetSimple  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "../includes/TrajetSimple.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const char * TrajetSimple::VilleDepart () const 
// Algorithme : Aucun
{
    return _villeDepart;
} //----- Fin de VilleDepart

const char * TrajetSimple::VilleArrivee () const
// Algorithme : Aucun
{
    return _villeArrivee;
} //----- Fin de VilleArrivee

void TrajetSimple::Afficher () const
// Algorithme : Aucun
{
    cout << "De " << _villeDepart 
        << " à " << _villeArrivee
        << " en " << _moyenDeTransport << endl;
} //----- Fin de Afficher

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple ( 
    const char * laVilleDepart,
    const char * laVilleArrivee,
    moyenDeTransport leMoyenDeTransport
) : Trajet(), _villeDepart(laVilleDepart), 
    _villeArrivee(laVilleArrivee), 
    _moyenDeTransport(leMoyenDeTransport)
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple> (" 
        << laVilleDepart << " -> "
        << laVilleArrivee << ","
        << leMoyenDeTransport << ")" << endl;
#endif
} //----- Fin de TrajetSimple

TrajetSimple::~TrajetSimple ( )
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
} //----- Fin de ~TrajetSimple

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
