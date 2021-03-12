CFLAGS = -Wall -g #gerar "warnings" detalhados e infos de depuração

objs = busca.o libstA.o libstB.o

#regra default (primeira regra)
all: busca

#regras de ligação
busca: $(objs)

#regras de compilação
busca.o: busca.c libstA.h libstB.h
libstB.o: libstB.c libstB.h
libstA.o: libstA.c libstB.c libstA.h libstB.h

#remove arquivos temporários
clean:
		-rm -f $(objs) *~

#remove tudo o que não for o código fonte
purge: clean
		-rm -f busca

