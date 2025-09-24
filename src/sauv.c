#ifndef _SAUV_C_ 
#define _SAUV_C_

#include "sauv.h"


int sauvegarder(char * nom_fic) {
    FILE * fic = NULL;

    if (nom_fic == NULL) {
        nom_fic = strdup("a.cpyrr");
    }

    if ((fic = fopen(nom_fic, "wb")) == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fic);
        return -1;
    }

    if (sauv_tabHashCode(fic) == -1) {
        return -1;
    }

    if (sauv_tabLexico(fic) == -1) {
        return -1;
    }

    if (sauv_tabDecl(fic) == -1) {
        return -1;
    }

    if (sauv_tabRep(fic) == -1) {
        return -1;
    }

    if (sauv_tabRegion(fic) == -1) {
        return -1;
    }

    fclose(fic);

    return 0;
}

int charger(char * nom_fic) {
    FILE * fic = NULL;

    if (nom_fic == NULL) {
        nom_fic = strdup("a.cpyrr");
    }

    if ((fic = fopen(nom_fic, "rb")) == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fic);
        return -1;
    }

    if (charge_tabHashCode(fic) == -1) {
        return -1;
    }

    if (charge_tabLexico(fic) == -1) {
        return -1;
    }

    if (charge_tabDecl(fic) == -1) {
        return -1;
    }

    if (charge_tabRep(fic) == -1) {
        return -1;
    }

    if (charge_tabRegion(fic) == -1) {
        return -1;
    }

    fclose(fic);

    return 0;
}


#endif /* _SAUV_C_ */



