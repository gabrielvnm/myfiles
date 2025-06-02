#include <stdio.h>

void selection_(int * v, int size);
void selection(int * v, int size);
 


int main()
{
    int vetor[] = {10, -8, -78, 91, 1, 9, 0};
 
    int len = sizeof(vetor)/sizeof(vetor[0]);

    selection(vetor, len);
 
    printf("\r\n");
 

    for (int i = 0; i < len; i++){
        printf("%2d ", vetor[i]);
    }
 
    return 0;
}
// função selection que ordena os valores
// argumentos sao a lista de elementos q vai ser organizada e o tamanho da lista
// ela passa os valores por referencia entao o return é void
void selection(int * v, int size){
    for(int i = 0; i < size; i++){
        selection_(&v[i], size-i);
    }
}
void selection_(int * v, int size){

    int menor = v[0];
    int pos = 0;

    if (size < 2){
        return;
    }
    for (int i = 1; i < size; i++){
        if (v[i] < menor){
            menor = v[i];
            pos = i;
        }
    }

    if (pos != 0){
        int transferencia = v[0];
        v[0] = v[pos];
        v[pos] = transferencia;
    }
}