#ifndef _TABREGION_H_
#define _TABREGION_H_

#include <string.h>
#include "TAD_Arbre/arbre.h"
#include "pileRegion.h"

#define N_TAB_REG_MAX 500 


/**********************************************************/
/*                       STRUCTURE                        */
/**********************************************************/

/* Ligne de la table des régions */
typedef struct {
    int taille;
    int nis;
    arbre * a;
} ligneTabReg;



/**********************************************************/
/*                       FONCTIONS                        */
/**********************************************************/


/* Initialise la table */
void init_tabRegion();

int inserer_region_taille(int i, int taille);

int inserer_region_nis(int i, int nis);

int inserer_region_arbre(int i, arbre *a);

int inserer_region(int i, int taille, int nis, arbre *a);

int getTabNis(int i);

void f_afficher_table_reg(FILE *flux);

void afficher_table_reg();

/* Ecrit la table des régions dans fic */
int sauv_tabRegion(FILE * fic);

/* Lit la table des régions dans fic */
int charge_tabRegion(FILE * fic);


#endif /* _TABREGION_H_ */



