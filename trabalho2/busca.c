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

//Cria um nodo do tipo A
t_nodeA *create_nodeA (t_nodeB *chave) {
    t_nodeA *new;

    //Abre espaço na memória e chega para ver se realemente abriu
    new = (t_nodeA*)malloc(sizeof(t_nodeA));
    if (!new) {
        perror ("Não foi possível alocar memória");
        exit (1);
    }

    //Anula todos os ponteiros e inicializa a chave
    new->chave = chave;
    new->left = NULL;
    new->right = NULL;
    new->p = NULL;

    return new;
}
//Cria um nodo do tipo B
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
//Dado uma arvore em formato de parenteses alinhados, monta essa árvore e retorna o seu ponteiro
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

        //Teste que serve para resolver os parenteses vazios da árvore
        tam = strlen (num);
        if (tam) {
            //Mostra qual nó vai ser criado e cria esse nó
            long key;
            char *ptr;

		    //printf("Criando nó %s\n", num);
            key = strtol (num, &ptr, 10);

            //Monta primeiramente a árvore da esquerda e depois a direita
		    tree = create_nodeB (key);
            tree->left = monta_arvoreB(expr,i);
            tree->right = monta_arvoreB(expr,i);
            (*i)++;
        }

	}
	return tree;
	
}
//Retira o comando da entrada e puxa a árvore para o começo da string
char trata_comando (char *palavra) {

    int i;
    char a;
    a = palavra[0];
    for (i = 2; palavra[i] != '\0'; i++) {  //A árvore começa na casa 2 do vetor,
        palavra[i - 2] = palavra[i];        //então puxa ela duas casa para traz
    }
    palavra[i] = '\0';

    return a;
}
//Soma a árvore b
int soma_arvore (t_nodeB *node) {

    if (node == NULL)
        return 0;
    
    return (node->chave + soma_arvore(node->left) + soma_arvore(node->right));
    
}
//Função que insere um nodo recursivamente na árvore
t_nodeA* inserir (t_nodeA* treeA, t_nodeB *chave) {

    int somaA, somaChave;

    //Testa para ver se o nodo é nulo, se for, cria um nodo
    if (treeA == NULL)
        return create_nodeA (chave);
    
    //Soma da arvore B e A; vai servir de comparação para ver se eu vou para a esquerda ou para a direita
    somaChave = soma_arvore (chave);
    somaA = soma_arvore (treeA->chave);

    //Se for menor, vai para a esquerda
    if (somaChave < somaA) {
        t_nodeA *node;
        node = inserir (treeA->left, chave);
        treeA->left = node;
        node->p = treeA; 
    }
    //Senão vai para a direita
    else {
        t_nodeA *node_r;
        node_r = inserir (treeA->right, chave);
        treeA->right = node_r;
        node_r->p = treeA;
    }

    return treeA;

}
//Destroi recurssivamente a árvore B
void destroiArvoreB(t_nodeB *node) {

    if (node != NULL) {
        destroiArvoreB (node->left);
        destroiArvoreB (node->right);
        node->left = NULL;
        node->right = NULL;
        free (node);
    }

}
//Imprime a árvore B, no formato de parênteses alinhados
void imprimir_arvoreB (t_nodeB *treeB) {

    if (treeB != NULL) {
        printf ("(");
        printf ("%d", treeB->chave);
        imprimir_arvoreB (treeB->left);
        imprimir_arvoreB (treeB->right);
        printf (")");
    }
}
//Imprime a árvore A, no formato de conchetes "nova linha"
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
//Destroi a árvore A recurssivamente
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
//Busca para ver se o valor é encontrado na árvore A
t_nodeA *busca (t_nodeA *node,int valor) {

    int soma;
    //Se for nulo o valor não existe, então retorna NULL
    if (node == NULL)
        return NULL;

    //soma o nodo da árvore A - uma árvore B - e checa para ver se é igual
    //se for retorta esse nodo
    soma = soma_arvore (node->chave);
    if (soma == valor)
        return node;
    
    //Se o valore for menor que a soma, vai para a esquerda
    if (valor < soma)
        busca (node->left,valor);
    //senão vai para a direita
    else
        busca (node->right,valor);

}
void ajustaNoPai (t_nodeA *node, t_nodeA *new) {
    if (node->p != NULL) {
        if (node->p->left == node){
            node->p->left = new;
        }
        else {
            node->p->right = new;
        }
        if (new != NULL)
            new->p = node->p;
    }
}
//Função que acha o valor mínimo de um nó
t_nodeA *min (t_nodeA *node) {
    if (node->left == NULL)
        return node;
    else
        min (node->left);
}
//Função que acha um sucessor de um nodo
t_nodeA* sucessor (t_nodeA*node) {

    t_nodeA *s = NULL;
    //Testa para ver se o nó dado tem filho a direita, se sim
    //retorna o mínimo do seu filho a direita (sucessor)
    if (node->right != NULL) {
        return min(node->right);
    }

    //Se ele não tiver filhos o sucessor vai ser algum nodo "acima" dele
    //essa parte acha esse nodo
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
        ajustaNoPai (node, node->right);
        free (node);
    }
    else {
        if (node->right == NULL) {
            ajustaNoPai (node, node->left);
            free (node);
        }
        else {
            s = sucessor (node);
            ajustaNoPai (s, s->right);
            s->left = node->left;
            s->right = node->right;
            if (s->right != NULL)
                s->right->p = s;
            if (s->left != NULL)
                s->left->p = s;  
            ajustaNoPai (node, s);
            if (node == root) {
                s->p = NULL;
                newroot = s;
            }
            free (node);   
        }
    }
    return newroot;
}
int main () {

    char *nomearquivo, comando, *palavra;
    t_nodeA *treeA = NULL;

    palavra = malloc(sizeof(char)*MAX);    
    nomearquivo = malloc(sizeof(char)*MAX);
    strcpy (nomearquivo, "/dev/stdin");

    FILE *arquivo;

    arquivo = fopen (nomearquivo, "r");

    while (fgets (palavra,MAX,arquivo)) {
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