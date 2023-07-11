//
//  GestionGrille.cpp
//  D5_BatailleNavale
//
//  Created by Marie-Flavie Auclair-Fortier on 2019-10-10.
//  Copyright © 2019 Marie-Flavie Auclair-Fortier. All rights reserved.
//

// bibliotheques personnelles
#include "gestionGrille.h"
#include <string>

// bibliotheques du systeme
#include <iomanip>  // Manipulateurs d'E/S

using namespace std;

// description :
// param[E] :
// retour :
// pre :
// post :

void afficherGrille(const Grille& e_grille)
{


        cout << "    " << "A B C D E F G H I J " <<endl << "------------------------"<< endl;

    for (int i = 1; i<= 10; i ++) {
            cout << i ;
            if (i <= 9) {
                cout << " |" ;
            }
            else {
                cout << "|" ;
            }
            for(int j = 1; j <= 10; j ++) {

                    switch(e_grille[i-1][j - 1]){
                       case((char) ContenuCase::EAU):
                        cout<<"  ";
                        break;
                       case((char) ContenuCase::MANQUE):
                        cout<<"O ";
                        break;
                       case((char) ContenuCase::TOUCHE):
                        cout<<"* ";
                        break;}
            }
            cout<<endl;

    }
    // fonction bidon : code à remplacer

   cout<<" Entrer dans afficherGrille"<<endl;


   return;
}

// description :
// retour :
// pre :
// post :


// description : Initialise une grille
// param[S] : grille
// retour : aucun
// pre : aucun
// post : La grille contient la valeur EAU a chaque case

void initialiserGrille(Grille& s_grille)
{

 for (int i = 0; i < 10; i ++) {
    for(int j = 0; j  < 10; j ++) {
        s_grille[i][j] = (char) ContenuCase::EAU;
    }
 }
    return;
}

// description :
// param[E] :
// param[E] :
// retour :
// pre :
// post :

bool validerPosition(Position e_pos)
{
    // fonction bidon : code à remplacer

    cout<<" Entrer dans validerPosition"<<endl;

    return true;

}
