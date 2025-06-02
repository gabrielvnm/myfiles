#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_NOME_ARQUIVO 30
#define MAX_LINHAS 1001
#define NOME_SENSOR 5

typedef struct{
    char nome_sensor[NOME_SENSOR];
    long long int timestamp_sensor;
    float medicao;
}Sensores ;

void abrirArquivo();
int obterNumeroLinhas();
time_t capturar_timestamp_valido();
void limparTela();
void sairComQualquerTecla();
int binSearch(Sensores *sensor, int left, int right, int key);

void sairComQualquerTecla(){
    printf("Aperte qualquer tecla para continuar: \n");
    while (1){
        if (_kbhit()){
            char tecla = getch();
            break;
        }
    }
}


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

    while (fscanf(arquivo, "%6[^;];%lld;%f\n", sensortemp.nome_sensor, &sensortemp.timestamp_sensor, &sensortemp.medicao)==3){
        
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
int binSearch(Sensores *sensor, int left, int right, int key) { 
      
    int mid;
  
    while (left <= right) {

        mid = left + (right - left) / 2;
        if (sensor[mid].timestamp_sensor == key) {
            return mid;
        }
        if (sensor[mid].timestamp_sensor < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return mid;
}

int main (){
    
    long long int key;
    int numero_linhas;
    char nome_arquivo[MAX_NOME_ARQUIVO];

    limparTela();

    printf("Digite um nome de arquivo:\n");
    fgets(nome_arquivo, MAX_NOME_ARQUIVO, stdin);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
    printf("abrindo o arquivo: %s\n",nome_arquivo);


    numero_linhas = obterNumeroLinhas(nome_arquivo);
    Sensores sensor[numero_linhas]; 
    abrirArquivo(nome_arquivo, numero_linhas, sensor);
    
    key = capturar_timestamp_valido();
    printf("timestamp informado: %d\n", key);

    int result = binSearch(sensor, 0, numero_linhas-1, key); 
    if (result == 0) {
        printf("Atencao: So existem leituras posteriores a data informada!\n");
        printf("Elemento mais proximo esta na posicao %d\n", result+1); // resultado da pesquisa, lembrando que a lista começa na posição 0
        printf("Resultado da busca: %s %lld %.2f\n", sensor[result].nome_sensor, sensor[result].timestamp_sensor, sensor[result].medicao);
    }
    else if (result == numero_linhas-1){
        printf("Atencao: So existem leituras anteriores a data informada!\n");
        printf("Elemento mais proximo esta na posicao %d\n", result+1); // resultado da pesquisa, lembrando que a lista começa na posição 0
        printf("Resultado da busca: %s %lld %.2f\n", sensor[result].nome_sensor, sensor[result].timestamp_sensor, sensor[result].medicao);
    }
    else {
        printf("Elemento mais proximo esta na posicao %d\n", result+1); // resultado da pesquisa, lembrando que a lista começa na posição 0
        printf("Resultado da busca: %s %lld %.2f\n", sensor[result].nome_sensor, sensor[result].timestamp_sensor, sensor[result].medicao);
    } 
    return 0;
}