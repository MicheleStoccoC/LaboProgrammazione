### Integrazione orbite planetarie

In questo file verra' descritto il sistema di codici che integrano le orbite dei pianeti attorno alla propria stella per il Sistema Solare e il sistema Trappist-1. I codici integrano le orbite attraverso il metodo euleriano.

#### Data files

Il file "DATA.txt" riporti i dati relativi alle distanze dei vari pianeti rispetto alla stella di riferimento (Sole o Trappist). Il file è stato scritto in modo da consentire una ricerca non posizionale da parte dello script. In base alla compilazione dei file *.c il programma ricrcherà i dati per il Sole o per Trappist. Inserendo le distanze in un file queste vengono gestite più facilmente senza rischiare di scriverle errate durante l'inserimento da terminale. 

#### Makefile

Il Makefile permette di compilare separatamente "main_orbite.c" e lo script di traduzione "bintotxt.c". Alla fine dell'esecuzione del modulo la regola 'clean' permette di pulire la cartella dai file in eccesso e mantenerla ordinata.

Come assicurazione sulla compilazione Gemini-AI ha consigliato di aggiungere la flag '-std=c99' in modo che i file vengano sempre compilati con una versione che supporta tutte le librerie utilizzate.

'Makefile' possiede due regole principali che permettono di compilare 'main_orbite.c' assieme a 'functions.c' in modo che integrino le orbite per il sistema solare e per il sistema di Trappist; questo perché all'interno dei file sono presenti degli '#ifdef'. Oltre a ciò possiede la regola per compilare il file 'bintotxt.c' (traduttore binario->testo).

#### Header.h

Nell'header.h' vengono incluse tutte le librerie utili ai codici e vengono definite le costanti matematiche.
'header.h' inoltre inizializza le costanti esterne relative all'astrofisica (che verranno assegnate nel file 'costanti.c'), la struttura del pianeta in modo che ogni script possa recuperarla se necessario e inizializza anche le funzioni che verranno esplicitate in 'functions.c' ed utilizzate in 'main_orbite.c' .

Gemini-AI ha consigliato di inserire una "Include Guard" di protezione nel caso il modulo dovesse utilizzare più file header linkati tra loro, di modo che il contenuto del file sia letto e processato dal compilatore una sola volta, indipendentemente da quante volte quel file venga referenziato tramite '#include'. Procedura che per ora non è necessaria ma che si può rivelare utile se si vorranno aggiungere nuovi metodi di integrazione delle orbite (e.g. RK4).

#### Costanti.c

Mi sembrava sprecato utilizzare le costanti astrofisiche come delle variabili, per questo al posto di inserirle in un file testo che necessitava una ricerca non posizionale le ho messe in un file compilabile che assegna i loro valori come costanti esterne (inizializzate nel header). In ogni caso il file mantiene la versatilità precedente di poter essere modificato a piacimento con l'unico accorgimento di ricordarsi di inizializzare le variabili globali nel header e poi assegnarle qui.

#### Functions.c

In 'functions.c' vengono esplicitate tutte le funzioni che servono ad integrare le orbite dei pianeti tramite il metodo di Eulero.

find_data: legge il file .txt alla ricerca dei valori associati ad una label specificata con la chiamata

pianeta assegnazione:

pianeta components:

pianeta printPlanet:

pianeta transcribe:

eulero: 

#### Main.c

SOLE

>> ./main_sun 2.0e30 4 0.001

TRAPPIST

>> ./main_trap 1.796e29 4 0.00001



#### Bintotxt.c

Dopo la compilazione, il codice va eseguito fornendo da terminale il numero (N) di pianeti che sono stati simulati e il numero (M) di salti che deve fare prima di leggere la riga successiva. Il programma legge i file '.bin' e da essi genera N file omologhi '.txt'  con 1/M valori che potranno essere utilizzati nel codice plot.py .

e.g.

>> ./bin2txt 4 9



#### Plot.py




#### 

