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
 * gui_globals.h
 *
 * FUNCTION: 
 * Global variables used in the user interface
 *
 */

#ifndef  __GUI_GLOBALS_H__
#define  __GUI_GLOBALS_H__

#include <gtk/gtk.h>
#include "crank.h"
#include "componant.h"


void clear_gui_globals(void);

GtkWidget *get_heuristic_log(void);
void set_heuristic_log(GtkWidget *heuristic_log);

int get_stop_heuristic(void);
void set_stop_heuristic(int stop_heuristic);

GtkWidget *get_current_transform_gui(void);
void set_current_transform_gui(GtkWidget *current_transform_gui);
GtkWidget *get_current_heuristic_gui(void);
void set_current_heuristic_gui(GtkWidget *current_heuristic_gui);
GtkWidget *get_current_fitness_gui(void);
void set_current_fitness_gui(GtkWidget *current_fitness_gui);


GtkWidget *get_main_window(void);
void set_main_window(GtkWidget *main_window);

instance **get_componant_choice_install_here(void);
void set_componant_choice_install_here(char *id_string);

componant *get_componant_choice_clist_selected_componant(void);
void set_componant_choice_clist_selected_componant(componant *);

void lock_callbacks(void);
void unlock_callbacks(void);
int islocked(void);

/* Conveniance macro for beginning of a callback */
#define LOCK_CALLBACKS if (islocked())		\
                          return;		\
                       else			\
                          lock_callbacks()
#define UNLOCK_CALLBACKS unlock_callbacks()


#endif  __GUI_GLOBALS_H__
