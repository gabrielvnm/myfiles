// Essa primeira linha inclui 6 bibliotecas necessárias para o funcionamento do programa
// As mais notáveis são <time.h>, que inclui funções para registrar o tempo atual da máquina, <locale.h> inclui informações para codificação de caracteres, e <conio.h>
// que inclui funções para limpar a tela do terminal e algumas maneiras de receber inputs do usuario
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <conio.h>

// Os macros definem valores que serão usados constantemente ao longo do programa, para maior clareza no codigo

#define TAMANHO_NOME_PRODUTO 50
#define TAMANHO_MARCA 30
#define MAX 100

// essa struct Produto define as variaveis correspondentes a um único produto, utilizadas nas funções de
// cadastrar produtos, ler produtos do arquivo de banco de dados, realizar alterações e consultas e
// gerar relatórios

typedef struct
{
    int codigo;
    char nome_produto[TAMANHO_NOME_PRODUTO];
    char marca[TAMANHO_MARCA];
    int estoque;
    float custo;
    float venda;
    float lucro;
} Produto;

// a segunda struct define variaveis a serem utilizadas para a venda de um produto e geração da nota fiscal

typedef struct
{
    int codigo_produto;
    char nome_produto[TAMANHO_NOME_PRODUTO];
    int qtd_produto;
    float venda;
    float valor_total;
    int tipo_pagamento; // vetor para poder obter forma de pagamento
} Vendas;

// essa parte faz a declaração das funções e seus argumentos, antes de definir as funções.
// Declarar as funções antes da função principal int main() permite que elas sejam definidas em qualquer ordem ao longo do código

void cadastrarProduto();
void abrirArquivoProdutos(FILE *arquivo);
void limparBuffer();
void sairComQualquerTecla();
void limparTela();
int obterInteiroPositivo(const char *mensagem);
float obterFloatPositivo(const char *mensagem);
void alterarProduto();
int obterQuantidadeProduto(int estoque);
void registrarVenda(Vendas *venda, int codigo, const char *nome_produto, int qtd_produto, float venda_valor);
void gerarVendas();
void venderProdutos();
void exibirCupomHeader(FILE *arquivo, const char *data, const char *hora, int numero_nota);
void exibirDetalhesProduto(FILE *arquivo, Vendas *venda);
void exibirCupomFooter(FILE *arquivo, int totalItens, float valorTotal, int tipo, const char *digitos);
void exibirNotaFiscal(Vendas *ptr_vetor_vendas, int tamanho, int tipo);
void gerarChaveAcesso(char *sequencia);
void exibirProdutos();
int compararCodigoProduto(int numero);
void credito();

// essa função será usada para cadastrar um produto em um arquivo .txt que será utilizado como banco de dados

void cadastrarProduto()
{

    limparTela();

    printf("========================\n");
    printf("Cadastro de produtos:\n");
    printf("========================\n");

    // essas linhas abrem o arquivo de produtos
    FILE *arquivo;
    abrirArquivoProdutos(arquivo);

    Produto produto; // aqui estamos criando uma variavel do tipo struct Produto chamada produto

    // essa parte do código vai ler o Código do produto digitado pelo usuário, conferindo se ele existe na base de dados
    do
    {
        printf("\nDigite o código do produto: ");

        if (scanf("%d", &produto.codigo) != 1 || produto.codigo <= 0)
        {
            printf("Entrada inváplida! O código deve ser um número inteiro positivo.\n");
            LimparBuffer();
        }
        else if (compararCodigoProduto(produto.codigo))
        {
            printf("Código já existente! Digite outro código!\n");
        }
        else
        {
            break;
        }

    } while (1);

    limparBuffer(); // após conferir o código e sair da função anterior, limpa o buffer

    // as proximas funções leem o input do usuário para as outras variaveis da struct Produto

    // Lendo Nome do produto...
    printf("\nDigite o nome do produto:");
    fgets(produto.nome_produto, 50, stdin);
    produto.nome_produto[strcspn(produto.nome_produto, "\n")] = 0;

    // Lendo Marca do produto...
    printf("\nDigite a marca do produto:");
    fgets(produto.marca, 50, stdin);
    produto.marca[strcspn(produto.marca, "\n")] = 0;

    // Lendo Estoque do produto...
    do
    {
        printf("\nDigite o estoque do produto:");

        if (scanf("%d", &produto.estoque) != 1 || produto.estoque <= 0) // verificação para números inválidos ou negativos
        {
            printf("\nEntrada inválida! O estoque não pode ser negativo.\n");
            limparBuffer();
        }
        else
        {
            break;
        }

    } while (1);

    limparBuffer();

    // Lendo Custo do produto...
    do
    {
        printf("\nDigite o custo do produto:");

        if (scanf("%f", &produto.custo) <= 0)
        {
            printf("\nEntrada inválida! O custo do produto não pode ser negativo;\n");
            limparBuffer();
        }
        else
        {
            break;
        }

    } while (1);

    limparBuffer();

    // Lendo Preço de venda do produto...
    printf("\nDigite o preço de venda do produto:");
    scanf("%f", &produto.venda);
    getchar();

    // Calculando o lucro do produto...
    printf("\nLucro bruto obtido na venda: ");
    produto.lucro = produto.venda - produto.custo;
    printf("R$%.2f\n", produto.lucro);

    char resposta;

    // a parte a seguir executa algumas funções para gravar os dados armazenados nos passos anteriores no arquivo de banco de dados

    do
    {
        printf("\nDeseja finalizar o cadastro? (S para Sim, N para Não): ");
        resposta = getchar();
        limparBuffer();

        if (resposta == 'S' || resposta == 's') // verificação para salvar ou não o produto criado
        {
            // Gravando os dados no arquivo...
            fprintf(arquivo, "%d; %s; %s; %d; %.2f; %.2f; %.2f\n",
                    produto.codigo,
                    produto.nome_produto,
                    produto.marca, produto.estoque,
                    produto.custo,
                    produto.venda,
                    produto.lucro); // essa linha vai escrever no arquivo .txt os dados digitados pelo usuário
                                    // em cada etapa, separados por um ; (para que ela também possa ser utilizada como .csv)

            printf("\nProduto %s cadastrado com sucesso!\n", produto.nome_produto);
            fclose(arquivo);
            break; // Finalizando o cadastro...
        }
        else if (resposta == 'N' || resposta == 'n')
        {
            printf("\nCadastro cancelado.\n");
            fclose(arquivo);
            return; // Cancelando o cadastramento e retornando à tela anterior...
        }
        else
        {
            printf("\nResposta inválida! Por favor, digite 'S' para Sim ou 'N' para Não.\n");
        }

    } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');

    sairComQualquerTecla();

    limparTela();
}

// essa função recebe o ponteiro do arquivo de banco de dados e é utilizada para abrir o arquivo.
// caso o programa não encontra um arquivo correspondente uma mensagem de erro será exibida

void abrirArquivoProdutos(FILE *arquivo)
{
    arquivo = fopen("produtos.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }
}

// função para limpar o buffer, utilizada para evitar entradas incorretas da memória e gravações em variaveis erradas

void limparBuffer()
{
    // Consome os caracteres restantes no buffer até encontrar o '\n' ou EOF
    while (getchar() != '\n' && getchar() != EOF)
        ;
}

// função para receber qualquer tecla como input

void sairComQualquerTecla()
{
    printf("Aperte qualquer tecla para sair: \n");

    while (1)
    {
        if (_kbhit())
        {
            char tecla = getch();
            break;
        }
    }
}

// essa função usa alguns comandos de C para interagir com o terminal do sistema operacional e limpar a tela
void limparTela()
{
#ifdef _WIN32 // verifica se o sistema é Windows ou não
    system("cls");
#else
    system("clear");
#endif
}

// essa função é utilizada no programa na opção de editar produtos para receber dados do usuário e atualizar o banco com os dados novos

int obterInteiroPositivo(const char *mensagem)
{
    int valor;
    char armazenador[50];

    // os dados digitados pelo usuario são armazenados em uma string, e depois transformados em integers
    do
    {
        printf("%s", mensagem);
        if (fgets(armazenador, sizeof(armazenador), stdin))
        {
            if (armazenador[0] == '\n')
                break; // Mantém o valor atual caso o usuário digite Enter

            if (sscanf(armazenador, "%d", &valor) != 1 || valor <= 0)
            {
                printf("Entrada inválida! O valor deve ser positivo.\n");
            }
            else
            {
                return valor;
            }
        }
        limparBuffer();
    } while (1);
    return -1; // Retorna valor inválido caso o usuário deseje manter o valor
}


// essa função é similar à anterior, mas transforma os dados capturados em variaveis do tipo float
float obterFloatPositivo(const char *mensagem)
{
    float valor;
    char armazenador[50];

    do
    {
        printf("%s", mensagem);
        if (fgets(armazenador, sizeof(armazenador), stdin))
        {
            if (armazenador[0] == '\n')
                break; // Mantém o valor atual

            if (sscanf(armazenador, "%f", &valor) != 1 || valor <= 0)
            {
                printf("Entrada inválida! O valor deve ser positivo.\n");
            }
            else
            {
                return valor;
            }
        }
        limparBuffer();
    } while (1);
    return -1; // Retorna valor inválido caso o usuário deseje manter o valor
}

// essa é a função que permite alterar quaisquer informações do banco de dados e substituí-las na mesma linha, usando as funções descritas anteriormente
// o código do produto, porém, não pode ser alterado.

void alterarProduto()
{

    FILE *ptr_arquivo_produtos;
    char linha[MAX];
    char cod_produto[MAX];
    char result[MAX];
    int i = 0;
    char reescrita[MAX];
    Produto produto;

    exibirProdutos(); // exibe a lista de produtos cadastrados
    printf("\nInforme o codigo do produto que deseja alterar:\n");
    scanf("%s", cod_produto);
    limparBuffer();

    // essa função abre o arquivo de produtos. Caso não exista um arquivo de produtos o programa retorna uma mensagem de erro.

    ptr_arquivo_produtos = fopen("produtos.txt", "r+"); 
    if (ptr_arquivo_produtos == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return;
    }

    while (fgets(linha, MAX, ptr_arquivo_produtos)) // armazena o input do banco em uma string
    {
        i = 0;
        while (linha[i] != ';' && linha[i] != '\0') // continua lendo os caracteres até encontrar ; e armazena o resultado lido em outra string
        {
            result[i] = linha[i];
            i++;
        }
        result[i] = '\0'; // inclui o fim da string 

        if (strcmp(cod_produto, result) == 0) // essa função compara o código do produto digitado com a string da memória
        {
            printf("========================\n");
            printf("Produto encontrado!\n");
            printf("========================\n");
            printf("## ALTERANDO PRODUTO ##\n");
            printf("========================\n");
            printf("Informe apenas os campos que deseja alterar\ncaso não queira, deixe em branco!\n");

            // Nome do produto
            printf("\nDigite o nome do produto (pressione Enter para manter o valor atual): ");
            fgets(produto.nome_produto, 50, stdin);
            produto.nome_produto[strcspn(produto.nome_produto, "\n")] = 0;
            sprintf(reescrita, "%s; %s", result, produto.nome_produto);

            // Marca do produto
            printf("\nDigite a marca do produto (pressione Enter para manter o valor atual): ");
            fgets(produto.marca, 50, stdin);
            produto.marca[strcspn(produto.marca, "\n")] = 0;
            sprintf(reescrita, "%s; %s", reescrita, produto.marca);

            // Estoque
            produto.estoque = obterInteiroPositivo("\nDigite o estoque do produto (pressione Enter para manter o valor atual): ");
            if (produto.estoque != -1)
            {
                sprintf(reescrita, "%s; %d", reescrita, produto.estoque);
            }

            // Custo
            produto.custo = obterFloatPositivo("\nDigite o custo do produto (pressione Enter para manter o valor atual): ");
            if (produto.custo != -1)
            {
                sprintf(reescrita, "%s; %.2f", reescrita, produto.custo);
            }

            // Preço de venda
            produto.venda = obterFloatPositivo("\nDigite o preço de venda do produto (pressione Enter para manter o valor atual): ");
            if (produto.venda != -1)
            {
                sprintf(reescrita, "%s; %.2f", reescrita, produto.venda);
            }

            // Lucro
            produto.lucro = produto.venda - produto.custo;
            sprintf(reescrita, "%s; %.2f", reescrita, produto.lucro);
            printf("Lucro bruto obtido na venda: R$%.2f\n", produto.lucro);

            fseek(ptr_arquivo_produtos, -strlen(linha), SEEK_CUR);
            fprintf(ptr_arquivo_produtos, "%s", reescrita);

            // Se a nova linha for menor que a original, preenche o restante com espaços. 
            // Isso é necessário porque o programa precisa sobrescrever a linha de dados anterior com as novas informações, 
            // e caso a anterior seja maior, os caracteres extras não serão deletados

            int tamanho_novo = strlen(reescrita);
            int tamanho_antigo = strlen(linha);
            if (tamanho_novo < tamanho_antigo)
            {
                for (int j = 0; j < (tamanho_antigo - tamanho_novo); j++)
                {
                    fputc(' ', ptr_arquivo_produtos); // inclui espaços para apagar os caracteres restantes na linha antiga
                }
            }

            break;
        }
    }

    fclose(ptr_arquivo_produtos); // fecha o arquivo
}

// essa função é utilizada ao realizar uma venda para comparar o valor digitado com o estoque

int obterQuantidadeProduto(int estoque)
{
    int qtd_produto;
    do
    {
        printf("Digite a quantidade que será vendida: ");
        if (scanf("%d", &qtd_produto) != 1 || qtd_produto <= 0 || qtd_produto > estoque)
        {
            printf("\nQuantidade inválida ou superior ao estoque disponível!\n");
            while (getchar() != '\n')
                ; // Limpa o buffer
        }
        else
        {
            break;
        }
    } while (1);
    return qtd_produto;
}

// essa função recebe os valores armazenados em algumas variaveis utilizadas durante a venda e 
// armazena em outras variaveis para posterior gravação das vendas

void registrarVenda(Vendas *venda, int codigo, const char *nome_produto, int qtd_produto, float venda_valor)
{
    venda->codigo_produto = codigo;
    strcpy(venda->nome_produto, nome_produto);
    venda->qtd_produto = qtd_produto;
    venda->venda = venda_valor;
    venda->valor_total = qtd_produto * venda_valor;
}

// essa função é usada para exibir o menu de vendas 

void gerarVendas()
{
    limparTela();

    FILE *arquivo = fopen("produtos.txt", "r"); // abre o arquivo de produtos
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    int op;
    do
    {
        printf("\n===== PDV =====\n"); // menu de vendas
        printf(
            "[1] - Consultar produtos\n"
            "[2] - Gerar vendas\n"
            "[3] - Voltar\n");
        printf("\nEscolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            ExibirProdutos();
            break;

        case 2:
            VenderProdutos();
            break;

        case 3:
            break;
        }
    } while (op != 3);

    fclose(arquivo);
    limparTela();
}

// função para gerar vendas, verificando o arquivo de produtos e o de vendas para gravar as informações de qualquer venda em um arquivo .csv
// cada venda gerará um código único para identificar quando mais de um tipo de produto for vendido ao mesmo tempo.

void venderProdutos()
{
    limparTela();
    int n;
    const char *nome_arquivo = "numero_nota.txt";
    int numero_nota = ler_numero_nota(nome_arquivo);

    FILE *arquivo = fopen("produtos.txt", "r"); // 
    FILE *vendas = fopen("vendas.txt", "a+");
    if (arquivo == NULL || vendas == NULL)
    {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    // função da biblioteca <time.h> para obter data e hora atuais
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data[20], hora[20];
    strftime(data, sizeof(data), "%d/%m/%Y", &tm);
    strftime(hora, sizeof(hora), "%H:%M:%S", &tm);

    // Obter a quantidade de produtos a serem vendidos
    printf("Informe quantos produtos diferentes deseja vender: ");
    scanf("%d", &n);
    int cod_produtos[n];
    for (int i = 0; i < n; i++)
    {
        do
        {
            printf("Informe o codigo do %dº produto que irá realizar a venda: ", i + 1);
            if (scanf("%d", &cod_produtos[i]) != 1 || !CompararCodigoProduto(cod_produtos[i]))
            {
                printf("Código do produto inválido ou produto não encontrado!\n");
                while (getchar() != '\n')
                    ; // Limpa o buffer
            }
            else
            {
                break;
            }
        } while (1);
    }

    // Variáveis para processamento de venda
    int codigo, estoque, formaPagamento;
    float custo, venda, lucro;
    char nome_produto[50], marca[50];
    Vendas vetor_vendas[n];
    int contador = 0;

    // Processar cada produto
    while (fscanf(arquivo, "%d; %49[^;]; %49[^;]; %d; %f; %f; %f\n",
                  &codigo, nome_produto, marca, &estoque, &venda, &custo, &lucro) == 7)
    {
        for (int i = 0; i < n; i++)
        {
            if (cod_produtos[i] == codigo)
            {
                int qtd_produto = obterQuantidadeProduto(estoque);
                if (qtd_produto > 0)
                {
                    registrarVenda(&vetor_vendas[contador], codigo, nome_produto, qtd_produto, venda);
                    contador++;
                }
                break;
            }
        }
    }

    // Obter a forma de pagamento
    limparTela();
    printf("\nDigite a forma de pagamento:\n[1] - Dinheiro\n[2] - Cartão débito\n[3] - Cartão crédito: ");
    scanf("%d", &formaPagamento);

    // Gravar vendas no arquivo
    for (int i = 0; i < contador; i++)
    {
        fprintf(vendas, "venda;%d;%s;%d;%.2f;%.2f;%s;%s;%d\n",
                numero_nota, vetor_vendas[i].nome_produto,
                vetor_vendas[i].qtd_produto, vetor_vendas[i].venda,
                vetor_vendas[i].valor_total, data, hora, formaPagamento);
    }

    // Exibir mensagem de sucesso e a nota fiscal
    printf("\nVenda realizada com sucesso!\n");
    exibirNotaFiscal(vetor_vendas, contador, formaPagamento);

    fclose(arquivo);
    fclose(vendas);
}

// função para exibir o cabeçalho do cupom fiscal
void exibirCupomHeader(FILE *arquivo, const char *data, const char *hora, int numero_nota)
{
    fprintf(arquivo, "===============================================\n");
    fprintf(arquivo, "              CUPOM FISCAL ELETRÔNICO          \n");
    fprintf(arquivo, "===============================================\n");
    fprintf(arquivo, "Loja LUIZ INÁCIO LTDA\n");
    fprintf(arquivo, "CNPJ: 66.666.666/0001-66\n");
    fprintf(arquivo, "Endereço: Congresso Nacional, 666 - Esquerda\n");
    fprintf(arquivo, "IE:000.000000.0000    CEP: 66666-666\n");
    fprintf(arquivo, "-----------------------------------------------\n");
    fprintf(arquivo, "Data:  %s     Hora: %s  Cupom: %d\n", data, hora, numero_nota);
    fprintf(arquivo, "Operador: Alexandre de Morais\n");
    fprintf(arquivo, "===============================================\n");
    fprintf(arquivo, "CÓDIGO   DESCRIÇÃO        QTD     UNIT.    TOTAL \n");
    fprintf(arquivo, "-----------------------------------------------\n");
}

void exibirDetalhesProduto(FILE *arquivo, Vendas *venda)
{
    fprintf(arquivo, "%-7d  %-10s      %-2d    %-8.2f   %-10.2f\n",
            venda->codigo_produto, venda->nome_produto, venda->qtd_produto, venda->venda, venda->valor_total);
}

// função para exibir o rodapé do cupom fiscal 

void exibirCupomFooter(FILE *arquivo, int totalItens, float valorTotal, int tipo, const char *digitos)
{
    fprintf(arquivo, "-----------------------------------------------\n");
    fprintf(arquivo, "QTD. total de itens         %d\n", totalItens);
    fprintf(arquivo, "Valor total do desconto                 R$ 0,00\n");
    fprintf(arquivo, "TOTAL                                 R$ %.2f\n", valorTotal);
    fprintf(arquivo, "-----------------------------------------------\n");
    fprintf(arquivo, "IMPOSTO TOTAL PAGO:                  R$ %.2f\n", valorTotal * 0.30);
    fprintf(arquivo, "-----------------------------------------------\n");

    // Forma de pagamento, dinheiro, cartao de débito ou crédito
    if (tipo == 1)
    {
        fprintf(arquivo, "FORMA DE PAGAMENTO: DINHEIRO \n");
    }
    else if (tipo == 2)
    {
        fprintf(arquivo, "FORMA DE PAGAMENTO: CARTÃO DÉBITO \n");
    }
    else if (tipo == 3)
    {
        fprintf(arquivo, "FORMA DE PAGAMENTO: CARTÃO CRÉDITO \n");
    }

    fprintf(arquivo, "-----------------------------------------------\n");
    fprintf(arquivo, "        Chave de acesso\n");
    fprintf(arquivo, " %s\n", digitos); // Exibe os 44 dígitos gerados
    fprintf(arquivo, "===============================================\n");
    fprintf(arquivo, "          Obrigado por comprar conosco!        \n");
    fprintf(arquivo, "===============================================\n");
}

// função para exibir e imprimir a nota fiscal inteira, incluindo algumas informações geradas ao longo da venda do produto

void exibirNotaFiscal(Vendas *ptr_vetor_vendas, int tamanho, int tipo)
{

    limparTela();

    const char *nome_arquivo = "numero_nota.txt";
    if (incrementar_nota(nome_arquivo) != 0)
    {
        fprintf(stderr, "Falha ao incrementar o número da nota.\n");
        return;
    }

    int numero_nota = ler_numero_nota(nome_arquivo);
    if (numero_nota == -1)
    {
        fprintf(stderr, "Falha ao ler o número da nota.\n");
        return;
    }

    char digitos[45];
    gerarChaveAcesso(digitos);

    // Obter data e hora atuais
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data[20], hora[20];
    strftime(data, sizeof(data), "%d/%m/%Y", &tm);
    strftime(hora, sizeof(hora), "%H:%M:%S", &tm);

    // Exibir cabeçalho do cupom fiscal
    printf("===============================================\n");
    printf("              CUPOM FISCAL ELETRÔNICO          \n");
    printf("===============================================\n");
    printf("Loja LUIZ INÁCIO LTDA\n");
    printf("CNPJ: 66.666.666/0001-66\n");
    printf("Endereço: Congresso Nacional, 666 - Esquerda\n");
    printf("IE:000.000000.0000    CEP: 66666-666\n");
    printf("-----------------------------------------------\n");
    printf("Data:  %s     Hora: %s  Cupom: %d\n", data, hora, numero_nota);
    printf("Operador: Alexandre de Morais\n");
    printf("===============================================\n");
    printf("CÓDIGO   DESCRIÇÃO        QTD     UNIT.    TOTAL \n");
    printf("-----------------------------------------------\n");

    // Processar e exibir cada item vendido
    int totalItens = 0;
    float valorTotal = 0;
    for (int i = 0; i < tamanho; i++)
    {
        Vendas venda = ptr_vetor_vendas[i];
        totalItens += venda.qtd_produto;
        valorTotal += venda.valor_total;

        printf("%-7d  %-10s      %-2d    %-8.2f   %-10.2f\n",
               venda.codigo_produto, venda.nome_produto, venda.qtd_produto, venda.venda, venda.valor_total);
    }

    printf("-----------------------------------------------\n");
    printf("QTD. total de itens         %d\n", totalItens);
    printf("Valor total do desconto                 R$ 0,00\n");
    printf("TOTAL                                 R$ %.2f\n", valorTotal);
    printf("-----------------------------------------------\n");
    printf("IMPOSTO TOTAL PAGO:                  R$ %.2f\n", valorTotal * 0.30);
    printf("-----------------------------------------------\n");

    // Exibir forma de pagamento
    if (tipo == 1)
    {
        printf("FORMA DE PAGAMENTO: DINHEIRO \n");
    }
    else if (tipo == 2)
    {
        printf("FORMA DE PAGAMENTO: CARTÃO DÉBITO \n");
    }
    else if (tipo == 3)
    {
        printf("FORMA DE PAGAMENTO: CARTÃO CRÉDITO \n");
    }

    // Exibir chave de acesso
    printf("Chave de acesso: %s\n", digitos);
    printf("===============================================\n");
    printf("          Obrigado por comprar conosco!        \n");
    printf("===============================================\n");

    // Salvar o cupom fiscal em um arquivo
    char nomeArquivo[100];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "C:\\Área de Trabalho\\Curso C\\projeto final adam\\NOTAS\\nota_fiscal_%d.txt", time(NULL));

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Gravar os dados no arquivo
    exibirCupomHeader(arquivo, data, hora, numero_nota);
    for (int i = 0; i < tamanho; i++)
    {
        exibirDetalhesProduto(arquivo, &ptr_vetor_vendas[i]);
    }
    exibirCupomFooter(arquivo, totalItens, valorTotal, tipo, digitos);

    fclose(arquivo);
    printf("Cupom fiscal gerado em '%s'\n", nomeArquivo);
    printf("Aperte qualquer tecla para sair: \n");

    // Aguarda a tecla pressionada
    while (!_kbhit())
    {
    }
    getch();

    limparTela();
}
// função para gerar um número aleatorio para a nota fiscal
void gerarChaveAcesso(char *sequencia)
{

    int i;
    for (i = 0; i < 44; i++)
    {
        sequencia[i] = '0' + (rand() % 10); // random number generator
    }
    sequencia[44] = '\0';
}

// função que escaneia o arquivo de produtos linha por linha, armazenando os valores entre ; nas variaveis da struct produtos e exibindo para o usuário
void exibirProdutos()
{

    limparTela();

    FILE *arquivo;
    AbrirArquivoProdutos(arquivo);

    printf("========================\n");
    printf("=== PRODUTOS CADASTRADOS ===\n");
    printf("========================\n");

    int codigo, estoque;
    float custo, venda, lucro;
    char nome_produto[50], marca[50];

    printf("----------------------------------------------------------------------------------");
    printf("\n%-7s|%-15s|%-15s|%-8s|%-10s|%-10s|%-10s\n", "Código", "Nome", "Marca", "Estoque", "Custo", " Venda", "  Lucro");
    printf("----------------------------------------------------------------------------------\n");
    while (fscanf(arquivo, "%d; %49[^;]; %49[^;]; %d; %f; %f; %f\n", &codigo, nome_produto, marca, &estoque, &custo, &venda, &lucro) == 7)
    {
        printf("%-7d|%-15s|%-15s|%-8d|R$%-9.2f|R$%-9.2f|R$%-9.2f\n", codigo, nome_produto, marca, estoque, custo, venda, lucro);
        printf("----------------------------------------------------------------------------------\n");
    }

    fclose(arquivo);
}

// função para escanear o arquivo de produtos e comparar o código do produto digitado pelo usuário até encontrar um match

int compararCodigoProduto(int numero)
{

    FILE *arquivo;
    abrirArquivoProdutos(arquivo);

    int codigo, estoque;
    float custo, venda, lucro;
    char nome_produto[50], marca[50];

    while (fscanf(arquivo, "%d; %49[^;]; %49[^;]; %d; %f; %f; %f\n", &codigo, nome_produto, marca, &estoque, &custo, &venda, &lucro) == 7) // escaneia cada linha do produtos.txt armazenando os valores entre ; nas variaveis
    {
        if (numero == codigo)
        {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// creditos dos programadores que fizeram essa bagaça enorme hihihi

void credito()
{
    limparTela();

    printf("========================\n");
    printf("\tDEVELOPERS\n");
    printf("========================\n");
    printf("\nAugusto Sérgio");
    printf("\nGabriel Martins");
    printf("\nSamuel Dias da silva Dantas");
    printf("\nJose Leonardo Neves da silva");
    printf("\nWeslley Silva Pinheiro");

    printf("Digite qualquer tecla para voltar...");
    sairComQualquerTecla();

}

// função para abrir o arquivo em formato csv
void abrirArquivoCsv(FILE *csv, char path[])
{
    csv = fopen(path, "w");

    if (csv == NULL)
    {
        printf("Erro ao abrir o arquivo CSV de produtos!\n");
        return;
    }
}
// função para salvar o arquivo de produtos em formato .csv
void GerarCSV() {
    
	limparTela();

    FILE *arquivo;
    abrirArquivoProdutos(arquivo);

	FILE *csv;
    abrirArquivoCsv(csv, "C:\\Área de Trabalho\\Curso C\\projeto final adam\\RELATORIOS\\produtos.csv");

	fprintf(csv, "Código;Nome;Marca;Estoque;Custo;Venda;Lucro\n"); 

	int codigo, estoque; 
	float custo, venda, lucro;
	char nome_produto[50], marca[50];

	while (fscanf(arquivo, "%d; %49[^;]; %49[^;]; %d; %f; %f; %f\n", &codigo, nome_produto, marca, &estoque, &custo, &venda, &lucro) == 7) {
		fprintf(csv, "%d;%s;%s;%d;%.2f;%.2f;%.2f\n", codigo, nome_produto, marca, estoque, custo, venda, lucro); 
	} 

	fclose(arquivo); 
	fclose(csv); 

	printf("\nRelatório gerado com sucesso em 'C:\\Área de Trabalho\\Curso C\\projeto final adam\\RELATORIOS\\produtos.csv'!\n");

}

// função para abrir o arquivo vendas.txt
void abrirArquivoVendas(FILE *arquivo)
{
    arquivo = fopen("vendas.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return;
    }
}
// função para gerar o relatório de vendas
void gerarRelatorioVenda() {

	limparTela();
	
    FILE *arquivo;
    abrirArquivoVendas(arquivo);

    FILE *csv;
    abrirArquivoCsv(csv, "D:\\code\\adam trabalho\\relatorios_vendas.csv");

    if (arquivo == NULL || csv == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    fprintf(csv, "Numero da Venda; Nome do Produto; Quantidade; Custo Unitario; Valor de Venda; Data; Hora; Tipo de Pagamento\n");

    int numero_venda, quantidade, tipo_pagamento;
    float custo, venda;
    char nome_produto[50], data[20], hora[20];

    while (fscanf(arquivo, "venda;%d;%[^;];%d;%f;%f;%[^;];%[^;];%d\n",
                  &numero_venda, nome_produto, &quantidade, &custo, &venda, data, hora, &tipo_pagamento) == 8) {
        fprintf(csv, "%d; %s; %d; %.2f; %.2f; %s; %s; %d\n",
                numero_venda, nome_produto, quantidade, custo, venda, data, hora, tipo_pagamento);
    }

    fclose(arquivo);
    fclose(csv);     

    printf("Relatório gerado com sucesso\n");
}

int main()
{

    // esta função codifica os caracteres para aceitar Latino Básico como input e output
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    // essa parte realiza a exibição do menu principal com as opções para o usuário
    do
    {
        printf("========================\n");
        printf("=    Menu de Opções    =\n");
        printf("========================\n");

        printf(
            "[1] - Realizar uma venda\n"
            "[2] - Consultar vendas\n"
            "[3] - Consultar produtos\n"
            "[4] - Cadastrar produto\n"
            "[5] - Gerar relatório\n"
            "[6] - Alterar um produto\n"
            "[7] - Créditos\n"
            "[10] - Sair do sistema\n");

        printf("\nDigite a escolha: ");
        scanf("%d", &opcao);
        // esse switch chama as funções respectivas de cada uma das opções do menu principal
        switch (opcao)
        {
        case 1:

            gerarVendas();

            break;

        case 2:

            consultarVendas();

            break;

        case 3:

            exibirProdutos();
            sairComQualquerTecla();
            limparTela();

            break;

        case 4:

            cadastrarProduto();

            break;

        case 5:

            gerarRelatorios();

            break;

        case 6:

            alterarProduto();

            break;

        case 7:

            creditos();

            break;
        }

    } while (opcao != 10); // essa linha permite que o usuário continue navegando no sistema, alternando as telas até que decida sair digitando o numero 10

    return 0;
}

