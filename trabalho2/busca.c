#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstA.h"
#include "libstB.h"

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
            printf ("\nExclusão\n");
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