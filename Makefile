# Digite 'make'  no terminal para compilar a aplicação #
all:
	gcc src/imagem.c -c `pkg-config gtk+-3.0 --cflags --libs` -g
	gcc src/meufiltro.c -c `pkg-config gtk+-3.0 --cflags --libs` -g
	gcc src/filtroGtk.c `pkg-config gtk+-3.0 --cflags --libs` meufiltro.o imagem.o -g
