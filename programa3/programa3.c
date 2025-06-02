#include <stdio.h>
#include <stdlib.h> //para usar rand
#include <time.h> //para usar time_t
#include <string.h>


//struct para data
typedef struct 
{
    int dia;
    int mes;
    int ano;
} Data; 

//funçao para converter data p/ timestamp
time_t converterData(Data data){
    struct tm t;
    t.tm_year = data.ano - 1900;
    t.tm_mon = data.mes - 1;
    t.tm_mday = data.dia;
    return mktime(&t);
    
}

time_t geradorTimestampAleatorio(time_t periodo_dia){
    return periodo_dia + (rand() % 86400); // é o periodo do dia em segundos 
}





int main(){
    Data data; //para usar a struct para guardar os dados quando o usuario digitar no console
    char *sensores[] = {"TEMP", "PRES", "VIBR", "UMID", "FLUX"};
    int n_sensores= 5;
    int qtd_leitura_sensores= 1000;

    srand(time(NULL)); // usar srand para iniciar a funçao rand com valor semente, p/ não repetir os valores

    printf("PROGRAM 3:\n");
    printf("Digite a data com os valores solicitados.\n");
    printf("Digite o dia: ");
    scanf("%d", &data.dia);
    printf("Digite o mes: ");
    scanf("%d", &data.mes);
    printf("Digite o ano: ");
    scanf("%d", &data.ano);


    time_t dia_usuario = converterData(data); // :(

    FILE *arquivo = fopen("sensores_random.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    //for para fazer gerar as leituras
    for (int j =0; j < qtd_leitura_sensores-1; j++){

            time_t timestamp = geradorTimestampAleatorio(dia_usuario); // vai gerar o timestamp aleatorio com base na data digitada pelo usuario
            float valor = rand() % 100; // valor aleatorio entre 0 - 100
            int nome_aleatorio = rand()%5;
            fprintf(arquivo, "%s;%ld;%.2f\n", sensores[nome_aleatorio], timestamp, valor);
    }
    time_t timestamp = geradorTimestampAleatorio(dia_usuario); 
    float valor = rand() % 100; 
    int nome_aleatorio = rand()%5;
    fprintf(arquivo, "%s;%ld;%.2f", sensores[nome_aleatorio], timestamp, valor);

        
   
    printf("Arquivo sensores_random.txt criado com sucesso!");
    fclose(arquivo);
    return 0;  



}
