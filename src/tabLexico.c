#ifndef _TABLEXICO_C_ 
#define _TABLEXICO_C_ 

#include <string.h>
#include <stdlib.h>
#include "tabLexico.h"

#define LONGUEUR 0
#define LEX 1
#define SUIV 2



/**********************************************************/
/*                         TABLES                         */
/**********************************************************/


/* Table des hash code */
int tabHashCode[N_TAB_HASH_CODE_MAX];

/* Table lexicographique */
ligneTabLexico tabLexico[N_TAB_LEXICO_MAX];

/* Nombre de lexemes dans la table lexicographique */
int n_lexemes;



/**********************************************************/
/*               Operations sur les tables                */
/**********************************************************/


/* Renvoie le hash code du lexeme */
int hash_code(const char *lexeme) {
    int sommeASCII = 0;
    int i;

    i = 0;
    while (lexeme[i] != '\0') {
        sommeASCII += lexeme[i];
        i++;
    }

    return (sommeASCII % 32);
}


/* Insert le lexeme dans la table */
int inserer_lexeme(char *lexeme) {
    int continuer = 1;
    int trouver = 0;
    int hc; 
    int num_lex;
    int num_lex_suiv;
    int lgr_lexeme;

    /* Si table lexico saturée */
    if (n_lexemes >= N_TAB_LEXICO_MAX) {
        fprintf(stderr, "[tabLexico] Erreur inserer_lexeme : plus assez d'espace dans la table pour inserer un nouveau lexeme\n");
        return -1;
    }

    /* Calcul du hash code du lexeme */
    hc = hash_code(lexeme);

    /* Si hc non utilisé dans la table */
    if (tabHashCode[hc] == -1) {
        tabHashCode[hc] = n_lexemes;
        continuer = 0;
    }

    /* Longueur du lexeme */
    lgr_lexeme = strlen(lexeme);

    /* Recuperation du premier numero lexical a comparer */
    num_lex = tabHashCode[hc];

    /*if (tabLexico[num_lex].longueur == -1) {
        continuer = 0;
    }*/

    while ((num_lex < n_lexemes) && continuer && !(trouver)) {
        /* On compare la longueur */
        if (tabLexico[num_lex].longueur == lgr_lexeme) {

            /* On compare les chaines */
            if (strcmp(tabLexico[num_lex].lexeme, lexeme) == 0) {
                trouver = 1;
            } else {
                num_lex_suiv = tabLexico[num_lex].suivant;
            }
        } else {
            num_lex_suiv = tabLexico[num_lex].suivant;
        } 

        /* Si on n'a pas encore trouve le lexeme       */
        /* et que le parcours n'est pas encore termine */
        if (!trouver && continuer) {
            if (num_lex_suiv == -1) {
                /* Maintenant on peut inserer */
                continuer = 0;
            } else {
                /* On continue de parcourrir la table lexico */
                num_lex = num_lex_suiv;
            }
        }
    }

    /* On insert */
    if (!(continuer) && !(trouver)) {
        tabLexico[num_lex].suivant  = n_lexemes;
        num_lex = n_lexemes;
        strncpy(tabLexico[num_lex].lexeme, lexeme, LGR_LEXEME_MAX);
        /* Pour avoir une chaine exploitable en cas de debordement */
        tabLexico[num_lex].lexeme[LGR_LEXEME_MAX-1] = '\0'; 
        tabLexico[num_lex].longueur = lgr_lexeme;
        tabLexico[num_lex].suivant = -1;
        n_lexemes++;
    }

    return num_lex;
}


/* Renvoie le lexeme a partir de son numero lexicographique */
char *lexeme(int numero_lexico) {
    return tabLexico[numero_lexico].lexeme;
}



/**********************************************************/
/*                    Initialisations                     */
/**********************************************************/


/* Initialise la table de hash code */
void init_tabHashCode() {
    int i;
    for (i=0; i<N_TAB_HASH_CODE_MAX; i++) {
        tabHashCode[i] = -1;
    }
}


/* Initialise la table lexicographique */
void init_tabLexico() {
    int i;

    /* Remise a zero du nombre de lexemes dans la table lexicographique */
    n_lexemes = 0;

    /* Initialisation de la table d'hashcode */
    init_tabHashCode();

    /* Initialisation du reste de la table a -1 */
    for (i=n_lexemes; i<N_TAB_LEXICO_MAX; i++) {
        tabLexico[i].longueur = -1;
        tabLexico[i].lexeme[0] = '\0';
        tabLexico[i].suivant = -1;
    }

    /* Initialisation des lexemes des types de base */
    inserer_lexeme("int");
    inserer_lexeme("float");
    inserer_lexeme("bool");
    inserer_lexeme("char");
    inserer_lexeme("string");
}



/**********************************************************/
/*                       Affichage                        */
/**********************************************************/

void f_afficher_char(FILE *flux, char c, int n) {
    int i;
    for (i=0; i<n; i++) {
        fprintf(flux, "%c", c);
    }
}

void f_afficher_table_lexico_lhorizontale(FILE *flux) {
    char chaine[LGR_LEXEME_MAX];
    int n;

    fprintf(flux, "+");

    /* Pour le champ numero lexicale */
    sprintf(chaine, "%d", N_TAB_LEXICO_MAX);
    n = strlen(chaine);
    f_afficher_char(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ longueur */
    f_afficher_char(flux, '-', n);

    fprintf(flux, "+");

    /* Pour le champ lexeme */
    f_afficher_char(flux, '-', LGR_LEXEME_MAX);

    fprintf(flux, "+");

    /* Pour le champ suivant */
    f_afficher_char(flux, '-', n);

    fprintf(flux, "+\n");

    return;
}

void f_afficher_table_lexico_ligne(FILE *flux, int i) {
    char chaine[LGR_LEXEME_MAX];
    int n;
    int n_tmp;

    sprintf(chaine, "%d", N_TAB_LEXICO_MAX);
    n = strlen(chaine);

    fprintf(flux, "|");

    /* Pour le champ numero lexical */
    sprintf(chaine, "%d", i);
    n_tmp = strlen(chaine);
    f_afficher_char(flux, ' ', n-n_tmp);
    fprintf(flux, "%d", i);

    fprintf(flux, "|");

    /* Pour le champ longueur */
    sprintf(chaine, "%d", tabLexico[i].longueur);
    n_tmp = strlen(chaine);
    f_afficher_char(flux, ' ', n-n_tmp);
    fprintf(flux, "%d", tabLexico[i].longueur);

    fprintf(flux, "|");

    /* Pour le champ lexeme */
    n_tmp = strlen(tabLexico[i].lexeme);
    fprintf(flux, "%s", tabLexico[i].lexeme);
    f_afficher_char(flux, ' ', LGR_LEXEME_MAX-n_tmp);

    fprintf(flux, "|");

    /* Pour le champ suivant */
    sprintf(chaine, "%d", tabLexico[i].suivant);
    n_tmp = strlen(chaine);
    f_afficher_char(flux, ' ', n-n_tmp);
    fprintf(flux, "%d", tabLexico[i].suivant);

    fprintf(flux, "|\n");

    return;
}

void f_afficher_table_lexico(FILE *flux) {
    int i;
    fprintf(flux, "Table Lexicographique\n");
    f_afficher_table_lexico_lhorizontale(flux);
    for (i=0; i<n_lexemes; i++) {
        f_afficher_table_lexico_ligne(flux, i);
        f_afficher_table_lexico_lhorizontale(flux);
    }
}

void afficher_table_lexico() {
    f_afficher_table_lexico(stdout);
}

void f_afficher_table_hcode(FILE *flux) {
    char chaine[LGR_LEXEME_MAX];
    int n_tmp;
    int i;

    fprintf(flux, "Table Hash Code\n");

    fprintf(flux, "+--+---+\n");

    for (i=0; i<N_TAB_HASH_CODE_MAX; i++) {
        fprintf(flux, "|");

        sprintf(chaine, "%d", i);
        n_tmp = strlen(chaine);
        f_afficher_char(flux, ' ', 2-n_tmp);
        fprintf(flux, "%d", i);

        fprintf(flux, "|");

        sprintf(chaine, "%d", tabHashCode[i]);
        n_tmp = strlen(chaine);
        f_afficher_char(flux, ' ', 3-n_tmp);
        fprintf(flux, "%d", tabHashCode[i]);

        fprintf(flux, "|\n");

        fprintf(flux, "+--+---+\n");
    }

    return;
}

void afficher_table_hcode() {
    f_afficher_table_hcode(stdout);
}



/**********************************************************/
/*                   Lecture / Ecriture                   */
/**********************************************************/

int sauv_tabHashCode(FILE * fic) {
    size_t taille_ecrit;

    taille_ecrit = fwrite(&tabHashCode, sizeof(int), sizeof(int) * N_TAB_HASH_CODE_MAX, fic);

    if (taille_ecrit < (sizeof(int) * N_TAB_HASH_CODE_MAX)) {
        fprintf(stderr, "Erreur sauv_tabHashCode : Erreur lors de l'ecriture de tabHashCode (%ld/%ld)\n", taille_ecrit, sizeof(int) * N_TAB_HASH_CODE_MAX);
        return -1;
    }

    return 0;
}

int charge_tabHashCode(FILE * fic) {
    size_t taille_ecrit;

    if ((taille_ecrit = fread(&tabHashCode, sizeof(int), sizeof(int) * N_TAB_HASH_CODE_MAX, fic)) < (sizeof(int) * N_TAB_HASH_CODE_MAX)) {
        fprintf(stderr, "Erreur charge_tabHashCode : Erreur lors de la lecture de tabHashCode (%ld/%ld)\n", taille_ecrit, sizeof(int) * N_TAB_HASH_CODE_MAX);
        return -1;
    }

    return 0;
}

int sauv_tabLexico(FILE * fic) {
    size_t taille_ecrit;

    if (fwrite(&n_lexemes, sizeof(int), sizeof(int), fic) < sizeof(int)) {
        fprintf(stderr, "Erreur sauv_tabLexico : Erreur lors de l'ecriture de n_lexemes\n");
        return -1;
    }

    taille_ecrit = fwrite(&tabLexico, sizeof(ligneTabLexico), sizeof(ligneTabLexico) * n_lexemes, fic);

    if (taille_ecrit < (sizeof(ligneTabLexico) * n_lexemes)) {
        fprintf(stderr, "Erreur sauv_tabLexico : Erreur lors de l'ecriture de tabLexico (%ld/%ld)\n", taille_ecrit, sizeof(ligneTabLexico) * n_lexemes);
        return -1;
    }

    return 0;
}

int charge_tabLexico(FILE * fic) {
    size_t taille_ecrit;
    int i;

    if (fread(&n_lexemes, sizeof(int), sizeof(int), fic) < sizeof(int)) {
        fprintf(stderr, "Erreur charge_tabLexico : Erreur lors de la lecture de n_lexemes\n");
        return -1;
    }

    if ((taille_ecrit = fread(&tabLexico, sizeof(ligneTabLexico), sizeof(ligneTabLexico) * n_lexemes, fic)) < (sizeof(ligneTabLexico) * n_lexemes)) {
        fprintf(stderr, "Erreur charge_tabLexico : Erreur lors de la lecture de tabLexico (%ld/%ld)\n", taille_ecrit, sizeof(ligneTabLexico) * n_lexemes);
        return -1;
    }
    
    /* Initialisation du reste de la table */
    for (i=n_lexemes; i<N_TAB_LEXICO_MAX; i++) {
        tabLexico[i].longueur = -1;
        tabLexico[i].lexeme[0] = '\0';
        tabLexico[i].suivant = -1;
    }

    return 0;
}



/**********************************************************/
/*                          TEST                          */
/**********************************************************/


/*int main() {
    init_tabLexico();
    printf("n_lexemes = %d\n", n_lexemes);
    afficher_table_lexico();
    afficher_table_hcode();
    inserer_lexeme("un_lexeme");
    afficher_table_lexico();
    inserer_lexeme("un_lexeem");
    afficher_table_lexico();
    exit(EXIT_FAILURE);
}*/





#endif /* _TABLEXICO_C_ */



