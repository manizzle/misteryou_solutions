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
 * gui_globals.c
 *
 * FUNCTION: 
 * Global variables used in the user interface
 *
 */

#include <gtk/gtk.h>
#include "crank.h"
#include "componant.h"
#include "gui_globals.h"
#include "globals.h"
#include "assert.h"

typedef struct {
    int lock_callbacks; /* Can callbacks be used? */
    componant *componant_choice_clist_selected_componant; /* Row currently selected in clist */
    instance **componant_choice_install_here; /* Place to put selected new instance */
    GtkWidget *main_window;
    GtkWidget *heuristic_log;
    GtkWidget *current_transform_gui;
    GtkWidget *current_heuristic_gui;
    GtkWidget *current_fitness_gui;
    int stop_heuristic;
} global_gui_type;

global_gui_type global_gui;

extern global_type globals; /* I guess gui_globals can play nice with globals */

GtkWidget *get_heuristic_log(void) { return global_gui.heuristic_log; }
void set_heuristic_log(GtkWidget *heuristic_log) {global_gui.heuristic_log = heuristic_log; }

int get_stop_heuristic(void){return global_gui.stop_heuristic;}
void set_stop_heuristic(int stop_heuristic) {global_gui.stop_heuristic = stop_heuristic;}

GtkWidget *get_current_transform_gui(void) {return global_gui.current_transform_gui; }
void set_current_transform_gui(GtkWidget *current_transform_gui) {assert(current_transform_gui); global_gui.current_transform_gui = current_transform_gui;}
GtkWidget *get_current_heuristic_gui(void) {return global_gui.current_heuristic_gui; }
void set_current_heuristic_gui(GtkWidget *current_heuristic_gui) {assert(current_heuristic_gui); global_gui.current_heuristic_gui = current_heuristic_gui;}
GtkWidget *get_current_fitness_gui(void) {return global_gui.current_fitness_gui;}
void set_current_fitness_gui(GtkWidget *current_fitness_gui) {assert(current_fitness_gui); global_gui.current_fitness_gui = current_fitness_gui;}

GtkWidget *get_main_window(void) {return global_gui.main_window;}
void set_main_window(GtkWidget *main_window) {assert(main_window); global_gui.main_window = main_window;}

instance **get_componant_choice_install_here(void) { return global_gui.componant_choice_install_here; }
void set_componant_choice_install_here(char *id_string) {
    assert(id_string);
    if (!strcmp(id_string, "transform_componant")) 
	global_gui.componant_choice_install_here = &globals.current_transform;
    else if (!strcmp(id_string, "heuristic_componant")) 
	global_gui.componant_choice_install_here = &globals.current_heuristic;
    else if (!strcmp(id_string, "fitness_componant")) 
	global_gui.componant_choice_install_here = &globals.current_fitness;
    else if (!strcmp(id_string, "transform_interface"))
	global_gui.componant_choice_install_here = &globals.current_gui_transform;
    else if ( !strcmp(id_string, "heuristic_interface"))
	global_gui.componant_choice_install_here = &globals.current_gui_heuristic;
    else if (!strcmp(id_string, "fitness_interface")) 
	global_gui.componant_choice_install_here = &globals.current_gui_fitness;
    else 
	global_gui.componant_choice_install_here = NULL;
}

void lock_callbacks(void) { global_gui.lock_callbacks = TRUE; }
void unlock_callbacks(void) { global_gui.lock_callbacks = FALSE; }
int islocked(void) { return global_gui.lock_callbacks; }

componant *get_componant_choice_clist_selected_componant(void) { return global_gui.componant_choice_clist_selected_componant; }
void set_componant_choice_clist_selected_componant(componant *componant) { global_gui.componant_choice_clist_selected_componant = componant; }

void clear_gui_globals(void) { 
    global_gui.lock_callbacks = FALSE;
    global_gui.componant_choice_clist_selected_componant = NULL;
    global_gui.componant_choice_install_here = NULL;
    global_gui.main_window = NULL;
    global_gui.heuristic_log = NULL;
    global_gui.current_transform_gui = NULL;
    global_gui.current_heuristic_gui = NULL;
    global_gui.current_fitness_gui = NULL;
    global_gui.stop_heuristic = FALSE;
}
