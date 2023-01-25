
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
 

  GtkListStore *store;
  GtkCellRenderer *renderer;

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
static void limit_text(GtkTextBuffer *buffer, GtkTextIter *new_text, GtkTextIter *new_text_end, gpointer user_data) {
    gint len = gtk_text_buffer_get_char_count(buffer);
    printf(" estas aqui?");
    if (len > 150) {
      printf(" estas aqui?");
        gtk_text_buffer_delete(buffer, new_text, new_text_end);
        printf(" estas aqui?");
    }
}


static void windowCreate (GtkApplication *app, gpointer user_data) {
  GtkWidget *Createwindow;
  GtkWidget *Createbox;
  GtkCssProvider *cssProvider;
  GtkWidget *textArea;
  GtkWidget *textScroll;


  Createbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  //datos necesarios para poder crear el text area
    textArea = gtk_text_view_new();
    //texScroll es necesario ya que contendra a el text view
    textScroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_container_add(GTK_CONTAINER(textScroll), textArea);
    gtk_container_add(GTK_CONTAINER(Createbox), textScroll);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
    gtk_text_buffer_set_text(buffer, "texto inicial", -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textArea), GTK_WRAP_NONE);
    gtk_widget_show(textArea);
    g_signal_connect(buffer, "insert-text", G_CALLBACK(limit_text), NULL);



    cssProvider = gtk_css_provider_new();

    // Set properties for winow
    Createwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(Createwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (Createwindow), "CREATE");
    gtk_window_set_default_size (GTK_WINDOW (Createwindow), 650, 700);
    gtk_window_set_resizable(GTK_WINDOW(Createwindow), FALSE);


    gtk_widget_set_name(GTK_WIDGET(Createbox), "Createbox");

    gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(cssProvider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(Createwindow), Createbox);
    gtk_widget_show_all (Createwindow);







}


static void windowOpen (GtkApplication *app, gpointer user_data) {
  GtkWidget *Openwindow;
  GtkWidget *Openbox;
  GtkCssProvider *cssProvider;


  Openbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    cssProvider = gtk_css_provider_new();

    // Set properties for winow
   Openwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(Openwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (Openwindow), "OPEN");
    gtk_window_set_default_size (GTK_WINDOW (Openwindow), 650, 700);
    gtk_window_set_resizable(GTK_WINDOW(Openwindow), FALSE);


    gtk_widget_set_name(GTK_WIDGET(Openbox), "Openbox");

    gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(cssProvider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(Openwindow), Openbox);
    gtk_widget_show_all (Openwindow);



}

static void windowAbout (GtkApplication *app, gpointer user_data) {
  GtkWidget *Aboutwindow;
  GtkWidget *Aboutbox;
  GtkCssProvider *cssProvider;


  Aboutbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    cssProvider = gtk_css_provider_new();

    // Set properties for winow
    Aboutwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(Aboutwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (Aboutwindow), "ABOUT");
    gtk_window_set_default_size (GTK_WINDOW (Aboutwindow), 650, 700);
    gtk_window_set_resizable(GTK_WINDOW(Aboutwindow), FALSE);


    gtk_widget_set_name(GTK_WIDGET(Aboutbox), "Aboutbox");

    gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(cssProvider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(Aboutwindow), Aboutbox);
    gtk_widget_show_all (Aboutwindow);



}


static void salir (){
  exit(-1);
}



static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *mainwindow;
    GtkWidget *buttBoxCreate, *buttBoxOpen, *buttBoxAbout, *buttBoxRoad, *buttBoxExit,*box;
    GtkWidget *buttonCreate, *buttonOpen, *buttonAbout, *buttonRoad,  *buttonExit;
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
    buttBoxRoad = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxExit = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    // Create buttons and add at box container
    buttonCreate = gtk_button_new();
    buttonRoad = gtk_button_new();
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
    gtk_container_add(GTK_CONTAINER(buttBoxAbout), buttonRoad);
    gtk_container_add(GTK_CONTAINER(buttBoxOpen), buttonOpen);
    gtk_container_add(GTK_CONTAINER(buttBoxRoad), buttonAbout);
    gtk_container_add(GTK_CONTAINER(buttBoxExit), buttonExit);
    
    // Add buttons at box
    gtk_container_add(GTK_CONTAINER(box), buttBoxCreate);
    gtk_container_add(GTK_CONTAINER(box), buttBoxOpen);
    gtk_container_add(GTK_CONTAINER(box), buttBoxRoad);
    gtk_container_add(GTK_CONTAINER(box), buttBoxAbout);
    
    gtk_container_add(GTK_CONTAINER(box), buttBoxExit);

    gtk_widget_set_size_request(GTK_WIDGET(buttonCreate), 240, 60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonRoad), 240, 60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonOpen), 240, 60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonAbout), 240,60);
    gtk_widget_set_size_request(GTK_WIDGET(buttonExit), 240, 60);

    
    
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCreate), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonRoad), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonOpen), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAbout), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "button");
    

    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxCreate), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxRoad), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxOpen), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxAbout), "button-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttBoxExit), "button-box");
   /// gtk_style_context_add_class(gtk_widget_get_style_context(imageExit), "images");


     
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCreate), "buttonCreate");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonRoad), "buttonRoad");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonOpen), "buttonOpen");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAbout), "buttonAbout");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "buttonExit");
    
        
    // Set properties for winow
    mainwindow = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(mainwindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (mainwindow), "SUPER GRAFOS");
    gtk_window_set_default_size (GTK_WINDOW (mainwindow), 400, 650);
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