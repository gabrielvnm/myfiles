#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
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
void selection_(Sensores *sensor, int size);
void selection(Sensores *sensor, int size);
void selection_nome(Sensores *sensor, int size);
void selectionNome(Sensores *sensor, int size);
int posicaoNome(Sensores *sensor, int size, int start);
void sairComQualquerTecla();
void criarArquivo(int nome, Sensores *sensor, int size);
void gravarArquivo(FILE *arquivo, Sensores *sensor, int size);



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


// função selection pra colocar as structs em ordem alfabetica pelo nome do sensor
void selection_nome(Sensores *sensor, int size){
    int i; // i= marca a posição que vai ser corrigida
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    Sensores temp;


    // ordenar por nome 
    for (i = 0; i < size - 1; i++) { 
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (strcmp(sensor[j].nome_sensor, sensor[min_idx].nome_sensor) < 0 ) { // observar sinal
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = sensor[i];
            sensor[i] = sensor[min_idx];
            sensor[min_idx] = temp;
        }
    }
}

void selectionNome(Sensores *sensor, int size){
    for (int i = 0; i < size + 1; i++) 
    {
        selection_nome(sensor, size -i);
    }
}

//função selection pra ordenar a lista:
// argumentos sao a lista de elementos q vai ser organizada e o tamanho da lista
// ela passa os valores por referencia entao o return é void

void selection_(Sensores *sensor, int size){
    int i; // posição inicial pra começar a ordenaçao
    int j; // j=variável que irá procurar o menor nome
    int min_idx; // min_idx= guarda o indice do menor valor

    Sensores temp;


    // ordenar por timestamp 
    for (i = 0; i < size - 1; i++) { 
        min_idx = i;
        for (j = i+1; j < size; j++) {
            if (sensor[j].timestamp_sensor < sensor[min_idx].timestamp_sensor) { // observar sinal
                min_idx = j;
            }
        }


        // se achar um valor menor, faz a troca
        if (min_idx != i) {
            temp = sensor[i];
            sensor[i] = sensor[min_idx];
            sensor[min_idx] = temp;
        }
    }
}

void selection(Sensores *sensor, int size){
    for (int i = 0; i < size + 1; i++) 
    {
        selection_(sensor, size -i);
    }
}

void gravarArquivo(FILE *arquivo, Sensores *sensor, int size){

    for (int i = 0; i < size-1; i++){
        printf("gravando linha %d: %s %lld %.2f\n",i, sensor[i].nome_sensor, sensor[i].timestamp_sensor, sensor[i].medicao);
        fprintf(arquivo, "%s;%lld;%.2f\n", sensor[i].nome_sensor, sensor[i].timestamp_sensor, sensor[i].medicao);   
    }
    fprintf(arquivo, "%s;%lld;%.2f", sensor[size-1].nome_sensor, sensor[size-1].timestamp_sensor, sensor[size-1].medicao);
    fclose(arquivo);

}
void criarArquivo(int nome, Sensores *sensor, int size){
    
    FILE *arquivo;
    switch (nome){
        case 0:
            arquivo = fopen("FLUX.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao criar o arquivo!\n");
                return;
            }
            gravarArquivo(arquivo, sensor, size);
            printf("arquivo FLUX.txt criado!");
            break;
        case 1:
            arquivo = fopen("PRES.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao criar o arquivo!\n");
                return;
            }
            gravarArquivo(arquivo, sensor, size);
            printf("arquivo PRES.txt criado!");
            break;
        case 2:
            arquivo = fopen("TEMP.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao criar o arquivo!\n");
                return;
            }
            gravarArquivo(arquivo, sensor, size);
            printf("arquivo TEMP.txt criado!");
            break;
        case 3:
            arquivo = fopen("UMID.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao criar o arquivo!\n");
                return;
            }
            gravarArquivo(arquivo, sensor, size);
            printf("arquivo UMID.txt criado!");
            break;
        case 4:
            arquivo = fopen("VIBR.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao criar o arquivo!\n");
                return;
            }
            gravarArquivo(arquivo, sensor, size);
            printf("arquivo VIBR.txt criado!");
            break;
        default:
            break;
    }
    return;
}


// posicao na lista quando o nome troca
int posicaoNome(Sensores *sensor, int size, int start){
    int i = start; // inicializando o indice na posicao informada pra comparar depois

    for (i; i < size ; i++){
        //printf("ainda nao achei um termo diferente\n");
        if (strcmp(sensor[i].nome_sensor, sensor[start].nome_sensor)!=0) { // se a lista estiver em ordem alfabetica ele vai retornar a posição do elemento diferente
            printf("rodando posicao nome %s %s\n",sensor[i].nome_sensor, sensor[start].nome_sensor);
            return i;
        }
        
    }
    return size;
}
// coloca aqui depois uma função de ordenar por nome, faz tudo ficar em ordem alfabetica
// depois q tiver em ordem faz uma função que retorna em qual posição o nome do sensor muda
// isso vai separar os arquivos por nome na struct
// depois de ordenar por nome da pra passar na função de selection de novo trocando o size pela posição da função de nome
// faz isso varias vezes pra cada nome
// depois da pra gravar um arquivo usando um for que vai até as posiçoes encontradas
// vai pensando ai maluco!!!

//funçao pra pausar a execução do programa até apertar alguma tecla
//ajuda muito na hora de debugar
void sairComQualquerTecla(){
    printf("Aperte qualquer tecla para continuar: \n");
    while (1){
        if (_kbhit()){
            char tecla = getch();
            break;
        }
    }
}

int main (){
    
    int key;
    int numero_linhas;
    char nome_arquivo[MAX_NOME_ARQUIVO];
    int posicao;
    int start = 0;
    int numero_sensores = 5;
    int size;

    limparTela();

    printf("Digite um nome de arquivo:\n");
    fgets(nome_arquivo, MAX_NOME_ARQUIVO, stdin);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
    printf("abrindo o arquivo: %s\n",nome_arquivo);


    numero_linhas = obterNumeroLinhas(nome_arquivo);
    Sensores sensor[numero_linhas]; 
    Sensores sensor_alfabetico[numero_linhas];

    //Sensores sensor_alfabetico[numero_linhas];
    // nessa função vai abrir o arquivo e copiar o conteudo pro array de struct da função main
    abrirArquivo(nome_arquivo, numero_linhas, sensor);


    printf("Aqui esta a lista com %d elementos sem ordenar:\n", numero_linhas);
    for (int i = 0; i < numero_linhas; i++) {
        // printando a lista sem ordenar
        printf("%d: %s %lld %.2f\n",i, sensor[i].nome_sensor, sensor[i].timestamp_sensor, sensor[i].medicao);
    } 
    //colocando essas pausas na execução pra debugar
    sairComQualquerTecla();
    limparTela();
    
    selection_nome(sensor, numero_linhas);
    printf("\nLista alfabetica:\n");
    for (int i = 0; i < numero_linhas; i++) {
        // printando a lista alfabetica
        printf("%d: %s %lld %.2f\n",i, sensor[i].nome_sensor, sensor[i].timestamp_sensor, sensor[i].medicao);
    }  
    sairComQualquerTecla();
    limparTela();
    // separando a struct por nome do sensor e guardando em outra struct
    // acha um jeito de fazer isso aqui varias vezes blz

    
    
    for (int k = 0; k < numero_sensores; k++){
        
        posicao = posicaoNome(sensor, numero_linhas, start);
        printf( "\nposicao %d\n",posicao);
        int j = 0;
        
        for (int i = start; i < posicao; i++) {
            // colocando a struct em ordem na outra struct para imprimir
            
            sensor_alfabetico[j] = sensor[i];
            printf("%d: %s %lld %.2f\n",j, sensor_alfabetico[j].nome_sensor, sensor_alfabetico[j].timestamp_sensor, sensor_alfabetico[j].medicao);
            j++;
        }  
        
        //printf("elemento %d: %s %lld %.2f\n",0, sensor_alfabetico[0].nome_sensor, sensor_alfabetico[0].timestamp_sensor, sensor_alfabetico[0].medicao);
        sairComQualquerTecla();
        limparTela();
        

        selection(sensor_alfabetico, j);
        printf("Aqui esta a lista %s a partir da posicao %d ordenados por timestamp com %d elementos:\n", sensor_alfabetico[0].nome_sensor, posicao, j);
        
        for (int i = 0; i < j; i++) {
        //printando a lista ordenada
            printf("%d: %s %lld %.2f\n",i, sensor_alfabetico[i].nome_sensor, sensor_alfabetico[i].timestamp_sensor, sensor_alfabetico[i].medicao);
        }
        
        start = posicao;
        sairComQualquerTecla();
        limparTela();
        criarArquivo(k, sensor_alfabetico, j);
        sairComQualquerTecla();
        limparTela();
    }
    

    return 0;
}