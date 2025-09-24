#ifndef _TABREP_H_
#define _TABREP_H_

#include <stdio.h>
#include <string.h>

#define N_TAB_REP_MAX 50000

void init_tabRep();

/* Insert une structure */
int inserer_struct_tabRep(int *tRepTmp);

/* Insert une procedure */
int inserer_proc_tabRep(int *tRepTmp);

/* Insert une fonction */
int inserer_fonct_tabRep(int *tRepTmp, int rtype);

/* Insert un tableau */
int inserer_tab_tabRep(int *tRepTmp);

/* Affiche la table dans le flux "flux" */
void f_afficher_table_rep(FILE * flux);

/* Affiche la table dans la flux stdout */
void afficher_table_rep();

/* Ecrit la table dans fic */
int sauv_tabRep(FILE * fic);

/* Lit la table dans fic */
int charge_tabRep(FILE * fic);

#endif /* _TABREP_H_ */



