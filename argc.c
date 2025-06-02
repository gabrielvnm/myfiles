#include <stdio.h>

struct cadastro_t 
{
    char nome[128];
    int mat;
};

int interpreta(int argc, char * argv[], struct cadastro_t * cad);
int registra(struct cadastro_t * cad);

int main(int argc, char * argv[])
{
    struct cadastro_t cadastro;
    
    if (interpreta(argc, argv, &cadastro) != 0)
    {
        printf("Erro na linha de comando \r\n");
        return -1;
    }
    
    if (registra(&cadastro) != 0)
    {
        printf("Erro ao registrar no arquivo \r\n");
        return -1;
    }

    return 0;
}

int interpreta(int argc, char * argv[], struct cadastro_t * cad)
{
    return 0;
}

int registra(struct cadastro_t * cad)
{
    return 0;
}