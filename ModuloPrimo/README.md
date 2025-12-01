### Integrazione orbite planetarie

In questo file verra' descritto il sistema di codici che integrano le orbite dei pianeti attorno alla propria stella per il Sistema Solare e il sistema Trappist-1. I codici integrano le orbite attraverso il metodo euleriano e successivamente attraverso il metodo Runge-Kutta 4.

#### Data files

I file dati sono organizzati in due: 'data\_SUN.txt' e 'data\_TRAP.txt'. In base alla massa della stella inserita da linea di comando il programma sceglie quale dei due file utilizzare, questo metodo è stato implementato con un if\&else perché i sistemi tra cui scegliere sono solo due, si può generalizzare per più sistemi per esempio con l'implementazione di un sistema di #ifdef che scelgono quali dati utilizzare in base alle indicazioni fornite durante la compilazione del codice.

Nel file dati sono stati inseriti anche i valori delle distanze dei pianeti dalla stella perché mi sembrava uno spreco avere un file di questo tipo e non sfruttarlo...

**Sono da rifare tutti in funzione della stella compilata e dei raggi. IDEA: usare un 'costanti.c' per mantenere le costanti inviolabili e fare un unico file per le posizioni dei pianeti in base alla stella compilata -> #ifdef sceglie quale tipo di pianeta deve essere ricercato. Si mantiene una ricerca non posizionale ma almeno non devo aggiungere troppe azioni a 'bintotxt.c'**

#### Makefile

Il Makefile permette di compilare separatamente "main_orbite.c" e lo script di traduzione "bintotxt.c". Alla fine dell'esecuzione del modulo l'opzione clean permette di pulire la cartella dai file in eccesso e mantenerla ordinata.

#### Header.h

Nell'header.h vengono incluse tutte le librerie utili ai codici, assieme alle costanti che però vorrei spostare in un file a parte per separarle dal resto.
'header.h' inizializza la struttura del pianeta in modo che ogni script possa recuperarla se necessario e inizializza anche le funzioni che verranno esplicitate in 'functions.c' ed utilizzate in 'main_orbite.c' .

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



#### Eulero.c



#### RK4.c





#### 

