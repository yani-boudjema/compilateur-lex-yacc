#ifndef _ERREURS_C_ 
#define _ERREURS_C_

#include "erreurs.h"


void erreur_type_non_declare(int ligne, int numLex) {
    couleur(ROUGE); 
    printf("Erreur: "); 
    couleur(REINIT); 
    printf("ligne %d : Type ", ligne); 
    couleur(MAGENTA); 
    printf("%s", lexeme(numLex)); couleur(REINIT);
    printf(" non déclaré\n");
}


#endif /* _ERREURS_C_ */



