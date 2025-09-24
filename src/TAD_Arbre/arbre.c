#ifndef _ARBRE_C_ 
#define _ARBRE_C_ 

#include "arbre.h"
#include "pile.h"


#define DEBUT "├── "
#define MILIEU "│   "
#define ESPACE "    "
#define FIN "└── "



arbre *arbre_vide() {
    return NULL;
}


int getValeur(arbre *a) {
    if (a == NULL) {
        fprintf(stderr, "Erreur getValeur (arbre.c) : arbre vide\n");
        return -1;
    }
    return a->valeur;
}


arbre *getFils(arbre *a) {
    return a->gauche;
}


arbre *getFrere(arbre *a) {
    return a->droite;
}


arbre *creer_noeud(int valeur, nlex num_lexico, int num_decl) {
    arbre *a = NULL;
    a = (arbre *) malloc(sizeof(arbre));
    if (a == NULL) {
        fprintf(stderr, "creer_noeud : erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    a->valeur = valeur;
    a->num_lexico = num_lexico;
    a->num_decl = num_decl;
    a->gauche = NULL;
    a->droite = NULL;
    return a;
}


arbre *concat_frere(arbre *a1, arbre *a2) {
    if (a1 == NULL) {
        fprintf(stderr, "concat_frere : arbre vide\n");
        exit(EXIT_FAILURE);
    }

    while(a1->droite != NULL){
      a1 = a1->droite;
    }
    a1->droite = a2;
    return a1;
}


arbre *concat_fils(arbre *a1, arbre *a2) {
    if (a1 == NULL) {
        fprintf(stderr, "concat_fils : arbre vide\n");
        exit(EXIT_FAILURE);
    }
    a1->gauche = a2;
    return a1;
}





void afficher_arbre_aux(FILE *flux, arbre *a, pile *p) {
    it_pile *itp = NULL;

    /* Initialisation de l'iterateur si besoin */
    if ((p != NULL) && (a != NULL)) {
        itp = creer_it_pile();
        init_it_pile(itp, p);
    }

    /* Parcours de l'arbre et affichage */
    if (a != NULL) {
        /* Affichage de la pile */
        if (itp != NULL) {
            init_it_pile_fin(itp);
            while (itp_courant(itp) != NULL) {
                if (itp_courant_val(itp) == 1) {
                    fprintf(flux, "%s", MILIEU);
                } else {
                    fprintf(flux, "%s", ESPACE);
                }
                itp_prec(itp);
            }
            /* Liberation de l'iterateur */
            liberer_itp(itp);
            itp = NULL;
        }

        /* Affichage de la valeur du noeud */
        if (a->droite == NULL) { /* Si le noeud a n'a pas de frere */
            fprintf(flux, "%s", FIN);
        } else {
            fprintf(flux, "%s", DEBUT);
        }
        switch (a->valeur) {
            case A_OPAFF:
                fprintf(flux, "A_OPAFF");
                break;
            case A_IDF:
                fprintf(flux, "A_IDF");
                break;
            case A_CSTE_E:
                fprintf(flux, "A_CSTE_E");
                break;
            case A_CSTE_F:
                fprintf(flux, "A_CSTE_F");
                break;
            case A_LISTE_I:
                fprintf(flux, "A_LISTE_I");
                break;
            case A_LISTE_IND:
                fprintf(flux, "A_LISTE_IND");
                break;
            case A_LISTE_CH:
                fprintf(flux, "A_LISTE_CH");
                break;
            case A_LISTE_P:
                fprintf(flux, "A_LISTE_P");
                break;
            case A_PLUS:
                fprintf(flux, "A_PLUS");
                break;
            case A_MOINS:
                fprintf(flux, "A_MOINS");
                break;
            case A_MULT:
                fprintf(flux, "A_MULT");
                break;
            case A_DIV:
                fprintf(flux, "A_DIV");
                break;
            case A_MODULO:
                fprintf(flux, "A_MODULO");
                break;
            case A_WHILE:
                fprintf(flux, "A_WHILE");
                break;
            case A_ITE:
                fprintf(flux, "A_ITE");
                break;
            case A_APPEL_FCT:
                fprintf(flux, "A_APPEL_FCT");
                break;
            case A_APPEL_PROC:
                fprintf(flux, "A_APPEL_PROC");
                break;
            case A_OR:
                fprintf(flux, "A_OR");
                break;
            case A_AND:
                fprintf(flux, "A_AND");
                break;
            case A_NOT:
                fprintf(flux, "A_NOT");
                break;
            case A_CSTE_B:
                fprintf(flux, "A_CSTE_B");
                break;
            case A_INF:
                fprintf(flux, "A_INF");
                break;
            case A_SUP:
                fprintf(flux, "A_SUP");
                break;
            case A_INF_EGAL:
                fprintf(flux, "A_INF_EGAL");
                break;
            case A_SUP_EGAL:
                fprintf(flux, "A_SUP_EGAL");
                break;
            case A_DIFF:
                fprintf(flux, "A_DIFF");
                break;
            case A_EGAL:
                fprintf(flux, "A_EGAL");
                break;
	        case A_PROG :
	            fprintf(flux, "A_PROG");
                break;
	        case A_LISTE_INST:
                fprintf(flux, "A_LISTE_INST");
                break;
            case A_LIRE:
                fprintf(flux, "A_LIRE");
                break;
            case A_ECRIRE:
                fprintf(flux, "A_ECRIRE");
                break;
            case A_LISTE_ARG:
                fprintf(flux, "A_LISTE_ARG");
                break;
	case LA_PHRASE :
	  fprintf(flux, "PHRASE");
	  break;
            
            default:
                fprintf(flux, "%d", a->valeur);
                break;
        }
        fprintf(flux, " | %d (%f) | %d\n", a->num_lexico.entier, a->num_lexico.flottant, a->num_decl);

        /* Affichage du fils */
        if (a->gauche != NULL) {
            if (a->droite != NULL) {
                p = empiler(p, 1);
            } else {
                p = empiler(p, 0);
            }
            afficher_arbre_aux(flux, a->gauche, p);
            p = depile(p);
        }

        /* Affichage du frere */
        afficher_arbre_aux(flux, a->droite, p);
    }

    /* Liberation de l'iterateur si besoin (facultatif) */
    if (itp != NULL) {
        liberer_itp(itp);
        itp = NULL;
    }
    return;
}


void afficher_arbre(FILE *flux, arbre *a) {
    /*char *debut  = "├── ";
    char *milieu = "│   ";
    char *fin    = "└── ";*/
    pile *p = NULL;

    if (a != NULL) {
        afficher_arbre_aux(flux, a, p);
    }
    return;
}


void liberer_arbre(arbre *a) {
    if (a != NULL) {
        liberer_arbre(a->gauche);
        liberer_arbre(a->droite);
        free(a);
        a = NULL;
    }
    return;
}


int nb_noeud(arbre *a) {
    if (a == NULL) {
        return 0;
    }
    return (1 + nb_noeud(a->gauche) + nb_noeud(a->droite));
}


int arbre_vers_table(arbre *a, arbre_sauv_noeud *arbre_sauv, int *indice) {
    int ind;
    if (a != NULL) {
        ind = *indice;
        /*fprintf(stderr, " - %d - \n", ind);
        afficher_arbre(stderr, a);*/
        arbre_sauv[ind].valeur = a->valeur;
        arbre_sauv[ind].num_lexico = a->num_lexico;
        arbre_sauv[ind].num_decl = a->num_decl;
        (*indice)++;
        /*fprintf(stderr, "[%d] indice1 <- %d\n", ind, *indice);*/
        arbre_sauv[ind].suiv_gauche = arbre_vers_table(a->gauche, arbre_sauv, indice);
        (*indice)++;
        /*fprintf(stderr, "[%d] indice2 <- %d\n", ind, *indice);*/
        arbre_sauv[ind].suiv_droite = arbre_vers_table(a->droite, arbre_sauv, indice);
        return ind;
    }
    (*indice)--;
    return -1;
}


arbre *table_vers_arbre(arbre_sauv_noeud *arbre_sauv, int indice) {
    arbre *a = NULL;
    if (indice == -1) {
        return NULL;
    }
    a = (arbre *) malloc(sizeof(arbre));
    if (a == NULL) {
        fprintf(stderr, "Erreur table_vers_arbre : erreur d'allocation mémoire pour le noeud %d\n", indice);
        exit(EXIT_FAILURE);
    }
    a->valeur = arbre_sauv[indice].valeur;
    a->num_lexico = arbre_sauv[indice].num_lexico;
    a->num_decl = arbre_sauv[indice].num_decl;
    a->gauche = table_vers_arbre(arbre_sauv, arbre_sauv[indice].suiv_gauche);
    a->droite = table_vers_arbre(arbre_sauv, arbre_sauv[indice].suiv_droite);
    return a;
}


int sauv_arbre(arbre *a, int indReg, FILE *fic) {
    size_t taille_ecrit;
    arbre_sauv_noeud *arbre_sauv = NULL;
    int indice = 0;
    int n; /* nombre de noeuds dans l'arbre */

    n = nb_noeud(a);

    arbre_sauv = (arbre_sauv_noeud *) malloc(n * sizeof(arbre_sauv_noeud));
    if (arbre_sauv == NULL) {
        fprintf(stderr, "Erreur sauv_arbre : erreur d'allocation mémoire de arbre_sauv\n");
        return -1;
    }

    /* arbre -> table */
    arbre_vers_table(a, arbre_sauv, &indice);

    /* Ecriture */
    taille_ecrit = fwrite(&indReg, sizeof(int), sizeof(int), fic);
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur sauv_arbre : Erreur lors de l'ecriture de indReg (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }
    taille_ecrit = fwrite(&n, sizeof(int), sizeof(int), fic);
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur sauv_arbre : Erreur lors de l'ecriture de n (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }
    taille_ecrit = fwrite(arbre_sauv, sizeof(arbre_sauv_noeud), sizeof(arbre_sauv_noeud) * n, fic);
    if (taille_ecrit < (sizeof(arbre_sauv_noeud) * n)) {
        fprintf(stderr, "Erreur sauv_arbre : Erreur lors de l'ecriture de arbre_sauv (%ld/%ld)\n", taille_ecrit, (sizeof(arbre_sauv_noeud) * n));
        return -1;
    }

    /*int i;
    fprintf(stderr, "n = %d\n", n);
    fprintf(stderr, " i |\t val \tFils \tFrere\n");
    for (i=0; i<n; i++) {
        fprintf(stderr, "%2d |\t %2d \t %2d \t %2d\n", i, arbre_sauv[i].valeur, arbre_sauv[i].suiv_gauche, arbre_sauv[i].suiv_droite);
    }*/

    free(arbre_sauv);
    return 0;
}


arbre *charge_arbre(int *indReg, FILE *fic) {
    size_t taille_ecrit;
    arbre_sauv_noeud *arbre_sauv = NULL;
    arbre *a = NULL;
    int n; /* nombre de noeuds dans l'arbre */
    int indRegTmp;

    /* Lecture */
    taille_ecrit = fread(&indRegTmp, sizeof(int), sizeof(int), fic);
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur charge_arbre : Erreur lors de la lecture de indReg (%ld/%ld)\n", taille_ecrit, sizeof(int));
        exit(EXIT_FAILURE);
    }
    *indReg = indRegTmp;
    /*fprintf(stderr, "irt <- %d\n", *indReg);*/
    taille_ecrit = fread(&n, sizeof(int), sizeof(int), fic);
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur charge_arbre : Erreur lors de la lecture de n (%ld/%ld)\n", taille_ecrit, sizeof(int));
        exit(EXIT_FAILURE);
    }
    /*fprintf(stderr, "n <- %d\n", n);*/
    arbre_sauv = (arbre_sauv_noeud *) malloc(n * sizeof(arbre_sauv_noeud));
    if (arbre_sauv == NULL) {
        fprintf(stderr, "Erreur charge_arbre : erreur d'allocation mémoire de arbre_sauv\n");
        exit(EXIT_FAILURE);
    }
    taille_ecrit = fread(arbre_sauv, sizeof(arbre_sauv_noeud), sizeof(arbre_sauv_noeud) * n, fic);
    if (taille_ecrit < (sizeof(arbre_sauv_noeud) * n)) {
        fprintf(stderr, "Erreur charge_arbre : Erreur lors de la lecture de arbre_sauv (%ld/%ld)\n", taille_ecrit, (sizeof(arbre_sauv_noeud) * n));
        exit(EXIT_FAILURE);
    }

    /* table -> arbre */
    if (n > 0) {
        a = table_vers_arbre(arbre_sauv, 0);
    }

    
    /*int i;
    fprintf(stderr, "n = %d\n", n);
    fprintf(stderr, " i |\t val \tFils \tFrere\n");
    for (i=0; i<n; i++) {
        fprintf(stderr, "%2d |\t %2d \t %2d \t %2d\n", i, arbre_sauv[i].valeur, arbre_sauv[i].suiv_gauche, arbre_sauv[i].suiv_droite);
    }*/

    free(arbre_sauv);
    return a;
}



#endif /* _ARBRE_C_ */ 



