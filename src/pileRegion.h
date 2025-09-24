#ifndef _PILEREGION_H_
#define _PILEREGION_H_

#include "TAD_Arbre/pile.h"
#include "tabledecl.h"

/* Rnvoie le numéro de la région courante */
int getNumReg();

/* Renvoie le nis de la région courante */
int getNis();

/* Initialise la pile de régions */
void initPileRegion();

/* Incrémente le numéro de région et le nis        */
/* et empile la région dans la région dans la pile */
void nvRegion();

/* Dépile la région courante */
/* et décrémente le nis      */
void sortieRegion();

/* Renvoie le numéro de région en sommet de pile */
int sommetPileRegion();

/* Renvoie le numéro de déclaration si trouvé */
/*         -1 sinon                           */
int assoc_nom(int numLex, int nature);

/* Libere la mémoire alouée à la pile */
void libererPileRegion();

#endif /* _PILEREGION_H_ */



