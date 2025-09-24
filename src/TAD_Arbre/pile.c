#ifndef _PILE_C_
#define _PILE_C_ 

#include "pile.h"

pile *pilevide() {
    return NULL;
}

pile *empiler(pile *p, int elem) {
    pile *nouv = NULL;
    nouv = (pile *) malloc(sizeof(pile));
    if (nouv == NULL) {
        fprintf(stderr, "empiler : erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->valeur = elem;
    nouv->suivant = p;
    nouv->precedant = NULL;
    if (p != NULL) {
        p->precedant = nouv;
    }
    return nouv;
}

pile *depile(pile *p) {
    pile *suiv = NULL;
    if (p == NULL) {
        fprintf(stderr, "depile : pile vide\n");
        exit(EXIT_FAILURE);
    }
    suiv = p->suivant;
    free(p);
    p = NULL;
    return suiv;
}

int sommet(pile *p) {
    if (p == NULL) {
        fprintf(stderr, "sommet : pile vide\n");
        exit(EXIT_FAILURE);
    }
    return p->valeur;
}

void liberer_pile(pile *p) {
    pile *tmp = NULL;
    if (p != NULL) {
        tmp = p->suivant;
        free(p);
        p = tmp;
    }
    return;
}





it_pile *creer_it_pile() {
    it_pile *itp = NULL;
    itp = (it_pile *) malloc(sizeof(it_pile));
    if (itp == NULL) {
        fprintf(stderr, "creer_it_pile : erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    itp->debut = NULL;
    itp->courant = NULL;
    itp->fin = NULL;
    return itp;
}

void init_it_pile(it_pile *itp, pile *p) {
    pile *suiv = NULL;

    /* Verification des parametres */
    if (itp == NULL) {
        fprintf(stderr, "init_it_pile : erreur l'iterateur n'existe pas\n");
        exit(EXIT_FAILURE);
    }
    if (p == NULL) {
        fprintf(stderr, "init_it_pile : erreur pile vide\n");
        exit(EXIT_FAILURE);
    }

    /* Initialisation de l'iterateur */
    itp->debut = p;
    itp->courant = p;
    suiv = p;
    while (suiv->suivant != NULL) {
        suiv = suiv->suivant;
    }
    itp->fin = suiv;
}

void init_it_pile_debut(it_pile *itp) {
    if (itp == NULL) {
        fprintf(stderr, "init_it_pile_debut : erreur l'iterateur n'existe pas\n");
        exit(EXIT_FAILURE);
    }
    if ((itp->debut == NULL) || (itp->fin == NULL)) {
        fprintf(stderr, "init_it_pile_debut : l'iterateur n'est pas initalise\n");
        exit(EXIT_FAILURE);
    }
    itp->courant = itp->debut;
}

void init_it_pile_fin(it_pile *itp) {
    if (itp == NULL) {
        fprintf(stderr, "init_it_pile_fin : erreur l'iterateur n'existe pas\n");
        exit(EXIT_FAILURE);
    }
    if ((itp->debut == NULL) || (itp->fin == NULL)) {
        fprintf(stderr, "init_it_pile_fin : l'iterateur n'est pas initalise\n");
        exit(EXIT_FAILURE);
    }
    itp->courant = itp->fin;
}

void itp_suiv(it_pile *itp) {
    if (itp->courant != NULL) {
        itp->courant = itp->courant->suivant;
    }
    return;
}

void itp_prec(it_pile *itp) {
    if (itp->courant != NULL) {
        itp->courant = itp->courant->precedant;
    }
    return;
}

pile *itp_courant(it_pile *itp) {
    if (itp == NULL) {
        fprintf(stderr, "itp_courant : erreur l'iterateur n'existe pas\n");
        exit(EXIT_FAILURE);
    }
    return itp->courant;
}

int itp_courant_val(it_pile *itp) {
    if (itp == NULL) {
        fprintf(stderr, "itp_courant_val : erreur l'iterateur n'existe pas\n");
        exit(EXIT_FAILURE);
    }
    if (itp->courant == NULL) {
        fprintf(stderr, "itp_courant_val : erreur il n'y a pas d'element courant\n");
        exit(EXIT_FAILURE);
    }
    return sommet(itp->courant);
}

void liberer_itp(it_pile *itp) {
    if (itp != NULL) { 
        free(itp);
    }
    return;
}

int itp_est_termine(it_pile *itp) {
    if (itp == NULL) {
        fprintf(stderr, "itp_est_termine : erreur l'iterateur n'existe pas\n");
        exit(EXIT_FAILURE);
    }
    return (itp->courant == NULL);
}


#endif /* _PILE_C_ */



