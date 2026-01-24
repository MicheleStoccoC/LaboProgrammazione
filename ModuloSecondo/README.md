# Implementazione di un codice SPH 1D con Lagrangiana Adattiva

L’obiettivo e' scrivere un programma in C che realizza una simulazione Smoothed Particle Hydrodynamic unidimensionale per il caso test dello shock-tube. A differenza delle implementazioni standard a raggio fisso, in questo esercizio viene implementata una lunghezza di smoothing adattiva (hi) variabile per ogni particella in base alla densita' locale, e la ricerca dei vicini viene effettuata attraverso due metodi: QuickSearch e LinkedList.

Data la complessita' dell'esercizio i codici sono stati separati in due gruppi distinti: SPH_q* integrano il sistema attraverso un algoritmo Qsort mentre SPH_* attraverso LLsearch.

### Makefile

Il make file contiene tutte le regole per compilare ed eseguire la simulasione SPH e in seguito pulire la cartella dai file di testo e dalle immagini generate

>> make SPH_quick : compila ed esegue i codici SPH utilizzando la ricerca dei vicini tramite metodo quicksort. Con l'avvio dell'eseguibile la regola immette di default i parametri di input: Npt=4000 rateo=0.8 snap_step=3 .

>> make SPH_list : compila ed esegue i codici SPH utilizzando la ricerca dei vicini tramite metodo linked list. Con l'avvio dell'eseguibile la regola immette di default i parametri di input: Npt=4000 rateo=0.8 snap_step=3 .

>> make clean : elimina tutti gli eseguibili generati dal Makefile

>> make clean_snaps : elimina tutti i file di snapshot nella cartella, o in ogni caso qualsiasi file che inizi per snap*

>> make clean_gifs : elimina tutte le gif presenti nella cartella

## QuickSearch:

### SPH_qrutil

SPH_qrutil.h e SPH_qrutil.c rendono possibile l'utilizzo della libreria Numerical Recipes nei codici; ulteriormente SPH_qrutil.h è stato utilizzato come header generico della simulazione con quicksort, contiene quindi la definizione dei parametri globali, le strutture di cui tutti i codici avranno bisogno e l'inizializzazione di tutte le funzioni sviluppate.

### SPH_qmain

Il codice principale gestisce tutte le funzioni all'interno della simulazione: inizializza le variabili utili al programma e controlla che gli argomenti forniti da terminale siano adeguati. Alloca e successivamente libera la memoria, imposta le condizioni iniziali del sistema e gestisce l'avanzamento degli step temporali della simulazione. Il tutto mostrando la percentuale di avanzamento della simulazione, calcolando il tempo di simulazione e emettendo un segnale sonoro alla fine della simulazione.

Nota: a differenza dei codici PM-1D in questo caso il tempo di esecuzione (mantenuto sempre sotto il minuto) non rendeva necessario un avviso sonoro.

### SPH_qio

Il file gestisce le funzioni di output del sistema e l'impostazione delle condizioni iniziali.

set_IC imposta le condizioni iniziali: inizialmente la lunghezza di smoothing era settata su un valore che tentava di permettere alla particella di osservare 64 particelle vicine, oguna delle quali distribuite uniformemente; questo metodo era fallimentare perche' sovrastimava enormemente la capacita' di interazione a lunga distanza delle particelle. Dopo svariate prove e' stato optato per un valore di h di default molto piccolo e indipendente dai parametri del sistema. In ogni caso il tentativo fallito e' rimasto commentato.

Le funzioni snap_* scrivono (o sovrascrivono) lo step temporale inserito su dei file binari in modo da occupare meno memoria possibile. Stara' al programma python smatassare le infomazioni nei diversi snapshot. 

### SPH_qphys

Il file di codice gestisce tutte le funzioni utili a descrivere la fisica del sistema: calcolo delle distanze, il kernel, viscosita', tassi di cambiamento, densita', pressione, aggiornamento del passo temporale e la procedura di kick-drift-kick.

Le varie funzioni controllano che le quantita' rimangano fisiche (u>0, P>0, ...) e stabiliscono delle condizioni al contorno.

> Nota: Contrariamente dal codice PM-1D il tubo non e' periodico ma possiede delle pareti rigide. La funzione distanza cercava di applicare ancora le PBC ma cio' generava problemi ai margini, percio' sono state commentate ed escluse. KDK invece ha reso necessaria l'implementazione degli urti elastici: un tubo rigido in cui le particelle si muovono senza conseguenze permette l'accumulo di queste ultime ai margini del sistema inficiando tutti i risultati, aggiungendo la possibilita' di urti elastici con le pareti le particelle al posto di schiantarsi anelasticamente rimbalzano e "tornano indietro".

### SPH_quicksearch

Il metodo quicksort ricerca i vicini delle particelle brutalmente andando a controllare particella per particella quali sono i rispettivi vicini, attraverso la funzione qsort l'array di particelle viene riordinato in funzione della distanza dalla particella in esame; nella procedura e' implementato un controllo sul numero di vicini minimo da trovare (64) e sulla distanza massima che questi possono avere (0.5*L). 

Alla fine viene applicato l'adattamento di h in funzione del vicino piu' vicino.

> Nota: in questo caso mantenere il numero di vicini pari a 64 non comporta grossi problemi.

###

## ListSearch:

### SPH_rutil

SPH_rutil.h e SPH_rutil.c rendono possibile l'utilizzo della libreria Numerical Recipes nei codici; ulteriormente SPH_rutil.h è stato utilizzato come header generico della simulazione con quicksort, contiene quindi la definizione dei parametri globali, le strutture di cui tutti i codici avranno bisogno e l'inizializzazione di tutte le funzioni sviluppate.

### SPH_main

Il codice principale gestisce tutte le funzioni all'interno della simulazione: inizializza le variabili utili al programma e controlla che gli argomenti forniti da terminale siano adeguati. Alloca e successivamente libera la memoria, imposta le condizioni iniziali del sistema e gestisce l'avanzamento degli step temporali della simulazione. Il tutto mostrando la percentuale di avanzamento della simulazione, calcolando il tempo di simulazione e emettendo un segnale sonoro alla fine della simulazione.

Nota: a differenza dei codici PM-1D in questo caso il tempo di esecuzione (mantenuto sempre sotto il minuto) non rendeva necessario un avviso sonoro.

### SPH_io

Il file gestisce le funzioni di output del sistema e l'impostazione delle condizioni iniziali.

set_IC imposta le condizioni iniziali: anche in questo caso, inizialmente la lunghezza di smoothing era settata su un valore che tentava di permettere alla particella di osservare 64 particelle vicine, oguna delle quali distribuite uniformemente; questo metodo era fallimentare perche' sovrastimava enormemente la capacita' di interazione a lunga distanza delle particelle. Dopo svariate prove e' stato optato per un valore di h di default molto piccolo e indipendente dai parametri del sistema. In ogni caso il tentativo fallito e' rimasto commentato.

Le funzioni snap_* scrivono (o sovrascrivono) lo step temporale inserito su dei file binari in modo da occupare meno memoria possibile. Starà al programma python smatassare le infomazioni nei diversi snapshot.

### SPH_phys

Il file di codice gestisce tutte le funzioni utili a descrivere la fisica del sistema: calcolo delle distanze, il kernel, viscosita', tassi di cambiamento, densita', pressione, aggiornamento del passo temporale e la procedura di kick-drift-kick.

Le varie funzioni controllano che le quantita' rimangano fisiche (u>0, P>0, ...) e stabiliscono delle condizioni al contorno.

> Nota: Contrariamente dal codice PM-1D il tubo non e' periodico ma possiede delle pareti rigide. La funzione distanza cercava di applicare ancora le PBC ma ciò generava problemi ai margini percui sono state commentate ed escluse. KDK invece ha reso necessaria l'implementazione degli urti elastici: un tubo rigido in cui le particelle si muovono senza conseguenze permette l'accumulo di queste ultime ai margini del sistema inficiando tutti i risultati, aggiungendo la possibilita' di urti elastici con le pareti le particelle al posto di schiantarsi sulle pareti rimbalzano e "tornano indietro".

### SPH_listsearch

Il metodo linked list tenta la ricerca dei vicini delle particelle con un approccio più efficiente: il tubo viene suddiviso in una griglia di celle tale per cui i vicini di una particella posso trovarsi unicamente nelle celle adiacenti, in questo modo la ricerca dei vicini viene effettteuta su molte meno particelle (e percio' molti meno cicli); nella procedura e' implementato un controllo sul numero di vicini minimo da trovare (110). Per evitare di lavorare con strutture troppo grandi viene definita "Pair" (che contiene la distanza e l'indice della particella) e delle funzioni dedicate ce possono operare su di essa.

Alla fine viene applicato l'adattamento di h in funzione del vicino piu' vicino.

> Nota: in questo caso mantenere il numero di vicini pari a 64 comporta grossi problemi nella fisica del sistema: a quanto pare il sistema listsearch con solo 64 particelle non riesce a descrivere adeguatamente le interazioni tra le particelle generando delle situazioni estremamente caotiche; aumentando il numero minimo di vicini a 110 invece il sistema riproduce dei grafici piu' che accettabili.

###

## Graficatura

### Plot.py

Il codice genera le gif che mostrano l'evoluzione temporale di densita', pressione, energia, velocita' (in aggiunta anche accelerazione e lunghezza di smoothing) lungo il tubo per vedere lo shock dell'onda d'urto.

AVVERTENZA: ricordarsi di cambiare la regola True/False all'inizio del codice in funzione della simulazione eseguita altrimenti vengono generati grrafici senza alcun senso fisico!

## Altre note, varie ed eventuali

#### Grafici ottenuti

Nella cartella sono presenti anche le gif delle evoluzioni temporali delle quantita' più importanti fatte tramite linked list (evol_LL*) e quicksort (evol_QS*).

#### Considerazioni a posteriori

Nota1: Contrariamente alle aspettative il metodo linked list viene eseguito molto piu' lentamente: e' tra le 5 e le 8 volte piu' lento. La spiegazione plausibile che mi sono dato e' che il metodo diventi veramente piu' efficiente nei casi multidimentsionali mentre in 1D la procedura impegna il codice piu' di quanto necessario.

Nota2: Troppo tardi mi sono reso conto che effettivamente i codici dei due metodi sono quasi identici e che per avere meno ingombro e piu' ordine nella cartella si possono riunire in un unico set di codici per entrambi e dividere le differenze attraverso l'implementazione di un #ifdef in fase di compilazione (o di una scelta da label come fatto nel codice BisecWPointers.c).