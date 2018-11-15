#ifndef MEUFILTRO_H
#define MEUFILTRO_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"

//declare aqui os seus widgets
GtkWidget *widgetControleTamanho;
GtkWidget *widgetControleEspacamento;
GtkWidget *radioOrientacao1, *radioOrientacao2, *radioEmbaralhar1, *radioEmbaralhar2;
GtkWidget *labelTextura, *labelOrientacao, *labelEmbaralhar, *labelTamanho, *labelEspacamento;

Imagem meuFiltro(Imagem origem);
void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);

#endif


