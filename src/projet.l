%{
/*extern int yylval;*/
#include "TAD_Arbre/arbre.h"
#include "y.tab.h"
#include "tabLexico.h"
int numligne=1;
%}
X [^"]
Y [^"*]
Z [^"*/]

%%
program {return(PROG);}
begin {return(DEBUT);}
end {return(FIN);}

if {return(SI);}
then {return(ALORS);}
else {return(SINON);}
while {return(TANT_QUE);}
do {return(FAIRE);}

procedure {return(PROCEDURE);}
function {return(FONCTION);}
return {return(RETOURNE);}

var {return(VARIABLE);}
type {return(TYPE);}
int {yylval.valeur=inserer_lexeme(yytext); return(ENTIER);}
float {yylval.valeur=inserer_lexeme(yytext); return(REEL);}
bool {yylval.valeur=inserer_lexeme(yytext); return(BOOLEEN);}
char {yylval.valeur=inserer_lexeme(yytext); return(CARACTERE);}
string {yylval.valeur=inserer_lexeme(yytext); return(CHAINE);}
of {return(DE);}
array {return(TABLEAU);}
struct {return(STRUCT);}
fstruct {return(FSTRUCT);}

true {return(TRUE);}
false {return(FALSE);}

vide {return(VIDE);}

read {return(LIRE);}
write {return(ECRIRE);}



; {return(POINT_VIRGULE);}
: {return(DEUX_POINTS);}
\( {return(PARENTHESE_OUVRANTE);}
\) {return(PARENTHESE_FERMANTE);}
, {return(VIRGULE);}
\[ {return(CROCHET_OUVRANT);}
\] {return(CROCHET_FERMANT);}
\.\. {return(POINT_POINT);}
\. {return(POINT);}



= {return(OPAFF);}

\+ {return(PLUS);}
- {return(MOINS);}
\* {return(MULT);}
\/ {return(DIV);}
\% {return(MODULO);}

\< {return(INF);}
\> {return(SUP);}
\<= {return(INF_EGAL);}
\>= {return(SUP_EGAL);}
\<\> {return(DIFF);}
== {return(EGAL);}

&& {return(AND);}
\|\| {return(OR);}
! {return(NOT);}



\n {numligne++;}



[a-zA-Z][a-zA-Z0-9]* {yylval.valeur = inserer_lexeme(yytext); return (IDF);}
0|[1-9][0-9]* {yylval.valeur = atoi(yytext); return(CSTE_ENTIERE);} 
([0-9]+([.][0-9]+)?) {yylval.valeurf = atof(yytext); return(CSTE_REEL); /* [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) */}
\/\*({Y}|\"{X}*\"|\*\**\"{X}*\"|\*\**{Z})*\*\**\/ {;}

\"[^\"]*\" {return(PHRASE);}



. ;



