#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	// Texturas
	labelTextura = gtk_label_new("Texturas");
	
	// Controle de tamanho e espaçamento das tiras
	labelTamanho = gtk_label_new("Tamanho das tiras");
	widgetControleTamanho = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
	g_signal_connect(G_OBJECT(widgetControleTamanho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	labelEspacamento = gtk_label_new("Espaçamento entre as tiras");
	widgetControleEspacamento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
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
	int i, j; 
	int iImg = 0, jImg = 0;
	int indiceEsp = 0;
	int img = 1;
	
	// Recebe os valores da barras de rolagem
	int tamanhoTiras = (int) gtk_range_get_value(GTK_RANGE(widgetControleTamanho));
	int tamanhoEspacamento = (int) gtk_range_get_value(GTK_RANGE(widgetControleEspacamento));

	// Calcula a qtd de tiras e espaçamentos
	int qtdTiras = origem.h / tamanhoTiras;
	int qtdEspacamentos = qtdTiras - 1;

	printf("%d %d  %d %d  %d \n", tamanhoTiras, tamanhoEspacamento, qtdTiras, qtdEspacamentos, ((origem.h) + (tamanhoEspacamento * qtdEspacamentos))); // usado apenas para a verificação dos valores


	//alocando uma nova imagem já com a altura modificada
	Imagem destino = alocarImagemDimensao(origem.w, ((origem.h) + (tamanhoEspacamento * qtdEspacamentos)), origem.numCanais);	 // altura = alturaOrigem + (tamanhoTiras * qntTiras)

	//percorrendo a imagem destino
	for(i = 0; i < destino.h; i++) {
		for(j = 0, jImg = 0; j < destino.w; j++) {
			if (img){ //copia o valor da imagem
				destino.m[i][j][0] = origem.m[iImg][jImg][0];
				destino.m[i][j][1] = origem.m[iImg][jImg][1];
				destino.m[i][j][2] = origem.m[iImg][jImg][2];
				jImg++; //incremento do indice j da imagem -> não é necessário usar aqui, mas vai facilitar na construção das tiras verticais

			}else{ //deixando a tira preta
				destino.m[i][j][0] = 0;
				destino.m[i][j][1] = 0;
				destino.m[i][j][2] = 0;
			}
		}

		if(img){ //incremento do indice i da imagem
			iImg++;
		} else { // incrmento do indice i do espaçamento
			indiceEsp++;
		}

		if((iImg != 0) && (iImg % tamanhoTiras == 0)  && img){ // condicional usada para alterar da imagem para o espaçamento 
			img = 0;
		}else if( (indiceEsp != 0) && (indiceEsp % tamanhoEspacamento == 0) && !img){ // condicional usada para alterar do espaçamento para a imagem
			img = 1;
		}
	}

	return destino;
	
}