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
int soma_arvore (t_nodeB *node) {

    if (node == NULL)
        return 0;
    
    return (node->chave + soma_arvore(node->left) + soma_arvore(node->right));
    
}
t_nodeA *busca (t_nodeA *node,int valor) {

    int soma;
    if (node == NULL)
        return NULL;

    soma = soma_arvore (node->chave);
    if (soma == valor)
        return node;
    
    if (valor > soma)
        busca (node->right,valor);
    else
        busca (node->left,valor);

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
void destroiArvoreB(t_nodeB *node) {

    if (node != NULL) {
        destroiArvoreB (node->left);
        destroiArvoreB (node->right);
        node->left = NULL;
        node->right = NULL;
        free (node);
    }

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
t_nodeA* inserir (t_nodeA* treeA, t_nodeB *chave) {

    int somaA, somaChave;
    if (treeA == NULL)
        return create_nodeA (chave);
    
    somaChave = soma_arvore (chave);
    somaA = soma_arvore (treeA->chave);

    if (somaChave > somaA) {
        treeA->right = inserir (treeA->right, chave);
        treeA->right->p = treeA;
    }
    else {
        treeA->left = inserir (treeA->left, chave);
        treeA->left->p = treeA;
    }

    return treeA;

}
void ajustaNoPai (t_nodeA *node, t_nodeA *new) {
    if (node->p != NULL) {
        if (node->p->left == node)
            node->p->left = new;
        else
            node->p->right = new;
        if (new != NULL)
            new->p = node->p;
    }
}
t_nodeA *min (t_nodeA *node) {
    if (node->left == NULL)
        return node;
    else
        min (node->left);
}
t_nodeA* sucessor (t_nodeA*node) {

    t_nodeA *s = NULL;
    if (node->right != NULL) {
        return min(node->right);
    }
    else {
        s = node->p;
        while (s != NULL && node == s->right) {
            node = s;
            s = s->p;
        }
    }
    return s;

}
t_nodeA* remover (t_nodeA *node, t_nodeA* root) {

    t_nodeA *s, *newroot = root;
    if (node->left == NULL){
        printf ("esquerda\n");
        if (node->right == NULL)
            printf ("caqui\n");
        ajustaNoPai (node, node->right);
        free (node);
    }
    else {
        if (node->right == NULL) {
            printf ("direita\n");
            ajustaNoPai (node, node->left);
            free (node);
        }
        else {
            printf ("nenhum\n");
            s = sucessor (node);
            ajustaNoPai (s, s->right);
            s->left = node->left;
            s->right = node->right;
            ajustaNoPai (node, s);
            if (node == root)
                newroot = s;
            free (node);   
        }
    }
    return newroot;
}
void imprimir_arvoreB (t_nodeB *treeB) {

    if (treeB != NULL) {
        printf ("(");
        printf ("%d", treeB->chave);
        imprimir_arvoreB (treeB->left);
        imprimir_arvoreB (treeB->right);
        printf (")");
    }
}
void imprimir_arvoreA (t_nodeA *treeA) {

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
int main () {

    char *nomearquivo, comando, *palavra;
    t_nodeA *treeA = NULL;

    palavra = malloc(sizeof(char)*MAX);    
    nomearquivo = malloc(sizeof(char)*MAX);
    strcpy (nomearquivo, "/dev/stdin");

    FILE *arquivo;

    arquivo = fopen (nomearquivo, "r");

    while (fgets (palavra,MAX,stdin)) {
        comando = trata_comando (palavra);
        if (comando == 'i'){
            int i = 0;
            t_nodeB* treeB;
            treeB = monta_arvoreB (palavra,&i);
            treeA = inserir (treeA,treeB);
            imprimir_arvoreA (treeA);
            printf ("\n");
        }
        else if (comando == 'b'){
            int valor, i = 0;
            t_nodeB*lixo;
            t_nodeA*resultado;
            lixo = monta_arvoreB (palavra, &i);
            valor = soma_arvore (lixo);
            resultado = busca(treeA, valor);
            if (resultado == NULL) {
                printf ("valor não encontrado\n");
            }
            else {
                printf ("Valor encontrado\n");
                imprimir_arvoreB (resultado->chave); 
            }
            imprimir_arvoreA(treeA);
            destroiArvoreB (lixo); 
        }
        else if (comando == 'r') {
            printf ("Exclusão\n");
            t_nodeB *lixo = NULL;
            t_nodeA *resultado;
            int i = 0, soma;
            lixo = monta_arvoreB (palavra, &i);
            soma = soma_arvore (lixo);
            resultado = busca (treeA, soma);

            printf ("\n");
            imprimir_arvoreB (resultado->chave);
            printf ("\n");

            if (resultado == NULL) {
                printf ("Valor não encontrado\n");
            }
            else 
                treeA = remover (resultado, treeA);
            destroiArvoreB (lixo);
            imprimir_arvoreA(treeA);
        }
        else {
            printf ("Opção não encontrada: encerrando o programa\n");
            exit (1);
        }    
    }

    destroiArvoreA (treeA);
    fclose (arquivo);
    free (palavra);
    free (nomearquivo);    
    return 0;
}