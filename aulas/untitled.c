//tenta rodar esse codigo nao é só anotação blz
#include <stdio.h>

struct baralho_t {
	int naipe;
	int rank;
	struct baralho_t *next;
};

int main(){
	struct baralho_t cartas[52];
	struct baralho_t *jogador1;
	struct baralho_t *jogador2;	

/*
	for (int i = 0; i< 51; i++){
		cartas[i].next = &cartas[i+2];
	}
	
	cartas[51].next = NULL;
	cartas[52].next = NULL;
*/
	struct baralho_t c1, c2, c3, head;

	head.next = &c1;
	c1.next = &c2;
	c2.next = &c3;
	c3.next = NULL;

	c1.naipe = 3;
	c1.rank = 3;
	c2.naipe = 4;
	c2.rank = 10;
	c3.naipe = 2;
	c3.rank = 11;

	printf("carta 3 = rank %d naipe %d\n", c2.next->rank, c2.next->naipe);

	// pra acessar o elemento apontado pelo ponteiro da struct tem que usar a notação da setinha
	// no caso fica c2.next->rank ou algo assim
	// cartas[1].next->rank

	//ele passou um agoritmo maluco aqui pra adicionar um elemento no fim da lista
	//pra adicionar no começo da lista é bem mais simples
}

// exercicio

// faz uma lista encadeada de 52 cartas do baralho
// inicialize todas as cartas do baralho pra nao ficar um monte de vetor vazio
// crie uma pilha vazia pra representar a mao do jogador
// adicione 5 cartas aleatorias na mao do jogador
// exibir as cartas da mao do jogador no terminal
// menu de operações pro jogador decidir comprar uma carta ou remover a ultima recebida

// inserir verificação pra mesma carta nao poder ser adicionada mais de uma vez
// tem que criar outra lista, uma de compra e uma de descarte

// kkkk eu 100% vou programar um castigo


//algoritmo pra colocar elemento na ultima posiçao da lista
struct lista_t{
	int elementos;
	struct lista_t* next;	
};
// essa função aqui usa double pointer kkkk que nojo
// tem que usar pq ela recebe o ponteiro e tem que alterar pra onde o ponteiro inicial aponta
// entao ela tem que receber o endereço do ponteiro
void tailPush(struct lista_t **head, struct lista_t *new){
	if (head == NULL || new == NULL){
		return;
	}
	struct lista_t * last = *head;
	//verificaçao pra ver se a lista esta vazia
	if (last != NULL){
	//esse while vai percorrer a lista toda até achar o ultimo
		while(last->next == NULL && last != new){
			last = last->next;
		}
		//esse if coloca o elemento novo no final depois do while rodar
		if (last != new){
			last->next = new;
		}

	}
	//esse else roda se a lista estiver vazia, o elemento novo entra no começo
	else {
		*head = new;
	}
}

//funçao pra remover o ultimo elemento da lista e retornar o endereço do penultimo

struct lista_t tailpop(struct lista_t **head){

	if (head == NULL || new == NULL){
		return;
	}
	struct lista_t *last = *head;
	struct lista_t *before = NULL;
	
	while (last !=NULL){
		before = last;
		last = last->next;
	}
	if (before != NULL){
		before->next = NULL;

	}
	else{
		*head = NULL;
	}
	return last;
}
//funçao pra inserir no começo da lista

void headPush (struct lista_t** head, struct lista_t *new){
	if (head == NULL || new == NULL){
		return;
	}
	new->next = *head;
	*head = head;
}
//remover o primeiro da lista e retornar o end do primeiro
struct lista_t *head_pop(struct lista_t **head){
	if (head == NULL) {
		return NULL;
	}
	struct lista_t *first = head;
	if (first !=NULL){
		*head = first->next;
	}
	return first;
}

// pra usar a logica de PILHA tem que usar esse negocio aqui
struct item_t{
	int elementos;
}
struct pilha_t{
	struct item_t buffer[1000];
	int count;
}


//inserir item na pilha é assim:
struct pilha_t pilha;

pilha.buffer[pilha.count-1] = new;
pilha.count++;

// remover item da pilha é assim
pilha.count --;