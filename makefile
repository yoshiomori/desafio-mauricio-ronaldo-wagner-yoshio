CFLAGS=-Wall

teste: ondas entrada
	./ondas entrada

ondas: ondas.c leitura_entrada.c matriz.c
