#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void imprime_lista (t_lista *l) {
	
	t_nodo *p;

	if (lista_vazia(l) != 1) {
		p = l->ini;
		printf ("Tam: %d -> ", l->tam);
		while (p->prox != NULL) {
			printf ("%d ", p->elemento);
			p = p->prox;
		}
		printf ("%d ", p->elemento);
		printf ("\n");
	}


}
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
	printf ("Não destruida: lista vazia\n");
}

int insere_inicio_lista(int x, t_lista *l) {
	
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
int insere_fim_lista(int x, t_lista *l) {

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

int insere_ordenado_lista(int x, t_lista *l) {

	if (lista_vazia(l))
		return insere_inicio_lista (x,l);

	t_nodo *new, *ant, *p;

	/*se a lista tem só um elemento*/
	if (l->ini->prox == NULL) {
		if (x > l->ini->elemento)
			return insere_fim_lista (x,l);
		else
			return insere_inicio_lista (x,l);
	}
	
	/*inserir no começo*/
	if (l->ini->elemento > x)
		return insere_inicio_lista (x,l);

	/*caso geral*/
	

	p=l->ini;
	while (p->prox != NULL && x > p->elemento){
		ant = p;
		p = p->prox;
	}

	if (x < p->elemento) {
		new=(t_nodo *)malloc(sizeof(t_nodo));
		if (new == NULL)
			return 0;
		new->elemento = x;
		new->prox = p;
		ant->prox = new;
		l->tam++;
		return 1;
	}
	return insere_fim_lista (x,l);
		
} 	
int remove_primeiro_lista(int *item, t_lista *l) {


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
int remove_ultimo_lista(int *item, t_lista *l) {

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
int remove_item_lista(int elemento, int *item, t_lista *l) {

	if (lista_vazia(l))
		return 0;
	
	t_nodo *p, *q;
	/*se o item que eu quero remover é o primeiro*/
	if (l->ini->elemento == elemento) {
		return (remove_primeiro_lista(item,l));
	}
	
	/*caso geral*/
	p = l->ini;
	while (p->prox != NULL && p->elemento != elemento){
		q = p;
		p = p->prox;
	}
	if (p->elemento == elemento){
		l->tam--;
		q->prox = p->prox;
		free (p);
		return 1;
	}
	printf ("Elemento não encontrado\n");
	return 0;
}
int pertence_lista(int elemento, t_lista *l) {

	if (lista_vazia(l))
		return 0;
	
	t_nodo *p;
	p = l->ini;
	while (p->prox != NULL && p->elemento != elemento)
		p = p->prox;
	if (p->elemento == elemento)
		return 1;
	printf ("Elemento não encontrado\n");
	return 0;

}
int concatena_listas(t_lista *l, t_lista *m) { /*Se ambas as listas não forem vazias ela concatena*/

	if (lista_vazia(l) && lista_vazia (m)) {
		return 0;
	}
	
	/*caso geral*/
	t_nodo *p;
	p = m->ini;
	while (p->prox != NULL) {
		insere_fim_lista (p->elemento,l);
		p = p->prox;
	}
	insere_fim_lista (p->elemento,l);
	destroi_lista(m);
	return 1;
}
int copia_lista(t_lista *l, t_lista *m) { /*se a lista l não for vazia, ela copia*/

	if (lista_vazia (l))
		return 0;


	t_nodo *p;
	int i;

	p = (t_nodo *)malloc(sizeof(t_nodo));
	if (p == NULL)
		return 0;

	p = l->ini;
	for (i = 0; i < l->tam; i++) {
		insere_fim_lista (p->elemento,m);
		p = p->prox;
	}
	return 1;
}


