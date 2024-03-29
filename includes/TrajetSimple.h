/*************************************************************************
                            TrajetSimple  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier <TrajetSimple.h>) ------

#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------- Constantes
const int NB_MOYENS = 6;

//------------------------------------------------------------------ Types
typedef enum {
    TRAIN, AUTO, BATEAU, AVION, VELO, MARCHE
} moyenDeTransport;

const moyenDeTransport INT_TO_MOYEN[] = {
    TRAIN, AUTO, BATEAU, AVION, VELO, MARCHE
};

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
// Un trajet simple est un trajet caractérisée par une ville de départ,
// une ville d'arrivée ainsi qu'un moyen de transport.
//------------------------------------------------------------------------
class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual const char * VilleDepart () const;
    // Mode d'emploi :
    // Retourne la ville de départ.

    virtual const char * VilleArrivee () const;
    // Mode d'emploi :
    // Retourne la ville d'arrivée

    virtual void Afficher () const;
    // Mode d'emploi :
    // Format d'affichage :
    // « De {villeDepart} à {villeArrivee} en {moyenDeTransport} »

    virtual void Sauvegarde ( std::ostream & out ) const;
    // Mode d'emploi :
    // Affiche le trajet sur la sortie en paramètre pour une sauvegarde

    virtual bool EstDeType( typeTrajet type ) const;
    // Mode d'emploi :
    // Vérifie si le type de ce trajet est le même que 
    // le type passé en paramètre

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( 
        const char * laVilleDepart,
        const char * laVilleArrivee,
        moyenDeTransport leMoyenDeTransport );
    // Mode d'emploi :
    // Constructeur à partir de la ville de départ, la ville d'arrivée et
    // le moyen de transport donnés en paramètre.
    // Effectue une copie de la chaîne de caractères de laVilleDepart et
    // laVilleArrivee.

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    // Destructeur de la classe <TrajetSimple>
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void afficherMoyenDeTransport() const;
    // Affiche le moyen de transport d'une manière lisible.

//----------------------------------------------------- Attributs protégés
    char * _villeDepart;
    char * _villeArrivee;
    moyenDeTransport _moyenDeTransport;
};

//----------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H