																/*Trabalho 1
												GRR20197154 - Giordano Henrique Silveira */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lista.h"

#define MAX 100


struct t_node {
	char *key;
	struct t_node *left, *right, *pai;   
};
typedef struct t_node t_node;

//Aloca espaço na memória para um vetor de char
char *allocate_men (int n) {

	char *vetor;

	vetor = malloc(sizeof(char)*n);
    if (!vetor) {                                           //Testa para ver se foi possível alocar espaço na memória
        perror ("Não foi possível alocar memória");
        exit (1);
    }

	return vetor;
}

//Cria um nó da árvore e retorna ele 
t_node *create_node (const char *numero) {
	
	t_node *new;

    //Aloca espaço e testa para ver se alocou
	new = (t_node*)malloc(sizeof(t_node));
    if (!new) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

    //Aloca espaço para o vetor de string da estrutura
	new->key = allocate_men(MAX);
    strcpy (new->key, numero);

    //Inicializa o ponteiro da esquerda, direita e pai como NULL	
	new->left = NULL;
	new->right = NULL;
	new->pai = NULL;

	return new;

}

//Recebe como parametro uma expressão de parênteses alinhados e monta a árvore;
//Retorna a árvore montada
t_node *monta_arvore(char *expr, int *i){

    int j;
    char *num;

    //Espaço para o vetor auxiliar que vai receber os números e as operações
    num = allocate_men (MAX);

	t_node *tree;
	tree = NULL;

    //Testa para ver se é um parênteses aberto
    //Ou seja, se vai precisar criar um novo nodo
	if (expr[*i] == '(') {
		
        (*i)++;
        j = 0;                                              //índice para o vetor num

        //Enquanto não é uma parênteses fechado (fim de um nó) ou aberto (começo de outro nó),
        //copia esses caracteres para o vertor num
        while (expr[*i] != ')' && expr[*i] != '(') {    
            num[j] = expr[*i];
            j++;
            (*i)++;
        }
        num[j] = '\0';

        //Mostra qual nó vai ser criado e cria esse nó
		printf("Criando nó %s\n", num);
		tree = create_node (num);

        //Monta primeiramente a árvore da esquerda e depois a direita
		tree->left = monta_arvore(expr,i);
		tree->right = monta_arvore(expr,i);
		(*i)++;
	}
	return tree;
	
}

//Anda de maneira "pos-ordem" arvore e coleta o resultado das operações
//Retorna o resultado da conta
long avalia_expressao (t_node* raiz) {

	int r_valor, l_valor;
    char *ptr;

    //Checa para ver se o nó é válido
	if (raiz == NULL)
		return 0;

    //Checa para ver se é um número
    //É um número se ambos filhos forem nulos, ou seja, se é um nó folha
	if (!raiz->left && !raiz->right)
		return strtol (raiz->key, &ptr, 10);
	
    //Recursivamente vai montando as operações
    //Vem da última sub-árvore da esquerda
	l_valor = avalia_expressao (raiz->left);
	r_valor = avalia_expressao (raiz->right);

    //Volta a chamada da recursão exatamente no nó do operador
    //É só checar para ver qual é a operação correspondente e efetuar essa operação
	if (strcmp(raiz->key,"+") == 0)
		return l_valor + r_valor;

	if (strcmp(raiz->key,"-") == 0)
		return l_valor - r_valor;
		
	if (strcmp(raiz->key,"*") == 0)
		return l_valor * r_valor;
		
    //A divisão merece uma atenção a mais por causa da divisão por 0
	if (strcmp(raiz->key,"/") == 0) {
		if (r_valor == 0) {
			printf ("Valor inválido - divisão por 0 - encerrando programa\n");
			exit (1);
		}
		return l_valor / r_valor;
	}

}
/*int analiza_parenteses(char *expr, t_lista *lista){

	char lixo;
	int i, tam;
	i = 0;

	tam = strlen (expr);
	for (i = 0; i < tam; i++){
		if (((expr[i] < 40 && expr[i] != 10 )|| expr[i] == 44 || expr[i] == 46 || expr[i] > 57)) {
			printf ("Caractere inválido: %c\n", expr[i]);
			return 0;
		}
		if (expr[i] == '('){
			if (! insere_fim_lista (expr[i], lista)) {
				printf ("Os parenteses estão mal colocados\n");
				//printf ("Não foi possível adicionar o elemento a lista\n");
				exit (1);
			}
		}
		else if (expr[i] == ')'){
			if (! remove_ultimo_lista(&lixo, lista)) {
				printf ("Os parenteses estão mal colocados\n");
				//printf ("Não foi possível remover os elemento da lista\n");
				return 0;
			}
		}
	}

	if (!lista_vazia (lista)) {
		printf ("Os parenteses estão mal colocados\n");
		return 0;
	}

	return 1;
}*/
void destroi_arvore (t_node* no) {
	if (no != NULL) {
		destroi_arvore (no->left);
		destroi_arvore (no->right);
		free (no->key);
		free (no);
	}
}
int main () {

	t_lista *lista;
	long resultado;
	char *expressao;
	t_node *arvore;

	int i = 0;

	lista = (t_lista*)malloc(sizeof(t_lista));
	if (! cria_lista(lista)){
		exit (1);
	}

    //Aloca espaço na memória para o vetor da expressão
	expressao = allocate_men (MAX);
	
    //Lê a expressão de parenteses alinhados do teclado
	fgets (expressao, MAX, stdin);

	//Analiza a expressão para ver se ela é válida
	/*if (! analiza_parenteses(expressao,lista)){
		printf ("A algo de errado com a expressão\n");
		exit (1);
	}*/

    //monta a árvore
	arvore = monta_arvore(expressao, &i);
    printf ("\n");

    //Calcula o resultado da árvore
	resultado = avalia_expressao (arvore);

	printf ("Resultado = %ld\n", resultado);

	destroi_arvore(arvore);
	destroi_lista (lista);
	free(expressao);
	free(lista);

	return 0;
}