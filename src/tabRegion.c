#ifndef _TABREGION_C_
#define _TABREGION_C_

#include "tabRegion.h"



/**********************************************************/
/*                         TABLE                          */
/**********************************************************/

/* Table des declarations */
ligneTabReg tabRegion[N_TAB_REG_MAX];

/* Nombre de régions */
int n_regions;

/* NIS courant */
int nis_courant;



/**********************************************************/
/*                Operations sur la table                 */
/**********************************************************/

void init_tabRegion() {
    memset(tabRegion, 0, N_TAB_REG_MAX * sizeof(ligneTabReg));
    n_regions = 0;
    nis_courant = 0;
}

int inserer_region_taille(int i, int taille) {
    if (i != sommetPileRegion()) {
        fprintf(stderr, "Erreur inserer_region_taille(%d, %d) : erreur insersion\n", i, taille);
    }
    tabRegion[i].taille = taille;
    return i;
}

int inserer_region_nis(int i, int nis) {
    if (i != n_regions) {
        fprintf(stderr, "Erreur inserer_region_nis : erreur insersion\n");
    }
    tabRegion[i].nis = nis;
    n_regions++;
    return i;
}

int inserer_region_arbre(int i, arbre *a) {
    if (i < n_regions) {
        tabRegion[i].a = a;
    } else {
        fprintf(stderr, "Erreur inserer_region_arbre : erreur insertion\n");
    }
    return i;
}

int inserer_region(int i, int taille, int nis, arbre *a) {
    tabRegion[i].nis = nis;
    tabRegion[i].taille = taille;
    tabRegion[i].a = a;
    n_regions++;
    return 0;
}

int getTabNis(int i) {
    return tabRegion[i].nis;
}



/**********************************************************/
/*                       Affichage                        */
/**********************************************************/

void f_afficher_char4(FILE *flux, char c, int n) {
    int i;
    for (i=0; i<n; i++) {
        fprintf(flux, "%c", c);
    }
}

void f_afficher_table_reg_lhorizontale(FILE *flux) {
    char chaine [50];
    int n;

    fprintf(flux, "+");

    /* Pour le numéro de région */
    sprintf(chaine, "%d", N_TAB_REG_MAX);
    n = strlen(chaine);
    f_afficher_char4(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ taille */
    sprintf(chaine, "%s", "   Taille   ");
    n = strlen(chaine);
    f_afficher_char4(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ nis */
    sprintf(chaine, "%s", " NIS ");
    n = strlen(chaine);
    f_afficher_char4(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ a (arbre) */
    sprintf(chaine, "%s", " Arbre ");
    n = strlen(chaine);
    f_afficher_char4(flux, '-', n);

    fprintf(flux, "+\n");
}

void f_afficher_table_reg_ligne(FILE *flux, int i) {
    char chaine [50];
    int n;
    int n_tmp;

    sprintf(chaine, "%d", N_TAB_REG_MAX);
    n = strlen(chaine);

    fprintf(flux, "|");

    /* Pour le numéro de région */
    sprintf(chaine, "%d", i);
    n_tmp = strlen(chaine);
    f_afficher_char4(flux, ' ', n-n_tmp);
    fprintf(flux, "%d", i);

    fprintf(flux, "|");

    /* Pour le champ taille */
    sprintf(chaine, "%s", "   Taille   ");
    n = strlen(chaine);
    fprintf(flux, " %d", tabRegion[i].taille);
    sprintf(chaine, " %d", tabRegion[i].taille);
    n_tmp = strlen(chaine);
    f_afficher_char4(flux, ' ', n-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ nis */
    sprintf(chaine, "%s", " NIS ");
    n = strlen(chaine);
    fprintf(flux, " %d", tabRegion[i].nis);
    sprintf(chaine, " %d", tabRegion[i].nis);
    n_tmp = strlen(chaine);
    f_afficher_char4(flux, ' ', n-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ a (arbre) */
    sprintf(chaine, "%s", " Arbre ");
    n = strlen(chaine);
    f_afficher_char4(flux, ' ', n);

    fprintf(flux, "|\n");

    return;
}

void f_afficher_table_reg(FILE *flux) {
    int i;
    fprintf(flux, "Table des Regions\n");
    f_afficher_table_reg_lhorizontale(flux);
    fprintf(flux, "|Num|   Taille   | NIS | Arbre |\n");
    f_afficher_table_reg_lhorizontale(flux);
    for (i=0; i<n_regions; i++) {
        f_afficher_table_reg_ligne(flux, i);
        f_afficher_table_reg_lhorizontale(flux);
    }
    return;
}

void afficher_table_reg() {
    f_afficher_table_reg(stdout);
}



/**********************************************************/
/*                   Lecture / Ecriture                   */
/**********************************************************/

int sauv_tabRegion(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fwrite(&n_regions, sizeof(int), sizeof(int), fic);
    
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur sauv_tabRegion : Erreur lors de l'ecriture de n_regions (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }

    taille_ecrit = fwrite(&tabRegion, sizeof(ligneTabReg), sizeof(ligneTabReg) * n_regions, fic);

    if (taille_ecrit < (sizeof(ligneTabReg) * n_regions)) {
        fprintf(stderr, "Erreur sauv_tabRegion : Erreur lors de l'ecriture de tabRegion (%ld/%ld)\n", taille_ecrit, (sizeof(ligneTabReg) * n_regions));
        return -1;
    }

    return 0;
}

int charge_tabRegion(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fread(&n_regions, sizeof(int), sizeof(int), fic);
    
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur charge_tabRegion : Erreur lors de lecture de n_regions (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }

    taille_ecrit = fread(&tabRegion, sizeof(ligneTabReg), sizeof(ligneTabReg) * n_regions, fic);

    if (taille_ecrit < (sizeof(ligneTabReg) * n_regions)) {
        fprintf(stderr, "Erreur charge_tabRegion : Erreur lors de la lecture de tabRegion (%ld/%ld)\n", taille_ecrit, (sizeof(ligneTabReg) * n_regions));
        return -1;
    }

    return 0;
}



#endif /* _TABREGION_C_ */



