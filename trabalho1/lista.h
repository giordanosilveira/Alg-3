#ifndef __LISTA__
#define __LISTA__

struct t_nodo {
	char elemento;
	struct t_nodo * prox;
};
typedef struct t_nodo t_nodo;

struct t_lista {
	t_nodo * ini;
	int tam;
};
typedef struct t_lista t_lista;

/*Cria uma lista vazia, isto  ́e, aponta para NULL e contém tamanho zero; 
Retorna 1 se a operação foi bem sucedida e zero caso contrario;*/
int cria_lista(t_lista *l);

int lista_vazia(t_lista *l);
/*Retorna 1 se a lista está vazia e zero caso contrario;*/

void destroi_lista(t_lista *l);
/*Remove todos os elementos da lista e faz com que ela aponte paraNULL;*/

int insere_inicio_lista(char x, t_lista *l);
/*Insere  o  elemento  x  no  inıcio  da  lista;*/  
/*Retorna  1  se  a  opera ̧c ̃ao  foi  bem  sucedida  e  zero  caso contrario;*/

int insere_fim_lista(char x, t_lista *l);
/*Insere  o  elemento  x  no  final  da  lista  
Retorna  1  se  a  opera ̧c ̃ao  foi  bem  sucedida  e  zero  caso contrario;*/

int remove_primeiro_lista(char *item, t_lista *l);
/*Remove o primeiro elemento da lista e o retorna em *item;  
Retorna 1 se a operacao foi bem sucedida e zero caso contrario;*/

int remove_ultimo_lista(char *item, t_lista *l);
/*Remove  o   ́ultimo  elemento  da  lista  e  o  retorna  em *item;  
Retorna  1  se  a  operacão  foi  bemsucedida e zero caso contrario;*/

#endif
