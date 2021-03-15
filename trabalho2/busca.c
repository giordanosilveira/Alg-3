#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstA.h"
#include "libstB.h"

int main () {

    int i, soma;
    char *nomearquivo, comando, *arvore;
    t_nodeA *treeA = NULL;

    //Aloca espaço para a string árvore e nomearquivo
    arvore = malloc(sizeof(char)*MAX);    
    nomearquivo = malloc(sizeof(char)*MAX);
    strcpy (nomearquivo, "/dev/stdin");                 //Copia o nome do arquivo de stdin para nomearquivo

    FILE *arquivo;

    arquivo = fopen (nomearquivo, "r");                 //Abre o arquivo

    while (fgets (arvore,MAX,arquivo)) {                //Enquanto "pegar" palavra
        comando = trata_comando (arvore);               //Retira o comando da árvore
        if (comando == 'i'){
            i = 0;
            t_nodeB* treeB;
            
            printf ("\nIncluindo\n");
            treeB = monta_arvoreB (arvore,&i);          //Monta a árvore B
            soma = soma_arvore (treeB);                 //Faz a soma da árvore B
            printf ("Criando nodo %d: ", soma);
            imprimir_arvoreB (treeB);                   //Printa a árvore B
            printf ("\n");

            treeA = inserir (treeA,treeB);              //Insere na árvore A
            imprimir_arvoreA (treeA);                   //Imprime na árvore A

            printf ("\n");
        }
        else if (comando == 'b'){
            t_nodeB*lixo;
            t_nodeA*resultado;

            i = 0;
            lixo = monta_arvoreB (arvore, &i);          //Monta a árvore B
            soma = soma_arvore (lixo);                  //Faz a soma da árvore B
            printf ("\nBuscando o valor %d: ", soma);
            imprimir_arvoreB (lixo);                    //Printa a árvore B
            printf ("\n");
            resultado = busca(treeA, soma);             //faz a busca

            //Bloco: Se não achou printa que não achou, senão printa a árvore do nodo
            if (resultado == NULL) {                    
                printf ("\nValor não encontrado\n");
            }
            else {
                printf ("\nValor encontrado %d: ", soma);
                imprimir_arvoreB (resultado->chave);
                printf ("\n"); 
            }                                           //fim do bloco

            imprimir_arvoreA(treeA);                    //imprime a árvore A
            destroiArvoreB (lixo);                      //Destroi a árvore B 
        }
        else if (comando == 'r') {
            t_nodeB *lixo = NULL;
            t_nodeA *resultado;
            i = 0;
            
            lixo = monta_arvoreB (arvore, &i);          //Monta a árvore B
            soma = soma_arvore (lixo);                  //Faz a soma da árvore B
            printf ("\nExcluindo o valor %d: ", soma);
            imprimir_arvoreB (lixo);                    //Printa a árvore B 
            printf ("\n");
            resultado = busca (treeA, soma);            //faz a busca

            //Bloco: Se não achou printa que não achou, senão remove o nodo
            if (resultado == NULL) {
                printf ("\nValor não encontrado\n");
            }
            else {
                treeA = remover (resultado, treeA);
            }                                           //fim do bloco                               

            destroiArvoreB (lixo);                      //Destroi a árvore B 
            imprimir_arvoreA(treeA);                    //imprime a árvore A
        }
        else {
            printf ("\nOpção não encontrada: encerrando o programa\n");
            exit (1);
        }    
    }
    destroiArvoreA (treeA);                             //Destroi a árvore A
    fclose (arquivo);                                   //Fecha o arquivo             
    free (arvore);                                      //Free na string árvore 
    free (nomearquivo);                                 //Free na string nomearquivo  
    return 0;
}