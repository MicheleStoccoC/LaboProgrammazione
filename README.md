# LaboProgrammazione

In questa cartella verranno caricati gli esercizi e i moduli d'esame del corso "Laboratorio di Programmazione Avanzata per l'Astrofisica".

## IntegrazioneEqD

La cartella contiene gli esecizi di integrazione delle equazioni differenziali con le librerie e i codici in grado di integrare attraverso metodo Runge&Kutta4 e TimeStep Adattivo. La cartella contiene un Makefile per eseguire il tutto più semplicemente.

### Makefile

Qui sono esplicitate le regole per la compilazione l'esecuzione e pulizia dei file nella cartella.

>> make DensityM : compila ed esegue Density_midpoint.c con densita' esponenziale

>> make DensityMC : compila ed esegue Density_midpoint.c con densita' parabolica

>> make DensityA : compila ed esegue Density_adaptive.c con densita' esponenziale

>> make DensityAC : compila ed esegue Density_adaptive.c con densita' parabolica

>> make Friedmann : compila ed esegue Friedmann.c con i dovuti argomenti

>> make clean : pulisce la cartella da tutti gli eseguibili generati da questo Makefile

>> make clean_txt : pulisce la cartella da tutti i file *.txt presenti

>> make clean_png : pulisce la cartella da tutte le immagini con estensione .png e .jpg

### Density_adaptive

Utilizzando la libreria Numerical Recepies e gli script forniti nella cartella github del corso, integra la densita' di stelle in una nube di gas in fase di starformation utilizzando un time-step adattivo. Genera un file di testo con i risultati dell'integrazione e i valori della soluzione analitica.

Nota: per ora la soluzione analitica (parabola) vale solo per il caso RHO costante, in quanto nell'altro caso essa sarebbe rappresentata da una curva esponenziale; il codice puo' essere modificato aggiungendo un'altra procedura 'ifdef' che definisce la funzione 'exact' in base agli argomenti forniti durante la compilazione.

### Density_midpoint

Utilizzando una funzione ricorsiva integra la densita' di stelle in una nube di gas in fase di starformation utilizzando il metodo midpoint e time-step fissato. Genera un file di testo con i risultati dell'integrazione e i valori della soluzione analitica.

Nota: come sopra, per ora la soluzione analitica (parabola) vale solo per il caso RHO costante, in quanto nell'altro caso essa sarebbe rappresentata da una curva esponenziale; il codice puo' essere modificato con una procedura 'ifdef' che definisce la funzione 'exact' in base agli argomenti forniti durante la compilazione.

### Friedmann2

Il codice integra la seconda equazione di Friedmann utilizzando due metodi: una funzione esterna con metodo midpoint e la libreria Numerical Recepies con i dovuti codici esterni (odeint.c, rkck.c, rkqs.c) per utilizzare un time-step adattivo. Nella parte di integrazione tramite midpoint non è stata utilizzata una funzione ricorsiva interna al codice ma e' stato ritenuto piu' adeguato implementare un file esterno con una procedura di midpoint più generica.

Il codice fornisce anche un confronto tra le velocità di integrazione del sistema dei due metodi: il midpoint risulta essere estremamente piu' lento con tempi di integrazione che in alcuni casi sono c/a 20 volte superiori all'altro (per quanto entrambi girino in brevi frazioni di secondo).

### InkDiffusion

Il codice integra nel tempo l'equazione differenziale di una goccia di inchiostro che si diffonde in una dimensione spaziale. Viene utilizzato il metodo adaptive time-step gestito da odeint.c 

### Plot*.py

I tre codici graficano i dati trascritti sui file .txt

## ModuloPrimo

La cartella contiene i files relativi allo svolgimento dell'esercizio del primo modulo d'esame: Integrazione delle orbite planetarie attorno al Sole e a Trappist. (README dettagliato all'interno della cartella)

## ModuloSecondo

La cartella contiene i files relativi allo svolgimento dell'esercizio del secondo modulo d'esame: Esecuzione di una simulazione SPH 1D con lunghezza di smoothing adattiva e ricerca di vicini tramite Qsort e LinkedList. (README dettagliato all'interno della cartella)

## ParticleMesh1D

La cartella contiene i files relativi ad una simulazione di un sistema di particelle autogravitanti in una dimensione.

### Makefile

Il file contiene le regole per compilare ed eseguire la simulazione PM-1D con tre kernel differenti: NearestGridPoint (NGP), CloudInCell (CIC), TriangularShapeCloud (TSC).

>> make ngp : compila main_pm.c e gli altri files con kernel NGP. Successivamente sara' necessaria l'esecuzione del programma tramite il comando " ./1dpm_ngp t_fin steps T m " (generalmente vengono usati 200. 2000 1. 1. ).

>> make tsc : compila main_pm.c e gli altri files con kernel TSC. Successivamente sara' necessaria l'esecuzione del programma tramite il comando " ./1dpm_tsc t_fin steps T m " (generalmente vengono usati 200. 2000 1. 1. ).

>> make cic : compila main_pm.c e gli altri files con kernel CIC. Successivamente sara' necessaria l'esecuzione del programma tramite il comando " ./1dpm_cic t_fin steps T m " (generalmente vengono usati 200. 2000 1. 1. ).

>> make clean : pulisce la crtella da tutti i file creati dalle regole del Makefile. Nota: file di testo e immagini rimangono e in caso devono essere rimossi manualmente.

### Header

Come nel caso del primo modulo, header.h possiede una include guard. Successivamente sono dichiarate tutte le variabili globali e le funzioni utilizzate dai file di codice.

### Main

Il main_pm.c contiene la procedura principale di definizione delle condizioni iniziali, inizializzazione della procedura di fourier e attuazione della procedura di avanzamento della simulazione; cosi' come la scrittura su file e la liberazione della memoria. Le righe 10,16,109-117 contengono la procedura che implementa il time-step adattivo nel caso la si voglia attivare.

Nota1: le righe 136,137 contengono il comando che annuncia con un segnale sonoro il momento in cui il programma termina tutte le procedure; e'stato aggiunto perche' inizialmente l'esecuzione era molto lenta. Feature simpatica che e' stata aggiunta anche nei codici del secondo modulo anche se non per lo stesso motivo.

### Functions

In functions.c sono implementate tutte le funzioni utili all'esecuzione della simulazione: dalla definizione dei kernel alla procedura di fourier, alle equazioni che integrano la fisica del sistema.

### Parameters

In parameters.c vengono definiti i parametri globali del sistema: le unita' di misura con cui lavora il sistema e i parametri che caratterizzano la scatola con la rispettiva griglia.

### Plot

plot.py genera una gif che mostra l'evoluzione temporale della densita' delle particelle nella griglia e l'evoluzione temporale dello spazio delle fasi.

## Altri Codici

### Bisec_Variabile

Il codice implementa l'algoritmo di bisezione per trovare un punto di minimo tra funzioni con argomenti variabili. Questo codice e' l'evoluzione di un algoritmo sviluppato in precedenza che non supportava gli argomenti variabili: può essere riesumato "attivando" le funzioni commentate e commentando il codice attuale.

Da comando possono essere scelte tre equazioni da sottoporre alla procedura di bisezione: 'quad','cube','trascI' e 'trascII'

e.g.

>> ./file funzione p q r

>> ./bisec quad -1 2 1

>> ./bisec trascI  

### BisecWPointers

Se non si vuole riesumare il codice decommentando gli elementi da Bisec_Variabile.c si può usare direttamente questo che è la versione precedente.

### Cerchi_e_Strutture

Il codice genera attraverso la definizione di una struttura "point" due set di punti con coordinare casuali all'interno di due sfere di raggio fissato. I punti generati sono scritti su due file differenti il cui nome viene definito in base alle caratteristiche dei cerchi generati. L'eseguibile ha bisogno di 4 parametri per funzionare: raggio della prima sfera e numero di punti da generare (N,r1) e raggio della seconda sfera con rispettivo numero di punti da generarci dentro (M, r2). (./exe N M r1 r2)

La generazione del punto casuale e' affidata ad una funzione associata alla struttura "point".

e.g.

>> ./sphere 500 10000 20 75

### LinkedList

File nato come un primo manuale di istruzioni alle liste linkate (argomento nuovo) e poi si e' evoluto nell'esercizio di inserimento di un nuovo elemento nella lista in un punto specifico.

### Pi_finder

Il file calcola approssimativamente il valore del pi greco utilizzando la generazione di numeri casuali all'interno di un quadrato di lato 2 centrato in O=(0;0) e confrontando quanti di questi cadono anche dentro il cerchio inscritto nel quadrato. Nel file sono appuntati i risultati fatti con diverso numero di punti generati.

### Prova_Parabola

Prova parabola implementa la soluzione analitica delle equazioni di secondo grado e trova le radici in funzione dei parametri della parabola (da inserire manualmente durante l'esecuzione).

### Prova_ricorsione

Prova ricorsione calcola il fattoriale di un numero intero attraverso l'implementazione di una funzione ricorsiva.

### RadiciExp

Il programma implementa due algoritmi per la ricerca del minimo di una funzione, Bisezione e Newton, e ne confronta i risultati. Il codice implementa per la prima volta un "#ifdef" che permette di testare il codice su una funzione con punto di minimo conosciuto in modo da verificarne l'efficacia.

### Random_e_Cerchi

Il codice genera N punti casuali in una sfera di raggio r in coordinate polari utilizzando una struttura point e mantenendo il raggio dei punti con distribuzione lineare. In fase di compilazione si puo' decidere di eseguire lo stesso programma ma su una sfera 3D in coordinate polari.

L'intero esercizio è ripetuto generando il raggio con distribuzione uniforme.

Viene scritto un file per entrambe le distribuzioni.

e.g. di compilazione

>> gcc Random_e_Cerchi.c -DTHREE_DIM  -Wall -lm -o cerchi3d

>> gcc Random_e_Cerchi.c -Wall -lm -o cerchi

## Note varie ed eventuali:
