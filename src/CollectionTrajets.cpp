/*************************************************************************
                            CollectionTrajets  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Réalisation de la classe <CollectionTrajets> (fichier CollectionTrajets.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "../includes/CollectionTrajets.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void CollectionTrajets::AjouterTrajet ( const Trajet * trajet )
// Algorithme :
{
    this->_elements[this->_nbElementCourant] = trajet;
    this->_nbElementCourant++;
} // 

unsigned int CollectionTrajets::NombreDeTrajets () const
// Algorithme :
{
    return this->_nbElementCourant;
}

const Trajet * CollectionTrajets::TrajetNumero ( unsigned int numero ) const
// Algorithme :
{
    return _elements[_nbElementCourant - 1];
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CollectionTrajets::CollectionTrajets ( )
// Algorithme :
{
    _nbElementMax = TAILLEMAX;
    _nbElementCourant = 0;
    _elements = new Trajet*[_nbElementMax];
    
    #ifdef MAP
        cout << "Appel au constructeur par défaut de <CollectionTrajets>" << endl;
    #endif
} //----- Fin de CollectionTrajets

CollectionTrajets::CollectionTrajets ( Trajet** trajets, unsigned int nbTrajets)
// Algorithme :
//
{
    _nbElementMax = nbTrajets;
    _nbElementCourant = nbTrajets;
    _elements = trajets;

#ifdef MAP
    cout << "Appel au constructeur de <CollectionTrajets> (nbTrajets : " 
        << nbTrajets << ")" << endl;
#endif

    
} //----- Fin de CollectionTrajets

CollectionTrajets::~CollectionTrajets ( )
// Algorithme :
//
{

    for(int i = 0; i < _nbElementCourant; i++)
    {
        delete _elements[i];
    }

    delete []_elements;

#ifdef MAP
    cout << "Appel au destructeur de <CollectionTrajets>" << endl;
#endif
} //----- Fin de ~CollectionTrajets

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
