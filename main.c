#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
// #include "grafo.c"
#include "dijkstra.c"
 
struct Grafo* grap;
GtkCellRenderer *renderer;
GtkWidget *mainwindow;
GtkListStore *store;
GString * bin;
gint i;

// Function to open a dialog box with a message
static void advertencia (GtkWindow *parent, gchar *message) {
 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;

 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Message",NULL,flags,("_OK"), GTK_RESPONSE_NONE,NULL);
 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (message);(bin->str)[i];

 // Ensure that the dialog box is destroyed when the user responds

 g_signal_connect_swapped (dialog, "response",G_CALLBACK (gtk_widget_destroy),dialog);

 // Add the label, and show everything we’ve added

 gtk_container_add (GTK_CONTAINER (content_area), label);
 gtk_widget_show_all (dialog);

}

void searchRoat () {
    dijkstra(grap, 0, 1);
}

void windowDijkstra () {
    GtkWidget *dijsWindow, *box, *button, *buttonBox, *desde, *hasta, *fixed1, *fixed2;
    GtkWidget *labelDesde, *labelHasta, *fixed3;
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    fixed1 = gtk_fixed_new();
    fixed2 = gtk_fixed_new();
    fixed3 = gtk_fixed_new();

    gtk_widget_set_name(GTK_WIDGET(box), "box-dijkstra");

    button = gtk_button_new_with_label("Buscar");
    buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    g_signal_connect(button, "clicked", G_CALLBACK(searchRoat), NULL);

    desde = gtk_combo_box_text_new();
    hasta = gtk_combo_box_text_new();
    labelDesde = gtk_label_new("Desde");
    labelHasta = gtk_label_new("Hasta");

    gtk_style_context_add_class(gtk_widget_get_style_context(labelDesde), "label-dijkstra");
    gtk_style_context_add_class(gtk_widget_get_style_context(labelHasta), "label-dijkstra");
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button-camino");

    char str[10];
    printf("%d\n", grap->num_nodos);
    for (int i = 0; i < grap -> num_nodos; i++) {
        sprintf(str, "%d", i + 1);
        gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(desde), i, str);
        gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(hasta), i, str);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(desde), 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(hasta), 0);

    gtk_fixed_put(GTK_FIXED(fixed1), desde, 40, 60);
    gtk_fixed_put(GTK_FIXED(fixed2), hasta, 40, 60);
    gtk_fixed_put(GTK_FIXED(fixed1), labelDesde, 40, 10);
    gtk_fixed_put(GTK_FIXED(fixed2), labelHasta, 40, 10);

    // Set properties for winow
    dijsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(dijsWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (dijsWindow), "CREATE");
    gtk_window_set_default_size (GTK_WINDOW (dijsWindow), 750, 460);
    gtk_window_set_resizable(GTK_WINDOW(dijsWindow), FALSE);

    gtk_container_add(GTK_CONTAINER(buttonBox), button);

    gtk_container_add(GTK_CONTAINER(box), fixed1);
    gtk_container_add(GTK_CONTAINER(box), fixed2);
    gtk_container_add(GTK_CONTAINER(box), buttonBox);
    gtk_container_add(GTK_CONTAINER(dijsWindow), box);
    gtk_widget_show_all (dijsWindow);
}

gchar* getFileName () {
    GtkWidget *dialog;
    gchar *filename;
    // Crea un diálogo de selección de archivos
    dialog = gtk_file_chooser_dialog_new("Seleccionar archivo",
                                                    GTK_WINDOW(mainwindow),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Cancelar", GTK_RESPONSE_CANCEL,
                                                    "_Abrir", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    // Muestra el diálogo y espera a que el usuario seleccione un archivo
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        // Obtiene la ruta del archivo seleccionado
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    // Destruye el diálogo
    gtk_widget_destroy(dialog);
        printf("Archivo seleccionado: %s\n", filename);
    return filename;
}
static void showMainWindow () {
    gtk_widget_set_visible(GTK_WIDGET(mainwindow), TRUE);

}

static void showWidget() {
    gtk_widget_set_visible(GTK_WIDGET(mainwindow), FALSE);
    GtkWidget *fix  = gtk_fixed_new();
    GtkWidget *box  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(box), 720, 450);
    gtk_widget_set_name(GTK_WIDGET(box), "show-grapho");

    GtkWidget *image;
    GtkWidget *button, *buttonBox;
    buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new();
    g_signal_connect(button, "clicked", G_CALLBACK(windowDijkstra), NULL);
    gtk_widget_set_size_request(GTK_WIDGET(button), 70, 70);
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button-dijkstra");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonBox), "button-box-dijkstra");


    GtkWidget *showWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(showWindow), 750, 450);
    gtk_window_set_title(GTK_WINDOW(showWindow), "Grafo dirigido");
    gtk_window_set_resizable(GTK_WINDOW(showWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(showWindow), GTK_WIN_POS_CENTER_ALWAYS);
    g_signal_connect(showWindow, "destroy", G_CALLBACK(showMainWindow), NULL);

    image = gtk_image_new_from_file("./grafo.png");
    
    gtk_fixed_put(GTK_FIXED(fix), buttonBox, 670, 25);
    gtk_fixed_put(GTK_FIXED(fix), image, 50, 25);
    gtk_container_add(GTK_CONTAINER(buttonBox), button);
    gtk_container_add(GTK_CONTAINER(box), fix);
    // gtk_container_add(GTK_CONTAINER(fix), image);
    gtk_container_add(GTK_CONTAINER(showWindow), box);

    gtk_widget_show_all(showWindow);
}

void exportar_grafo_dot(struct Grafo *grafo, char *nombre_archivo) {
    int i, j;
    FILE *archivo = fopen(nombre_archivo, "w");
    if(archivo == NULL) {
        printf("Error al crear el archivo %s", nombre_archivo);
        return;
    }
    // fprintf(archivo, "digraph {\n");

    fprintf(archivo, "digraph %s {\n\tnode[shape = %s fillcolor = \"%s\" style = filled]\n", "grafo", "none", "#ffffff00");
    
    fprintf(archivo, "\tbgcolor=transparent;\n");
    fprintf(archivo, "\tbgimage=\"./image/Fondo.png\";\n");
    fprintf(archivo, "\tnode [shape=none, image=\"./image/Estrella.png\"];\n");

    for(i = 0; i < grafo->num_nodos; i++) {
        for(j = 0; j < grafo->num_nodos; j++) {
            if(grafo->matriz_adyacencia[i][j] != 0) {
                fprintf(archivo, "    %d -> %d [label=%d color=\"#ffffff\" fontcolor=aqua];\n", i + 1, j + 1, grafo->matriz_adyacencia[i][j]);
            }

        }
    }
    // fprintf(archivo, "\t}");
    fprintf(archivo, "}");
    fclose(archivo);
    puts("Exportado");
}

static void openFile (GtkApplication* app, gpointer user_data) {
    puts("1");
    gchar *path = getFileName();
    puts("2");
    printf("Archivo: %s\n", path);
    // Valida que se seleccione un archivo
    if(strcmp(path, "") != 0){
        puts("3");
        FILE *file = fopen(path, "rb");

        if (file != NULL) {

            int *vector = (int *) malloc(sizeof(int)); //Asigna memoria al vector antes de llamar a realloc()
            int tamanio = 0; //Variable para llevar el registro del tamaño del vector
            int valor;
            char caracter;
        
            file = fopen("matriz.txt", "r"); //Abre el archivo en modo lectura

            // Save data for in array 
            while((caracter = fgetc(file)) != EOF) { //Lee caracter por caracter hasta el fin del archivo
                if(caracter != '-') { //Compara si el caracter es diferente de "-"
                    valor = caracter - '0'; //Convierte el caracter a un número
                    tamanio++;
                    vector = (int *) realloc(vector, tamanio * sizeof(int)); //Aumenta el tamaño del vector
                    // puts("Abierto");
                    vector[tamanio-1] = valor; //Agrega el valor al vector
                }
            }

            fclose(file); //Cierra el archivo

            // Search size for array bidimencional
            int size = 0;
            for(int i = 0; i < tamanio; i++) {
                if (vector[i] == 0-38) {
                    puts("");
                    size = i;
                    printf("size: %d\n", i);
                    break;
                }
            }
            int data[size][size];
            int aux = 0;
            int k = 0;
            for(int i = 0; i < tamanio; i++) {
                // printf("%d ", vector[i]);
                if (vector[i] == -38) {
                    // puts("");
                    aux = i + 1;
                    k++;
                } else {
                    data[i - aux][k] = vector[i];    
                    // printf("i: %d j: %d, total: %d\n", i - aux, k, tamanio);
                }
            }
            free(vector);
            // Print data
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    printf("%d-", data[j][i]);
                }
                puts("");
            }
            struct Grafo* grapho = (struct Grafo *) malloc(sizeof(struct Grafo));;
            inicializar_grafo(grapho, size, data);
            imprimir_grafo(grapho);
            exportar_grafo_dot(grapho, "grafo.dot");
            grap=grapho;
            system("dot -Tpng -Gsize=600,600 -o grafo.png grafo.dot");
            showWidget();
        }
    }    
}

static void salir (){
  exit(-1);
}

static void windowAbout (GtkApplication *app, gpointer user_data) {
  GtkWidget *Aboutwindow;
  GtkWidget *Aboutbox;
  GtkCssProvider *cssProvider;


  Aboutbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);


    // Set properties for winow
    Aboutwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(Aboutwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (Aboutwindow), "ABOUT");
    gtk_window_set_default_size (GTK_WINDOW (Aboutwindow), 650, 700);
    gtk_window_set_resizable(GTK_WINDOW(Aboutwindow), FALSE);


    gtk_widget_set_name(GTK_WIDGET(Aboutbox), "Aboutbox");

    gtk_container_add(GTK_CONTAINER(Aboutwindow), Aboutbox);
    gtk_widget_show_all (Aboutwindow);

}

static void limit_text(GtkTextBuffer *buffer, GtkTextIter *new_text, GtkTextIter *new_text_end, gpointer user_data) {
    gint len = gtk_text_buffer_get_char_count(buffer);
    // printf(" estas aqui?");
    if (len > 150) {
    //   printf(" estas aqui?");
        gtk_text_buffer_delete(buffer, new_text, new_text_end);
        // printf(" estas aqui?");
    }
}

void inputText (GtkApplication *app, gpointer user_data) {
    GtkTextBuffer *buffer = (GtkTextBuffer*) user_data;

    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    gchar *text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &start, &end, TRUE);
    printf("%s\n", text);

    int band = 0;

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] != '1' && text[i] != '0' && text[i] != '-' && text[i] != '\n') {
            printf("El caracter en la posicion %d no es valido\n", i);
            band++;
        }
    }

    if (band == 0) {
        int n = 0, m = 0;
        for (int i = 0; text[i] != '\0'; i++) {
            if (text[i] == '1' || text[i] == '0') {
                if (m == 0)
                    n++;
                // if(m == 0 && text[i] == '\n') 
                //     m++;
            }
            if (text[i] == '\n') {
                m++;
            }
                // printf("%d\n", m);
        }
        m++;
        printf("%d == %d\n", n,m);
        if(n == m) {
        // puts("1");

            int matriz[n][m];
            
            int aux = 0;
            int k = 0;
            for(int i = 0; text[i] != '\0'; i++) {
                // printf("%d ", vector[i]);
                if (!(text[i] != '\n')) {
                    // puts("ln");
                    aux = i + 1;
                    k++;
                } else {
                    if (text[i] == '0') {
                        matriz[i - aux][k] = 0;
                        // printf("0.- mat: %d id: %d\n", matriz[i - aux][k], i);
                    }
                    if (text[i] == '1') {
                        matriz[i - aux][k] = 1;
                        // printf("1.- mat: %d id: %d\n", matriz[i - aux][k], i);
                    }
                    // matriz[i - aux][k] =  (int)text[i] - '0';    
                    // printf("i: %d j: %d, total: %d\n", i - aux, k, matriz[i - aux][k]);
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // printf("%d-", matriz[i][j]);
                }
                puts("");
            }
            
              
            puts("aqui");
            printf("n:%d", n);
            struct Grafo* grapho = (struct Grafo *) malloc(sizeof(struct Grafo));
            inicializar_grafo(grapho, n, matriz);
            imprimir_grafo(grapho);
            exportar_grafo_dot(grapho, "grafo.dot");
            system("dot -Tpng -Gsize=600,600 -o grafo.png grafo.dot");
            grap = grapho;
            showWidget();
        }
            puts("fuera");

    }
}

static void windowCreate (GtkApplication *app, gpointer user_data) {
  GtkWidget *Createwindow;
  GtkWidget *Createbox;
  GtkWidget *textArea;
  GtkWidget *textScroll;
  GtkWidget *button, *buttBox;

    button = gtk_button_new_with_label("Crear");
    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(buttBox), button);
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button-okay");
    gtk_widget_set_margin_top(GTK_WIDGET(buttBox), 40);

  Createbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_margin_top(GTK_WIDGET(Createbox), 40);
  gtk_widget_set_margin_end(GTK_WIDGET(Createbox), 40);
  gtk_widget_set_margin_start(GTK_WIDGET(Createbox), 40);

  //datos necesarios para poder crear el text area
    textArea = gtk_text_view_new();
    //texScroll es necesario ya que contendra a el text view
    textScroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_style_context_add_class(gtk_widget_get_style_context(textArea), "GtkTextView");
    gtk_widget_set_name(GTK_WIDGET(textArea), "text-area");
    gtk_widget_set_size_request(GTK_WIDGET(textScroll), -1, 200);
    // gtk_style_context_add_class(gtk_widget_get_style_context(textScroll), "text-area");

    gtk_container_add(GTK_CONTAINER(textScroll), textArea);
    gtk_container_add(GTK_CONTAINER(Createbox), textScroll);
    gtk_container_add(GTK_CONTAINER(Createbox), buttBox);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
    gtk_text_buffer_set_text(buffer, "", -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textArea), GTK_WRAP_NONE);
    gtk_widget_show(textArea);
    g_signal_connect(buffer, "insert-text", G_CALLBACK(limit_text), NULL);
    g_signal_connect(button, "clicked", G_CALLBACK(inputText), buffer);


    // Set properties for winow
    Createwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(Createwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (Createwindow), "CREATE");
    gtk_window_set_default_size (GTK_WINDOW (Createwindow), 650, 360);
    gtk_window_set_resizable(GTK_WINDOW(Createwindow), FALSE);

    gtk_widget_set_name(GTK_WIDGET(Createbox), "Createbox");

    gtk_container_add(GTK_CONTAINER(Createwindow), Createbox);
    gtk_widget_show_all (Createwindow);
}


static void activate (GtkApplication *app, gpointer user_data) {
    // GtkWidget *mainwindow;
    GtkWidget *buttBoxCreate, *buttBoxOpen, *buttBoxAbout, *buttBoxExit,*box;
    GtkWidget *buttonCreate, *buttonOpen, *buttonAbout,  *buttonExit;
    GtkWidget *imageExit, *imageAcer, *imagePlay, *imageScore, *imageSett;
    GtkCssProvider *cssProvider;
    // Load images for buttons
    // imagePlay = gtk_image_new_from_file("./image/PLAY.png");
    // imageScore = gtk_image_new_from_file("./image/SCORE.png");
    // imageAcer = gtk_image_new_from_file("./image/CREDITS.png");
    // imageExit = gtk_image_new_from_file("./image/EXIT.png");
    // imageSett = gtk_image_new_from_file("./image/SETTINGS.png");

    cssProvider = gtk_css_provider_new();

    // Create container fixed
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    // gtk_widget_set_margin_start(GTK_WIDGET(box), 20);

    // Create box for buttons
    buttBoxCreate = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxOpen = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxAbout = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    // buttBoxRoad = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxExit = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    // Create buttons and add at box container
    buttonCreate = gtk_button_new();
    // buttonRoad = gtk_button_new();
    buttonOpen = gtk_button_new();
    buttonAbout = gtk_button_new();
    buttonExit = gtk_button_new();

    // gtk_button_set_image(GTK_BUTTON(buttonOpen), imagePlay);
    // gtk_button_set_image(GTK_BUTTON(buttonAbout), imageScore);
    // gtk_button_set_image(GTK_BUTTON(buttonRoad), imageSett);
    // gtk_button_set_image(GTK_BUTTON(buttonCreate), imageAcer);
    // gtk_button_set_image(GTK_BUTTON(buttonExit), imageExit);


    // Add signals at buttons

    g_signal_connect(buttonCreate, "clicked", G_CALLBACK(windowCreate), NULL);
    g_signal_connect(buttonOpen, "clicked", G_CALLBACK(openFile), NULL);
    g_signal_connect(buttonAbout, "clicked", G_CALLBACK(windowAbout), NULL);
    g_signal_connect(buttonExit, "clicked", G_CALLBACK(salir), NULL);


    // Add buttons  at button box
    gtk_container_add(GTK_CONTAINER(buttBoxCreate), buttonCreate);
    // gtk_container_add(GTK_CONTAINER(buttBoxAbout), buttonRoad);
    gtk_container_add(GTK_CONTAINER(buttBoxOpen), buttonOpen);
    gtk_container_add(GTK_CONTAINER(buttBoxAbout), buttonAbout);
    gtk_container_add(GTK_CONTAINER(buttBoxExit), buttonExit);
    
    // Add buttons at box
    gtk_container_add(GTK_CONTAINER(box), buttBoxCreate);
    gtk_container_add(GTK_CONTAINER(box), buttBoxOpen);
    // gtk_container_add(GTK_CONTAINER(box), buttBoxRoad);
    gtk_container_add(GTK_CONTAINER(box), buttBoxAbout);
    
    gtk_container_add(GTK_CONTAINER(box), buttBoxExit);

    gtk_widget_set_size_request(GTK_WIDGET(buttonCreate), 230, 60);
    // gtk_widget_set_size_request(GTK_WIDGET(buttonRoad), 230, 60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonOpen), 230, 60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonAbout), 230,60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonExit), 230, 60);

    
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCreate), "button");
    // gtk_style_context_add_class(gtk_widget_get_style_context(buttonRoad), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonOpen), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAbout), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "button");
    

    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxCreate), "button-box");
    // gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxRoad), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxOpen), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxAbout), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxExit), "button-box");
   /// gtk_style_context_add_class(gtk_widget_get_style_context(imageExit), "images");


     
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCreate), "buttonCreate");
    // gtk_style_context_add_class(gtk_widget_get_style_context(buttonRoad), "buttonRoad");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonOpen), "buttonOpen");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAbout), "buttonAbout");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "buttonExit");
    
        
    // Set properties for winow
    mainwindow = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(mainwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (mainwindow), "SUPER GRAFOS");
    gtk_window_set_default_size (GTK_WINDOW (mainwindow), 450, 650);
    gtk_window_set_resizable(GTK_WINDOW(mainwindow), FALSE);


    gtk_widget_set_name(GTK_WIDGET(box), "box");

    gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(cssProvider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(mainwindow), box);
    gtk_widget_show_all (mainwindow);
}


int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}



 // Compiler: gcc `pkg-config --cflags gtk+-3.0` -o auto main.c `pkg-config --libs gtk+-3.0`