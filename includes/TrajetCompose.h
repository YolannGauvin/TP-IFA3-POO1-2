/*************************************************************************
                            TrajetCompose  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier <TrajetCompose.h>) ------

#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "CollectionTrajets.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// Un TrajetCompose est une suite ordonnée de Trajets qui se suivent les 
// les autres. La ville d'arrivée d'un trajet doit être la ville de départ
// du trajet suivant.
//------------------------------------------------------------------------
class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual const char * VilleDepart () const;
    // Mode d'emploi :
    // Renvoie la ville de départ du premier trajet.

    virtual const char * VilleArrivee () const;
    // Mode d'emploi :
    // Renvoie la ville d'arrivée du dernier trajet.

    virtual void Afficher () const;
    // Mode d'emploi :
    // Format d'affichage :
    // « {trajet1.Afficher()} - {trajet2.Afficher()} - ...»

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ( CollectionTrajets composants );
    // Mode d'emploi :
    // Constructeur de la classe <TrajetCompose>.
    // Construit un trajet à partir d'une copie profonde d'une collection
    // de trajets.

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    // Destructeur de la classe <TrajetCompose>
    //
    // Contrat :
    // Aucun
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    CollectionTrajets _trajets;
};

//--------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H