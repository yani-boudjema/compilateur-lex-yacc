#ifndef _ERREURS_H_ 
#define _ERREURS_H_

#include "tabLexico.h"


#define couleur(param) printf("\033[%sm",param)
#define NOIR  "30"
#define ROUGE "31"
#define VERT  "32"
#define JAUNE "33"
#define BLEU  "34"
#define MAGENTA "35"
#define CYAN  "36"
#define BLANC "37"
#define REINIT "0"


void erreur_type_non_declare(int ligne, int numLex);


#endif /* _ERREURS_H_ */



