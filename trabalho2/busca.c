#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstA.h"
#include "libstB.h"

int main () {

    int i, soma;
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
            i = 0;
            t_nodeB* treeB;
            
            printf ("\nIncluindo\n");
            treeB = monta_arvoreB (palavra,&i);
            soma = soma_arvore (treeB);
            printf ("Criando nodo %d: ", soma);
            imprimir_arvoreB (treeB);
            printf ("\n");

            treeA = inserir (treeA,treeB);
            imprimir_arvoreA (treeA);

            printf ("\n");
        }
        else if (comando == 'b'){
            t_nodeB*lixo;
            t_nodeA*resultado;

            i = 0;
            lixo = monta_arvoreB (palavra, &i);
            soma = soma_arvore (lixo);
            printf ("\nBuscando o valor %d: ", soma);
            imprimir_arvoreB (lixo);
            printf ("\n");
            resultado = busca(treeA, soma);

            if (resultado == NULL) {
                printf ("\nValor não encontrado\n");
            }
            else {
                printf ("\nValor encontrado %d: ", soma);
                imprimir_arvoreB (resultado->chave);
                printf ("\n"); 
            }

            imprimir_arvoreA(treeA);
            destroiArvoreB (lixo); 
        }
        else if (comando == 'r') {
            t_nodeB *lixo = NULL;
            t_nodeA *resultado;
            i = 0;
            
            lixo = monta_arvoreB (palavra, &i);
            soma = soma_arvore (lixo);
            printf ("\nExcluindo o valor %d: ", soma);
            imprimir_arvoreB (lixo);
            printf ("\n");
            resultado = busca (treeA, soma);

            if (resultado == NULL) {
                printf ("\nValor não encontrado\n");
            }
            else {
                treeA = remover (resultado, treeA);
            }
            destroiArvoreB (lixo);
            imprimir_arvoreA(treeA);
        }
        else {
            printf ("\nOpção não encontrada: encerrando o programa\n");
            exit (1);
        }    
    }
    destroiArvoreA (treeA);
    fclose (arquivo);
    free (palavra);
    free (nomearquivo);    
    return 0;
}