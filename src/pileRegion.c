#ifndef _PILEREGION_C_
#define _PILEREGION_C_

#include "pileRegion.h"

int nis = -1;
int numReg = -1;
pile *pileRegion = NULL;

int getNumReg() {
    /*return numReg;*/
    return sommetPileRegion();
}

int getNis() {
    return nis;
}

void initPileRegion() {
    pileRegion = pilevide();
    return;
}

void nvRegion() {
    nis++;
    numReg++;
    pileRegion = empiler(pileRegion, numReg);
}

void sortieRegion() {
    nis--;
    pileRegion = depile(pileRegion);
}

int sommetPileRegion() {
    return sommet(pileRegion);
}

int assoc_nom(int numLex, int nature) {
    it_pile itp;
    int nreg; 
    int tmp_num; /* pour le numéro de déclaration */
    int tmp_reg; /* pour le numéro de région */
    int tmp_nat; /* pour la nature */
    int tmp_suiv; /* pour le champ suivant */
    int trouve = 0; /* On ne l'a pas encore trouvé */
    int resultat = -1; /* Numéro de déclaration renvoyé si trouvé */

    /* Initialisation d'itérateur pour parcourir la pile des régions */
    init_it_pile(&itp, pileRegion);
    init_it_pile_debut(&itp);

    while (!trouve && !itp_est_termine(&itp)) { /* tant qu'on a pas parcouru toute la pile et qu'on n'a pas trouvé la numéro de déclaration */
        nreg = itp_courant_val(&itp);
        tmp_num = numLex;
        do {
            ligneTableDecl(tmp_num, &tmp_nat, &tmp_suiv, &tmp_reg, NULL, NULL);
            if ((tmp_reg == nreg) && (tmp_nat == nature)) {
                trouve = 1; /* On l'a trouvé */
            } else {
                if (((nature == VAR) && (tmp_nat == PARAM)) || ((nature == PARAM) && (tmp_nat == VAR))) {
                    trouve = 1;
                } else {
                    tmp_num = tmp_suiv;
                }
            }
        } while (!trouve && (tmp_suiv != -1));
        itp_suiv(&itp);
    }

    if (trouve) { /* Si on l'a trouvé */
        resultat = tmp_num;
    } /* Sinon il y a une erreur qui sera géré dans le yacc */
    
    return resultat; /* numéro de déclaration */
}

void libererPileRegion() {
    liberer_pile(pileRegion);
    return;
}


#endif /* _PILEREGION_C_ */



