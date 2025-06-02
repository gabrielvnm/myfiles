#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NOME_ARQUIVO 30
#define MAX_LINHAS 1001
#define NOME_SENSOR 5

//int arr_arquivo[MAX]; //{10,12,14,16,18,21,23,25,27,29,32,34,36,38,41,43,45,47,49,52,54,56,58,61,63,65,67,69,72,74,76,78,81,83,85,87,89,92,94,96}


//char arquivo_copiado[MAX];

typedef struct{
    char nome_sensor[NOME_SENSOR];
    long long int timestamp_sensor;
    float medicao;
}Sensores ;

void abrirArquivo();
int obterNumeroLinhas();
time_t capturar_timestamp_valido();
void limparTela();

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

// função pra receber o valor do usuario e transformar em timestamp
time_t capturar_timestamp_valido() {
    int dia, mes, ano, hora, min, seg;
    struct tm t;
    

    while (1) {
        printf("Digite a data e hora (dd mm aaaa hh mm ss): ");
        if (scanf("%d %d %d %d %d %d", &dia, &mes, &ano, &hora, &min, &seg) != 6) {
            while (getchar() != '\n');
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        t.tm_year = ano - 1900;
        t.tm_mon = mes - 1;
        t.tm_mday = dia;
        t.tm_hour = hora;
        t.tm_min = min;
        t.tm_sec = seg;
        t.tm_isdst = -1;

        time_t timestamp = mktime(&t);
        if (timestamp == -1) {
            printf("Data inválida. Tente novamente.\n");
        } else {
            return timestamp;
        }
    }
}

void limparTela(){
#ifdef _WIN32 // verifica se o sistema é Windows ou não
    system("cls");
#else
    system("clear");
#endif
}

//função pra abrir o arquivo e guardar como integer
void abrirArquivo(char nome_arquivo[MAX_NOME_ARQUIVO], int numero_linhas, Sensores *sensor){
    FILE* arquivo = fopen(nome_arquivo, "r");
    
    if (!arquivo) {
        perror("Erro ao abrir arquivo.");
        return;
    }
    Sensores sensortemp;
    int i = 0;
    // esse while aqui vai continuar rodando até que o numero de inputs recebidos do arquivo seja diferente de 3
    // cada vez que ele roda
    while (fscanf(arquivo, "%6[^;];%lld;%f\n", sensortemp.nome_sensor, &sensortemp.timestamp_sensor, &sensortemp.medicao)==3){
        //printf("variavel interna da funcao: %s, %lld, %.2f\n",sensortemp.nome_sensor, sensortemp.timestamp_sensor, sensortemp.medicao);
        sensor[i] = sensortemp;
        i++;
    }
    
    fclose(arquivo);
    return;
}
int obterNumeroLinhas(char nome_arquivo[MAX_NOME_ARQUIVO]){

    FILE *arquivo;
    int contador_linhas = 0;
    char buffer;

    arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }

    // isso aqui fica movendo o buffer pelo arquivo até achar uma quebra de linha
    // depois que acha um \n ele aumenta o contador de linhas
    // termina no EOF, fim do arquivo
    while ((buffer = fgetc(arquivo)) != EOF) {
        if (buffer == '\n') {
            contador_linhas++;
        }
    }
    fseek(arquivo, -1, SEEK_END);
    buffer = fgetc(arquivo);
    if (buffer != '\n') {
   
        fseek(arquivo, 0, SEEK_END);
        long tamanho = ftell(arquivo);
        if (tamanho > 0) {
            contador_linhas++;
        }
    }

    if (contador_linhas> MAX_LINHAS){
        printf("Arquivo excede o tamanho máximo!");
        return -1;
    }
    return contador_linhas;
}

// função de pesquisa binaria
// argumentos sao: a lista que vai ser pesquisada, a posiçao do primeiro elemento, a posição do ultimo elemento, o elemento pesquisado
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

int main (){
    //int arr[MAX]; // lista de numeros para pesquisar
    //int size; //= sizeof(arr)/ sizeof(arr[0]); //numero de elementos do array
    int key;
    int numero_linhas;
    char nome_arquivo[MAX_NOME_ARQUIVO];

    printf("Digite um nome de arquivo:\n");
    fgets(nome_arquivo, MAX_NOME_ARQUIVO, stdin);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
    printf("abrindo o arquivo: %s\n",nome_arquivo);


    numero_linhas = obterNumeroLinhas(nome_arquivo);
    Sensores sensor[numero_linhas]; 
    abrirArquivo(nome_arquivo, numero_linhas, sensor);
    //printf("funcao executada: %s %lld %f\n", sensor[0].nome_sensor, sensor[0].timestamp_sensor, sensor[0].medicao);

    //size = abrirArquivo(nome_arquivo);

    //printf("Aqui esta a lista com %d elementos:\n", numero_linhas);
   //  for (int i = 0; i < numero_linhas; i++) {
        //printf("funcao executada: %s %lld %f\n", sensor->nome_sensor[i], sensor[i].timestamp_sensor, sensor[i].medicao);
        //printf("funcao executada: %s %lld %.2f\n", sensor[i].nome_sensor, sensor[i].timestamp_sensor, sensor[i].medicao);
   // } 
    //printf("\n");

    
     printf("Digite um numero: \n");
    scanf("%d",&key);

    int result = binSearch(sensor, 0, numero_linhas-1, key); 
    if (result == -1) {
        printf("Numero nao existe na lista!");
    }
    else {
        printf("Elemento esta na posicao %d\n", result); // resultado da pesquisa, lembrando que a lista começa na posição 0
        printf("Resultado da busca: %s %lld %.2f\n", sensor[result].nome_sensor, sensor[result].timestamp_sensor, sensor[result].medicao);
    } 

    return 0;
}