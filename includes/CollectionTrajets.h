/*************************************************************************
                            CollectionTrajets  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc Serrania
*************************************************************************/

//---------- Interface de la classe <CollectionTrajets> (fichier <CollectionTrajets.h>) ------

#if ! defined ( COLLECTIONTRAJETS_H )
#define COLLECTIONTRAJETS_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <CollectionTrajets>
// La classe CollectionTrajets permet d'ordonner des pointeurs
// sur des instances de Trajet dans un tableau dynamique.
// Elle propose des services d'ajout de trajets après sa construction
// ainsi
//------------------------------------------------------------------------
class CollectionTrajets
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AjouterTrajet ( const Trajet * trajet );
    // Mode d'emploi :
    // Ajoute un trajet dans la collection.
    // Ce trajet se trouve à la suite du dernier trajet ajouté à la
    // collection.
    //
    // Contrat de cohérence :
    // La ville de départ du trajet ajouté doit être la même que la ville 
    // d'arrivée du dernier trajet dans la collection.

    unsigned int NombreDeTrajets () const;
    // Mode d'emploi :
    // Renvoie la taille courante de la collection et donc le nombre
    // de trajets.

    const Trajet * TrajetNumero ( unsigned int numero ) const;
    // Mode d'emploi :
    // Renvoie le numero-ieme trajet de la collection de trajets
    // (1 = premier trajet, ..., taille courante = dernier trajet)
    // 
    // Contrat de performance :
    // Si la collection est vide, cette méthode ne doit pas être 
    // appelé. Le numéro doit être compris entre 1 et la taille courante 
    // de la collection incluse.

    
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    CollectionTrajets ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe <CollectionTrajets>
    // Les éléments de la collection sont des pointeurs sur Trajet et sont
    // rangés dans un tableau dynamique de taille maximale définie par une
    // constante.
    // La collection est vide et par conséquent la taille courante est de 
    // 0 après la construction.
    // Les éléments sont ordonnés par ordre d'ajout grâce à la méthode
    // AjouterTrajet.

    CollectionTrajets ( Trajet** trajets, unsigned int nbTrajets );
    // Mode d'emploi :
    // Constructeur par copie de la classe <CollectionTrajets>
    // Construit une suite ordonnée de trajets à partir des nbTrajets
    // premiers éléments significatifs du tableau trajets. La collection
    // est pleine au sens où la taille courante donnée par la méthode
    // NombreDeTrajets est égale à la taille max du tableau dynamique.
    //
    // Contrat de cohérence :
    // Les nbTrajets premiers éléments du tableau trajet sont significatifs.

    virtual ~CollectionTrajets ( );
    // Mode d'emploi :
    // Destructeur de la classe <CollectionTrajets>

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Trajet** elements;
};

//--------------------------- Autres définitions dépendantes de <CollectionTrajets>

#endif // COLLECTIONTRAJETS_H