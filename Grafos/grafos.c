
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
 

  GtkListStore *store;
  GtkCellRenderer *renderer;

  GString * bin;
  gint i;
// Function to open a dialog box with a message
static void advertencia (GtkWindow *parent, gchar *message)
{
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





static void activate (GtkApplication *app, gpointer user_data) {
    GtkWidget *mainwindow;
    GtkWidget *buttBoxCrear, *buttBoxPlay, *buttBoxHelp, *buttBoxScore, *buttBoxExit, *box;
    GtkWidget *buttonCrear, *buttonPlay, *buttonHelp, *buttonScore, *buttonExit;
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
    buttonHelp = gtk_button_new();
    buttonPlay = gtk_button_new();
    buttonScore = gtk_button_new();
    buttonExit = gtk_button_new();

    // gtk_button_set_image(GTK_BUTTON(buttonPlay), imagePlay);
    // gtk_button_set_image(GTK_BUTTON(buttonScore), imageScore);
    // gtk_button_set_image(GTK_BUTTON(buttonHelp), imageSett);
    // gtk_button_set_image(GTK_BUTTON(buttonCrear), imageAcer);
    // gtk_button_set_image(GTK_BUTTON(buttonExit), imageExit);


    // Add signals at buttons
    //g_signal_connect(buttonPlay, "clicked", G_CALLBACK(initGame), NULL);
    //g_signal_connect(buttonCrear, "clicked", G_CALLBACK(acercaDe), NULL);
    //g_signal_connect(buttonScore, "clicked", G_CALLBACK(windowScore), NULL);

    // Add buttons  at button box
    gtk_container_add(GTK_CONTAINER(buttBoxCrear), buttonCrear);
    gtk_container_add(GTK_CONTAINER(buttBoxHelp), buttonHelp);
    gtk_container_add(GTK_CONTAINER(buttBoxPlay), buttonPlay);
    gtk_container_add(GTK_CONTAINER(buttBoxScore), buttonScore);
    gtk_container_add(GTK_CONTAINER(buttBoxExit), buttonExit);
    
    // Add buttons at box
    gtk_container_add(GTK_CONTAINER(box), buttBoxPlay);
    gtk_container_add(GTK_CONTAINER(box), buttBoxScore);
    gtk_container_add(GTK_CONTAINER(box), buttBoxHelp);
    gtk_container_add(GTK_CONTAINER(box), buttBoxCrear);
    gtk_container_add(GTK_CONTAINER(box), buttBoxExit);

    gtk_widget_set_size_request(GTK_WIDGET(buttonCrear), 240, 80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonHelp), 240, 80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonPlay), 240, 80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonScore), 240,80);
    gtk_widget_set_size_request(GTK_WIDGET(buttonExit), 240, 80);

    
    
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCrear), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonHelp), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonPlay), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonScore), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "button");
   /// gtk_style_context_add_class(gtk_widget_get_style_context(imageExit), "images");


     
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonCrear), "buttonCrear");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonHelp), "buttonHelp");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonPlay), "buttonPlay");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonScore), "buttonScore");
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