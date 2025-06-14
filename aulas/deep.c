#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_LINHAS 50
#define MAX_TAM_LINHAS 80
#define MAX_TAM_ARQUIVO 4096
#define MAX 50
#define MED 10
#define MIN 5

char nome_arquivo[MAX];
char arquivo_copiado[MAX_TAM_ARQUIVO];
int numero_linhas;


// criando uma struct pra colocar as strings como char e outra pra colocar depois que transformar nos outros tipos de memoria
struct linha_char{
    char nome1[MAX];
    char preco1[MED];
    char quantidade1[MED];
    char codigo1[MED];
};
struct linha{
    char nome[MAX];
    float preco;
    int quantidade;
    int codigo;
};
void obterNumeroLinhas(){

    FILE *arquivo;
    int contador_linhas = 0;
    char buffer1;

    arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // isso aqui fica movendo o buffer pelo arquivo até achar uma quebra de linha
    // depois que acha um \n ele aumenta o contador de linhas
    // termina no EOF, fim do arquivo
    while ((buffer1 = fgetc(arquivo)) != EOF) {
        if (buffer1 == '\n') {
            contador_linhas++;
        }
    }
    fseek(arquivo, -1, SEEK_END);
    buffer1 = fgetc(arquivo);
    if (buffer1 != '\n') {
   
        fseek(arquivo, 0, SEEK_END);
        long tamanho = ftell(arquivo);
        if (tamanho > 0) {
            contador_linhas++;
        }
    }

    numero_linhas = contador_linhas;

    return;
}
void copiarArquivo() {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo.");
        return;
    }

    // criando uma variavel pra armazenar a ultima posição do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    size_t lendo_arquivo = fread(arquivo_copiado, 1, tamanho_arquivo, arquivo);

    // fazer a ultima posição do arquivo virar uma string com um terminator nulo
    arquivo_copiado[tamanho_arquivo] = '\0';

    fclose(arquivo);
    return;
}
//funçao para exibir menu
void exibirMenu() {
    printf("\nEscolha uma opcao de ordenacao:\n");
    printf("1 - Ordenar por nome (ordem alfabetica)\n");
    printf("2 - Ordenar por preco (crescente)\n");
    printf("3 - Ordenar por preco (decrescente)\n");
    printf("4 - Ordenar por quantidade (crescente)\n");
    printf("5 - Ordenar por quantidade (decrescente)\n");
    printf("6 - Ordenar por codigo (crescente)\n");
    printf("7 - Ordenar por codigo (decrescente)\n");
    printf("8 - Salvar em arquivo CSV\n");
    printf("9 - Sair\n");
    printf("Opcao: ");
}
//funçao para exibir o arquivo aberto na tela do terminal 
void exibirArquivo(struct linha *Linhas){
    for (int i =0; i< numero_linhas; i++){
        printf("linha %d = %s %.2f %d %d\n",i,Linhas[i].nome,Linhas[i].preco,Linhas[i].quantidade,Linhas[i].codigo);
    }
    return;
} 
//funçao para criar um novo arquivo csv
int salvarCSV(struct linha *Linhas ){
    FILE* arquivo;
    char nomeArquivo[MAX];

    printf("Digite o nome do arquivo para gravar:\n");
    fgets(nomeArquivo, MAX, stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
    arquivo = fopen(nomeArquivo, "w");
    /*if (arquivo == NULL) {
        printf("Erro abrindo arquivo!\n");
        return 1;
    }*/

    for(int i=0; i < numero_linhas; i++){
        fprintf(arquivo,"%s;%.2f;%d;%d;\n",Linhas[i].nome,Linhas[i].preco,Linhas[i].quantidade,Linhas[i].codigo);
    }
    fclose(arquivo);
    return 0;
}
// funçao ordenar produto por nome ordem alfabetica
void ordenarPorNome_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;
    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(produtos[j].nome, produtos[min_idx].nome) < 0) {
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

void ordenarPorNome(struct linha *produtos, int size){
    for (int i = 0; i < size - 1; i++) {
        ordenarPorNome_(produtos, size - i);
    }
}


// funçao ordenar produto por ordem crescente
void ordenarPorPrecoCrescente_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;

    for (i = 0; i < size - 1; i++) { 
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (produtos[j].preco < produtos[min_idx].preco) { // observar sinal
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

void ordenarPorPrecoCrescente(struct linha *produtos, int size){
    for (int i = 0; i < size + 1; i++) {
        ordenarPorPrecoCrescente_(produtos, size - i);
    }
}

// funçao ordenar produto por ordem decrescente
void ordenarPorPrecoDecrescente_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (produtos[j].preco > produtos[min_idx].preco) { // esse sinal muda quando for descrecente
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

void ordenarPorPrecoDecrescente(struct linha *produtos, int size){
    for (int i = 0; i < size - 1; i++) {
        ordenarPorPrecoDecrescente_(produtos, size - i);
    }
}

// funçao para ordenar produto em quantidade crescente
void ordenarPorQuantidadeCrescente_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (produtos[j].quantidade < produtos[min_idx].quantidade) {
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

void ordenarPorQuantidadeCrescente(struct linha *produtos, int size){
    for (int i = 0; i < size - 1; i++) {
        ordenarPorQuantidadeCrescente_(produtos, size - i);
    }
}

// funçao para ordenar produto por quantidade decrescente
void ordenarPorQuantidadeDecrescente_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (produtos[j].quantidade > produtos[min_idx].quantidade) { // esse sinal muda quando for descrecente
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

void ordenarPorQuantidadeDecrescente(struct linha *produtos, int size){
    for (int i = 0; i < size - 1; i++) {
        ordenarPorQuantidadeDecrescente_(produtos, size - i);
    }
}

// funçao para ordenar produtos por codico crescente
void ordenarPorCodigoCrescente_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (produtos[j].codigo < produtos[min_idx].codigo) {
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

void ordenarPorCodigoCrescente(struct linha *produtos, int size){
    for (int i = 0; i < size - 1; i++) {
        ordenarPorCodigoCrescente_(produtos, size - i);
    }
}

// função para ordenar produtos por codigo decrescente
void ordenarPorCodigoDecrescente_(struct linha *produtos, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    struct linha temp;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (produtos[j].codigo > produtos[min_idx].codigo){ // esse sinal muda quando for descrecente
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

void ordenarPorCodigoDecrescente(struct linha *produtos, int size){
    for (int i = 0; i < size - 1; i++) {
        ordenarPorCodigoDecrescente_(produtos, size - i);
    }
} 

struct linha obterLinhas(int i, char linha_inteira[MAX_TAM_LINHAS]) {

    struct linha_char Linhas_char[numero_linhas];
    struct linha Linhas[numero_linhas];
    char *token = strtok(linha_inteira, ";"); // token recebe a primeira linha 

    //dividindo a string arquivo_copiado que tem o arquivo todo em strings menores e colocando na struct
    strcpy(Linhas_char[i].nome1, token);
    token = strtok(NULL, ";");
    strcpy(Linhas_char[i].preco1, token);
    token = strtok(NULL, ";");
    strcpy(Linhas_char[i].quantidade1, token);
    token = strtok(NULL, ";");
    strcpy(Linhas_char[i].codigo1, token);

    //convertendo as strings de uma struct pra outra struct com tipos de dados diferentes
    strcpy(Linhas[i].nome,Linhas_char[i].nome1);
    Linhas[i].preco = atof(Linhas_char[i].preco1);
    Linhas[i].quantidade = atoi(Linhas_char[i].quantidade1);
    Linhas[i].codigo = atoi(Linhas_char[i].codigo1);

    
    return Linhas[i];

}

int main(void) {

    char linha_inteira[MAX_TAM_LINHAS][MAX_LINHAS];

    printf("Digite o nome do arquivo: para abrir:\n");
    
    // função pra ler um input do usuario
    fgets(nome_arquivo, MAX, stdin);
    //essa funçao substitui o enter no final do input pelo char de terminar string \0, importante!!!
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
    copiarArquivo();
    obterNumeroLinhas();

    //tem que declarar a struct DEPOIS de rodar a função de obter numero de linhas senao dá ruim
    struct linha Linhas[numero_linhas];
    //struct linhas Linha[numero_linhas];

    if (numero_linhas > MAX_LINHAS){
        printf("Arquivo excede o numero de linhas!\n");
        return -1;
    }
    char *token = strtok(arquivo_copiado, "\n");
    for (int j = 0; j<numero_linhas;j++){
        strcpy(linha_inteira[j], token);
        token = strtok(NULL, "\n");
        if (token == "\0"){
            break;
        }
    }
    for (int i = 0; i< numero_linhas; i++){
        Linhas[i] = obterLinhas(i, linha_inteira[i]);
    } 
    printf("Arquivo atual: %s\n",nome_arquivo);
    exibirArquivo(Linhas);
// MENU DE SELEÇAO
    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                ordenarPorNome(Linhas, numero_linhas); // funçao feita
                exibirArquivo(Linhas);
                break;
            case 2:
                ordenarPorPrecoCrescente(Linhas, numero_linhas); 
                exibirArquivo(Linhas);
                break;
            case 3:
                ordenarPorPrecoDecrescente(Linhas, numero_linhas);
                exibirArquivo(Linhas);
                break;
            case 4:
                ordenarPorQuantidadeCrescente(Linhas, numero_linhas);
                exibirArquivo(Linhas);
                break;
            case 5:
                ordenarPorQuantidadeDecrescente(Linhas, numero_linhas);
                exibirArquivo(Linhas);
                break;
            case 6:
                ordenarPorCodigoCrescente(Linhas, numero_linhas);
                exibirArquivo(Linhas);
                break;
            case 7:
                ordenarPorCodigoDecrescente(Linhas, numero_linhas);
                exibirArquivo(Linhas);
                break;
            case 8:
                salvarCSV(Linhas);
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);

    return 0;
}