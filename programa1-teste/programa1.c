#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <string.h>
#include <conio.h>

#define MAX_LINHAS 5000

/*typedef struct {
    long long timestamp;
    float valor;
} Leitura_sensor;
*/
typedef struct {
    char id_sensor[5];
    //Leitura_sensor * leituras;
    int timestamp;
    float valor;
} Sensores;

int encontrar_sensores(Sensores sensores[], int n, char id[5]){
    for(int i = 0; i < n; i++){
        if(strcmp(sensores[i].id_sensor, id)==0)
        return i;
    }
    return -1;
}

void sairComQualquerTecla(){
    printf("Aperte qualquer tecla para continuar: \n");
    while (1){
        if (_kbhit()){
            char tecla = getch();
            break;
        }
    }
}
void ordenar_sensores_alfabetico(Sensores *leituras, int size){
    int i;
    int j;
    int indx;

    Sensores temp;

    for(i =0; i < size; i++){
        indx = i;
        for(j = i+1; j < size; j++){
            if(leituras[j].timestamp < leituras[indx].timestamp){
                indx = j;
            }
        }
        if(indx != i){
            temp = leituras[i];
            leituras[i] = leituras[indx];
            leituras[indx] = temp;
        }
    }
}
void ordenar_sensores_alfabetico_(Sensores *leituras, int size){
    for (int i = 0; i < size + 1; i++) {
        ordenar_sensores_alfabetico(leituras, size -i);
    }
}

void ordenar_sensores_timestamp(Sensores *leituras, int size){
    int i;
    int j;
    int indx;

    Sensores temp;

    for(i =0; i < size; i++){
        indx = i;
        for(j = i+1; j < size; j++){
            if(leituras[j].timestamp < leituras[indx].timestamp){
                indx = j;
            }
        }
        if(indx != i){
            temp = leituras[i];
            leituras[i] = leituras[indx];
            leituras[indx] = temp;
        }
    }
}
void ordenar_sensores_timestamp_(Sensores *leituras, int size){
    for (int i = 0; i < size + 1; i++) {
        ordenar_sensores_timestamp(leituras, size -i);
    }
}
int main(){

    FILE *arquivo = fopen("sensores_novo.txt", "r");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo\n");
        return -1; 
    }

    Sensores sensores[MAX_LINHAS];
    Sensores temp;
    int total_sensores = 5000;
    int timestamp;
    char id_sensor[5];
    float valor;
    int index = 0;

    char linha[MAX_LINHAS];
    while (fscanf(arquivo,"%5[^;];%d;%f\n", temp.id_sensor, &temp.timestamp, &temp.valor)==3){
        
        
        printf("%s %d %.2f\n",temp.id_sensor, temp.timestamp, temp.valor);
        int i=encontrar_sensores(sensores, total_sensores, id_sensor);
        /*if(sscanf(arquivo, "%ld;%s;%f\n", &timestamp, &id_sensor, &valor)==3){
            int i=encontrar_sensores(sensores, total_sensores, id_sensor);
        }*/
       // printf("%d %.2f\n",timestamp, valor);
        //for (int i = 0; i< MAX_LINHAS; i++){
        sensores[index] = temp;
        
        printf("%d %.2f\n",sensores[index].timestamp,sensores[index].valor);
        //}
        index++;
    }
    fclose(arquivo);

    for(int i=0; i < total_sensores; i++){
        ordenar_sensores_timestamp_(sensores, sensores[i].count);

        char nome_arquvo_novo[5];
        sprintf(nome_arquvo_novo, "%s.txt", sensores[i].id_sensor);

        FILE *arquivo_saida = fopen (nome_arquvo_novo, "w");
        if (arquivo_saida = NULL){
            printf ("Erro ao tentar gerar novo arquivo");
            continue;
        }
        for(int j=0; j < sensores[i].count; j++){
            fprintf(arquivo_saida, "%s;%d;%.2f", sensores[i].id_sensor, sensores[i].timestamp, sensores[i].valor);
        }
        fclose(arquivo_saida);
    }
        
    printf("Arquivos gerados com sucesso!");
    return 0;

}