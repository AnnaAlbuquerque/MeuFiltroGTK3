all:
	gcc src/imagem.c -c `pkg-config gtk+-3.0 --cflags --libs` 
	gcc src/meufiltro.c -c `pkg-config gtk+-3.0 --cflags --libs`
	gcc src/filtroGtk.c `pkg-config gtk+-3.0 --cflags --libs` meufiltro.o imagem.o
