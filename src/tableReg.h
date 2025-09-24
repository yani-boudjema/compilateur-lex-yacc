#ifndef _TABLEREG_H_
#define _TABLEREG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./TAD_Arbre/arbre.h"
#define N_TAB_REG_MAX 500

/*la structure de ligne table region*/

typedef struct{
  
  int taille;
  int NIS;
  arbre tree;
  
} ligneTableReg;

/*les variables globales*/
int LigneSuivante = 0;
ligneTableReg tabReg[N_TAB_REG_MAX];//declaration du tableau

/*les fonctions */
int insererTableReg(int laTaille, int leNis, arbre a);
void affichageTableReg(FILE *flux);

#endif
