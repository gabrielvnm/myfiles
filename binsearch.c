#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOME_ARQUIVO 30
#define MAX 101

int arr_arquivo[MAX]; //{10,12,14,16,18,21,23,25,27,29,32,34,36,38,41,43,45,47,49,52,54,56,58,61,63,65,67,69,72,74,76,78,81,83,85,87,89,92,94,96}

//char arquivo_copiado[MAX];

// ler o arquivo e guardar como string, talvez seja melhor ja guardar tudo como integer com a outra função
/* void copiarArquivo(char nome_arquivo[MAX_NOME_ARQUIVO]) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo.");
        return;
    }

    // criando uma variavel pra armazenar a ultima posição do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    if (tamanho_arquivo > MAX){
        printf("Arquivo grande demais!");
        fclose(arquivo);
        return;
    }
    // copiando o arquivo inteiro pra uma variavel global
    size_t lendo_arquivo = fread(arquivo_copiado, 1, tamanho_arquivo, arquivo);

    // fazer a ultima posição do arquivo virar uma string com um terminator nulo
    arquivo_copiado[tamanho_arquivo] = '\0';

    fclose(arquivo);
    return;
}  */

//função pra abrir o arquivo e guardar como integer
int abrirArquivo(char nome_arquivo[MAX_NOME_ARQUIVO]);

int abrirArquivo(char nome_arquivo[MAX_NOME_ARQUIVO]){
    FILE* arquivo = fopen(nome_arquivo, "r");
    int contador = 0;
    char buffer;

    if (!arquivo) {
        perror("Erro ao abrir arquivo.");
        return -1;
    }
    while (fscanf(arquivo, "%d", &arr_arquivo[contador]) == 1) {
        contador++;
        
        // char buffer andando pelo arquivo e removendo as virgulas
        if ((buffer = fgetc(arquivo)) != ',') {
            if (buffer == EOF) break; 
            ungetc(buffer, arquivo);      
        }
        if (contador >= MAX) {
            printf("Arquivo grande demais!\n");
            return -1;
        }
    }
    fclose(arquivo);
    return contador;
}
// função de pesquisa binaria
// argumentos sao: a lista que vai ser pesquisada, a posiçao do primeiro elemento, a posição do ultimo elemento, o elemento pesquisado
int binSearch(int left, int right, int key) { 
  
    // esse while continua rodando até que left > right
    // se chegar nesse ponto é pq nao achou o elemento na lista
    while (left <= right) {

        // calcular a posição do meio da lista
        // a primeira vez a posição inicial vai ser right/2,
        // cada vez que o while roda ele atualiza o left e a posição mid
        int mid = left + (right - left) / 2;

        // essa aqui é a pesquisa propriamente dita
        // o while vai ficar comparando o elemento pesquisado com a posição mid até dar match
        if (arr_arquivo[mid] == key) {
            return mid; // retorna a posição do elemento quando achar
        }

        // se nao tiver achado, vai comparar o valor do mid com a chave,
        // se a chave for maior a posição left vai ficar igual ao mid
        // ou seja todos os elementos left vão ser ignorados
        if (arr_arquivo[mid] < key) {
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

int main (){
    //int arr[MAX]; // lista de numeros para pesquisar
    int size; //= sizeof(arr)/ sizeof(arr[0]); //numero de elementos do array
    int key;
    char nome_arquivo[MAX_NOME_ARQUIVO];

    
    printf("Digite um nome de arquivo:\n");
    fgets(nome_arquivo, MAX_NOME_ARQUIVO, stdin);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
    printf("abrindo o arquivo: %s\n",nome_arquivo);
    size = abrirArquivo(nome_arquivo);

    printf("Aqui esta a lista com %d numeros:\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr_arquivo[i]);
    }
    printf("\n");

    
    printf("Digite um numero: \n");
    scanf("%d",&key);

    int result = binSearch(0, size-1, key); 
    if (result == -1) {
        printf("Numero nao existe na lista!");
    }
    else {
        printf("Elemento esta na posicao %d", result); // resultado da pesquisa, lembrando que a lista começa na posição 0
    }

    return 0;
}