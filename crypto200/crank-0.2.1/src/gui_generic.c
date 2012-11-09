/* This program is part of Crank, a cryptanalysis tool
 * Copyright (C) 2001 Matthew Russell
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
 * gui_generic.c
 *
 * FUNCTION: 
 * Componant GUI interface to any componant type
 */

#include "crank.h"
#include "componant.h"
#include "error.h"
#include "instance.h"
#include <assert.h>
#include "gui_generic_interface.h"
#include "gui_support.h"
#include "gui_generic_callbacks.h"
#include "parameter.h"

#include <gtk/gtk.h>

#ifdef BUILD_DYNAMIC
#define SYM(symbol) symbol
#else  BUILD_DYNAMIC
#define SYM(symbol) gui_generic_ ## symbol
#endif BUILD_DYNAMIC

/* Componant-wide state */

/** Common componant interface **********************/

const componant_type SYM(type) = COMPONANT_TYPE_GUI;
const char SYM(name)[] = "generic";
const char SYM(description)[] = "A generic componant interface.";

#define NUM_PARAMS 0

const int SYM(number_of_parameters) = 0;
const parameter_description SYM(parameter_description_table)[NUM_PARAMS] = { };

int SYM(boot)(void) {  return TRUE; }

/** GUI specific interface ********************/

componant_type SYM(componant_target_type) = COMPONANT_TYPE_ANY;
char *SYM(componant_target_name) = NULL;

#define BUFFER_SIZE 1024
#define CLIST_COLUMN_MIN_WIDTH 50

gui_item *SYM(build_gui_item)(instance *gui, instance *i) {
    GtkWidget *gui_item, *container_window, *clist, *change_button;
    int param_index, number_of_parameters;
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE], *buf[2], *tempname;
    buf[0] = buf1; buf[1] = buf2;

    assert(gui);  assert(i); assert(gui->componant_class->type == COMPONANT_TYPE_GUI);
    number_of_parameters = i->componant_class->number_of_parameters;

    /* Get GLADE generated window, and retrieve child widget */
    container_window = create_dummy_gui_generic_window();
    gui_item = GTK_BIN(container_window)->child;

    /* Need to grab this widget before it's removed form its window */
    clist = lookup_widget(GTK_WIDGET(container_window), "gui_generic_clist");
    change_button = lookup_widget(GTK_WIDGET(container_window), "gui_generic_change_button");

    /* Migrate GLADE's "lookup_widget" information from the window to the clist */
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_title_data_one", lookup_widget(GTK_WIDGET(container_window), "gui_generic_title_data_one"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_title_data_two", lookup_widget(GTK_WIDGET(container_window), "gui_generic_title_data_two"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_description", lookup_widget(GTK_WIDGET(container_window), "gui_generic_description"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_default", lookup_widget(GTK_WIDGET(container_window), "gui_generic_default"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_data_one", lookup_widget(GTK_WIDGET(container_window), "gui_generic_data_one"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_data_two", lookup_widget(GTK_WIDGET(container_window), "gui_generic_data_two"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_type", lookup_widget(GTK_WIDGET(container_window), "gui_generic_type"));
    gtk_object_set_data(GTK_OBJECT(clist), "gui_generic_table", lookup_widget(GTK_WIDGET(container_window), "gui_generic_table"));
    gtk_object_set_data(GTK_OBJECT(clist), "instance", i);
    gtk_object_set_data(GTK_OBJECT(clist), "change_button", change_button);
    gtk_container_remove(GTK_CONTAINER(container_window), gui_item);

    /* Populate CLIST with parameter information */

    for (param_index = 0; param_index < number_of_parameters; param_index++) {
	strcpy(buf1, i->componant_class->parameter_description_table[param_index].name);
	switch (i->componant_class->parameter_description_table[param_index].type) {
	case PARAM_TYPE_INT:
	    sprintf(buf2, "%d", * (int *) peek_param(i, param_index));
	    break;
	case PARAM_TYPE_ENUM:
	    tempname = parameter_enum_value_name(i->componant_class->parameter_description_table + param_index,
                                                 * (int *) peek_param(i, param_index));
	    strcpy(buf2, tempname);
	    free(tempname);
	    break;
	case PARAM_TYPE_FLOAT:
	    sprintf(buf2, "%f", * (double *) peek_param(i, param_index));
	    break;
	case PARAM_TYPE_STRING:
	    strcpy(buf2, (char *) peek_param(i, param_index));
	    break;
	default:
	    warn("Unknown param_type\n");
	    break;
	}
	gtk_clist_append(GTK_CLIST(clist), buf);

    }

    gtk_clist_columns_autosize(GTK_CLIST(clist));
    if (gtk_clist_optimal_column_width(GTK_CLIST(clist), 0) < CLIST_COLUMN_MIN_WIDTH) 
	gtk_clist_set_column_width(GTK_CLIST(clist), 0, CLIST_COLUMN_MIN_WIDTH);

//	    gtk_clist_set_column_width(GTK_CLIST(clist), 0, gtk_clist_optimal_column_width(GTK_CLIST(clist), 0));

    /* Set data for 'change' button */
    gtk_object_set_data(GTK_OBJECT(change_button), "instance", i);
    gtk_object_set_data(GTK_OBJECT(change_button), "entry", lookup_widget(GTK_WIDGET(container_window), "gui_generic_entry"));
    return gui_item;
}

void SYM(update_gui_item)(instance *gui, instance *i) {
    return;
}
