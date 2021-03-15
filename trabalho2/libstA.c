#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstA.h"

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
        node->p = treeA;                        // ajusta o pai do nodo criado 
    }
    //Senão vai para a direita
    else {
        t_nodeA *node_r;
        node_r = inserir (treeA->right, chave);
        treeA->right = node_r;
        node_r->p = treeA;                      // ajusta o pai do nodo criado
    }

    return treeA;
}
void imprimir_arvoreA (t_nodeA *treeA) {

    //Se o nodo for nulo abre e fecha um conchete vazio
    if (treeA == NULL) {
        printf ("\n[NULL");
        printf ("]");
    }
    //Se não for nulo, abre um conchete, imprime a chave da árvore A
    //e em ordem segue esses passos pela árvore A
    if (treeA != NULL) {
        printf ("\n[");
        imprimir_arvoreB(treeA->chave);
        imprimir_arvoreA (treeA->left);
        imprimir_arvoreA (treeA->right);
        printf ("\n]");
    }

}
//Destroi a árvore A recurssivamente
//Percursos pos ordem
void destroiArvoreA (t_nodeA *treeA) {

    if (treeA != NULL) {
        destroiArvoreA (treeA->left);
        destroiArvoreA (treeA->right);
        destroiArvoreB (treeA->chave);
        treeA->left = NULL;                 //nulifica os ponteiros
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
//Ajusta os ponteiros filho do nodo pai para new
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
t_nodeA *min (t_nodeA *node) {
    
    if (node->left == NULL)
        return node;
    else                        //enquanto não for nulo o ponteiro da esquerda, continua indo para a esquerda
        min (node->left);
}
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

    //Se o nó não tem filho a esquerda
    //atualiza o seu pai com o filho da direita do nodo
    if (node->left == NULL){                    
        ajustaNoPai (node, node->right);
        free (node);
    }
    else {
        //Se o nó não tem filho a direita
        //atualiza o seu pai com o filho da esquerda do nodo
        if (node->right == NULL) {
            ajustaNoPai (node, node->left);
            free (node);
        }
        //Se o nodo tem os dois filhos
        else {
            s = sucessor (node);            //acha o sucessor
            ajustaNoPai (s, s->right);      //atualiza o pai do sucessor com o filho a direita do nodo sucessor
            s->left = node->left;           //O filho a esquerda do sucessor recebe o filho a esquerda do nodo excluido
            s->right = node->right;         //O filho a direita do sucessor receve o filho a direita do nodo excluido
            //BLOCO: atualiza o ponteiro pai dos filho que são do sucessor agora (se necessário)
            if (s->right != NULL)           
                s->right->p = s;
            if (s->left != NULL)
                s->left->p = s;             //fim do bloco  
            ajustaNoPai (node, s);          //Ajusta para que os ponteiros filhos do pai do nodo aponte para s
            if (node == root) { 
                s->p = NULL;                //Se o nodo for a raiz atualiza o pai do nodo sucessor para NULL
                newroot = s;                //atualiza a raiz
            }
            free (node);                    //apaga o nodo
        }
    }
    return newroot;
}