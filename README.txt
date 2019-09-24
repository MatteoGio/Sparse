=========================================================================
ISTRUZIONI e SPECIFICHE per il primo frammento 2015/16
========================================================================
Il progetto prevede lo sviluppo di un programma/insieme di funzioni che lavorano su matrici sparse

------------------------------------------------
Estrarre il materiale dal KIT
------------------------------------------------
Creare una directory temporanea, copiare kit_f1.tar
nella directory e spostarsi nella directory appena creata. Es.

$$ mkdir Progetto
$$ mv kit_f1.tar Progetto
$$ cd Progetto

S-tarare i file del kit con

$$ tar xvf kit_f1.tar

questo comando crea nella directory corrente una directory "SPARSE" con i seguenti file

$$ ls SPARSE
sparse.h		: file che contiene la definizione del tipo di dato
			"matrici sparse" ed i prototipi di alcune funzioni
 			da realizzare (NON MODIFICARE)

sparse_docenti.c	: file che contiene l'implementazioni della
                        funzione di stampa fornita dai docenti
 			(NON MODIFICARE)

test-*.c
Makefile
			: programmi di test e Makefile per i test e
                        la consegna
			(NON MODIFICARE se non nelle parti indicate)

DATI/*			: file di dati da elaborare e risultati attesi
                          per i test (NON MODIFICARE)

README.txt		  : questo file
README.doxygen		  : informazioni sul dformato doxygen dei commenti
                            alle funzioni (FACOLTATIVO)

gruppo-check.pl		: uno script Perl che controlla il formato del file
			  gruppo.txt prima di effettuare la consegna
			  (NON MODIFICARE)

gruppo.txt		: un file di esempio di specifica del gruppo
			  (massimo 2 studenti per gruppo)
			  (deve essere aggiornato con i dati di chi consegna,
			  secondo il formato esemplificato)

========================================================================
ISTRUZIONI per la realizzazione
========================================================================

Il progetto prevede la realizzazione di un insieme di funzioni C che
lavorano su matrici sparse di double. Si intendono "sparse" la matrici che
contengo una bassissima percentuale di elementi diversi da 0. Queste
matrici vengono solitamente rappresentate registrando solo gli
elementi diversi da 0 e la loro posizione.
Nel nostro caso utilizzeremo un array di puntatori a righe che
contiene NULL se la riga contiene tutti valori uguali a zero o la
lista delle colonne e dei valori diversi da zero.

Ad esempio la matrice

3.1  0   0   0
 0   0   0   0
 0  7.2  0  9.0

è rappresentata come

0 | ------>([0,3.1] , NULL)
1 | NULL
2 | ------>([1,7.2] , --)-->( [3,9.0] ,NULL)

Le strutture dati da utilizzare per la realizzazione delle matrici sparse
e i prototipi delle funzioni da implementare sono definiti nel file
sparse.h.
Consigliamo di leggere accuratamente sparse.h prima di proseguire.


L'implementazione della funzione di stampa e' fornita nel file
sparse_docenti.c.

Le funzioni definite in sparse.h possono essere implementate in un
unico file "sparse.c".  Se si vogliono usare piu' file si deve
modificare il Makefile in modo che la compilazione avvenga
automaticamente in modo corretto e tutti i file sviluppati vengano
consegnati nel tar finale.

I commenti in sparse.h spiegano in dettaglio il comportamento delle
varie funzioni, il significato dei parametri ed i valori restituiti
secondo il formato Doxygen (chi e' interessato puo' leggere
README.doxygen per i dettagli).

Conviene testare le funzioni man mano che vengono sviluppate con dei
main() di test evitando di scrivere tutto il codice prima di testarne
il funzionamento.
Questo permette di localizzare molto meglio errori ed anomalie.
Solo quando siamo ragionevolmente convinti della correttezza del
codice si puo' passare al testing automatico del codice con i test
forniti dai docenti.

------------------
Come procedere :
-----------------

1) leggere attentamente le specifiche e capire il funzionamento il codice di test
   fornito dai docenti

2) implementare le funzioni richieste ed effettuare testing
   preliminare utilizzando programmi sviluppati allo scopo

3) testare il software con i test forniti dai
  docenti.

       bash:~$ make test1
       bash:~$ make test2
       bash:~$ make test3
       bash:~$ make test4

  NOTA: (1) il file sparse.c si deve trovare nella directory SPARSE
  (2) E' importante che il test fornito dai docenti venga effettuato solo su
  un programma gia' funzionante e testato altrimenti i risultati
  possono essere di difficile interpretazione, fuorvianti o inutili.


4) preparare la documentazione: ovvero commentare adeguatamente il/i file che
   contengono la soluzione  ed inserire un' intestazione contenente il nome
   dello sviluppatore ed una dichiarazione di originalita'

   /** \file pippo.c
       \author Giuseppe Garibaldi 456789 & Nino Bixio 123456
     Si dichiara che il contenuto di questo file e' in ogni sua parte opera
     originale degli autori.  */


5) aggiornare il file "gruppo.txt" con nomi e dati

6) inserire nel makefile il nome dei file da consegnare (se e' stato utilizzato solo sparse.c e' gia' corretto)
   (variabile FILE_DA_CONSEGNARE)

8) consegnare il file ESCLUSIVAMENTE eseguendo

      bash:~$ make consegna

   e seguendo le istruzioni.
   Il target consegna crea un file tar che deve essere inviato
   all'indirizzo lso.di@listgateway.unipi.it

   "sol1516: consegna primo frammento"

   Tutte le consegne verranno confermate con un messaggio entro 2/3
   giorni all'indirizzo da cui e' stata effettuata la consegna. In
   caso questo non si verifichi contattare il docente.


---------------------------------------
 NOTE IMPORTANTI: LEGGERE ATTENTAMENTE
---------------------------------------

1) gli eleborati contenenti tar non creati con "make consegna" o
   comunque seguendo le istruzioni riportate sopra non verranno
   accettati (gli studenti sono invitati a controllare che il tar
   contenga tutti i file richiesti sopra con il
   comando " tar tvf nomefiletar " prima di inviare il file)

2) tutti gli elaborati verranno confrontati fra di loro con tool automatici
   per stabilire eventuali situazioni di PLAGIO. Se gli elaborato sono
   ragionevolmente simili verranno scartati.

3) Chi in sede di orale risulta palesemente non essere l'autore del software
   consegnato dovra' ricominicare da zero con un altro progetto

4) Tutti i comportamenti scorretti ai punti 2 e 3 verranno segnalati
   ufficialmente al presidente del corso di laurea


