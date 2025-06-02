#include <stdio.h>

struct carta_t {
    int naipe;
    int rank;
    struct carta_t* next;
};

int main(){

    struct carta_t baralho[52];
    struct carta_t* jogador1;
    struct carta_t* jogador2;
    struct carta_t* head;

    // colocando cartas do baralho em ordem
    int k = 0;
    for (int i = 1; i<=4; i++){
        for (int j = 1; j<= 13; j++){
            baralho[k].naipe = i;
            baralho[k].rank = j;
            printf("carta %d = %d %d\n",k+1,baralho[k].naipe, baralho[k].rank);
            k++;
        }
    }

    printf("carta 26 = %d %d\n",baralho[25].naipe, baralho[25].rank);
    
    head = &baralho[0];
    for (int i = 0; i<52; i++){
        baralho[i].next = &baralho[i+1];
    }
    baralho[52].next = NULL;
    
    printf("a carta %d %d aponta para a carta %d %d",baralho[3].naipe,baralho[3].rank, baralho[3].next->naipe, baralho[3].next->rank);
    
    return 0;



}