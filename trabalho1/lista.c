#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int cria_lista(t_lista *l){
	l->ini = NULL;
	l->tam = 0;
	return 1;
}

int lista_vazia(t_lista *l) {
	if (l->tam == 0)
		return 1;
	return 0;
}

void destroi_lista(t_lista *l) {

	t_nodo *p;
	
	if (lista_vazia(l) != 1) {
		p=l->ini;
		while (p->prox != NULL) {
			l->ini = p->prox;
			free (p);
			p = p->prox;
		}
		free (p);
		l->tam = 0;
		l->ini = NULL;
	}
	//printf ("Não destruida: lista vazia\n");
}

int insere_inicio_lista(char x, t_lista *l) {
	
	t_nodo *new_no;

	new_no=(t_nodo *)malloc(sizeof(t_nodo));
	if (new_no != NULL) {
		new_no->elemento = x;
		new_no->prox= l->ini;
		l->ini = new_no;
		l->tam++;
		return 1;
	}
	return 0;
}
int insere_fim_lista(char x, t_lista *l) {

	t_nodo *new, *p;
	
	if (lista_vazia(l)) {
		return insere_inicio_lista (x,l);
	}

	new=(t_nodo *) malloc (sizeof(t_nodo));
	if (new==NULL)		
		return 0;

	l->tam++;
	new->prox=NULL;

	/*caso geral*/	
	p = l->ini;
	while (p->prox != NULL) {
		p = p->prox;
	}
	new->elemento = x;	
	p->prox=new;
	return 1;
}
	
int remove_primeiro_lista(char *item, t_lista *l) {


	if (lista_vazia(l))
		return 0;
	
	/*caso geral*/
	*item = l->ini->elemento;
	l->tam--;

	t_nodo *aux;
	aux = l->ini->prox;

	free(l->ini);
	l->ini = aux;
	return 1;
}
int remove_ultimo_lista(char *item, t_lista *l) {

	t_nodo *p;
	
	if (lista_vazia(l))
		return 0;


	/*se a lista tem somente um elemento*/

	if (l->ini->prox == NULL){
		return remove_primeiro_lista (item,l);
	}
	
	l->tam--;

	/*caso geral*/
	p = l->ini;
	while (p->prox->prox != NULL) {
		p = p->prox;
	}
	free (p->prox);
	p->prox = NULL;
	return 1;
}


