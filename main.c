#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "grafo.c"
 

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
 
static void showWidget() {
    GtkWidget *box  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_name(GTK_WIDGET(box), "show-grapho");

    GtkWidget *image;

    GtkWidget *showWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(showWindow), 750, 450);
    gtk_window_set_title(GTK_WINDOW(showWindow), "Grafo dirigido");
    gtk_window_set_resizable(GTK_WINDOW(showWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(showWindow), GTK_WIN_POS_CENTER_ALWAYS);

    image = gtk_image_new_from_file("./grafo.png");
    gtk_container_add(GTK_CONTAINER(box), image);
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

    fprintf(archivo, "digraph %s {\n\tnode[shape = %s fillcolor = \"%s\" style = filled]\n", "grafo", "none", "#ffffff");
    
    fprintf(archivo, "\tbgcolor=transparent;\n");
    fprintf(archivo, "\tbgimage=\"./image/Fondo.png\";\n");
    fprintf(archivo, "\tnode [shape=none, image=\"./image/Estrella.png\"];\n");

    for(i = 0; i < grafo->num_nodos; i++) {
        for(j = 0; j < grafo->num_nodos; j++) {
            if(grafo->matriz_adyacencia[i][j] != 0) {
                fprintf(archivo, "    %d -> %d [label=%d];\n", i + 1, j + 1, grafo->matriz_adyacencia[i][j]);
            }

        }
    }
    // fprintf(archivo, "\t}");
    fprintf(archivo, "}");
    fclose(archivo);
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

            system("dot -Tpng -Gsize=600,600 -o grafo.png grafo.dot");
            showWidget();
        }
    }    
}


static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *buttBoxCrear, *buttBoxPlay, *buttBoxHelp, *buttBoxScore, *buttBoxExit, *box;
    GtkWidget *buttonCrear, *buttonAbrir, *buttonRecorr, *buttonSearch, *buttonExit;
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

    // Create box for buttons
    buttBoxCrear = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxPlay = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxHelp = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxScore = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxExit = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    // Create buttons and add at box container
    buttonCrear = gtk_button_new();
    buttonRecorr = gtk_button_new();
    buttonAbrir = gtk_button_new();
    buttonSearch = gtk_button_new();
    buttonExit = gtk_button_new();

    g_signal_connect(buttonAbrir, "clicked", G_CALLBACK(openFile), NULL);

    // Add buttons  at button box
    gtk_container_add(GTK_CONTAINER(buttBoxCrear), buttonCrear);
    gtk_container_add(GTK_CONTAINER(buttBoxHelp), buttonRecorr);
    gtk_container_add(GTK_CONTAINER(buttBoxPlay), buttonAbrir);
    gtk_container_add(GTK_CONTAINER(buttBoxScore), buttonSearch);
    gtk_container_add(GTK_CONTAINER(buttBoxExit), buttonExit);
    
    // Add buttons at box
    gtk_container_add(GTK_CONTAINER(box), buttBoxPlay);
    gtk_container_add(GTK_CONTAINER(box), buttBoxScore);
    gtk_container_add(GTK_CONTAINER(box), buttBoxHelp);
    gtk_container_add(GTK_CONTAINER(box), buttBoxCrear);
    gtk_container_add(GTK_CONTAINER(box), buttBoxExit);

    gtk_widget_set_size_request(GTK_WIDGET(buttonCrear), 240, 80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonRecorr), 240, 80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonAbrir), 240, 80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonSearch), 240,80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonExit), 240, 80);    
    
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCrear), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonRecorr), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAbrir), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonSearch), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "button");
   /// gtk_style_context_add_class(gtk_widget_get_style_context(imageExit), "images");
     
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCrear), "buttonCrear");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonRecorr), "buttonPlay");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAbrir), "buttonScore");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonSearch), "buttonSearch");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "buttonExit");
        
    // Set properties for winow
    mainwindow = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(mainwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (mainwindow), "torreAs");
    gtk_window_set_default_size (GTK_WINDOW (mainwindow), 650, 700);
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