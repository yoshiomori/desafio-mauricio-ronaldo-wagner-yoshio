CFLAGS=-Wall -lm

ondas: ondas.c lib/leitura_entrada.c lib/matriz.c lib/alloc_safe.c lib/ondas_lib.c lib/imagem.c lib/segundo_arquivo.c

teste:
	cd testes && $(MAKE) all
