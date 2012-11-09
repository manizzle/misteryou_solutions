/* This program is part of Crank, a cryptanalysis tool
 * Copyright (C) 2000 Matthew Russell
 *
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License (LICENSE) for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 * USA
 */

/* FILE: 
 * gui_init.c
 *
 * FUNCTION: 
 * Functions for building the graphic user interface
 *
 */

#include "gui_init.h"
#include "gui_interface.h"
#include "gui_support.h"
#include "gui_globals.h"
#include "gui_textarea.h"
#include "globals.h"
#include "patch.h"
#include "error.h"

#define BUFFER_SIZE 1024

void update_patch_description(void) {
    GtkWidget *patch_combo_entry, *patch_description;
    char *entry_text, *description;
    char *patch;
    patch_combo_entry = lookup_widget(GTK_WIDGET(get_main_window()), "patch_combo_entry");
    patch_description = lookup_widget(GTK_WIDGET(get_main_window()), "patch_description");
    entry_text = gtk_editable_get_chars(GTK_EDITABLE(patch_combo_entry), 0, -1);
    patch = lookup_patch_by_name(get_patch_list(), entry_text);
    if (!patch) { warn("Invalid patch name %s\n", entry_text); }
    description = get_patch_description(patch);
    gtk_text_set_point(GTK_TEXT(patch_description), 0);
    gtk_text_forward_delete(GTK_TEXT(patch_description), gtk_text_get_length(GTK_TEXT(patch_description)));
    gtk_text_insert(GTK_TEXT(patch_description), NULL, NULL, NULL, description, -1);

    free(description);
    g_free(entry_text);
}

static void update_status_bar_fitness(double fitness_value) {
    GtkWidget *statusbar, *main_window;
    char buf[BUFFER_SIZE];
    main_window  = get_main_window();
    statusbar = lookup_widget(GTK_WIDGET(main_window), "statusbar");    
    sprintf(buf, "Fitness: %f", fitness_value);
    gtk_statusbar_pop(GTK_STATUSBAR(statusbar), gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "handle_source_text_change"));
    gtk_statusbar_push(GTK_STATUSBAR(statusbar), gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "handle_source_text_change"), buf);
}

static void update_status_bar_and_text_view(double fitness_precalculated) {
    char *text, *transformed_text;
    double fitness_value;

    text = get_source_text();
    transformed_text = transform(get_current_transform(), text);

    if (IS_UNKNOWN_FITNESS(fitness_precalculated))
	fitness_value = fitness(get_current_fitness(), transformed_text);
    else
	fitness_value = fitness_precalculated;

    update_status_bar_fitness(fitness_value);
    set_view_text(transformed_text);

    free(text);
    free(transformed_text);

}

void handle_source_text_change(void) { update_status_bar_and_text_view(UNKNOWN_FITNESS); }

static GtkWidget *rebuild_componant_gui_part(const char *componant_frame_name, 
                                       const char *componant_entry_name, 
				       const char *interface_entry_name,
                                       instance *current_instance, 
				       instance *current_gui_instance,
                                       GtkWidget *current_componant_gui) {
    GtkWidget *new_widget;
    GtkWidget *main_window;
    GtkWidget *frame, *componant_entry, *interface_entry;
    char buf[BUFFER_SIZE];

    /* Find widgets */
    main_window  = get_main_window();
    frame = lookup_widget(GTK_WIDGET(main_window), componant_frame_name);
    componant_entry = lookup_widget(GTK_WIDGET(main_window), componant_entry_name);
    interface_entry = lookup_widget(GTK_WIDGET(main_window), interface_entry_name);

    /* Make componant gui widget */
    new_widget = build_gui_item(current_gui_instance, current_instance);
    gtk_widget_show(new_widget);
    if (current_componant_gui)
	gtk_container_remove(GTK_CONTAINER(frame), current_componant_gui);
    gtk_container_add(GTK_CONTAINER(frame), new_widget);

    /* Set the GTK_ENTRY box texts */
    sprintf(buf, "%s_%s", componant_type_lookup(current_instance->componant_class->type), current_instance->componant_class->name);
    gtk_entry_set_text(GTK_ENTRY(componant_entry), buf);

    sprintf(buf, "%s_%s", componant_type_lookup(current_gui_instance->componant_class->type), current_gui_instance->componant_class->name);
    gtk_entry_set_text(GTK_ENTRY(interface_entry), buf);


    return new_widget;
}

void rebuild_componant_gui(componant_type componant_type, double fitness_precalculated) {
    GtkWidget *new_widget;

    if (componant_type == COMPONANT_TYPE_TRANSFORM || componant_type == COMPONANT_TYPE_ANY) {
	new_widget = rebuild_componant_gui_part("transform_frame", "transform_componant_entry", "transform_interface_entry", 
                                                get_current_transform(), get_current_gui_transform(), get_current_transform_gui());
	set_current_transform_gui(new_widget);
	update_status_bar_and_text_view(fitness_precalculated);
    }

    if (componant_type == COMPONANT_TYPE_HEURISTIC || componant_type == COMPONANT_TYPE_ANY) {
	new_widget = rebuild_componant_gui_part("heuristic_frame", "heuristic_componant_entry", "heuristic_interface_entry", 
                                                get_current_heuristic(), get_current_gui_heuristic(), get_current_heuristic_gui());
	set_current_heuristic_gui(new_widget);
    }

    if (componant_type == COMPONANT_TYPE_FITNESS || componant_type == COMPONANT_TYPE_ANY) {
	new_widget = rebuild_componant_gui_part("fitness_frame", "fitness_componant_entry", "fitness_interface_entry", 
                                                get_current_fitness(), get_current_gui_fitness(), get_current_fitness_gui());
	set_current_fitness_gui(new_widget);
	if (IS_UNKNOWN_FITNESS(fitness_precalculated))
	    update_status_bar_and_text_view(fitness_precalculated);
	else
	    update_status_bar_fitness(fitness_precalculated);
    }

}

void rebuild_patch_list(void) {
    GList *patch_list, *patch;
    GList *names = NULL;
    GtkWidget *patch_combo;
    patch_combo = lookup_widget(GTK_WIDGET(get_main_window()), "patch_combo");
    patch_list = get_patch_list();
    patch = patch_list;
    while (patch) {
	names = g_list_append(names, get_patch_name((char *)patch->data));
	patch = g_list_next(patch);
    }
    gtk_combo_set_popdown_strings(GTK_COMBO(patch_combo), names);
    /* TODO: free name strings! */
    g_list_free(names);
    update_patch_description();
}

void init_gui(int argc, char **argv) {
    GtkWidget *main_window;
    static int is_gtk_inited = FALSE;
    add_pixmap_directory(DATADIR);
    clear_gui_globals();

    /* Initiate GTK+, and create main window */
    if (!is_gtk_inited)
	if (!gtk_init_check(&argc, &argv))
	    return;
    main_window = create_main_window();
    set_main_window(main_window);
    
    /* Setup textareas */
    set_source_text_gui(lookup_widget(GTK_WIDGET(main_window), "source_text"));
    set_view_text_gui(lookup_widget(GTK_WIDGET(main_window), "view_text"));
    
    rebuild_componant_gui(COMPONANT_TYPE_ANY, UNKNOWN_FITNESS);

    rebuild_patch_list();

#ifndef HAVE_LIBGUILE
    gtk_widget_set_sensitive(lookup_widget(GTK_WIDGET(get_main_window()), "patch_box"), FALSE);
#endif

    gtk_widget_show(main_window);

}

void enter_gui(void) { gtk_main(); }
