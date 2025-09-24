#ifndef _TABLEDECL_C_
#define _TABLEDECL_C_

#include "tabledecl.h"



/**********************************************************/
/*                         TABLE                          */
/**********************************************************/

/* Table des declarations */
ligneTabDecl tabDecl[N_TAB_DECL_MAX];

/* Nombre de declarations dans la zone de debordement */
int n_decl_zone_debordement;



/**********************************************************/
/*                Operations sur la table                 */
/**********************************************************/

/* Initialise la table et les autres variables */
void init_tabDecl() {
    memset(tabDecl, 0, N_TAB_DECL_MAX * sizeof(ligneTabDecl));
    n_decl_zone_debordement = 0;
    inserer_declaration(0, TYPE_B, 0, 0, 1); /* type int      */
    inserer_declaration(1, TYPE_B, 0, 1, 1); /* type float    */
    inserer_declaration(2, TYPE_B, 0, 2, 1); /* type bool     */
    inserer_declaration(3, TYPE_B, 0, 3, 1); /* type char     */
    inserer_declaration(4, TYPE_B, 0, 4, 1); /* type string   */
}


/* Insert un enregistrement dans la table des declarations */
/* Renvoie le numero de declaration                        */
/* Si l'insertion est impossible la fonction renvoie -1    */
int inserer_declaration(int num_lex, int nature, int region, int description, int exec){
    int i;
    if(tabDecl[num_lex].nature == LIGNE_VIDE){
        tabDecl[num_lex].nature = nature;
        tabDecl[num_lex].suivant = -1;
        tabDecl[num_lex].region = region;
        tabDecl[num_lex].description = description;
        tabDecl[num_lex].execution = exec;
        return num_lex;
    }
    /*si la ligne est deja occupée on cherche une place libre dans la zone de débordement*/
    int actuel = num_lex;
    while (tabDecl[actuel].suivant != -1) {
        actuel = tabDecl[actuel].suivant;
    }
    /* On inert dans la premiere ligne vide de la zone de debordement */
    i = DEBUT_DEBORDEMENT + n_decl_zone_debordement;
    if (i < N_TAB_DECL_MAX) {
        tabDecl[i].nature = nature;
        tabDecl[i].suivant = -1;
        tabDecl[i].region = region;
        tabDecl[i].description = description;
        tabDecl[i].execution = exec;
        tabDecl[actuel].suivant = i;
        n_decl_zone_debordement++;
        return i;
    }
    /* Si il n'y a plus de place dans le zone de debordement */
    fprintf(stderr, "Erreur : dépassement de la zone de débordement\n");
    return -1;
}


int ligneTableDecl(int i, int *nature, int *suivant, int *region, int *descr, int *exec) {
    if (i >= N_TAB_DECL_MAX) {
        fprintf(stderr, "Erreur ligneTableDecl: indice invalide\n");
        return -1;
    }
    if (nature != NULL) {
        *nature = tabDecl[i].nature;
    }
    if (suivant != NULL) {
        *suivant = tabDecl[i].suivant;
    }
    if (region != NULL) {
        *region = tabDecl[i].region;
    }
    if (descr != NULL) {
        *descr = tabDecl[i].description;
    }
    if (exec != NULL) {
        *exec = tabDecl[i].execution;
    }
    return 0;
}



/**********************************************************/
/*                       Affichage                        */
/**********************************************************/

void f_afficher_char2(FILE *flux, char c, int n) {
    int i;
    for (i=0; i<n; i++) {
        fprintf(flux, "%c", c);
    }
}

void f_afficher_table_decl_lhorizontale(FILE *flux) {
    char chaine[50];
    int n;

    fprintf(flux, "+");

    /* Pour le champ numero de declaration */
    sprintf(chaine, "%d", N_TAB_DECL_MAX);
    n = strlen(chaine);
    f_afficher_char2(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ nature */
    sprintf(chaine, "%s", " Nature ");
    n = strlen(chaine);
    f_afficher_char2(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ suivant */
    sprintf(chaine, "%s", " Suivant ");
    n = strlen(chaine);
    f_afficher_char2(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ region */
    sprintf(chaine, "%s", " Region ");
    n = strlen(chaine);
    f_afficher_char2(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ description */
    sprintf(chaine, "%s", " Description ");
    n = strlen(chaine);
    f_afficher_char2(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ execution */
    sprintf(chaine, "%s", " Execution ");
    n = strlen(chaine);
    f_afficher_char2(flux, '-', n);

    fprintf(flux, "+\n");

    return;
}

void f_afficher_table_decl_ligne(FILE *flux, int i) {
    char chaine[50];
    char chaine_nature[50];
    int n;
    int n_tmp;

    if (tabDecl[i].nature == LIGNE_VIDE) {
        return;
    }

    sprintf(chaine, "%d", N_TAB_DECL_MAX);
    n = strlen(chaine);

    fprintf(flux, "|");

    /* Pour le champ numero de declaration */
    sprintf(chaine, "%d", i);
    n_tmp = strlen(chaine);
    f_afficher_char2(flux, ' ', n-n_tmp);
    fprintf(flux, "%d", i);

    fprintf(flux, "|");
    
    /* Pour le champ nature */
    sprintf(chaine, "%s", " Nature ");
    n = strlen(chaine);
    switch (tabDecl[i].nature){
    case TYPE_B:
        sprintf(chaine_nature, " %s", "TYPE_B");
        break;
    case TYPE_S:
        sprintf(chaine_nature, " %s", "TYPE_S");
        break;
    case TYPE_T:
        sprintf(chaine_nature, " %s", "TYPE_T");
        break;
    case VAR:
        sprintf(chaine_nature, " %s", "VAR");
        break;
    case PROC:
        sprintf(chaine_nature, " %s", "PROC");
        break;
    case FCT:
        sprintf(chaine_nature, " %s", "FCT");
        break;
    case PARAM:
        sprintf(chaine_nature, " %s", "PARAM");
        break;
    default:
        break;
    }
    fprintf(flux, "%s", chaine_nature);
    n_tmp = strlen(chaine_nature);
    f_afficher_char2(flux, ' ', n-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ suivant */
    sprintf(chaine, "%s", " Suivant ");
    n = strlen(chaine);
    fprintf(flux, " %d", tabDecl[i].suivant);
    sprintf(chaine, " %d", tabDecl[i].suivant);
    n_tmp = strlen(chaine);
    f_afficher_char2(flux, ' ', n-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ region */
    sprintf(chaine, "%s", " Region ");
    n = strlen(chaine);
    fprintf(flux, " %d", tabDecl[i].region);
    sprintf(chaine, " %d", tabDecl[i].region);
    n_tmp = strlen(chaine);
    f_afficher_char2(flux, ' ', n-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ description */
    sprintf(chaine, "%s", " Description ");
    n = strlen(chaine);
    fprintf(flux, " %d", tabDecl[i].description);
    sprintf(chaine, " %d", tabDecl[i].description);
    n_tmp = strlen(chaine);
    f_afficher_char2(flux, ' ', n-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ execution */
    sprintf(chaine, "%s", " Execution ");
    n = strlen(chaine);
    fprintf(flux, " %d", tabDecl[i].execution);
    sprintf(chaine, " %d", tabDecl[i].execution);
    n_tmp = strlen(chaine);
    f_afficher_char2(flux, ' ', n-n_tmp);

    fprintf(flux, "|\n");

    return;
}

void f_afficher_table_decl(FILE *flux) {
    int i;
    fprintf(flux, "Table des Declarations\n");
    f_afficher_table_decl_lhorizontale(flux);
    fprintf(flux, "|Num | Nature | Suivant | Region | Description | Execution |\n");
    f_afficher_table_decl_lhorizontale(flux);
    for (i=0; i<DEBUT_DEBORDEMENT; i++) {
        if (tabDecl[i].nature != LIGNE_VIDE) {
            f_afficher_table_decl_ligne(flux, i);
            f_afficher_table_decl_lhorizontale(flux);
        }
    }
    fprintf(flux, "|                   ZONE DE DEBORDEMENT                    |\n");
    f_afficher_table_decl_lhorizontale(flux);
    for (i=DEBUT_DEBORDEMENT; i<(DEBUT_DEBORDEMENT + n_decl_zone_debordement); i++) {
        if (tabDecl[i].nature != LIGNE_VIDE) {
            f_afficher_table_decl_ligne(flux, i);
            f_afficher_table_decl_lhorizontale(flux);
        }
    }
}



/*void f_afficher_table_decl(FILE *flux) {
    int i;
    fprintf(flux, "Table des déclarations\n");
    fprintf(flux,"index\tnature\tsuivant\tdescription\texecution\n");
    for (i=0;i<N_TAB_DECL_MAX;i++){
        if(tabDecl[i].nature != LIGNE_VIDE) {
            fprintf(flux,"%d\t%d\t%d\t%d\t%d\n",i,tabDecl[i].nature,tabDecl[i].suivant,tabDecl[i].description,tabDecl[i].execution);
        }
    }
}*/

void afficher_table_decl(){
    f_afficher_table_decl(stdout);
}



/**********************************************************/
/*                   Lecture / Ecriture                   */
/**********************************************************/

int sauv_tabDecl(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fwrite(&n_decl_zone_debordement, sizeof(int), sizeof(int), fic);
    
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur sauv_tabDecl : Erreur lors de l'ecriture de n_decl_zone_debordement (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }

    taille_ecrit = fwrite(&tabDecl, sizeof(ligneTabDecl), sizeof(ligneTabDecl) * (n_decl_zone_debordement + DEBUT_DEBORDEMENT), fic);

    if (taille_ecrit < (sizeof(ligneTabDecl) * (n_decl_zone_debordement + DEBUT_DEBORDEMENT))) {
        fprintf(stderr, "Erreur sauv_tabDecl : Erreur lors de l'ecriture de tabDecl (%ld/%ld)\n", taille_ecrit, (sizeof(ligneTabDecl) * (n_decl_zone_debordement + DEBUT_DEBORDEMENT)));
        return -1;
    }

    return 0;
}

int charge_tabDecl(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fread(&n_decl_zone_debordement, sizeof(int), sizeof(int), fic);
    
    if (taille_ecrit < sizeof(int)) {
        fprintf(stderr, "Erreur charge_tabDecl : Erreur lors de lecture de n_decl_zone_debordement (%ld/%ld)\n", taille_ecrit, sizeof(int));
        return -1;
    }

    taille_ecrit = fread(&tabDecl, sizeof(ligneTabDecl), sizeof(ligneTabDecl) * (n_decl_zone_debordement + DEBUT_DEBORDEMENT), fic);

    if (taille_ecrit < (sizeof(ligneTabDecl) * (n_decl_zone_debordement + DEBUT_DEBORDEMENT))) {
        fprintf(stderr, "Erreur charge_tabDecl : Erreur lors de la lecture de tabDecl (%ld/%ld)\n", taille_ecrit, (sizeof(ligneTabDecl) * (n_decl_zone_debordement + DEBUT_DEBORDEMENT)));
        return -1;
    }

    return 0;
}
    
        
        
        
            

#endif /* _TABLEDECL_C_ */



