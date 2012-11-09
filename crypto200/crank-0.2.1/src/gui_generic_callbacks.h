#include <gtk/gtk.h>


void
on_gui_generic_clist_select_row        (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_gui_generic_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);
