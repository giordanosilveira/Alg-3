struct t_nodo {
	int elemento;
	struct t_nodo * prox;
};
typedef struct t_nodo t_nodo;

struct t_lista {
	t_nodo * ini;
	int tam;
};
typedef struct t_lista t_lista;

int cria_lista(t_lista *l);
/*Cria uma lista vazia, isto  ́e, aponta para NULL e contém tamanho zero; 
Retorna 1 se a operação foi bem sucedida e zero caso contrario;*/

int lista_vazia(t_lista *l);
/*Retorna 1 se a lista está vazia e zero caso contrario;*/

void destroi_lista(t_lista *l);
/*Remove todos os elementos da lista e faz com que ela aponte paraNULL;*/

int insere_inicio_lista(int x, t_lista *l);
/*Insere  o  elemento  x  no  inıcio  da  lista;*/  
/*Retorna  1  se  a  opera ̧c ̃ao  foi  bem  sucedida  e  zero  caso contrario;*/

int insere_fim_lista(int x, t_lista *l);
/*Insere  o  elemento  x  no  final  da  lista  
Retorna  1  se  a  opera ̧c ̃ao  foi  bem  sucedida  e  zero  caso contrario;*/

int insere_ordenado_lista(int x, t_lista *l); /*Insere o elemento x na lista de maneira que ela fique em ordem crescente, do início para o finaldela; 
Retorna 1 se a opera ̧c ̃ao foi bem sucedida e zero caso contr ́ario;*/
/*void imprime_lista(t_lista *l);Imprime os elementos da lista, do inıcio ao final.  Se ela for vazia nao imprime nada, nem um \n*/

int remove_primeiro_lista(int *item, t_lista *l);
/*Remove o primeiro elemento da lista e o retorna em *item;  
Retorna 1 se a operacao foi bem sucedida e zero caso contrario;*/

int remove_ultimo_lista(int *item, t_lista *l);
/*Remove  o   ́ultimo  elemento  da  lista  e  o  retorna  em *item;  
Retorna  1  se  a  operacão  foi  bemsucedida e zero caso contrario;*/

int remove_item_lista(int chave, int *item, t_lista *l);
/*Se o elemento chave existir na lista, o retorna em *item;  
Retorna 1 se a operação foi bem sucedida e zero caso contrário (elemento nao encontrado também retorna zero);*/

int pertence_lista(int chave, t_lista *l);
/*Retorna 1 se o elemento contendo a chave chave existe na lista, caso contrario retorna zero;*/

int concatena_listas(t_lista *l, t_lista *m);
/*Concatena os elementos da lista (na mesma ordem) ao final da lista.  Faz a lista conter no valor NULL;*/

int copia_lista(t_lista *l, t_lista *m);
/*Cria uma nova lista contendo uma copia exata da lista.  Retorna 1 se operação foi bem sucedida e zero caso contrário.*/


