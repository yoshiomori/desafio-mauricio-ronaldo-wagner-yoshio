CFLAGS=-Wall -lm

teste: ondas entrada
	./ondas entrada

ondas: ondas.c leitura_entrada.c matriz.c alloc_safe.c gotas.c
