#include <gtk/gtk.h>

#include "crank.h"
#include "componant.h"
#include "gui_init.h"
#include "gui_callbacks.h"
#include "gui_interface.h"
#include "gui_support.h"
#include "gui_globals.h"
#include "gui_textarea.h"
#include "globals.h"
#include "error.h"
#include "files.h"
#include <assert.h>
#include "patch.h"
#include "scheme_interface.h"

#ifdef HAVE_LIBGUILE
#include <libguile.h>
#endif /* HAVE_LIBGUILE */

/* Text to use in the ABOUT dialog box */
#define STR_ABOUT_DIALOG_TEXT					\
"Crank v" VERSION " (C) 2001\n\n"				\
"Author: Matthew Russell <twig5151@yahoo.com>\n"		\
"Built: " __TIME__ " on " __DATE__ "\n"				\
"\n"								\
"For more information visit http://crank.sourceforge.net/\n"

void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    GtkWidget *about_dialog;
    GtkWidget *about_dialog_text;

    LOCK_CALLBACKS;
    
    about_dialog = create_about_dialog();

    about_dialog_text = lookup_widget(GTK_WIDGET(about_dialog), "about_dialog_text");
    gtk_text_insert(GTK_TEXT(about_dialog_text), NULL, NULL, NULL, STR_ABOUT_DIALOG_TEXT, -1);

    gtk_widget_show(about_dialog);
    
    UNLOCK_CALLBACKS;

}

#define BUFFER_SIZE 4096
static GtkWidget *build_componant_choice_dialog(char *id_string) {
    int i, componant_count = 0;
    char *row_buf[2], buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    GtkWidget *choice_dialog;
    GtkWidget *componant_choice_list;
    GtkWidget *componant_choice_table;
    componant *componant_list = get_componant_list();
    componant *ith_componant;
    int number_of_componants = get_number_of_componants();
    componant_type componant_filter = COMPONANT_TYPE_ANY;
    row_buf[0] = buf1; row_buf[1] = buf2;
    
    if (!strcmp(id_string, "transform_componant")) 
	componant_filter = COMPONANT_TYPE_TRANSFORM;
    else if (!strcmp(id_string, "heuristic_componant")) 
	componant_filter = COMPONANT_TYPE_HEURISTIC;
    else if (!strcmp(id_string, "fitness_componant")) 
	componant_filter = COMPONANT_TYPE_FITNESS;
    else if (!strcmp(id_string, "transform_interface") || !strcmp(id_string, "heuristic_interface") || !strcmp(id_string, "fitness_interface")) 
	componant_filter = COMPONANT_TYPE_GUI;
    else 
	componant_filter = COMPONANT_TYPE_ANY;

    set_componant_choice_install_here(id_string);
    
    choice_dialog = create_componant_choice_dialog();

    componant_choice_list = lookup_widget(GTK_WIDGET(choice_dialog), "componant_choice_list");
    gtk_clist_set_column_visibility(GTK_CLIST(componant_choice_list), 1, FALSE);

    for (i = 0; i < number_of_componants; i++) {
	ith_componant = lookup_componant(componant_list, i);
	if (!strcmp(ith_componant->name, "null"))
	    continue;

	if (componant_filter != COMPONANT_TYPE_ANY) 
	    if (componant_filter != ith_componant->type)
		continue;

	/* TODO: Check GUI componants */

	sprintf(buf1, "%s_%s", componant_type_lookup(ith_componant->type), ith_componant->name);
	sprintf(buf2, "%d", i);
	gtk_clist_append(GTK_CLIST(componant_choice_list), row_buf);
	componant_count++;
    }
    gtk_clist_set_column_width(GTK_CLIST(componant_choice_list), 0, gtk_clist_optimal_column_width(GTK_CLIST(componant_choice_list), 0));

    componant_choice_table = lookup_widget(GTK_WIDGET(choice_dialog), "componant_choice_table");
    gtk_widget_set_sensitive(componant_choice_table, FALSE);    

    set_componant_choice_clist_selected_componant(NULL);

    return choice_dialog;

}

void
on_choose_componant_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;
    gtk_widget_show(build_componant_choice_dialog((char *) user_data));
    UNLOCK_CALLBACKS;
}


void
on_componant_choice_list_select_row    (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    int assoc_componant_index;
    char *buf_ptr, buf[BUFFER_SIZE];
    componant *comp, *componant_list = get_componant_list();
    GtkWidget *componant_choice_name, *componant_choice_source, *componant_choice_description, *componant_choice_applies_to, *componant_choice_label_applies_to, *componant_choice_table;

    componant_choice_name = lookup_widget(GTK_WIDGET(clist), "componant_choice_name");
    componant_choice_source = lookup_widget(GTK_WIDGET(clist), "componant_choice_source");
    componant_choice_description = lookup_widget(GTK_WIDGET(clist), "componant_choice_description");
    componant_choice_applies_to = lookup_widget(GTK_WIDGET(clist), "componant_choice_applies_to");
    componant_choice_label_applies_to = lookup_widget(GTK_WIDGET(clist), "componant_choice_label_applies_to");
    componant_choice_table = lookup_widget(GTK_WIDGET(clist), "componant_choice_table");
    
    LOCK_CALLBACKS;

    gtk_widget_set_sensitive(componant_choice_table, TRUE);
    gtk_widget_set_sensitive(componant_choice_label_applies_to, TRUE);

    gtk_clist_get_text(GTK_CLIST(clist), row, 1, &buf_ptr);
    if (sscanf(buf_ptr, "%d", &assoc_componant_index) != 1) { warn("Internal error in clist associated componant index\n"); }
    comp = lookup_componant(componant_list, assoc_componant_index);

    sprintf(buf, "%s_%s", componant_type_lookup(comp->type), comp->name);
    gtk_label_set_text(GTK_LABEL(componant_choice_name), buf);
    gtk_label_set_text(GTK_LABEL(componant_choice_source), comp->filename);
    gtk_text_set_point(GTK_TEXT(componant_choice_description), 0);
    gtk_text_forward_delete(GTK_TEXT(componant_choice_description), gtk_text_get_length(GTK_TEXT(componant_choice_description)));
    gtk_text_insert(GTK_TEXT(componant_choice_description), NULL, NULL, NULL, comp->description, -1);

    if (comp->type == COMPONANT_TYPE_GUI) {
	switch (comp->type_data.gui->componant_target_type) {
	case COMPONANT_TYPE_ANY:
	    gtk_label_set_text(GTK_LABEL(componant_choice_applies_to), "Any componant");
	    break;
	case COMPONANT_TYPE_TRANSFORM:
	    gtk_label_set_text(GTK_LABEL(componant_choice_applies_to), "Transform componants");
	    break;
	case COMPONANT_TYPE_FITNESS:
	    gtk_label_set_text(GTK_LABEL(componant_choice_applies_to), "Fitness componants");
	    break;
	case COMPONANT_TYPE_HEURISTIC:
	    gtk_label_set_text(GTK_LABEL(componant_choice_applies_to), "Heuristic componants");
	    break;
	case COMPONANT_TYPE_SPECIFIC:
	    gtk_label_set_text(GTK_LABEL(componant_choice_applies_to), comp->type_data.gui->componant_target_name);
	    break;
	default:
	    warn("Unknown componant target type\n");
	    break;
	} 
	
    } else {
	    gtk_label_set_text(GTK_LABEL(componant_choice_applies_to), "");
	    gtk_widget_set_sensitive(componant_choice_label_applies_to, FALSE);
    }
    set_componant_choice_clist_selected_componant(comp);
    UNLOCK_CALLBACKS;
}

void
on_componant_choice_cancel_button_clicked (GtkButton       *button,
                                           gpointer         user_data)
{
    GtkWidget *componant_choice_dialog;
    LOCK_CALLBACKS;
    componant_choice_dialog = lookup_widget(GTK_WIDGET(button), "componant_choice_dialog");
    gtk_widget_destroy(componant_choice_dialog);    
    UNLOCK_CALLBACKS;
}


void
on_componant_choice_ok_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *componant_choice_dialog;
    instance **install_here;
    componant *componant;
    LOCK_CALLBACKS;
    componant_choice_dialog = lookup_widget(GTK_WIDGET(button), "componant_choice_dialog");
    gtk_widget_destroy(componant_choice_dialog);    

    if ((componant = get_componant_choice_clist_selected_componant())) {
	install_here = get_componant_choice_install_here();  /* Get location to place new instance */           
	if (install_here) {
	    free_instance(*install_here);
	    *install_here = make_new_instance(componant);
	    rebuild_componant_gui(componant->type, UNKNOWN_FITNESS);
	}
    }
    UNLOCK_CALLBACKS;
}


void
on_source_text_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;

    handle_source_text_change();
    
    UNLOCK_CALLBACKS;
}


void
on_equate                              (GtkButton       *button,
                                        gpointer         user_data)
{
    char *text;
    LOCK_CALLBACKS;
    text = get_view_text();
    set_source_text(text);
    free(text);
    handle_source_text_change();
    UNLOCK_CALLBACKS;
}

static int yield(char *message, double progress) {
    GtkWidget *heuristic_log, *progress_bar, *textarea;

    assert(message); assert(progress >= 0.0 && progress <= 1.0);
    heuristic_log = get_heuristic_log();


    if (heuristic_log) {
	progress_bar = lookup_widget(GTK_WIDGET(heuristic_log), "heuristic_log_progress_bar");
	textarea = lookup_widget(GTK_WIDGET(heuristic_log), "heuristic_log_text");
	gtk_progress_set_percentage(GTK_PROGRESS(progress_bar), progress);
	if (*message)
	    gtk_text_insert(GTK_TEXT(textarea), NULL, NULL, NULL, message, -1);
    }

    while (gtk_events_pending())
	gtk_main_iteration();

    return get_stop_heuristic();
}

static void improvement_found(instance *i, double fitness) {
    set_current_transform(i);
    rebuild_componant_gui(COMPONANT_TYPE_TRANSFORM, fitness);
}

void
on_start_heuristic                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *source_text, *heuristic_log, *heuristic_log_text;
    char *text, message_buf[BUFFER_SIZE];
    LOCK_CALLBACKS;

    set_stop_heuristic(FALSE);
    
    /* Ghost out some of the gui */
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_open_button"), FALSE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_save_button"), FALSE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_equate_button"), FALSE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_heuristic_button"), FALSE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "main_menubar"), FALSE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "source_text"), FALSE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "main_notebook"), FALSE);


    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_stop_button"), TRUE);

    /* If the log window exists, then reset it, otherwise create a new one */
    if ((heuristic_log = get_heuristic_log())) {
	heuristic_log_text = lookup_widget(GTK_WIDGET(heuristic_log), "heuristic_log_text");
	gtk_text_set_point(GTK_TEXT(heuristic_log_text), 0);
	gtk_text_forward_delete(GTK_TEXT(heuristic_log_text), gtk_text_get_length(GTK_TEXT(heuristic_log_text)));
    } else {
	set_heuristic_log(heuristic_log = create_heuristic_log());
    }
    gtk_widget_show(get_heuristic_log());

    sprintf(message_buf, "*** BEGIN heuristic_%s\n", get_current_heuristic()->componant_class->name);
    yield(message_buf, 0.0);
    sprintf(message_buf, "Transform Class: transform_%s\nFitness Class: fitness_%s\n", get_current_transform()->componant_class->name, get_current_fitness()->componant_class->name);
    yield(message_buf, 0.0);

    source_text = lookup_widget(GTK_WIDGET(get_main_window()), "source_text");
    text = gtk_editable_get_chars(GTK_EDITABLE(source_text), 0, -1);
    heuristic(get_current_heuristic(), text, get_current_transform()->componant_class, get_current_transform(), get_current_fitness(), yield, improvement_found);
    free(text);

    sprintf(message_buf, "*** END heuristic_%s\n", get_current_heuristic()->componant_class->name);
    yield(message_buf, 1.0);

    rebuild_componant_gui(COMPONANT_TYPE_TRANSFORM, UNKNOWN_FITNESS);

    /* Unghost */
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_open_button"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_save_button"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_equate_button"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_heuristic_button"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "main_menubar"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "source_text"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "main_notebook"), TRUE);
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "toolbar_stop_button"), FALSE);

    UNLOCK_CALLBACKS;
}


void
on_about_ok_button_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;
    gtk_widget_destroy(lookup_widget(GTK_WIDGET(button), "about_dialog"));
    UNLOCK_CALLBACKS;
}


void
on_open                                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;
    gtk_widget_show(create_open_fileselection());
    UNLOCK_CALLBACKS;
}


void
on_save                                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;
    gtk_widget_show(create_save_fileselection());
    UNLOCK_CALLBACKS;
}


void
on_open_file_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    char *filename, *new_text;
    LOCK_CALLBACKS;
    filename = gtk_file_selection_get_filename(GTK_FILE_SELECTION(lookup_widget(GTK_WIDGET(button), "open_fileselection")));
    if ((new_text = file_load_text(filename))) {
	set_source_text(new_text);
	handle_source_text_change();
    }
    gtk_widget_destroy(lookup_widget(GTK_WIDGET(button), "open_fileselection"));
    UNLOCK_CALLBACKS;
}


void
on_open_file_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;
    gtk_widget_destroy(lookup_widget(GTK_WIDGET(button), "open_fileselection"));
    UNLOCK_CALLBACKS;
}


void
on_save_file_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    char *filename;
    LOCK_CALLBACKS;
    filename = gtk_file_selection_get_filename(GTK_FILE_SELECTION(lookup_widget(GTK_WIDGET(button), "save_fileselection")));
    file_save_text(filename, get_view_text());
    gtk_widget_destroy(lookup_widget(GTK_WIDGET(button), "save_fileselection"));
    UNLOCK_CALLBACKS;

}


void
on_save_file_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    LOCK_CALLBACKS;
    gtk_widget_destroy(lookup_widget(GTK_WIDGET(button), "save_fileselection"));
    UNLOCK_CALLBACKS;

}


void
on_stop_heuristic                      (GtkButton       *button,
                                        gpointer         user_data)
{
    set_stop_heuristic(TRUE);
}


gboolean
on_heuristic_log_delete_event          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    GtkWidget *heuristic_log;
    heuristic_log = get_heuristic_log();
    assert(heuristic_log);
    if (islocked()) {
	gtk_widget_hide(heuristic_log); /* May want to get this back again */
    } else {
	set_heuristic_log(NULL);
	gtk_widget_destroy(heuristic_log);
    }
    return TRUE;
}

void
on_guile_shell_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifdef HAVE_LIBGUILE
    enter_shell();

#else /* HAVE_LIBGUILE */
    warn("Guile support not enabled\n");
    gtk_widget_set_sensitive(GTK_WIDGET(menuitem), FALSE);
#endif /* HAVE_LIBGUILE */
}


void
on_patch_combo_entry_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{
    GtkWidget *patch_apply_button;

    LOCK_CALLBACKS;
    patch_apply_button = lookup_widget(GTK_WIDGET(editable), "patch_apply_button");
    gtk_widget_set_sensitive(GTK_WIDGET(patch_apply_button), TRUE);
    update_patch_description();
    UNLOCK_CALLBACKS;
}


void
on_patch_apply_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *patch_combo_entry;
    char *entry_text;

    LOCK_CALLBACKS;
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    patch_combo_entry = lookup_widget(GTK_WIDGET(get_main_window()), "patch_combo_entry");
    entry_text = gtk_editable_get_chars(GTK_EDITABLE(patch_combo_entry), 0, -1);
    apply_patch(entry_text);
    rebuild_componant_gui(COMPONANT_TYPE_ANY, UNKNOWN_FITNESS);
    g_free(entry_text);
    UNLOCK_CALLBACKS;
}

