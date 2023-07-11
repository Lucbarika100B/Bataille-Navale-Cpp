//
//  batailleNavale.cpp
//  D5_BatailleNavale
//
//  Created by Marie-Flavie Auclair-Fortier on 2019-10-11.
//  Copyright © 2019 Marie-Flavie Auclair-Fortier. All rights reserved.
//

#include "batailleNavale.h"
#include "bnRandom.h"

#include <cassert>  // Pour les assertions

using namespace std;

// constantes
const char TERMINER {'q'};          // Caractère entré pour terminer la partie

const int NB_BATEAUX {5};           // Nombre de bateaux
const int TAILLE_TORPILLEUR {2};    // Taille du torpilleur
const int TAILLE_C_TORPILLEUR {3};  // Taille du contre-torpilleur
const int TAILLE_SOUS_MARIN {3};    // Taille du sous-marin
const int TAILLE_CROISEUR {4};      // Taille du croiseur
const int TAILLE_PORTE_AVION {5};   // Taille du porte-avion
const int TAILLES_BATEAUX[] {TAILLE_TORPILLEUR, TAILLE_C_TORPILLEUR, TAILLE_SOUS_MARIN, TAILLE_CROISEUR, TAILLE_PORTE_AVION};

// énumération
enum class Orientation {HORIZONTAL, VERTICAL}; // orientation d'un bateau

// type synonyme
using EtatBateaux = bool[NB_BATEAUX];   // tableau d'indicateurs de l'état coulé ou non des bateaux

// description :
// param[ES] :
// retour :
// pre :
// post :

void placerBateaux(Grille& es_grille)
{

	// fonction bidon : code à remplacer
	cout<<" Entrer dans placerBateaux"<<endl;

    return;

}

// description :
// param[E] :
// retour :
// pre :
// post :

void jouer(const Grille& e_grilleBateaux)
{
	// fonction bidon : code à remplacer
	cout<<" Entrer dans jouer"<<endl;

    return;
}

// description :
// param[E] :
// param[ES] :
// param[ES] :
// retour :
// pre :
// post :

bool jouerUnTour(const Grille& e_grilleBateaux, Grille& es_grilleTirs,  EtatBateaux& es_etatBateau)
{
    bool tirer(const Grille&, Position, Grille&,  EtatBateaux&); // retourne true si la partie est gagnée avec ce tour

    char cColonne;
    int nLigne;

    // 3.1 Lire la colonne du tir
    cout<<"Colonne (en majuscules) et ligne du tir ('"<<TERMINER<<"' pour quitter) : ";
    cin>>cColonne;

    // 3.2 Vérifier si TERMINER
    if (cColonne == TERMINER || cin.fail())
    {
        // 3.1.2.1 Afficher un message et quitter le jeu
        cout<<"quitter"<<endl;
        return false;
    }

    cColonne = toupper(cColonne) - 'A';

    // 3.3 Lire la ligne du tir
    cin>>nLigne;
    nLigne -= 1;
    cout<<endl;

    // 3.4 Valider que la position est bien dans la grille (module ValiderEntrees)
    if (validerPosition({cColonne, nLigne}))
    {

        // 3.4.1 Vérifier le résultat du tir (module Tir)
        if (tirer(e_grilleBateaux, {cColonne, nLigne}, es_grilleTirs, es_etatBateau))
        {
            afficherGrille(es_grilleTirs); // optionnel
            // 3.4.1.1 Si le tir est celui qui fait gagner la partie, sortir du jeu
            return false;
        }

    }

    // 3.5 Sinon, afficher un message
    else cout<< "En dehors de la grille!"<<endl;

    return true;
};

// description :
// param[E] :
// param[E] :
// param[E] :
// param[ES] :
// param[ES] :
// retour :
// pre :
// post :

bool tirer(const Grille& e_grilleBateaux, Position e_pos, Grille& es_grilleTir, EtatBateaux& es_etatBateau)
{

    assert(e_pos.m_ligne<NB_LIGS);
    assert(e_pos.m_ligne>=0);
    assert(e_pos.m_colonne<NB_COLS);
    assert(e_pos.m_colonne>=0);

    bool validerCoule(const Grille&, Position, const Grille&);
    bool Partie(const EtatBateaux&);

    // 1 Si on a déjà tiré sur la position
    if (es_grilleTir[e_pos.m_colonne][e_pos.m_ligne] != (char) ContenuCase::EAU)
    {
        // 1.1 Afficher un message indiquant qu'on a déjà tiré sur cette position
        cout<<"Vous avez déjà tiré là!"<<endl;
        return false;
    }

    // 1 Si le tir n'est pas sur une position déjà tirée
    // 1.1 Si on a touché un bateau
    if (e_grilleBateaux[e_pos.m_colonne][e_pos.m_ligne] != (char) ContenuCase::EAU)
    {
        // 1.1.1 Afficher le message "Touche!"
        cout<<"Touche!"<<endl;

        // 1.1.2 Indiquer sur la carte de tir qu'on a touché un bateau
        es_grilleTir[e_pos.m_colonne][e_pos.m_ligne] = (char) ContenuCase::TOUCHE;

        // 1.1.3 Vérifier que le bateau touché a été coulé (module validerCoule)
        if (validerCoule(e_grilleBateaux, e_pos, es_grilleTir))
        {
            // 1.1.3.1 Afficher le message "Coule!"
            cout<<"Coule!"<<endl;
            es_etatBateau[e_grilleBateaux[e_pos.m_colonne][e_pos.m_ligne]] = true;

            // 1.1.3.2 Si on a coulé tous les bateaux (module validerFinPartie)
            if (validerFinPartie(es_etatBateau)){

                // 1.1.3.2.1 Afficher le message de victoire
                cout<<"VICTOIRE... BRAVO!"<<endl;

                // 1.1.3.2.2 C'est la fin de la partie, retourne vrai
                return true;
            }
        }
    }

    // 1.2 Sinon on a manqué le tir
    else
    {
        // 1.2.1 Afficher le message "A l'eau!"
        cout << "A l'eau!"<<endl;
        // 1.2.2 Indiquer sur la carte qu'on a tiré sur cette position
        es_grilleTir[e_pos.m_colonne][e_pos.m_ligne] = (char) ContenuCase::MANQUE;
    }

    // 3 Ce n'est pas la fin de la partie, retourne faux
    return false;
}

// description :
// param[ES] :
// retour :
// pre :
// post :

bool validerFinPartie(const EtatBateaux& es_etatBateau)
{

    // 1 Pour tous les bateaux


    int numbers[] = { 1, 2, 3, 4, 5 };
    for (int& n : numbers) {
        n *= 2;
    }



    for (int i=0; i<NB_BATEAUX; i++) {
      for (bool etat : es_etatBateau) {

        // 1.1 La partie n'est pas terminée si un bateau n'est pas coulé
        if (!io_etatBateau[i])
          if (!etat)
            return false;
    }

    // 2 Tous les bateaux sont coulés, retourne vrai
    return true;
}

// description :
// param[E] :
// param[E] :
// param[E] :
// param[E] :
// retour :
// pre :
// post :

bool validerCoule(const Grille& e_grilleBateaux, Position e_pos, const Grille& e_grilleTirs)
{

    assert(e_pos.m_ligne<NB_LIGS);
    assert(e_pos.m_ligne>=0);
    assert(e_pos.m_colonne<NB_COLS);
    assert(e_pos.m_colonne>=0);

    Orientation determinerOrientation(const Grille&, int, Position);
    bool validerCouleH(const Grille&, int, Position, const Grille&);
    bool validerCouleV(const Grille&, int, Position, const Grille&);

    // 1 Récupérer le numéro du bateau courant
    int nBateau {e_grilleBateaux[e_pos.m_colonne][e_pos.m_ligne]};

    // 2 Déterminer si le bateau est positionné horizontalement ou verticalement
    Orientation bOrientation {determinerOrientation(e_grilleBateaux, nBateau, e_pos)};

    // 3 Vérifier si toutes les cases du bateau sont touchées
    // 3.1 Si le bateau est horizontal
    if (bOrientation == Orientation::HORIZONTAL){
        return validerCouleH(e_grilleBateaux, nBateau, e_pos, e_grilleTirs);
    }

    // 3.2  Sinon, le bateau est vertical
    return validerCouleV(e_grilleBateaux, nBateau, e_pos, e_grilleTirs);
}

// description :
// param[E] :
// param[E] :
// param[E] :
// param[E] :
// param[E] :
// retour :
// pre :
// post :

bool validerCouleH(const Grille& e_grilleBateaux, int e_noBateau, Position e_pos, const Grille& e_grilleTirs)
{

    assert(e_pos.m_ligne<NB_LIGS);
    assert(e_pos.m_ligne>=0);
    assert(e_pos.m_colonne<NB_COLS);
    assert(e_pos.m_colonne>=0);
    assert(e_noBateau>=0);
    assert(e_noBateau<5);

    int nTaille {TAILLES_BATEAUX[e_noBateau]};
    int ncol {e_pos.m_colonne};

    // 3.1 Trouver la colonne de départ du bateau
    // 3.1.1 Revenir vers la gauche jusqu’à ce que ce ne soit plus le numéro du bateau
    do {
       ncol--;
    } while (e_grilleBateaux[ncol][e_pos.m_ligne] == e_noBateau);
    ncol++;

    assert(ncol>=0);

    // 3.2.1 Pour toute la taille du bateau
    for (int i=0; i<nTaille; i++, ncol++) {
        // 3.2.1.1 Le bateau n'est pas coulé si la case n'est pas touché
        if (e_grilleTirs[ncol][e_pos.m_ligne] != (char) ContenuCase::TOUCHE)
            return false;
    }

    return true;
};

// description :
// param[E] :
// param[E] :
// param[E] :
// param[E] :
// param[E] :
// retour :
// pre :
// post :

bool validerCouleV(const Grille& e_grilleBateaux, int e_noBateau, Position e_pos, const Grille& e_grilleTirs)
{
    assert(e_pos.m_ligne<NB_LIGS);
    assert(e_pos.m_ligne>=0);
    assert(e_pos.m_colonne<NB_COLS);
    assert(e_pos.m_colonne>=0);
    assert(e_noBateau>=0);
    assert(e_noBateau<5);

    int nlig {e_pos.m_ligne};
    int nTaille {TAILLES_BATEAUX[e_noBateau]};

    // Revenir vers le haut jusqu’à ce que ce ne soit plus le numéro du bateau
    while (e_grilleBateaux[e_pos.m_colonne][nlig] == e_noBateau)
        nlig--;
    nlig++;

    assert(nlig>=0);

    // 4.2 Vérifier si toutes les cases du bateau sont touchées
    // 4.2.1 Pour toute la taille du bateau
    for (int i = 0; i<nTaille; i++, nlig++)
    {
        // 4.2.1.1 Le bateau n'est pas coulé si la case n'est pas touchée
        if (e_grilleTirs[e_pos.m_colonne][nlig] != (char) ContenuCase::TOUCHE)
            return false;
    }

    return true;
}

// description :
// param[E] :
// param[E] :
// param[E] :
// param[E] :
// retour :
// pre :
// post :

Orientation determinerOrientation(const Grille& e_grilleBateaux, int e_noBateau, Position e_pos)
{
    assert(e_pos.m_ligne<NB_LIGS);
    assert(e_pos.m_ligne>=0);
    assert(e_pos.m_colonne<NB_COLS);
    assert(e_pos.m_colonne>=0);
    assert(e_noBateau>=0);
    assert(e_noBateau<5);

    const char PREMIERE_COLONNE = 0;
    const char DERNIERE_COLONNE = NB_COLS - 1;

    // 2.1 Si la colonne est la première
    if (e_pos.m_colonne == PREMIERE_COLONNE)
    {
        // 2.1.1 Le bateau est horizontal si la colonne 2 a le même numéro de bateau
        if (e_grilleBateaux[2][e_pos.m_ligne] == e_noBateau)
            return Orientation::HORIZONTAL;
    }
    // 2.2 Si la colonne est la dernière
    else if (e_pos.m_colonne == DERNIERE_COLONNE)
    {
        // 2.2.1 Le bateau est horizontal si l'avant-dernière colonne a le même numéro de bateau
        if (e_grilleBateaux[NB_COLS-2][e_pos.m_ligne] == e_noBateau)
            return Orientation::HORIZONTAL;
    }
    // 2.3 Sinon, si la colonne précédente le bateau est horizontal
    else if ((e_grilleBateaux[e_pos.m_colonne - 1][e_pos.m_ligne] == e_noBateau))
        return Orientation::HORIZONTAL;

    // ou suivante a le même numéro de bateau
    else if ((e_grilleBateaux[e_pos.m_colonne + 1][e_pos.m_ligne] == e_noBateau))
        return Orientation::HORIZONTAL;

    // 2.4 Sinon, le bateau est vertical
    return Orientation::VERTICAL;

};
