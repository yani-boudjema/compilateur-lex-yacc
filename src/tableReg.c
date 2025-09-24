#include "tableReg.h"



int insererTableReg(int laTaille, int leNis, arbre a){

  tabReg[LigneSuivante].taille = laTaille;
  tabReg[LigneSuivante].NIS = leNis;
  tabReg[LigneSuivante].tree = a;
  LigneSuivante++;

}


void affichageTableReg(FILE *flux){
  int i;
  fprintf(flux, "table de Region:\n");
  fprintf(flux,"index\tTaille\tNIS\tArbre\n");
  for (i=0;i<LigneSuivante;i++){
    fprintf(flux,"%d\t%d\n",tabReg[i].taille, tabReg[i].NIS);/*mettre la suite avec les arbres*/
  }
}




