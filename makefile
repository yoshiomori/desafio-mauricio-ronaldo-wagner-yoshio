CFLAGS=-Wall -fopenmp -O3

ondas: ondas.c lib/leitura_entrada.c lib/matriz.c lib/alloc_safe.c lib/ondas_lib.c lib/imagem.c lib/segundo_arquivo.c  -lm

teste:
	cd testes && $(MAKE) all

debug:
	gcc -o ondas ondas.c lib/*.c $(CFLAGS) -g -lm
