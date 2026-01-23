#include <stdio.h>
#include <stdlib.h>

/* Definizione della struttura del Nodo */
typedef struct Node{
    int indice ;              // Indice da scorrere per inserire un nuovo elemento. In q. caso particolare indice=data
    int data ;                 // Il dato che vogliamo conservare
    struct Node *next ;        // Il puntatore al prossimo nodo
} Node;

/* Funzione per creare un nuovo nodo. Ritorna un puntatore al nodo creato */
Node* create_node(int ind, int data){
    // allocazione nel sistema di memoria sufficiente per un nuovo nodo
    Node *newNode=(Node*)malloc(sizeof(Node)) ;
    if(newNode==NULL){
        printf("Errore: impossibile allocare memoria.\n") ;
        exit(1) ;
    }
    newNode->indice=ind ; // Impostare l'indice dell'elemento
    newNode->data=data ; // Mettere il dato nel nodo
    newNode->next=NULL ; // Il nuovo nodo, per ora, non punta a nulla
    return newNode;
}

/* Funzione per inserire un nuovo nodo in testa alla lista */
void insert_at_head(Node **head, Node *node_to_insert){
    node_to_insert->next=*head ;    // Il nuovo nodo punta a quello che prima era il primo
    *head=node_to_insert ;          // La "testa" della lista e' il nuovo nodo
}

/* Inserimento nel mezzo */
void insert_there(Node *head, Node *node_to_insert){
    int there ;
    printf("Inserire l'indice dopo il quale si vuole posizionare il nuovo nodo: ") ;
    scanf("%d", &there) ;
    Node *current=head ;
    while (current != NULL && current->indice > there) {
        current=current->next ; // Passiamo al prossimo
    }
    node_to_insert->next=current->next ;
    current->next=node_to_insert ;
}

/* Funzione per stampare la lista */
void print_list(Node *head){
    Node *current=head ;
    while(current != NULL){
        printf("Indice: %d, Valore: %d\n", current->indice, current->data) ;
        current=current->next ; // Passiamo al prossimo
    }
    printf("NULL\n") ;
}

/* Funzione per liberare tutta la memoria allocata per la lista */
void free_list(Node *head){
    Node *current=head ;
    Node *temp ;
    while(current != NULL){
        temp=current ;              // Salvataggio il nodo corrente
        current=current->next ;     // Passaggio al successivo
        free(temp) ;                 // Liberazione della memoria del nodo salvato
    }
}


int main() {
    // Inizialmente, la lista e' vuota
    Node *head = NULL;

    // Creazione di alcuni nodi
    Node *n1=create_node(10,10) ;
    Node *n2=create_node(20,20) ;
    Node *n3=create_node(30,30) ;
    Node *n4=create_node(40,40) ;
    // Nodi intermedi da inserire a posteriori
    Node *m1=create_node(21,21) ;
    Node *m2=create_node(22,22) ;
    Node *m3=create_node(38,38) ;
    
    
    // Inseriamoli in testa e in un punto specifico
    insert_at_head(&head,n1) ;
    insert_at_head(&head,n2) ;
    insert_at_head(&head,n3) ;
    insert_at_head(&head,n4) ;
    insert_there(head,m2) ;
    insert_there(head,m1) ;
    insert_there(head,m3) ;

    printf("La mia lista concatenata: \n");
    print_list(head);

    // Liberazione della memoria
    free_list(head);

    return 0;
}


/* Trova un modo per fare un inserimento in mezzo agli elementi gia' presenti */ // FATTO