#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* define: metodo per memorizzare le definizioni
 in fase di compilazione tutte le volte che verra' incontrata
 la variabile MAXWORD, al suo posto verra' automaticamente scritto
 100
*/
#define MAXWORD 100

// Struttura del nodo dell'albero
struct tnode {
    char *word;             // La parola
    int count;              // Quante volte e' apparsa
    struct tnode *left;     // Puntatore ai nodi con parole "minori"
    struct tnode *right;    // Puntatore ai nodi con parole "maggiori"
};

// Funzione helper per allocare un nuovo nodo
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

// Funzione helper per duplicare una stringa.
// strdup non e' nello standard C, quindi e' buona norma scriverne una propria.
char *my_strdup(char *s) {
    char *p = (char *) malloc(strlen(s) + 1); // +1 per il terminatore '\0'
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

// addtree: aggiunge un nodo con la parola w, all'albero p
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    // Caso base 1: siamo arrivati in un punto vuoto dell'albero.
    // Qui e' dove dobbiamo inserire la nuova parola.
    if (p == NULL) {
        p = talloc();
        p->word = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    // La parola che stiamo inserendo (w) e' uguale a quella del nodo corrente (p->word)
    else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++; // Trovata! Aumentiamo il contatore.
    }
    // La parola w viene prima (alfabeticamente) di p->word
    else if (cond < 0) {
        p->left = addtree(p->left, w); // Chiamata ricorsiva sul sotto-albero sinistro
    }
    // La parola w viene dopo (alfabeticamente) di p->word
    else {
        p->right = addtree(p->right, w); // Chiamata ricorsiva sul sotto-albero destro
    }
    return p;
}

// treeprint: stampa l'albero in ordine alfabetico (visita in-order)
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);                 // 1. Prima vai a sinistra
        printf("%4d %s\n", p->count, p->word); // 2. Poi stampa il nodo corrente
        treeprint(p->right);                // 3. Infine vai a destra
    }
}

// Funzione per liberare tutta la memoria allocata per la lista -> lo modificheremo per l'albero
void free_list(Node *head) {
    Node *current = head;
    Node *temp;
    while (current != NULL) {
        temp = current;          // Salviamo il nodo corrente
        current = current->next; // Passiamo al successivo
        free(temp);              // Liberiamo la memoria del nodo salvato
    }
}


// main: funzione principale (semplificata per l'esempio)
int main() {
    struct tnode *root = NULL;
    char words[][MAXWORD] = {"now", "is", "the", "time", "for", "all", "good", "men", "to", "come", "to", "the", "aid", "of", "their", "party"};
    int num_words = sizeof(words)/sizeof(words[0]);

    for (int i = 0; i < num_words; i++) {
        root = addtree(root, words[i]);
    }

    printf("Frequenza delle parole in ordine alfabetico:\n");
    treeprint(root);

    return 0;
}

/* NB: In un programma reale bisognerebbe anche scrivere 
una funzione per liberare la memoria di tutto l'albero!*/