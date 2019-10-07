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

    if(_nbElementMax <= _nbElementCourant)
    {
        // realouer tableau 
        _nbElementMax *= FACTEUR_AJUSTEMENT;
        const Trajet** nouveauTab = new const Trajet*[_nbElementMax];

        // copier les élements

        for (unsigned int i = 0; i < _nbElementCourant; i++)
        {
            nouveauTab[i] = _elements[i];
        }

        delete []_elements;

        _elements = nouveauTab;

    }

    _elements[_nbElementCourant] = trajet;
    _nbElementCourant++;

} // 

unsigned int CollectionTrajets::NombreDeTrajets () const
// Algorithme :
{
    return this->_nbElementCourant;
}

const Trajet * CollectionTrajets::TrajetNumero ( unsigned int numero ) const
// Algorithme :
{
    return _elements[numero - 1];
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CollectionTrajets::CollectionTrajets ( const CollectionTrajets & source)
// Algorithme :
{
    _nbElementMax = source._nbElementMax;
    _nbElementCourant = source._nbElementCourant;
    _elements = new const Trajet*[_nbElementMax];
    
    for (unsigned int i = 0; i < _nbElementCourant; i++)
    {
        _elements[i] = source._elements[i];
    }
    
#ifdef MAP
    cout << "Appel au constructeur par copie de <CollectionTrajets>" << endl;
#endif
} //----- Fin de CollectionTrajets

CollectionTrajets::CollectionTrajets ( )
// Algorithme :
{
    _nbElementMax = TAILLEMAX;
    _nbElementCourant = 0;
    _elements = new const Trajet*[_nbElementMax];
    
#ifdef MAP
    cout << "Appel au constructeur par défaut de <CollectionTrajets>" << endl;
#endif
} //----- Fin de CollectionTrajets



CollectionTrajets::~CollectionTrajets ( )
// Algorithme :
//
{
    delete []_elements;

#ifdef MAP
    cout << "Appel au destructeur de <CollectionTrajets>" << endl;
#endif
} //----- Fin de ~CollectionTrajets

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
