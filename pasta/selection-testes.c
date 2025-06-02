#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.c"

// funçao ordenar produto por nome ordem alfabetica
void ordenarPorNome(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        ordenarPorNome_(&produtos[i], size - i);
    }
}

void ordenarPorNome_(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].nome1, produtos[min_idx].nome1) < 0) {
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}
//---------------------------------------------------------------------------


// funçao ordenar produto por ordem crescente

void ordenarPorPrecoCrescente(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size + 1; i++) {
        ordenarPorNome_(&produtos[i], size - i);
    }
}


void ordenarPorPrecoCrescente_(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) { 
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].preco1, produtos[min_idx].preco1) < 0) { // observar sinal
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}

//-------------------------------------------------------------------------------


// funçao ordenar produto por ordem decrescente

void ordenarPorPrecoDecrescente(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        ordenarPorPrecoDecrescente_(&produtos[i], size - i);
    }
}

void ordenarPorPrecoDecrescente_(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].preco1, produtos[min_idx].preco1) > 0) { // esse sinal muda quando for descrecente
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}

// --------------------------------------------------------------------------------------------


// funçao para ordenar produto em quantidade crescente

void ordenarPorQuantidadeCrescente(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        ordenarPorQuantidadeCrescente_(&produtos[i], size - i);
    }
}

void ordenarPorQuantidadeCrescente_(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].quantida1, produtos[min_idx].quantidade1) < 0) {
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}

//------------------------------------------------------------------------------------

// funçao para ordenar produto por quantidade decrescente

void ordenarPorQuantidadeDecrescente(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        ordenarPorQuantidadeDecrescente(&produtos[i], size - i);
    }
}

void ordenarPorQuantidadeDecrescente(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].quantida1, produtos[min_idx].quantidade1) > 0) { // esse sinal muda quando for descrecente
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}

//------------------------------------------------------------------------------------


// funçao para ordenar produtos por codico crescente

void ordenarPorCodigoCrescente(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        ordenarPorCodigoCrescente_(&produtos[i], size - i);
    }
}

void ordenarPorCodigoCrescente_(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].codigo1, produtos[min_idx].codigo1) < 0) {
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}

//---------------------------------------------------------------------------------------------------

// função para ordenar produtos por codigo decrescente

void ordenarPorCodigoDecrescente(struct linha_char produtos[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        ordenarPorCodigoDecrescente_(&produtos[i], size - i);
    }
}

void ordenarPorCodigoDecrescente_(struct linha_char produtos[], int size)
{
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha_char temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].codigo1, produtos[min_idx].codigo1) > 0) { // esse sinal muda quando for descrecente
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = produtos[i];
            produtos[i] = produtos[min_idx];
            produtos[min_idx] = temp;
        }
    }
}

