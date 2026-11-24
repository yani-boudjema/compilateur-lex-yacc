# Compilateur (Lex & Yacc)

Compilateur écrit en **C** avec **Lex** et **Yacc**, réalisé en Licence Informatique à l'Université Jean Monnet de Saint-Étienne.

## Fonctionnalités

- **Analyse lexicale** (`projet.l`) et **analyse syntaxique** (`projet.y`)
- **Tables** : table lexicographique, table des déclarations, table des régions, table des représentations
- **Arbre abstrait** et pile (`src/TAD_Arbre/`)
- **Gestion des erreurs** (`erreurs.c`) et sauvegarde des tables (`sauv.c`)

## Structure

```
src/
├── projet.l, projet.y        # grammaire Lex / Yacc
├── tabLexico.*, tabledecl.*  # tables lexicographique et des déclarations
├── tabRegion.*, pileRegion.* # régions et portée
├── tabRep.*                  # table des représentations
├── TAD_Arbre/                # arbre abstrait et pile
├── erreurs.*, sauv.*         # erreurs et sauvegarde
└── Makefile
fichiers_test/                # programmes de test (d1 à d9)
```

## Compilation

Prérequis : `gcc`, `lex` (ou `flex`) et `yacc` (ou `bison`).

```bash
cd src
make          # construit l'exécutable « projet »
make debug    # version avec symboles de débogage
```

## Tests

Les programmes d'exemple se trouvent dans `fichiers_test/` (déclarations, initialisation de tableau, factorielle, etc.).

## Auteur

Yani Boudjema — [LinkedIn](https://www.linkedin.com/in/yani-boudjema/)
