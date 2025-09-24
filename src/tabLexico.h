#ifndef _TABLEXICO_H_ 
#define _TABLEXICO_H_ 

#include <stdio.h>

#define N_TAB_HASH_CODE_MAX 32
#define N_TAB_LEXICO_MAX 500
#define LGR_LEXEME_MAX 50



/**********************************************************/
/*                       STRUCTURE                        */
/**********************************************************/

/* Ligne de la table lexicographique */
typedef struct {
    int longueur;
    char lexeme[LGR_LEXEME_MAX];
    int suivant;
} ligneTabLexico;



/**********************************************************/
/*                       FONCTIONS                        */
/**********************************************************/

/* Insere le lexeme dans la table lexicographique */
int inserer_lexeme(char *lexeme);

/* Renvoie le lexeme de numero lexicographique numero_lexico */
char *lexeme(int numero_lexico);

/* Initialise les tables */
void init_tabLexico();

/* Affiche la table lexicographique dans le flux */
void f_afficher_table_lexico(FILE *flux);

/* Affiche la table lexicographique dans stdout */
void afficher_table_lexico();

/* Ecrit la table Hash Code dans fic */
int sauv_tabHashCode(FILE * fic);

/* Lit la table Hash Code dans fic */
int charge_tabHashCode(FILE * fic);

/* Ecrit la table lexicographique dans fic */
int sauv_tabLexico(FILE * fic);

/* Lit la table lexicographique dans fic */
int charge_tabLexico(FILE * fic);


#endif /* _TABLEXICO_H_ */



