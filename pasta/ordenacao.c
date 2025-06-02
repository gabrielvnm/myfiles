#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINHAS 50
#define MAX_TAM_LINHAS 100
#define MAX_TAM_ARQUIVO 4096
#define MAX 30
#define MED 10
#define MIN 5

//declarando as funcoes
//void selecao_crescente();
//void selecao_crescente2();
//void selecao_decrescente();
//void selecao_decrescente2();
//int obterNumeroItens();
//int obterNumeroLinhas();

char nomeArquivo[MAX];
int numero_linhas;
char buffer1;
char buffer2[MAX_TAM_ARQUIVO];
char buffer3[MAX_TAM_ARQUIVO];


int obterNumeroLinhas(){

	FILE *arquivo;
	int contador_linhas = 0;

	arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }


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

    printf("o arquivo possui %d linhas\n",numero_linhas);
    return numero_linhas;
}

void abrirArquivo(){
    
    FILE *arquivo;

	arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    while(fgets(buffer2, MAX_TAM_ARQUIVO, arquivo)!=NULL){
        
    }
    fclose(arquivo);
    return;

}

void dividirLinhas(){

    abrirArquivo();

    //char linha[MAX_TAM_LINHAS][numero_linhas];
	
	//char *token = strtok(buffer2, "\n");
    //printf("dividir?? %s",buffer2);
    return;
	
}

//algoritmo pra ordenar string em ordem crescente
//tem dois com nome parecido pra evitar recursividade
/*void selecao_crescente(int * v, int size){
    
    for(int i = 0; i < size; i++){
        selecao_(&v[i], size-i);
    }
}

void selecao_crescente(int * v, int size){
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

    FILE *arquivo;
    char nomeArquivo[] = "arquivo.csv"; 
    char *linhas[MAX_LINHAS];
    int contador_linhas = 0;
    int menu;

    arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    while (contador_linhas < MAX_LINHAS && fgets(buffer, MAX_TAM_LINHAS, arquivo) != NULL){
        buffer[strcspn(buffer, "\n")] = '\0';
    
        linhas[contador_linhas] = malloc (strlen(buffer)+1);
        if (linhas[contador_linhas] == NULL){
        perror("Erro ao copiar!");
        return -1;
        }
        strcpy(linhas[contador_linhas],buffer);
        contador_linhas++;
    }
    fclose(arquivo);

    printf("aqui estao as %d linhas do arquivo:\n", contador_linhas);
    for (int i =0; i< contador_linhas; i++){
        printf("linha %d: %s \n",i+1, linhas[i]);
    } 
*/
int main(void){

    int menu;

    printf("Digite o nome do arquivo:\n");
    
    // função pra ler um imput do usuario
    fgets(nomeArquivo, MAX, stdin);
    //essa funçao substitui o enter no final do input pelo char de terminar string \0, importante!!!
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';    


    printf("voce digitou: %s\n", nomeArquivo);


    //IMPORTANTE tem que executar a função LINHAS PRIMEIRO!!!!!
    obterNumeroLinhas();
    obterNumeroItens();

    printf("numero itens: %d\nnumero linhas: %d\n",numero_itens, numero_linhas);

    dividirLinhas();

    printf("\nbuffer?? %s",buffer2);

    /*char nome[MAX][numero_linhas];
	char preco[MED][numero_linhas];
	char quantidade[MED][numero_linhas];
	char codigo[MED][numero_linhas];
*/






    /*printf("selecione uma ordem para organizar as colunas:\n1:Crescente\n2:Decrescente\n");
    scanf("%d",&menu);

    switch (menu){
        default: printf("Opcao invalida!");
        case 1: 
            selecao_crescente();
            break;
        case 2: 
            selecao_decrescente();
            break;
    }*/
   return 0;
}
