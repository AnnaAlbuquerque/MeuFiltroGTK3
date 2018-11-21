#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	// Texturas
	labelTextura = gtk_label_new("Texturas");
	
	// Controle de tamanho e espaçamento das tiras
	labelTamanho = gtk_label_new("Tamanho das tiras");
	widgetControleTamanho = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 10, 1);
	g_signal_connect(G_OBJECT(widgetControleTamanho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	labelEspacamento = gtk_label_new("Espaçamento entre as tiras");
	widgetControleEspacamento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 10, 1);
	g_signal_connect(G_OBJECT(widgetControleEspacamento), "value-changed", G_CALLBACK(funcaoAplicar), NULL);

	// Orientação das Tiras (Horizontal ou Vertical)
	labelOrientacao = gtk_label_new("Orientação das tiras");
	radioOrientacao1 = gtk_radio_button_new_with_label (NULL, "Horizontais");
   	radioOrientacao2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radioOrientacao1), "Verticais");
	   
	// Embaralhar tiras (Sim ou Não)
	labelEmbaralhar = gtk_label_new("Embaralhar tiras");
	radioEmbaralhar1 = gtk_radio_button_new_with_label (NULL, "Sim");
   	radioEmbaralhar2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radioEmbaralhar1), "Não");
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {
	// Cria os GtkBox necessários
	GtkWidget *vboxMain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *vboxOrientacao = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *vboxEmbaralhar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *vboxTamanhoTiras = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	GtkWidget *hboxMain = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *hboxText = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *hboxOrientacao = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *hboxEmbaralhar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	// Altera o tamanho da borda dos GtkBox
	gtk_container_set_border_width(GTK_CONTAINER(vboxMain), 20);
	gtk_container_set_border_width(GTK_CONTAINER(vboxOrientacao), 20);
	gtk_container_set_border_width(GTK_CONTAINER(vboxEmbaralhar), 20);
	gtk_container_set_border_width(GTK_CONTAINER(vboxTamanhoTiras), 20);
	gtk_container_set_border_width(GTK_CONTAINER(hboxMain), 20);
	
	// Adiciona os GtkBox no container
	gtk_container_add(GTK_CONTAINER(container), vboxMain);
	gtk_container_add(GTK_CONTAINER(container), vboxOrientacao);
	gtk_container_add(GTK_CONTAINER(container), vboxEmbaralhar);
	gtk_container_add(GTK_CONTAINER(container), vboxTamanhoTiras);
	gtk_container_add(GTK_CONTAINER(container), hboxMain);
	gtk_container_add(GTK_CONTAINER(container), hboxText);
	gtk_container_add(GTK_CONTAINER(container), hboxOrientacao);
	gtk_container_add(GTK_CONTAINER(container), hboxEmbaralhar);
	
	// Add textura widgets
	gtk_container_add(GTK_CONTAINER(vboxMain), labelTextura);
	gtk_container_add(GTK_CONTAINER(vboxMain), hboxText);
	
	// Add widgets de tamanho e espacamento das tiras
	gtk_container_add(GTK_CONTAINER(hboxMain), vboxTamanhoTiras);
	gtk_container_add(GTK_CONTAINER(vboxTamanhoTiras), labelTamanho);
	gtk_container_add(GTK_CONTAINER(vboxTamanhoTiras), widgetControleTamanho);
	gtk_container_add(GTK_CONTAINER(hboxMain), vboxTamanhoTiras);
	gtk_container_add(GTK_CONTAINER(vboxTamanhoTiras), labelEspacamento);
	gtk_container_add(GTK_CONTAINER(vboxTamanhoTiras), widgetControleEspacamento);

	// Add widgets de orientação das tiras
	gtk_container_add(GTK_CONTAINER(vboxMain), hboxMain);
	gtk_container_add(GTK_CONTAINER(hboxMain), vboxOrientacao);
	gtk_container_add(GTK_CONTAINER(vboxOrientacao), labelOrientacao);
	gtk_container_add(GTK_CONTAINER(vboxOrientacao), hboxOrientacao);
	gtk_container_add(GTK_CONTAINER(hboxOrientacao), radioOrientacao1);
	gtk_container_add(GTK_CONTAINER(hboxOrientacao), radioOrientacao2);

	// Add widgets de embaralhamento das tiras
	gtk_container_add(GTK_CONTAINER(hboxMain), vboxEmbaralhar);
	gtk_container_add(GTK_CONTAINER(vboxEmbaralhar), labelEmbaralhar);
	gtk_container_add(GTK_CONTAINER(vboxEmbaralhar), hboxEmbaralhar);
	gtk_container_add(GTK_CONTAINER(hboxEmbaralhar), radioEmbaralhar1);
	gtk_container_add(GTK_CONTAINER(hboxEmbaralhar), radioEmbaralhar2);
	
}

Imagem meuFiltro(Imagem origem) {
	int i, j, x;
	int cont = 0, toggle = 1;
	int ch1 = 0, ch2 = 1, ch3 = 2;
	
	// Recebe os valores da barras de rolagem
	int nivelTiras = (int) gtk_range_get_value(GTK_RANGE(widgetControleTamanho));
	nivelTiras = origem.h / nivelTiras;
	int nivelEspacamento = (int) gtk_range_get_value(GTK_RANGE(widgetControleEspacamento));
	nivelEspacamento= origem.h / nivelEspacamento;

	// Calcula a qtd de tiras e espaçamentos
	int qtdTiras = origem.h / nivelTiras;
	int qtdEspacamentos = qtdTiras - 1;

	Imagem destino = alocarImagemDimensao(origem.w, (origem.h + (nivelEspacamento * qtdEspacamentos)), origem.numCanais);	

	for(i = 0, x = 0; i < destino.h; i++) {
		for(j = 0; j < destino.w; j++) {
			if (toggle % 2) {
				destino.m[i][j][ch1] = origem.m[x][j][ch1];
				destino.m[i][j][ch2] = origem.m[x][j][ch2];
				destino.m[i][j][ch3] = origem.m[x][j][ch3];
			} else {
				destino.m[i][j][0] = 0;
				destino.m[i][j][1] = 0;
				destino.m[i][j][2] = 0;
			}		
		}
		cont ++;

		if (toggle % 2) {
			x++;
		}
		
		if (cont == nivelTiras && toggle % 2) {
			toggle = 2;
			cont = 0;
		} else if (cont == nivelEspacamento && (!(toggle % 2))) {
			toggle = 1;
			cont = 0;
		}
	}

	return destino;
}
