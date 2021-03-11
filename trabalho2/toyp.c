#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128
struct t_nodeB {
    int chave;
    struct t_nodeB *left, *right, *p;
};
typedef struct t_nodeB t_nodeB;

struct t_nodeA {
    t_nodeB *chave;
    struct t_nodeA *left, *right, *p;
};
typedef struct t_nodeA t_nodeA;

t_nodeA *create_nodeA (t_nodeB *chave) {
    t_nodeA *new;

    new = (t_nodeA*)malloc(sizeof(t_nodeA));
    if (!new) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

    new->chave = chave;
    new->left = NULL;
    new->right = NULL;
    new->p = NULL;

    return new;
}
t_nodeB *create_nodeB (int numero) {
	
	t_nodeB *new;

    //Aloca espaço e testa para ver se alocou
	new = (t_nodeB*)malloc(sizeof(t_nodeB));
    if (!new) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

    //Inicializa o ponteiro da esquerda, direita e pai como NULL
    new->chave = numero;	
	new->left = NULL;
	new->right = NULL;
	new->p = NULL;

	return new;

}
t_nodeB *monta_arvoreB (char *expr, int *i){

    int j, tam;
    char num[MAX];

	t_nodeB *tree;
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

        tam = strlen (num);
        //printf ("%c %d\n", expr[*i], *i);
        if (tam) {
            //Mostra qual nó vai ser criado e cria esse nó
            long key;
            char *ptr;

		    //printf("Criando nó %s\n", num);
            key = strtol (num, &ptr, 10);

		    tree = create_nodeB (key);
            tree->left = monta_arvoreB(expr,i);
            tree->right = monta_arvoreB(expr,i);
            (*i)++;
        }

        //Monta primeiramente a árvore da esquerda e depois a direita
	}
	return tree;
	
}
char trata_comando (char *palavra) {

    int i;
    char a;
    a = palavra[0];
    for (i = 2; palavra[i] != '\0'; i++) {
        palavra[i - 2] = palavra[i];
    }
    palavra[i] = '\0';

    return a;
}
int soma_arvore (t_nodeB *node) {

    if (node == NULL)
        return 0;
    
    return (node->chave + soma_arvore(node->left) + soma_arvore(node->right));
    
}
t_nodeA* inserir (t_nodeA* treeA, t_nodeB *chave) {

    int somaA, somaChave;
    if (treeA == NULL)
        return create_nodeA (chave);
    
    somaChave = soma_arvore (chave);
    somaA = soma_arvore (treeA->chave);

    if (somaChave < somaA) {
        t_nodeA *node;
        node = inserir (treeA->left, chave);
        treeA->left = node;
        node->p = treeA; 
    }
    else {
        t_nodeA *node_r;
        node_r = inserir (treeA->right, chave);
        treeA->right = node_r;
        node_r->p = treeA;
    }

    return treeA;

}
void destroiArvoreB(t_nodeB *node) {

    if (node != NULL) {
        destroiArvoreB (node->left);
        destroiArvoreB (node->right);
        node->left = NULL;
        node->right = NULL;
        free (node);
    }

}
void imprimir_arvoreB (t_nodeB *treeB) {

    if (treeB != NULL) {
        printf ("(");
        printf ("%d", treeB->chave);
        imprimir_arvoreB (treeB->left);
        imprimir_arvoreB (treeB->right);
        printf (")");
    }
}void imprimir_arvoreA (t_nodeA *treeA) {

    if (treeA == NULL) {
        printf ("\n[");
        printf ("\n]");
    }
    if (treeA != NULL) {
        printf ("\n[");
        imprimir_arvoreB(treeA->chave);
        imprimir_arvoreA (treeA->left);
        imprimir_arvoreA (treeA->right);
        printf ("\n]");
    }

}
void destroiArvoreA (t_nodeA *treeA) {

    if (treeA != NULL) {
        destroiArvoreA (treeA->left);
        destroiArvoreA (treeA->right);
        destroiArvoreB (treeA->chave);
        treeA->left = NULL;
        treeA->right = NULL;
        free (treeA);
    }

}
t_nodeA *busca (t_nodeA *node,int valor) {

    int soma;
    if (node == NULL)
        return NULL;

    soma = soma_arvore (node->chave);
    if (soma == valor)
        return node;
    
    if (valor < soma)
        busca (node->left,valor);
    else
        busca (node->right,valor);

}
int main () {

    t_nodeA* treeA;
    char arvore[100];

    for (int i = 0; i < 7; i++) {
        t_nodeB* treeB = NULL;
        int j = 0;
        fgets (arvore,100,stdin);
        treeB = monta_arvoreB (arvore,&j);
        treeA = inserir (treeA,treeB);
        imprimir_arvoreA (treeA);
        printf ("\n");
    }

    t_nodeA *ret;
    ret = busca (treeA,50);
    imprimir_arvoreB (ret->chave);
    printf ("1\n");
    if (ret != NULL) {
        imprimir_arvoreB (ret->p->chave);
        printf ("\n");
    }

    ret = NULL;
    ret = busca (treeA,13);
    imprimir_arvoreB (ret->chave);
    printf ("2\n");
    if (ret != NULL) {
        imprimir_arvoreB (ret->p->p->right->chave);
        printf ("\n");
    }

    ret = NULL;
    ret = busca (treeA,24);
    imprimir_arvoreB (ret->chave);
    printf ("3\n");
    if (ret != NULL) {
        imprimir_arvoreB (ret->p->left->chave);
        printf ("\n");
    }

    ret = NULL;
    ret = busca (treeA,50);
    imprimir_arvoreB (ret->chave);
    printf ("4\n");
    if (ret != NULL) {
        imprimir_arvoreB (ret->p->p->chave);
        printf ("\n");
    }

    ret = NULL;
    ret = busca (treeA,48);
    imprimir_arvoreB (ret->chave);
    printf ("5\n");
    if (ret != NULL) {
        imprimir_arvoreB (ret->right->chave);
        printf ("\n");
    }

    destroiArvoreA (treeA);   

}