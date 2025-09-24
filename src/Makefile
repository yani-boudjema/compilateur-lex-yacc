CC=gcc
#CFLAGS=-W -Wall -std=c89 -O2
CFLAGS=-W -Wall -O2
EXEC_FILES=projet debug #tabLexico


prod: projet 

all: $(EXEC_FILES)



debug: y.tab.c lex.yy.o tabLexico.o tabledecl.o pileRegion.o tabRegion.o TAD_Arbre/pile.o erreurs.o TAD_Arbre/arbre.o tabRep.o sauv.o 
	$(CC) -g $^ -ll $(CFLAGS) -o $@

projet: y.tab.c lex.yy.o tabLexico.o tabledecl.o pileRegion.o tabRegion.o TAD_Arbre/pile.o erreurs.o TAD_Arbre/arbre.o tabRep.o sauv.o 
	$(CC) $^ -ll $(CFLAGS) -o $@

lex.yy.c: projet.l 
	lex $< 

lex.yy.o: lex.yy.c y.tab.h
	$(CC) -c $< $(CFLAGS)

y.tab.c: projet.y 
	yacc -v -d $< 



#tabLexico: tabLexico.o tabLexico.h
#	$(CC) $< -o $@

tabLexico.o: tabLexico.c tabLexico.h
	$(CC) -c $< $(CFLAGS) -o $@



tabledecl.o: tabledecl.c tabledecl.h
	$(CC) -c $< $(CFLAGS) -o $@



pileRegion.o: pileRegion.c pileRegion.h
	$(CC) -c $< $(CFLAGS) -o $@



tabRegion.o: tabRegion.c tabRegion.h
	$(CC) -c $< $(CFLAGS) -o $@



tabRep.o: tabRep.c tabRep.h
	$(CC) -c $< $(CFLAGS) -o $@



erreurs.o: erreurs.c erreurs.h
	$(CC) -c $< $(CFLAGS) -o $@



sauv.o: sauv.c sauv.h
	$(CC) -c $< $(CFLAGS) -o $@



TAD_Arbre/arbre.o : TAD_Arbre/arbre.c TAD_Arbre/arbre.h TAD_Arbre/arbre_macros.h TAD_Arbre/pile.o
	$(CC) -c $< $(CFLAGS) -o $@

TAD_Arbre/pile.o : TAD_Arbre/pile.c TAD_Arbre/pile.h
	$(CC) -c $< $(CFLAGS) -o $@



.PHONY:clean

clean:
	rm -f *.o TAD_Arbre/*.o 
	rm -f lex.yy.c
	rm -f y.tab.c y.output y.tab.h
	rm -f *~ *.swp

.PHONY:mrproper

mrproper: clean
	rm -f $(EXEC_FILES)
	rm -f *.cpyrr 



