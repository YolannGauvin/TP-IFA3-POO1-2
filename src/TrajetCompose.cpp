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
    return this->VilleDepart;
} //----- Fin de VilleDepart

const char * TrajetCompose::VilleArrivee () const
// Algorithme :
{
     return this->VilleArrivee;
} //----- Fin de VilleArrivee

void TrajetCompose::Afficher () const
// Algorithme :
{
    // afficher tous le trajets

    for(int i = 0; i < this-> _trajets.NombreDeTrajets ; i++)
    {
        //_trajets.getElements[i]->afficher();
    }
    
} //----- Fin de Afficher

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( CollectionTrajets composants )
// Algorithme :
//
{

    // construire CollectionTrajet
    //this->_trajets->setNbElementMax();
    //this->_trajets.setElements(trajets);
    

#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose> (nbTrajets : " 
        << composants.NombreDeTrajets() << ")" << endl;
#endif
} //----- Fin de TrajetCompose

TrajetCompose::~TrajetCompose ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de ~TrajetCompose

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
