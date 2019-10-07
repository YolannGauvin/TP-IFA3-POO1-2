/*************************************************************************
                            Catalogue  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier <Catalogue.h>) ------

#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "CollectionTrajets.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// La classe Catalogue permet de gérer des trajets et de 
// rechercher des trajets permettant de partir d'une ville 
// de départ jusqu'à une ville d'arrivée
//------------------------------------------------------------------------
class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AjouterTrajet (Trajet * unTrajet );
    // Mode d'emploi :
    // Permet d'ajouter le trajet unTrajet dans le catalogue.
    //
    // Contrat de cohérence :
    // Le trajet doit être un trajet valide (pour un trajet composé, 
    // la ville d'arrivée d'un trajet doit être la ville de départ
    // du suivant.)

    void Afficher () const;
    // Mode d'emploi :
    // Affiche tous les trajets du catalogue. 
    // Format d'affichage :
    // {num} - {trajet.Affichage()}

    CollectionTrajets * Rechercher ( 
        const char * villeDepart, 
        const char * villeArrivee) const;
    // Mode d'emploi :
    // Retourne tous les trajet dont la ville de départ 
    // et la ville d’arrivée sont celles données en paramètre.
    // 
    // Le tableau trajetsTrouves sera alloué dynamiquement 
    // dans la méthode et devra donc être libérés plus tard dans 
    // le programme en dehors de celle-ci.


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe <Catalogue> avec
    // aucun trajet.

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur de la classe <Catalogue>
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    CollectionTrajets _trajets;
//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H