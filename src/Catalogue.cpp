/*************************************************************************
                            Catalogue  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> 
//                                         (fichier Catalogue.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "../includes/Catalogue.h"
#include "../includes/TrajetSimple.h"
#include "../includes/TrajetCompose.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::AjouterTrajet ( const Trajet * t )
// Algorithme : aucun
{
    _trajets.AjouterTrajet(t);
} //----- Fin de AjouterTrajet

void Catalogue::Afficher () const
// Algorithme : boucle sur tous les trajets et invoque pour chacun
// sa méthode d'affichage.
{
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        cout << i << " - ";
        _trajets.TrajetNumero(i)->Afficher();
        cout << endl;
    }
} //----- Fin de Afficher

void Catalogue::Sauvegarde ( ostream & out ) const
// Algorithme :
{
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        _trajets.TrajetNumero(i)->Sauvegarde(out);
        out << endl;
    }
} //----- Fin de AfficherFiltre

void Catalogue::Sauvegarde ( ostream & out, typeTrajet type ) const
// Algorithme :
{
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        if (_trajets.TrajetNumero(i)->EstDeType(type))
        {
            _trajets.TrajetNumero(i)->Sauvegarde(out);
            out << endl;
        }
    }
} //----- Fin de AfficherFiltre

void Catalogue::Sauvegarde (
    ostream & out, 
    const char * villeDepart, 
    const char * villeArrivee ) const
// Algorithme :
{
    bool villeDepartSansFiltre = ( strlen(villeDepart) == 0 ) ;
    bool villeArriveeSansFiltre = ( strlen(villeArrivee) == 0 ) ;
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        bool memeVilleDepart = strcmp(
            _trajets.TrajetNumero(i)->VilleDepart(), 
            villeDepart) == 0 || villeDepartSansFiltre;

        bool memeVilleArrivee = strcmp(
            _trajets.TrajetNumero(i)->VilleArrivee(), 
            villeArrivee) == 0 || villeArriveeSansFiltre;

        if (memeVilleDepart && memeVilleArrivee)
        {
            _trajets.TrajetNumero(i)->Sauvegarde(out);
            out << endl;
        }
    }
} //----- Fin de AfficherFiltre

void Catalogue::Sauvegarde ( 
    ostream & out,
    unsigned int debut, 
    unsigned int fin ) const
// Algorithme :
{
    for (unsigned int i (debut); i <= fin; i++)
    {
        _trajets.TrajetNumero(i)->Sauvegarde(out);
        out << endl;
    }
} //----- Fin de AfficherFiltre

CollectionTrajets * Catalogue::Rechercher ( 
    const char * villeDepart,
    const char * villeArrivee) const
// Algorithme : Boucle sur tous les trajet du catalogue et ajoute le 
// trajet dans la collection si la ville de départ et la ville 
// d'arrivée sont les mêmes
{
    CollectionTrajets * trajetsTrouves (new CollectionTrajets());
    
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        const Trajet * trajetCourant = _trajets.TrajetNumero(i);
        if (strcmp(trajetCourant->VilleDepart(), villeDepart) == 0
        && strcmp(trajetCourant->VilleArrivee(), villeArrivee) == 0)
        {
            trajetsTrouves->AjouterTrajet(trajetCourant);
        }
    }

    return trajetsTrouves;
} //----- Fin de Rechercher

void Catalogue::RechercherComplet (
    const char * villeDepart, 
    const char * villeArrivee,
    CollectionTrajets **& trajetsTrouves,
    unsigned int & nbTrajetsTrouves ) const
// Algorithme : 
// Le principe de base est de parcourir toutes les combinaisons possibles
// de trajets.
// Pour ce faire, pour chaque trajet on divise la recherche en deux :
// on prend le trajet et on ne prends pas le trajet, et on réitère pour
// les projets suivants.
// De cette manière, on aura simuler le parcours d'un arbre binaire,
// qui, à chaque niveau de l'arbre décide de prendre ou ne pas prendre
// un trajet.
{
    const unsigned int TAILLE_MAX_DEF (10);
    unsigned int tailleMaxTrajets (TAILLE_MAX_DEF);
    const Trajet** uneCombinaison (
        new const Trajet*[_trajets.NombreDeTrajets()]
    );
    bool * pris ( new bool[_trajets.NombreDeTrajets()] );
    for (unsigned int i = 0; i < _trajets.NombreDeTrajets(); i++)
    {
        pris[i] = false;
    }

    trajetsTrouves = new CollectionTrajets*[tailleMaxTrajets];
    nbTrajetsTrouves = 0;

    for (unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
    {
        pris[i-1] = true;
        combinaison(
            villeDepart, 
            villeArrivee,
            pris,
            i, // index du prochain à prendre
            uneCombinaison, 
            0, // nombre de trajets dans la combinaison
            trajetsTrouves, 
            tailleMaxTrajets, 
            nbTrajetsTrouves
        );
        pris[i-1] = false;
    }

    

    delete[] uneCombinaison;
}

void Catalogue::Charger ( istream & in )
// Algorithme :
{
    string buffer;

    while (getline(in, buffer, '|')) 
    {
        Trajet * t (nullptr);
        if (buffer == "S") 
        {
            t = chargerTrajetSimple(in);
        }
        if (buffer == "C")
        {
            t = chargerTrajetCompose(in);
        }


        if (t != nullptr) {
            AjouterTrajet(t);
        }
    }
} //----- Fin de Charger

void Catalogue::Charger ( istream & in, typeTrajet type )
// Algorithme :
{
    string buffer;

    while (getline(in, buffer, '|')) 
    {
        Trajet * t (nullptr);
        if (buffer == "S") 
        {
            t = chargerTrajetSimple(in);
        }
        if (buffer == "C")
        {
            t = chargerTrajetCompose(in);
        }


        if (t != nullptr) 
        {
            if (t->EstDeType(type))
            {
                AjouterTrajet(t);
            }
            else 
            {
                delete t;
            }
        }
    }
} //----- Fin de Charger

void Catalogue::Charger (
        istream & in,
        const char * villeDepart, 
        const char * villeArrivee )
// Algorithme :
{
    string buffer;

    bool villeDepartSansFiltre = ( strlen(villeDepart) == 0 ) ;
    bool villeArriveeSansFiltre = ( strlen(villeArrivee) == 0 ) ;
        

    while (getline(in, buffer, '|')) 
    {
        Trajet * t (nullptr);
        if (buffer == "S") 
        {
            t = chargerTrajetSimple(in);
        }
        if (buffer == "C")
        {
            t = chargerTrajetCompose(in);
        }


        if (t != nullptr) 
        {
            bool memeVilleDepart = strcmp(
                t->VilleDepart(), 
                villeDepart) == 0 || villeDepartSansFiltre;

            bool memeVilleArrivee = strcmp(
                t->VilleArrivee(), 
                villeArrivee) == 0 || villeArriveeSansFiltre;

            if (memeVilleDepart && memeVilleArrivee)
            {
                AjouterTrajet(t);
            }
            else 
            {
                delete t;
            }
        }
    }
} //----- Fin de Charger

void Catalogue::Charger ( 
    istream & in,
    unsigned int debut, 
    unsigned int fin )
// Algorithme :
{
    string buffer;
    unsigned int indexCourant = 1;

    while (getline(in, buffer, '|') && indexCourant <= fin ) 
    {
        Trajet * t (nullptr);
        if (buffer == "S") 
        {
            t = chargerTrajetSimple(in);
        }
        if (buffer == "C")
        {
            t = chargerTrajetCompose(in);
        }


        if (t != nullptr) 
        {
            if (indexCourant >= debut)
            {
                AjouterTrajet(t);
            }
            else 
            {
                delete t;
            }
            ++indexCourant;
        }
    }
} //----- Fin de Charger

unsigned int Catalogue::NombreDeTrajets ( ) const
// Algorithme :
{
    return _trajets.NombreDeTrajets();
} //----- Fin de NombreDeTrajets

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue () : _trajets()
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue

Catalogue::~Catalogue ( )
// Algorithme : boucle sur les trajets de la collection pour les 
// détruire.
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif

    for(unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        delete _trajets.TrajetNumero(i);
    }
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::combinaison(
    const char * villeDepart,
    const char * villeArrivee,
    bool * pris,
    unsigned int indexAPrendre,
    const Trajet** uneCombinaison,
    unsigned int tailleCombinaison,
    CollectionTrajets **& trajetsTrouves,
    unsigned int tailleMaxTrajets,
    unsigned int & nbTrajetsTrouves ) const
// Algorihtme :
// Si on décide de ne pas prendre le trajet courant, on passe
// au trajet suivant (qu'on doit ou ne doit pas prendre).
// Si on décide de prendre le trajet courant, il y a deux cas :
//  - Cas général : vérifier que la ville de départ du trajet courant
//    est la même que la ville d'arrivée du dernier trajet de 
//    la combinaison, sinon on arrête la récursivité.
//  - Cas particulier : il n'y a aucun trajet dans la combinaison, 
//    on vérifie que la ville de départ du trajet courant est la 
//    même que celle demandée  en paramètre, sinon on arrête la 
//    récursivité.
// Dans tous les cas, si la ville d'arrivée du trajet courant 
// (celui ajouté) est la même que la ville d'arrivée donnée en 
// paramètre, on ajoute la combinaison de trajet dans notre 
// tableau de collection de trajets `trajetsTrouves` : c'est
// un trajet qui répond à la demande.
// S'il n'y a plus de trajets à ajouter, la récursivité s'arrête.
{
    // vérification de la cohésion entre trajet précédent et 
    // trajet courant
    if (tailleCombinaison == 0)
    {
        if (strcmp(_trajets.TrajetNumero(indexAPrendre)->VilleDepart(), 
        villeDepart) != 0)
            return;
    }
    else
    {
        if (strcmp( _trajets.TrajetNumero(indexAPrendre)->VilleDepart(),
        uneCombinaison[tailleCombinaison-1]->VilleArrivee()) != 0)
            return;
    }

    // ajout du trajet dans la combinaison
    uneCombinaison[tailleCombinaison] = _trajets.TrajetNumero(indexAPrendre);
    tailleCombinaison++;

    // si la combinaison de trajets répond à la demande,
    // on l'ajoute dans notre tableau.
    const Trajet * premier ( uneCombinaison[0] );
    const Trajet * dernier ( uneCombinaison[tailleCombinaison-1] );
    if (strcmp(villeDepart, premier->VilleDepart()) == 0
    && strcmp(villeArrivee,dernier->VilleArrivee()) == 0)
    {
        if (nbTrajetsTrouves >= tailleMaxTrajets)
        {
            tailleMaxTrajets += tailleMaxTrajets;
            CollectionTrajets** nouvTableau (
                new CollectionTrajets*[tailleMaxTrajets]
            );
            
            for (unsigned int i (0); i < nbTrajetsTrouves; i++) 
            {
                nouvTableau[i] = trajetsTrouves[i];
            }

            delete[] trajetsTrouves;
            trajetsTrouves = nouvTableau;
        }

        trajetsTrouves[nbTrajetsTrouves] = new CollectionTrajets;
        for (unsigned int i = 0; i < tailleCombinaison; i++)
        {
            trajetsTrouves[nbTrajetsTrouves]
                ->AjouterTrajet(uneCombinaison[i]);
        }
        nbTrajetsTrouves++;
    }
    
    for (unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
    {
        if (!pris[i-1])
        {
            pris[i-1] = true;
            combinaison(
                villeDepart, 
                villeArrivee,
                pris,
                i, // index du prochain à prendre
                uneCombinaison, 
                tailleCombinaison,
                trajetsTrouves, 
                tailleMaxTrajets, 
                nbTrajetsTrouves
            );
            pris[i-1] = false;
        }
    }
}

Trajet * Catalogue::chargerTrajetSimple ( istream & in ) const
// Algorithme :
{
    istringstream iss;
    string ligne;
    string villeDepart, villeArrivee;
    unsigned int moyenDeTransport;

    // Récupération de la ligne
    getline(in, ligne);

    iss.str(ligne);

    // Récupération de la ville de départ
    if (!getline(iss, villeDepart, '|')) 
    {
        cerr << "Erreur lors de la lecture de la ville de départ" << endl;
        return nullptr;
    }

    // Récupération de la ville d'arrivée
    if (!getline(iss, villeArrivee, '|'))
    {
        cerr << "Erreur lors de la lecture de la ville d'arrivée" << endl;
        return nullptr;
    }

    // Récupération du moyen de transport
    if (!(iss >> moyenDeTransport) 
    || moyenDeTransport < 0 
    || moyenDeTransport >= NB_MOYENS)
    {
        cerr << "Erreur lors de la lecture du moyen de transport" << endl;
        return nullptr;
    }

    return new TrajetSimple(
        villeDepart.c_str(), 
        villeArrivee.c_str(), 
        INT_TO_MOYEN[moyenDeTransport]);

} //----- Fin de chargerTrajetSimple

Trajet * Catalogue::chargerTrajetCompose ( istream & in ) const
// Algorithme :
{

    istringstream iss;
    string ligne;
    string villeDepart, villeArrivee;
    unsigned int nbTrajetsComposants;

    // Récupération de la ligne
    getline(in, ligne);

    iss.str(ligne);

    // Récupération de la ville de départ
    if (!getline(iss, villeDepart, '|')) 
    {
        cerr << "Erreur lors de la lecture de la ville de départ" << endl;
        return nullptr;
    }

    // Récupération de la ville d'arrivée
    if (!getline(iss, villeArrivee, '|'))
    {
        cerr << "Erreur lors de la lecture de la ville d'arrivée" << endl;
        return nullptr;
    }

    // Récupération du moyen de transport
    if (!(iss >> nbTrajetsComposants))
    {
#ifdef MAP
        cerr << "Erreur lors de la lecture du nombre de trajets" << endl;
#endif
        return nullptr;
    }

    CollectionTrajets ct;
    for (unsigned int i = 0; i < nbTrajetsComposants; i++) 
    {
        string buffer;
        if (getline(in, buffer, '|')) 
        {
            Trajet * t (nullptr);
            if (buffer == "S") 
            {
                t = chargerTrajetSimple(in);
            }
            if (buffer == "C")
            {
                t = chargerTrajetCompose(in);
            }

            if (t != nullptr) 
            {
                ct.AjouterTrajet(t);
            }
        }
    }

    return new TrajetCompose(ct);

} //----- Fin de TrajetCompose