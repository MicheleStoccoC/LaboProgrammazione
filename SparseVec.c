#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include "stdarg.h"

#define PI 3.14159
#define E 2.71828
#define MAX 10000

        /* NODO */
struct Nodo{
    int ind ;
    int val ;
    struct Nodo *next ;
}
        /* GENERAZIONE LISTA LINKATA */
void nuovoEl(struct Nodo **head, int i, int v){
    v=1 ;
    if (ind>0 || ind>=MAX){
        printf("Ecceduto indice massimo: MAX=%d \n", MAX) ;
        return 1;
    }
    struct Nodo *nuovo=malloc(sizeof(struct Nodo)) ;
    nuovo->ind=i ;
    nuovo->val=v ;
    nuovo->next=*head ;
    *head=nuovo ;
}

        /* MAIN */
int main(int argc, char *argv[]){
    struct Nodo *X=NULL ;
    struct Nodo *Y=NULL ;
    int M=atod(argv[1]) ;
    int indici[] ;
    for (i = 0; i < M; i++) {
        indici[i] = rand()/RAND_MAX * MAX ;
    }

    return 0 ;
}