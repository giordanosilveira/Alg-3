#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100


struct t_node {
	char *key;
	struct t_node *left, *right, *pai;   
};
typedef struct t_node t_node;

int *allocate_menI (int n) {

	int *vetor;

	vetor = malloc(sizeof(int)*n);
    if (!vetor) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

	return vetor;

}
char *allocate_men (int n) {

	char *vetor;

	vetor = malloc(sizeof(char)*n);
    if (!vetor) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

	return vetor;
}

t_node *create_node (const char *numero) {
	
	t_node *new;
	new = (t_node*)malloc(sizeof(t_node));

    if (!new) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

	new->key = allocate_men(MAX);
    strcpy (new->key, numero);
    	
	new->left = NULL;
	new->right = NULL;
	new->pai = NULL;

	return new;

}
t_node *monta_arvore(char *expr, int *i){

    int j;
    char *num;

    num = allocate_men (MAX);

	t_node *tree;
	tree = NULL;
	if (expr[*i] == '(') {
		
        (*i)++;
        j = 0;
        while (expr[*i] != ')' && expr[*i] != '(') {
            num[j] = expr[*i];
            j++;
            (*i)++;
        }
        num[j] = '\0';

		printf("Criando nó %s\n", num);
		tree = create_node (num);

		tree->left = monta_arvore(expr,i);
		tree->right = monta_arvore(expr,i);
		(*i)++;
	}
	return tree;
	
}
/*void posordem(t_node *no){
    if (no != NULL){    
        posordem(no->left);        
        printf ("%s\n", no->key);
        posordem(no->right);
    }
}*/
long avalia_expressao (t_node* raiz) {

	int r_valor, l_valor;
    char *ptr;

	if (raiz == NULL)
		return 0;

	if (!raiz->left && !raiz->right)
		return strtol (raiz->key, &ptr, 10);
	
	l_valor = avalia_expressao (raiz->left);
	r_valor = avalia_expressao (raiz->right);

	if (strcmp(raiz->key,"+") == 0)
		return l_valor + r_valor;

	if (strcmp(raiz->key,"-") == 0)
		return l_valor - r_valor;
		
	if (strcmp(raiz->key,"*") == 0)
		return l_valor * r_valor;
		
	if (strcmp(raiz->key,"/") == 0) {
		if (r_valor == 0) {
			printf ("Valor inválido - divisão por 0 - encerrando programa\n");
			exit (1);
		}
		return l_valor / r_valor;
	}

}
int main () {

	long resultado;
	char *expressao;
	t_node *arvore;

	int i = 0;
	expressao = allocate_men (MAX);
	
	fgets (expressao, MAX, stdin);

	arvore = monta_arvore(expressao, &i);
    printf ("\n");
    
	resultado = avalia_expressao (arvore);

	printf ("Resultado = %ld\n", resultado);

	return 0;
}