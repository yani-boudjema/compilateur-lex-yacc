%{
    #include <stdio.h>
    #include "tabLexico.h"
    #include "tabledecl.h"
    #include "pileRegion.h"
    #include "tabRegion.h"
    #include "tabRep.h"
    #include "erreurs.h"
    #include "TAD_Arbre/arbre.h"
    #include "sauv.h"

    extern FILE * yyin;
    int yylex();
    int yyerror();
    extern int numligne;

    int tmp_sommet_pile;
    int tmp, tmp1, tmp2;
    int num_decl_tmp1, num_decl_tmp2;
    int num_reg_tmp1, num_reg_tmp2;
    int exec_tmp;
    nlex num_lexico_tmp;
    nlex num_lexico_tmp2;
    int i;
    int tRepTmp[100];
    int dx[N_TAB_REG_MAX]; /* pour stocker les décalages pour l'execution */



   void affiche_arbre(arbre* racine, int niveau) {
        if (racine == NULL) return;

        for (int i = 0; i < niveau; i++) {
            printf("    ");
        }

        printf("Valeur: %d, Num_decl: %d, Num_lexico: ", racine->valeur, racine->num_decl);
        if (racine->num_lexico.entier != 0) {
            printf("%d", racine->num_lexico.entier);
        } else {
            printf("%.2f", racine->num_lexico.flottant);
        }
        printf("\n");

        affiche_arbre(racine->gauche, niveau + 1);
        affiche_arbre(racine->droite, niveau);
    }


%}


%union {
    /*struct T arbre_type;*/
    int valeur;
    float valeurf;
    char *str; 
    arbre *abr;
}

%token PROG DEBUT FIN 
%token SI ALORS SINON TANT_QUE FAIRE 
%token PROCEDURE FONCTION RETOURNE 
%token VARIABLE 
%token TYPE 
%token <valeur> ENTIER REEL BOOLEEN CARACTERE CHAINE 
%token DE TABLEAU STRUCT FSTRUCT 
%token TRUE FALSE 
%token VIDE 
%token LIRE ECRIRE 
%token POINT_VIRGULE DEUX_POINTS 
%token PARENTHESE_OUVRANTE PARENTHESE_FERMANTE 
%token VIRGULE 
%token CROCHET_OUVRANT CROCHET_FERMANT 
%token POINT_POINT 
%token POINT
%token OPAFF 
%token PLUS MOINS MULT DIV MODULO 
%token INF SUP INF_EGAL SUP_EGAL DIFF EGAL 
%token AND OR NOT 
%token <valeur> IDF 
%token <valeur> CSTE_ENTIERE 
%token <valeurf> CSTE_REEL 
%token <str>PHRASE

%type <valeur> nom_type type_simple une_dimension liste_dimensions dimension 
%type <abr> variable affectation expression expression_comparaison 
%type <abr> expression_arithmetique expression_arithmetique2 expression_arithmetique3 
%type <abr> expression_booleenne expression_booleenne2 expression_booleenne3 expression_booleenne4 
%type <abr> condition tant_que resultat_retourne 
%type <abr> instruction suite_liste_inst  
%type <abr> appel liste_arguments liste_args un_arg corps
%type <abr> liste_instructions liste_variables instruction_lecture instruction_ecriture suite_ecriture format declaration_fonction declaration_procedure

%%
programme: PROG {nvRegion(); inserer_region_nis(getNumReg(), getNis()); dx[getNumReg()] = 0;} corps //{num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_PROG, num_lexico_tmp, -1), $2);}
;

corps: 
    liste_declarations liste_instructions {/*$$ = $2; */num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_CORPS, num_lexico_tmp, -1), $2); inserer_region_arbre(getNumReg(), $$); inserer_region_taille(getNumReg(), dx[getNumReg()]);}
   | liste_instructions {/*$$ = $1;*/ num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_CORPS, num_lexico_tmp, -1), $1); inserer_region_arbre(getNumReg(), $$);}
;

liste_declarations: 
    declaration POINT_VIRGULE
    | liste_declarations declaration POINT_VIRGULE
;

liste_instructions: DEBUT suite_liste_inst FIN {$$= $2;}
;

suite_liste_inst: 
    instruction POINT_VIRGULE suite_liste_inst  {num_lexico_tmp.entier = -1; if($1 != NULL) 
                                                                                $$ = concat_fils(creer_noeud(A_LISTE_INST, num_lexico_tmp, -1), concat_frere($1, $3));
                                                                            else
                                                                                $$ = $3;
                                                }                            
    | instruction POINT_VIRGULE {num_lexico_tmp.entier = -1; if ($1 != NULL){ 
                                                                $$ = creer_noeud(A_LISTE_INST,num_lexico_tmp,-1); $$ = concat_fils($$, $1);
                                                           }else{
                                                                $$ = creer_noeud(A_LISTE_INST,num_lexico_tmp,-1);
                                                            }
                                }
;

declaration: 
    declaration_type
    | declaration_variable
    | declaration_procedure
    | declaration_fonction
;

declaration_type:
    TYPE IDF DEUX_POINTS {tRepTmp[0] = 0;} STRUCT liste_champs FSTRUCT {tmp = 0; /*taille*/
                                                                        for (i=0; i<tRepTmp[0]; i++) {
                                                                            tmp += tRepTmp[i * 3 + 3];
                                                                        }
                                                                        inserer_declaration($2, TYPE_S, getNumReg(), inserer_struct_tabRep(tRepTmp), tmp);}
    | TYPE IDF DEUX_POINTS {tRepTmp[0] = 0;} TABLEAU dimension DE nom_type {tRepTmp[0] = $8;
                                                                            ligneTableDecl($8, NULL, NULL, NULL, NULL, &tmp); /*taille d'un element*/
                                                                            inserer_declaration($2, TYPE_T, getNumReg(), inserer_tab_tabRep(tRepTmp), $6 * tmp);}
;

dimension: 
    CROCHET_OUVRANT liste_dimensions CROCHET_FERMANT {$$ = $2;}
;

liste_dimensions: 
    une_dimension
    | liste_dimensions VIRGULE une_dimension {$$ = $1 * $3;}
;

une_dimension: CSTE_ENTIERE POINT_POINT CSTE_ENTIERE {$$ = $3 - $1 + 1; tRepTmp[tRepTmp[1] * 2 + 2] = $1; tRepTmp[tRepTmp[1] * 2 + 3] = $3; tRepTmp[1]++;}
;

liste_champs: 
    un_champ
    | liste_champs POINT_VIRGULE un_champ 
;

un_champ: 
    IDF DEUX_POINTS nom_type {tRepTmp[tRepTmp[0] * 3 + 1] = $1; /* numero lexico */
                            tRepTmp[tRepTmp[0] * 3 + 2] = $3; /* type */
                            ligneTableDecl($3, NULL, NULL, NULL, NULL, &tmp);
                            tRepTmp[tRepTmp[0] * 3 + 3] = tmp; /* taille */
                            tRepTmp[0]++;}
;

nom_type: 
    type_simple {$$ = $1;}
    | IDF {(((tmp1 = assoc_nom($1, TYPE_S)) == -1)? (tmp = assoc_nom($1, TYPE_T)): (tmp = tmp1));
            if (tmp == -1) {
                erreur_type_non_declare(numligne, $1); 
            }; 
            $$ = tmp;}
;

type_simple: 
    ENTIER {$$ = $1;}
    | REEL {$$ = $1;}
    | BOOLEEN {$$ = $1;}
    | CARACTERE {$$ = $1;}
    | CHAINE CROCHET_OUVRANT CSTE_ENTIERE CROCHET_FERMANT {$$ = $1;}
;

declaration_variable: 
    VARIABLE IDF DEUX_POINTS nom_type {inserer_declaration($2, VAR, getNumReg(), $4 /*a modifier*/, dx[getNumReg()] /* a verif */); ligneTableDecl($4, NULL, NULL, NULL, NULL, &exec_tmp); dx[getNumReg()] += exec_tmp;}
;

declaration_procedure: 
    PROCEDURE IDF {tmp_sommet_pile = sommetPileRegion(); nvRegion(); tRepTmp[0] = 0; inserer_region_nis(getNumReg(), getNis()); dx[getNumReg()] = getNis() + 1;} liste_parametres {inserer_declaration($2, PROC, tmp_sommet_pile, inserer_proc_tabRep(tRepTmp), getNumReg());} corps {inserer_region_arbre(getNumReg(), $$);sortieRegion();}
;

declaration_fonction: 
    FONCTION IDF {tmp_sommet_pile = sommetPileRegion(); nvRegion(); tRepTmp[0] = 0; inserer_region_nis(getNumReg(), getNis()); dx[getNumReg()] = getNis() + 1;} liste_parametres RETOURNE type_simple {inserer_declaration($2, FCT, tmp_sommet_pile, inserer_fonct_tabRep(tRepTmp, $6), getNumReg());} corps {inserer_region_arbre(getNumReg(), $$); sortieRegion();}
;

liste_parametres: 
    PARENTHESE_OUVRANTE PARENTHESE_FERMANTE
    | PARENTHESE_OUVRANTE liste_param PARENTHESE_FERMANTE
;

liste_param:
    un_param
    | liste_param POINT_VIRGULE un_param
;

un_param:
    IDF DEUX_POINTS type_simple {inserer_declaration($1, PARAM, getNumReg(), $3, dx[getNumReg()]);
                                tRepTmp[tRepTmp[0] * 2 + 1] = $1; /* numero lexico */
                                tRepTmp[tRepTmp[0] * 2 + 2] = $3; /* type */
                                dx[getNumReg()] += 1;
                                tRepTmp[0]++;}
;

instruction: 
    affectation {$$ = $1;}
    | condition {$$ = $1;}
    | tant_que {$$ = $1;}
    | appel {$$ = $1;}
    | VIDE {$$ = NULL;}
    | RETOURNE resultat_retourne {$$ = $2;}
    | instruction_ecriture {$$ = $1;}
    | instruction_lecture {$$ = $1;}
;

resultat_retourne:
    {$$ = NULL;}
    | expression {$$ = $1;}
;

appel: 
    IDF liste_arguments {num_decl_tmp1 = assoc_nom($1, PROC);
                        num_decl_tmp2 = assoc_nom($1, FCT);
                        ligneTableDecl(num_decl_tmp1, NULL, NULL, &num_reg_tmp1, NULL, NULL);
                        ligneTableDecl(num_decl_tmp2, NULL, NULL, &num_reg_tmp2, NULL, NULL);
                        num_lexico_tmp.entier = -1; 
                        if (getTabNis(num_reg_tmp1) > getTabNis(num_reg_tmp2)) {
                            $$ = concat_fils(creer_noeud(A_APPEL_PROC, num_lexico_tmp, -1), concat_fils(creer_noeud(A_LISTE_P, num_lexico_tmp, -1), $2));
                        } else {
                            $$ = concat_fils(creer_noeud(A_APPEL_FCT, num_lexico_tmp, -1), concat_fils(creer_noeud(A_LISTE_P, num_lexico_tmp, -1), $2));
                        }

                        }
;

liste_arguments:
    PARENTHESE_OUVRANTE PARENTHESE_FERMANTE {$$ = NULL;}
    | PARENTHESE_OUVRANTE liste_args PARENTHESE_FERMANTE {$$ = $2;}
;

liste_args: 
    un_arg {num_lexico_tmp.entier = -1; $$ = concat_frere($1, creer_noeud(A_LISTE_P, num_lexico_tmp, -1));}
    | liste_args VIRGULE un_arg {$$ = concat_fils($1, $3);}
;

un_arg: 
    expression {$$ = $1;}
;

condition: 
    SI expression_booleenne
    ALORS liste_instructions
    SINON liste_instructions {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_ITE, num_lexico_tmp, -1), concat_frere($2, concat_frere($4, $6)));}
    | SI expression_booleenne
    ALORS liste_instructions {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_ITE, num_lexico_tmp, -1), concat_frere($2, $4));}
;

tant_que:
    TANT_QUE expression_booleenne FAIRE liste_instructions {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_WHILE, num_lexico_tmp, -1), concat_frere($2, $4));}
;

affectation:
    variable OPAFF expression {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_OPAFF, num_lexico_tmp, -1), concat_frere($1, $3));}
;

variable: 
    IDF {num_lexico_tmp.entier = $1; $$ = creer_noeud(A_IDF, num_lexico_tmp, assoc_nom($1, VAR));}
    | variable POINT IDF {num_lexico_tmp.entier = -1; num_lexico_tmp2.entier = $3; $$ = concat_frere($1, concat_fils(creer_noeud(A_LISTE_CH, num_lexico_tmp, -1), concat_frere(creer_noeud(A_IDF, num_lexico_tmp2, assoc_nom($3, VAR)), creer_noeud(A_LISTE_CH, num_lexico_tmp, -1))));}
    | variable CROCHET_OUVRANT expression_arithmetique CROCHET_FERMANT {num_lexico_tmp.entier = -1; $$ = concat_frere($1, concat_fils(creer_noeud(A_LISTE_I, num_lexico_tmp, -1), concat_frere($3, creer_noeud(A_LISTE_I, num_lexico_tmp, -1))));}
;

expression:
    expression_arithmetique {$$ = $1;}
    | expression_booleenne {$$ = $1;}
;

expression_arithmetique:
    expression_arithmetique PLUS expression_arithmetique2 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_PLUS, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique MOINS expression_arithmetique2 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_MOINS, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique2 {$$ = $1;}
;

expression_arithmetique2:
    expression_arithmetique2 MULT expression_arithmetique3 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_MULT, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique2 DIV expression_arithmetique3 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_DIV, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique2 MODULO expression_arithmetique3 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_MODULO, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique3 {$$ = $1;}
;

expression_arithmetique3:
    PARENTHESE_OUVRANTE expression_arithmetique PARENTHESE_FERMANTE {$$ = $2;}
    | CSTE_ENTIERE {num_lexico_tmp.entier = $1; $$ = creer_noeud(A_CSTE_E, num_lexico_tmp, -1);}
    | CSTE_REEL {num_lexico_tmp.flottant = $1; $$ = creer_noeud(A_CSTE_F, num_lexico_tmp, -1);}
    | variable 
    | appel 
;

expression_booleenne:
    expression_booleenne OR expression_booleenne2 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_OR, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_booleenne2 {$$ = $1;}
;

expression_booleenne2: 
    expression_booleenne2 AND expression_booleenne3 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_AND, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_booleenne3 {$$ = $1;}
;

expression_booleenne3:
    NOT expression_booleenne4 {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_NOT, num_lexico_tmp, -1), $2);}
    | expression_booleenne4 {$$ = $1;}
;

expression_booleenne4:
    TRUE {num_lexico_tmp.entier = 1; $$ = creer_noeud(A_CSTE_B, num_lexico_tmp, -1);}
    | FALSE {num_lexico_tmp.entier = 0; $$ = creer_noeud(A_CSTE_B, num_lexico_tmp, -1);}
    | expression_comparaison {$$ = $1;}
    | PARENTHESE_OUVRANTE expression_booleenne PARENTHESE_FERMANTE {$$ = $2;}
;

expression_comparaison:
    expression_arithmetique INF expression_arithmetique {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_INF, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique SUP expression_arithmetique {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_SUP, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique INF_EGAL expression_arithmetique {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_INF_EGAL, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique SUP_EGAL expression_arithmetique {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_SUP_EGAL, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique DIFF expression_arithmetique {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_DIFF, num_lexico_tmp, -1), concat_frere($1, $3));}
    | expression_arithmetique EGAL expression_arithmetique {num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_EGAL, num_lexico_tmp, -1), concat_frere($1, $3));}
;


instruction_lecture: 
    LIRE PARENTHESE_OUVRANTE liste_variables PARENTHESE_FERMANTE
    {num_lexico_tmp.entier = -1;
        $$ = concat_fils(creer_noeud(A_LIRE,num_lexico_tmp,-1), $3);}/*faudra t'il faire une association_nom ?*/
;

liste_variables:
    variable {$$ = $1;}
    | liste_variables VIRGULE variable {$$ = concat_frere($3, $1);}
;

instruction_ecriture: 
    ECRIRE PARENTHESE_OUVRANTE format suite_ecriture PARENTHESE_FERMANTE

        {num_lexico_tmp.entier = -1;
        $$ = creer_noeud(A_ECRIRE,num_lexico_tmp,-1);

        if($4 != NULL){
            $$ = concat_fils($$, concat_frere($3, $4));
        }
        else{
            $$ = concat_fils($$, $3);
        }
        }
;
format:
    PHRASE {num_lexico_tmp.entier = -1; $$ = creer_noeud(LA_PHRASE /*a modifier*/ , num_lexico_tmp, -1); /*commment recup la valeur dans la table de declarations*/}
;
suite_ecriture:
    VIRGULE variable suite_ecriture { num_lexico_tmp.entier = -1; $$ = concat_fils(creer_noeud(A_LISTE_ARG, num_lexico_tmp, -1), concat_frere($2, $3));}
    | {$$ = NULL;}
;


%%
int yyerror() {
    printf("\033[%sm", "31"); /* Couleur rouge */
    printf("Erreur: ");
    printf("\033[%sm", "0"); /* Couleur defaut */
    printf("Erreur de syntax en ligne %d\n", numligne);
    return numligne;
}

void usage(char *s) {
    fprintf(stderr, "Usage : %s <nom_fichier>\n", s);
    return;
}

int main(int argc, char* argv[]) {
    int resyyparse;

    if (argc < 2) {
        fprintf(stderr, "Erreur : nombre d'arguments incorrecte\n");
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((yyin = fopen(argv[1],"r")) == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s\n", argv[1]);
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Initialisation des tables */
    init_tabLexico();
    init_tabDecl();
    init_tabRep();
    init_tabRegion();
    memset(dx, 0, N_TAB_REG_MAX * sizeof(int));

    /* Initialisation de la pile des régions */
    initPileRegion();

    resyyparse = yyparse();

    /* Affichage des tables */
    afficher_table_lexico();
    afficher_table_decl();
    afficher_table_rep();
    afficher_table_reg();

    /* Libération de la pile des régions */
    libererPileRegion();

    /* Tests */
    /*fprintf(stderr, "Sauvegarde...");
    sauvegarder("test.cpyrr");
    fprintf(stderr, "Fait\n");
    init_tabLexico();
    init_tabDecl();
    init_tabRep();
    afficher_table_lexico();
    afficher_table_decl();
    afficher_table_rep();
    fprintf(stderr, "Charge...");
    charger("test.cpyrr");
    fprintf(stderr, "Fait\n");
    afficher_table_lexico();
    afficher_table_decl();
    afficher_table_rep();*/

    return resyyparse;
}



