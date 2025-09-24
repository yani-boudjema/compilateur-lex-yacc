#ifndef _PILE_H_ 
#define _PILE_H_ 

#include <stdio.h>
#include <stdlib.h>

typedef struct pile_t {
    int valeur;
    struct pile_t *suivant;
    struct pile_t *precedant;
} pile;

typedef struct it_pile_t {
    pile *debut; /* Sommet de pile */
    pile *courant;
    pile *fin; /* Fond de pile */
} it_pile;


pile *pilevide();
/* Renvoie la pile vide (renvoie NULL)                    */

pile *empiler(pile *p, int elem);
/* Empile l'element e dans la pile et renvoie la pile     */

pile *depile(pile *p);
/* Supprime l'element en sommet de pile et renvoie la     */
/* pile                                                   */

int sommet(pile *p);
/* Renvoie l'element en sommet de pile                    */
/* (La pile n'est pas modifiee)                           */

void liberer_pile(pile *p);
/* Libere la memoire allouee a la pile p                  */



it_pile *creer_it_pile();
/* Creation de l'iterateur                                */

void init_it_pile(it_pile *itp, pile *p); 
/* Initalisation de l'iterateur                           */

void init_it_pile_debut(it_pile *itp);
/* Initialise l'iterateur en sommet de pile               */

void init_it_pile_fin(it_pile *itp);
/* Initialise l'iterateur en fond de pile                 */

void itp_suiv(it_pile *itp);
/* Passe a l'element suivant de la pile                   */

void itp_prec(it_pile *itp);
/* Passe a l'element precedant de la pile                 */

pile *itp_courant(it_pile *itp);
/* Renvoie le pointeur de l'element courant               */

int itp_courant_val(it_pile *itp);
/* Renvoie la valeur de l'element courant                 */

void liberer_itp(it_pile *itp);
/* Libere la memoire allouee a l'iterateur                */

int itp_est_termine(it_pile *itp); 
/* Envoie : 0 si le parcours n'est pas termine            */
/*          1 si le parcours est termine                  */


#endif /* _PILE_H_ */



