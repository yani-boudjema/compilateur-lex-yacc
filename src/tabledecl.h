#ifndef _TABLEDECL_H_
#define _TABLEDECL_H_

#include <stdio.h>
#include <string.h>

#define N_TAB_DECL_MAX 5000
#define DEBUT_DEBORDEMENT 500



/**********************************************************/
/*       Champ nature de la table des declarations        */
/**********************************************************/

#define LIGNE_VIDE 0    /* pour les lignes vides de la table    */
#define TYPE_B 1        /* pour les types de base               */
#define TYPE_S 2        /* pour les structures                  */
#define TYPE_T 3        /* pour les tableaux					*/
#define VAR 4           /* pour les variables 					*/
#define PROC 5          /* pour les procedures					*/
#define FCT 6           /* pour les fonctions 					*/
#define PARAM 7         /* pour les parametres					*/



/**********************************************************/
/*                       STRUCTURE                        */
/**********************************************************/

/* Ligne de la table de declaration */
typedef struct {
    int nature;
    int suivant;
    int region;
    int description;
    int execution;
} ligneTabDecl;



/**********************************************************/
/*                       FONCTIONS                        */
/**********************************************************/


/* Initialise la table et les autres variables */
void init_tabDecl();

/* Insert un enregistrement dans la table des declarations */
/* Renvoie le numero de declaration                        */
/* Si l'insertion est impossible la fonction renvoie -1    */
int inserer_declaration(int num_lex, int nature, int region, int description, int exec);

/* Récupère les informations de l'enregistrement i de la table */
int ligneTableDecl(int i, int *nature, int *suivant, int *region, int *descr, int *exec);

/* Affiche la table de declaration dans le flux */
void f_afficher_table_decl(FILE *flux);

/* Affiche la table de declaration dans stdout */
void afficher_table_decl();

/* Ecrit la table des déclarations dans fic */
/* Renvoie 0 si pas de probleme             */
/*        -1 sinon                          */
int sauv_tabDecl(FILE * fic);

/* Lit la table des déclarations dans fic */
/* Renvoie 0 si pas de probleme           */
/*        -1 sinon                        */
int charge_tabDecl(FILE * fic);



#endif /* _TABLEDECL_H_ */



