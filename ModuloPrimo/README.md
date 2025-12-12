### Integrazione orbite planetarie

In questo file verra' descritto il sistema di codici che integrano le orbite dei pianeti attorno alla propria stella per il Sistema Solare e il sistema Trappist-1. I codici integrano le orbite attraverso il metodo euleriano.

#### Data files

Il file "DATA.txt" riporta i dati relativi alle distanze dei vari pianeti rispetto alla stella di riferimento (Sole o Trappist). Il file è stato scritto in modo da consentire una ricerca non posizionale da parte dello script. In base alla compilazione dei file *.c il programma ricrcherà i dati per il Sole o per Trappist. Inserendo le distanze in un file queste vengono gestite più facilmente senza rischiare di scriverle errate durante l'inserimento da terminale. 

#### Makefile

Il Makefile permette di compilare separatamente "main_orbite.c" e lo script di traduzione "bintotxt.c". Alla fine dell'esecuzione del modulo la regola 'clean' permette di pulire la cartella dai file in eccesso e mantenerla ordinata.

Come assicurazione sulla compilazione Gemini-AI ha consigliato di aggiungere la flag '-std=c99' in modo che i file vengano sempre compilati con una versione che supporta tutte le librerie utilizzate.

'Makefile' possiede due regole principali che permettono di compilare 'main_orbite.c' assieme a 'functions.c' in modo che integrino le orbite per il sistema solare e per il sistema di Trappist; questo perché all'interno dei file sono presenti degli '#ifndef'. Oltre a ciò possiede la regola per compilare il file 'bintotxt.c' (traduttore binario->testo).

#### Header.h

Nell'header.h' vengono incluse tutte le librerie utili ai codici e vengono definite le costanti matematiche.
'header.h' inoltre inizializza le costanti esterne relative all'astrofisica (che verranno assegnate nel file 'costanti.c'), la struttura del pianeta in modo che ogni script possa recuperarla se necessario e inizializza anche le funzioni che verranno esplicitate in 'functions.c' ed utilizzate in 'main_orbite.c' .

Gemini-AI ha consigliato di inserire una "Include Guard" di protezione nel caso il modulo dovesse utilizzare più file header linkati tra loro, di modo che il contenuto del file sia letto e processato dal compilatore una sola volta indipendentemente da quante volte quel file venga referenziato tramite '#include'. Procedura che per ora non è necessaria ma che si può rivelare utile se si vorranno aggiungere nuovi metodi di integrazione delle orbite (e.g. RK4).

#### Costanti.c

Mi sembrava sprecato utilizzare le costanti astrofisiche come delle variabili, per questo al posto di inserirle in un file testo che necessitava una ricerca non posizionale le ho messe in un file compilabile che assegna i loro valori come costanti esterne (inizializzate nel header). In ogni caso il file mantiene la versatilità precedente di poter essere modificato a piacimento con l'unico accorgimento di ricordarsi di inizializzare le variabili globali nel header e poi assegnarle qui.

#### Functions.c

In 'functions.c' vengono esplicitate tutte le funzioni che servono ad integrare le orbite dei pianeti tramite il metodo di Eulero.

find_data: legge il file .txt alla ricerca dei valori associati ad una label specificata con la chiamata; in questo modo è possibile leggere il file in maniera non posizionale.

pianeta assegnazione: funzione associata alla struttura pianeta; fa utilizzo di 'find_data' per trovare le distanze di partenza dei pianeti nel file 'DATA.txt' e assegnare le condizioni iniziali al sistema; in base alle opzioni di compilazione la funzione presenta un '#ifndef' che distingue il caso di Trappist da quello del Sole.	Nota: questa distinzione poteva essere applicata in fase di esecuzione anziché in compilazione, in funzione della massa stellare fornita da terminale il 'main_orbite.c' avrebbe assegnato (attraverso un 'if&else') una diversa stringa di caratteri da fornire come label alle funzioni che la richiedevano. 

pianeta components: funzione associata alla struttura pianeta: a partire dai moduli di velocità e accelerazione definisce le loro componenti. Viene usata una sola volta in 'assegnazione' ma rimane distinta perché può tornare utile.

pianeta printPlanet: funzione associata alla struttura pianeta; veniva utilizzata in fase di test per stampare a schermo i valori della struttura in modo da verificare il corretto funzionamento dello script.

pianeta transcribe: funzione associata alla struttura pianeta; trascrive gli attuali valori della struttura in un file binario. Dato che 'pianeta' contiene troppi valori, la funzione si avvale di un array temporaneo in cui tenere solo i valori necessari e poi da esso trascriverli nel file binario.

eulero: applica il processo di avanzamento del pianeta, sposta l'oggetto in funzione della sua velocità e ricalcola il raggio, modifica l'accelerazione in funzione delle nuove coordinate e da essa ricava il nuovo valore della velocità da applicare allo step successivo. Alla fine il processo trascrive i valori aggiornati della struttura pianeta avvalendosi della funzione dedicata: 'transcribe'.

#### Main.c

SOLE

>> ./main_sun 2.0e30 4 0.001

TRAPPIST

>> ./main_trap 1.796e29 4 0.00001



#### Bintotxt.c

Dopo la compilazione, il codice va eseguito fornendo da terminale il numero (N) di pianeti che sono stati simulati e il numero (M) di salti che deve fare prima di leggere la riga successiva. Il programma legge i file '.bin' e da essi genera N file omologhi '.txt'  con 1/M valori che potranno essere utilizzati nel codice plot.py . 

e.g. scrivere una riga ogni 10:

>> ./bin2txt 4 9

#### Plot.py

'plot.py' è uno script python che permette di graficare le orbite dei pianeti appena simulate, leggendo i file .txt generati da 'bin2txt'. Nello script è presente anche una parte dedicata a graficare le componenti della velocità del pianeta 3 (la Terra nel caso solare) per verificarne gli andamenti sinusoidali. Nota: nel caso le immagini generate venissero salvate queste non saranno rimosse dalla procedura 'make clean'.

#### 

