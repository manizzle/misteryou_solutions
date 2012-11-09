#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "crank.h"
#include "error.h"
#include "gui_generic_callbacks.h"
#include "gui_generic_interface.h"
#include "componant.h"
#include "parameter.h"
#include "gui_globals.h"
#include "gui_init.h"

#define MAX_ENUM_VALUES_STRING 80

void
on_gui_generic_clist_select_row        (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    char *enum_string;
    int enum_string_length;
    instance *i = (instance *) gtk_object_get_data(GTK_OBJECT(clist), "instance");
    parameter_description *parameter_table = i->componant_class->parameter_description_table;
    parameter_type type = parameter_table[row].type;
    GtkWidget *gui_generic_title_data_one = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_title_data_one");
    GtkWidget *gui_generic_title_data_two = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_title_data_two");
    GtkWidget *gui_generic_description = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_description");
    GtkWidget *gui_generic_default = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_default");
    GtkWidget *gui_generic_data_one = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_data_one");
    GtkWidget *gui_generic_data_two = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_data_two");
    GtkWidget *gui_generic_type = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_type");
    GtkWidget *gui_generic_table = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "gui_generic_table");
    GtkWidget *change_button = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(clist), "change_button");

    LOCK_CALLBACKS;

    gtk_object_set_data(GTK_OBJECT(change_button), "row", GINT_TO_POINTER(row));

    gtk_widget_set_sensitive(GTK_WIDGET(gui_generic_table), TRUE);
    gtk_label_set_text(GTK_LABEL(gui_generic_type), parameter_type_lookup(type));
    gtk_label_set_text(GTK_LABEL(gui_generic_description), parameter_table[row].description);
	gtk_label_set_text(GTK_LABEL(gui_generic_default), parameter_table[row].default_value);
    switch (type) {
    case PARAM_TYPE_ENUM:
	gtk_label_set_text(GTK_LABEL(gui_generic_title_data_one), "Possible values:");
	enum_string_length = strlen(parameter_table[row].data_one);
	enum_string = malloc(enum_string_length + 1);
	strcpy(enum_string, parameter_table[row].data_one);
	if (enum_string_length > MAX_ENUM_VALUES_STRING) 
	    enum_string[MAX_ENUM_VALUES_STRING] = '\0';
	gtk_label_set_text(GTK_LABEL(gui_generic_data_one), enum_string);
	free(enum_string);

	gtk_label_set_text(GTK_LABEL(gui_generic_title_data_two), "Number of possible values:");
	break;
    case PARAM_TYPE_INT:
    case PARAM_TYPE_FLOAT:
	gtk_label_set_text(GTK_LABEL(gui_generic_title_data_one), "Minimum value:");
	gtk_label_set_text(GTK_LABEL(gui_generic_title_data_two), "Maximum value:");
	gtk_label_set_text(GTK_LABEL(gui_generic_data_one), parameter_table[row].data_one);
	break;
    case PARAM_TYPE_STRING:
	gtk_label_set_text(GTK_LABEL(gui_generic_title_data_one), "");
	gtk_label_set_text(GTK_LABEL(gui_generic_title_data_two), "");
	gtk_label_set_text(GTK_LABEL(gui_generic_data_one), parameter_table[row].data_one);
	break;
    default:
	warn("Unknown parameter type %d\n", type);
	break;
    }
    gtk_label_set_text(GTK_LABEL(gui_generic_data_two), parameter_table[row].data_two);
    UNLOCK_CALLBACKS;
}


void
on_gui_generic_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    gchar *text;
    GtkWidget *entry = (GtkWidget *) gtk_object_get_data(GTK_OBJECT(button), "entry");
    instance *i =  (instance *) gtk_object_get_data(GTK_OBJECT(button), "instance");
    int row = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(button), "row"));
    int intvalue;
    double doublevalue;

    LOCK_CALLBACKS;

    text = gtk_editable_get_chars(GTK_EDITABLE(entry), 0, -1);
    switch (i->componant_class->parameter_description_table[row].type) {

    /* Error checking needed on user data!! */
    case PARAM_TYPE_ENUM:
    case PARAM_TYPE_INT:
	intvalue = atoi(text);
	poke_param(i, row, &intvalue);
	break;
    case PARAM_TYPE_FLOAT:
	doublevalue = atof(text);
	poke_param(i, row, &doublevalue);
	break;
    case PARAM_TYPE_STRING:
	poke_param(i, row, text);
	break;
    default:
	warn("Unknown parameter type\n");
	break;
    }
    rebuild_componant_gui(i->componant_class->type, UNKNOWN_FITNESS);
    g_free(text);
    UNLOCK_CALLBACKS;
}

