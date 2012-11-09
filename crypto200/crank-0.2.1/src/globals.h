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
 * globals.h
 *
 * FUNCTION: 
 * Global variables used by Crank
 *
 */

#ifndef  __GLOBALS_H__
#define  __GLOBALS_H__

#include "crank.h"
#include "instance.h"
#include <glib.h>

typedef struct {
    instance *current_transform;
    instance *current_heuristic;
    instance *current_fitness;
    instance *current_gui_transform;
    instance *current_gui_heuristic;
    instance *current_gui_fitness;
    
    componant *componant_list;
    int number_of_componants;
    GList *patch_list;
} global_type;

void init_globals(void);

GList *get_patch_list(void);
void set_patch_list(GList *list);

instance *get_current_transform(void);
instance *get_current_heuristic(void);
instance *get_current_fitness(void);
instance *get_current_gui_transform(void);
instance *get_current_gui_heuristic(void);
instance *get_current_gui_fitness(void);
void set_current_transform(instance *i);
void set_current_heuristic(instance *i);
void set_current_fitness(instance *i);
void set_current_gui_transform(instance *i);
void set_current_gui_heuristic(instance *i);
void set_current_gui_fitness(instance *i);

componant *get_componant_list(void);
void set_componant_list(componant *componant_list);

int get_number_of_componants(void);
void set_number_of_componants(int number_of_componants);

#endif  __GLOBALS_H__
