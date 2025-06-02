// funçao menu

/* void exibirMenu() {
    printf("\nEscolha uma opção de ordenação:\n");
    printf("1 - Ordenar por nome (ordem alfabética)\n");
    printf("2 - Ordenar por preço (crescente)\n");
    printf("3 - Ordenar por preço (decrescente)\n");
    printf("4 - Ordenar por quantidade (crescente)\n");
    printf("5 - Ordenar por quantidade (decrescente)\n");
    printf("6 - Ordenar por código (crescente)\n");
    printf("7 - Ordenar por código (decrescente)\n");
    printf("8 - Salvar em arquivo CSV\n");
    printf("9 - Sair\n");
    printf("Opção: ");
} */

// ------------------------------------------------------------------------

// adicionar no int main() 
/* int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                ordenarPorNome(produtos, numero_linhas); // funçao feita
                break;
            case 2:
                ordenarPorPrecoCrescente(produtos, numero_linhas); 
                break;
            case 3:
                ordenarPorPrecoDecrescente(produtos, numero_linhas);
                break;
            case 4:
                ordenarPorQuantidadeCrescente(produtos, numero_linhas);
                break;
            case 5:
                ordenarPorQuantidadeDecrescente(produtos, numero_linhas);
                break;
            case 6:
                ordenarPorCodigoCrescente(produtos, numero_linhas);
                break;
            case 7:
                ordenarPorCodigoDecrescente(produtos, numero_linhas);
                break;
            case 8:
                {
                    char nomeArquivo[MAX];
                    printf("Digite o nome do arquivo CSV para salvar: ");
                    fgets(nomeArquivo, MAX, stdin);
                    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
                    salvarCSV(produtos, numero_linhas, nomeArquivo);
                }
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);
 */

