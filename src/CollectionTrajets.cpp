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
    
} // Fin de AjouterTrajet

unsigned int CollectionTrajets::NombreDeTrajets () const
// Algorithme :
{
    return 0;
}

const Trajet * CollectionTrajets::TrajetNumero ( unsigned int numero ) const
// Algorithme :
{
    return nullptr;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CollectionTrajets::CollectionTrajets ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <CollectionTrajets>" << endl;
#endif
} //----- Fin de CollectionTrajets

CollectionTrajets::CollectionTrajets ( const CollectionTrajets & source )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CollectionTrajets> (nbTrajets : " 
        << source.NombreDeTrajets() << ")" << endl;
#endif
} //----- Fin de CollectionTrajets

CollectionTrajets::~CollectionTrajets ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CollectionTrajets>" << endl;
#endif
} //----- Fin de ~CollectionTrajets

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
