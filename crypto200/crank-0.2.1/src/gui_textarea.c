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
 * gui_textarea.c
 *
 * FUNCTION: 
 * Accessing the gui text areas
 *
 */

#include "stdlib.h"
#include "gui_textarea.h"
#include <gtk/gtk.h>
#include <assert.h>

static GtkWidget *source_text;
static GtkWidget *view_text;

void set_source_text_gui(gui_item *source_text_gui) {
    assert(source_text_gui);
    source_text = source_text_gui;
}
void set_source_text(char *text) {
    assert(text);
    gtk_text_set_point(GTK_TEXT(source_text), 0);
    gtk_text_forward_delete(GTK_TEXT(source_text), gtk_text_get_length(GTK_TEXT(source_text)));
    gtk_text_insert(GTK_TEXT(source_text), NULL, NULL, NULL, text, -1);


}
char *get_source_text(void) {
    gchar *text;
    char *ordinary_text;
    text = gtk_editable_get_chars(GTK_EDITABLE(source_text), 0, -1);

    ordinary_text = malloc(strlen(text) + 1);
    strcpy(ordinary_text, text);
    g_free(text);
    return(ordinary_text);
}

void set_view_text_gui(gui_item *view_text_gui) {
    assert(view_text_gui);
    view_text = view_text_gui;
}
void set_view_text(char *text) {
    assert(text);
    gtk_text_set_point(GTK_TEXT(view_text), 0);
    gtk_text_forward_delete(GTK_TEXT(view_text), gtk_text_get_length(GTK_TEXT(view_text)));
    gtk_text_insert(GTK_TEXT(view_text), NULL, NULL, NULL, text, -1);
}
char *get_view_text(void) {
    gchar *text;
    char *ordinary_text;
    text = gtk_editable_get_chars(GTK_EDITABLE(view_text), 0, -1);

    ordinary_text = malloc(strlen(text) + 1);
    strcpy(ordinary_text, text);
    g_free(text);
    return(ordinary_text);
}

