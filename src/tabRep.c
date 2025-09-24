#ifndef _TABREP_C_
#define _TABREP_C_

#include "tabRep.h"


/**********************************************************/
/*                         TABLE                          */
/**********************************************************/

int tabRep[N_TAB_REP_MAX];
int nTabRep = 0;



/**********************************************************/
/*                Operations sur la table                 */
/**********************************************************/

void init_tabRep() {
    memset(tabRep, 0, N_TAB_REP_MAX * sizeof(int));
    nTabRep = 0;
}

int inserer_struct_tabRep(int *tRepTmp) {
    int retour = nTabRep;
    int n = tRepTmp[0] * 3 + 1;
    int i;
    nTabRep += n;
    tabRep[retour] = tRepTmp[0];
    for (i=0; i<tabRep[0]; i++) {
        tabRep[retour + i * 3 + 1] = tRepTmp[i * 3 + 1]; /* numero lexico */
        tabRep[retour + i * 3 + 2] = tRepTmp[i * 3 + 2]; /* type */
        if (i == 0) {
            tabRep[retour + i * 3 + 3] = 0;
        } else {
            tabRep[retour + i * 3 + 3] = tabRep[retour + (i - 1) * 3 + 3] + tRepTmp[(i - 1) * 3 + 3]; /* decalage */
        }
    }
    return retour;
}

int inserer_proc_tabRep(int *tRepTmp) {
    int retour = nTabRep;
    int n = tRepTmp[0] * 2 + 1;
    int i;
    nTabRep += n;
    tabRep[retour] = tRepTmp[0];
    for (i=0; i<tabRep[0]; i++) {
        tabRep[retour + i * 2 + 1] = tRepTmp[i * 2 + 1]; /* numero lexico */
        tabRep[retour + i * 2 + 2] = tRepTmp[i * 2 + 2]; /* type */
    }
    return retour;
}

int inserer_fonct_tabRep(int *tRepTmp, int rtype) {
    int retour = nTabRep;
    int n = tRepTmp[0] * 2 + 2;
    int i;
    nTabRep += n;
    tabRep[retour] = tRepTmp[0];
    tabRep[retour + 1] = rtype; /* type de retour */
    for (i=0; i<tabRep[0]; i++) {
        tabRep[retour + i * 2 + 2] = tRepTmp[i * 2 + 1]; /* numero lexico */
        tabRep[retour + i * 2 + 3] = tRepTmp[i * 2 + 2]; /* type */
    }
    return retour;
}

int inserer_tab_tabRep(int *tRepTmp) {
    int retour = nTabRep;
    int n = tRepTmp[1] * 2 + 2;
    int i;
    nTabRep += n;
    tabRep[retour] = tRepTmp[0]; /* type du tableau */
    tabRep[retour + 1] = tRepTmp[1]; /* nombre de dimensions */
    for (i=0; i<tabRep[1]; i++) {
        tabRep[retour + i * 2 + 2] = tRepTmp[i * 2 + 2]; /* borne inf */
        tabRep[retour + i * 2 + 3] = tRepTmp[i * 2 + 3]; /* borne sup */
    }
    return retour;
}



/**********************************************************/
/*                       Affichage                        */
/**********************************************************/

void f_afficher_char3(FILE *flux, char c, int n) {
    int i;
    for (i=0; i<n; i++) {
        fprintf(flux, "%c", c);
    }
}

void f_afficher_table_rep_lhorizontale(FILE *flux, int k) {
    char chaine [10];
    int n;
    int i;
    sprintf(chaine, "%d", N_TAB_REP_MAX);
    n = strlen(chaine) + 2;
    fprintf(flux, "+");
    for (i=0; i<k; i++) {
        f_afficher_char3(flux, '-', n);
        fprintf(flux, "+");
    }
    fprintf(flux, "\n");
}

void f_afficher_table_rep_ligne_indice(FILE *flux, int k, int k2) {
    char chaine[10];
    int i;
    int n, n_tmp;

    sprintf(chaine, "%d", N_TAB_REP_MAX);
    n = strlen(chaine);

    fprintf(flux, "| ");

    for (i=k; i<(k + k2); i++) {
        sprintf(chaine, "%d", i);
        n_tmp = strlen(chaine);
        fprintf(flux, "%d", i);
        f_afficher_char3(flux, ' ', n-n_tmp);
        fprintf(flux, " | ");
    }

    fprintf(flux, "\n");

    return;
}

void f_afficher_table_rep_ligne(FILE *flux, int k, int k2) {
    char chaine[10];
    int i;
    int n, n_tmp;

    sprintf(chaine, "%d", N_TAB_REP_MAX);
    n = strlen(chaine);

    fprintf(flux, "| ");

    for (i=k; i<(k + k2); i++) {
        sprintf(chaine, "%d", tabRep[i]);
        n_tmp = strlen(chaine);
        fprintf(flux, "%d", tabRep[i]);
        f_afficher_char3(flux, ' ', n-n_tmp);
        fprintf(flux, " | ");
    }

    fprintf(flux, "\n");

    return;
}

void f_afficher_table_rep(FILE * flux) {
    int i;
    fprintf(flux, "Table de représentation des types et des entêtes de sous-programmes\n");
    if (nTabRep > 0) {
        for (i=0; i<(nTabRep / 10); i++) {
            f_afficher_table_rep_lhorizontale(flux, 10);
            f_afficher_table_rep_ligne_indice(flux, i * 10, 10);
            f_afficher_table_rep_lhorizontale(flux, 10);
            f_afficher_table_rep_ligne(flux, i * 10, 10);
            f_afficher_table_rep_lhorizontale(flux, 10);
        }
        if ((nTabRep % 10) > 0) {
            f_afficher_table_rep_lhorizontale(flux, (nTabRep % 10));
            f_afficher_table_rep_ligne_indice(flux, (nTabRep / 10) * 10, (nTabRep % 10));
            f_afficher_table_rep_lhorizontale(flux, (nTabRep % 10));
            f_afficher_table_rep_ligne(flux, (nTabRep / 10) * 10, (nTabRep % 10));
            f_afficher_table_rep_lhorizontale(flux, (nTabRep % 10));
        }
    } else {
        fprintf(flux, "[vide]\n");
    }
    /*for (i=0; i<nTabRep; i++) {
        fprintf(flux, "%d\t", tabRep[i]);
    }
    fprintf(flux, "\n");*/
    return;
}

void afficher_table_rep() {
    f_afficher_table_rep(stdout);
    return;
}



/**********************************************************/
/*                   Lecture / Ecriture                   */
/**********************************************************/

int sauv_tabRep(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fwrite(&nTabRep, sizeof(int), sizeof(int), fic);
    
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur sauv_tabRep : Erreur lors de l'ecriture de nTabRep (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }

    taille_ecrit = fwrite(&tabRep, sizeof(int), sizeof(int) * nTabRep, fic);

    if (taille_ecrit < (sizeof(int) * nTabRep)) {
        fprintf(stderr, "Erreur sauv_tabRep : Erreur lors de l'ecriture de tabRep (%ld/%ld)\n", taille_ecrit, sizeof(int) * nTabRep);
        return -1;
    }

    return 0;
}

int charge_tabRep(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fread(&nTabRep, sizeof(int), sizeof(int), fic);
    
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur charge_tabRep : Erreur lors de lecture de nTabRep (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }

    taille_ecrit = fread(&tabRep, sizeof(int), sizeof(int) * nTabRep, fic);

    if (taille_ecrit < (sizeof(int) * nTabRep)) {
        fprintf(stderr, "Erreur charge_tabRep : Erreur lors de la lecture de tabRep (%ld/%ld)\n", taille_ecrit, (sizeof(int) * nTabRep));
        return -1;
    }

    return 0;
}


#endif /* _TABREP_C_ */



