#ifndef _ARBRE_H_ 
#define _ARBRE_H_ 

#include <stdio.h>
#include <stdlib.h>
#include "arbre_macros.h"


typedef union {
    int entier;
    float flottant;
} nlex;

typedef struct arbre_noeud {
    int valeur;
    nlex num_lexico;            /* numero lexicographique */
    int num_decl;               /* numero de declaration  */
    struct arbre_noeud *gauche; /* fils gauche            */ 
    struct arbre_noeud *droite; /* frere droit            */
} arbre;


typedef struct {
    int valeur;
    nlex num_lexico;
    int num_decl;
    int suiv_gauche;
    int suiv_droite;
} arbre_sauv_noeud;


arbre *arbre_vide();
/* Renvoie un arbre vide (retourne NULL)                  */

/* Renvoie le champ valeur de la racine de l'abre         */
int getValeur(arbre *a);

arbre *getFils(arbre *a);
/* Renvoie le fils de l'arbre a (branche gauche)          */

arbre *getFrere(arbre *a);
/* Renvoie le frere de l'arbre a (branche droite)         */

arbre *creer_noeud(int valeur, nlex num_lexico, int num_decl); 
/* Cree un noeud dont le champ                            */
/* - valeur prend la valeur de valeur                     */
/* - num_lexico prend la valeur de num_lexico             */
/* - num_decl prend ma valeur de num_decl                 */
/* et le fils gauche et le frere droit prennent la valeur */
/* NULL et renvoie le pointeur qui point sur le  noeud    */
/* cree                                                   */

arbre *concat_frere(arbre *a1, arbre *a2);
/* Concatene a2 au frere droit de a1 et retourne a1       */

arbre *concat_fils(arbre *a1, arbre *a2);
/* Concatene a2 au fils gauche de a1 et retourne a1       */

void afficher_arbre(FILE *flux, arbre *a);
/* Affiche l'arbre a sur le flux "flux"                   */

void liberer_arbre(arbre *a);
/* Libere la memoire alloue a l'arbre a                   */

int nb_noeud(arbre *a);
/* Renvoie le nombre de neouds dans l'arbre a             */

int sauv_arbre(arbre *a, int indReg, FILE *fic); /*NON TESTE*/
/* Ecrit l'arbre a dans fic                               */
/* Renvoie 0 si pas de probleme                           */
/*        -1 sinon                                        */

arbre *charge_arbre(int *indReg, FILE *fic); /*NON TESTE*/
/* Lit l'arbre dans fic et met dans indReg la region de   */
/* l'arbre                                                */
/* Renvoie l'arbre a lu                                   */



#endif /* _ARBRE_H_ */ 



