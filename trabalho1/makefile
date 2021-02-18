CFLAGS = -Wall -g #gerar "warnings" detalhados e infos de depuração

objs = trabalho.o lista.o

#regra default (primeira regra)
all: trabalho

#regras de ligação
trabalho: $(objs)

#regras de compilação
trabalho.o: trabalho.c lista.h
lista.o: lista.c lista.h

#remove arquivos temporários
clean:
		-rm -f $(objs) *~

#remove tudo o que não for o código fonte
purge: clean
		-rm -f trabalho
