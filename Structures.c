#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include "ctype.h"

#define PI 3.14159
#define E 2.71828

struct point funzione(int, int){
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

//Per comparare strutture e' utile definire un'altra funzione
int compare(struct point p1,p2){
    if(p1.x==p2 && p1.y==p2.y){
        return 1;
    }else{
        return o;
    }
}

int main(){
    //Le strutture possono contenere altre strutture
    struct point{
        int x;
        int y;
    };
    struct rect{
        struct point pt1;
        struct point pt2;
    };
// Inoltre e' possibile utilizzarle per permettere indirettamente alle funzioni di ritornare piu' di un dato !!!
/*
ATTENZIONE il '.' ha priorita' assoluta! '*pp.y' e' come scrivere '*(pp.y)' quando in realta' vogliamo '(*pp).y' 
 inoltre 'p->member' si puo' riferire al membro specifico di struttura ed e' tale per cui le seguenti sono uguali:
r.pt1.x
rp->pt1.x
(r.pt1).x
(rp->pt1).x
*/
//NOTA la struttura viene passata per valori => 150 elementi vengono passati uno per uno a meno di non usare un puntatore.
}