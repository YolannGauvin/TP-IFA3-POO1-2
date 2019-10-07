/*************************************************************************
                            TrajetCompose  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "../includes/TrajetCompose.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const char * TrajetCompose::VilleDepart () const
// Algorithme :
{
    return _trajets.TrajetNumero(1)->VilleDepart();
} //----- Fin de VilleDepart

const char * TrajetCompose::VilleArrivee () const
// Algorithme :
{
    return _trajets.TrajetNumero(_trajets.NombreDeTrajets())->VilleArrivee();

} //----- Fin de VilleArrivee

void TrajetCompose::Afficher () const
// Algorithme :
{
    if (_trajets.NombreDeTrajets() >= 1)
    {
        _trajets.TrajetNumero(1)->Afficher();
        
        for(unsigned int i (2); i <= this-> _trajets.NombreDeTrajets() ; i++)
        {
            cout << " - ";
            _trajets.TrajetNumero(i)->Afficher();
        }
    }
    
} //----- Fin de Afficher

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( const CollectionTrajets & composants ) :
    Trajet (),
    _trajets (composants)
// Algorithme :
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose> (nbTrajets : " 
        << composants.NombreDeTrajets() << ")" << endl;
#endif
} //----- Fin de TrajetCompose

TrajetCompose::~TrajetCompose ( )
// Algorithme :
{
    for(unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        delete _trajets.TrajetNumero(i);
    }

#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de ~TrajetCompose

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
