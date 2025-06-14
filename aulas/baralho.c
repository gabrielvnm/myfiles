#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cadastro_t{
	char nome[128];
	int mat;
}

int interpreta(int argc, char* argv[],struct *cadastro_t);
int registra(struct cadastro_t *cad);

int interpreta(int argc, char* argv[],struct *cadastro_t){
	return 0;
}

int registra(struct cadastro_t *cad){
	return 0;
}
int pesquisa(int mat, struct cadastro_t* cad){

}

int main (int argc , char * argv[]){

	struct cadastro_t cadastro;

	if (interpreta(argc(argc, argv, &cadastro) !=0){
		printf("Erro na linha de comando");
		return -1;
	}
	
	int mat = atoi
	
	interpreta(argc, *argv, &cadastro);
	registra(&cadastro);
	//argc - quantidade de argumentos da linha de comando
	//argv - vetor de argumentos


	for (int i =0; i< argc; i++){
		printf("%s \r\n",argv[i]);
	}
	return 0;

}