#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome_sensor[5];
    long long int timestamp_sensor;
    float medicao;
}Sensores;

int binSearch(Sensores *sensor, int left, int right, int key) { 
  
    // esse while continua rodando até que left > right
    // se chegar nesse ponto é pq nao achou o elemento na lista
    while (left <= right) {

        // calcular a posição do meio da lista
        // a primeira vez a posição inicial vai ser right/2,
        // cada vez que o while roda ele atualiza o left e a posição mid
        int mid = left + (right - left) / 2;

        // essa aqui é a pesquisa propriamente dita
        // o while vai ficar comparando o elemento pesquisado com a posição mid até dar match
        if (sensor[mid].timestamp_sensor == key) {
            return mid; // retorna a posição do elemento quando achar
        }

        // se nao tiver achado, vai comparar o valor do mid com a chave,
        // se a chave for maior a posição left vai ficar igual ao mid
        // ou seja todos os elementos left vão ser ignorados
        if (sensor[mid].timestamp_sensor < key) {
            left = mid + 1;
        }

        // se a chave for menor ele vai ignorar os elementos right
        else {
            right = mid - 1;
        }
    }
    // se não cair em nenhum return no while ele cai nesse aqui
    // retorna -1 se o elemento não existe na lista
    return -1;
}

int main(){
    return 0;
}