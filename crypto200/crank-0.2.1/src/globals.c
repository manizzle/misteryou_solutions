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
 * globals.c
 *
 * FUNCTION: 
 * Global variables used by Crank
 *
 */

#include "crank.h"
#include "componant.h"
#include "globals.h"
#include "assert.h"

global_type globals;

GList *get_patch_list(void) {return globals.patch_list;}
void set_patch_list(GList *list) { globals.patch_list = list; }

instance *get_current_transform(void) { return globals.current_transform; }
instance *get_current_heuristic(void) { return globals.current_heuristic; }
instance *get_current_fitness(void) { return globals.current_fitness; }
instance *get_current_gui_transform(void) { return globals.current_gui_transform; }
instance *get_current_gui_heuristic(void) { return globals.current_gui_heuristic; }
instance *get_current_gui_fitness(void) { return globals.current_gui_fitness; }

void set_current_transform(instance *i)     { 
    assert(i && i->componant_class->type == COMPONANT_TYPE_TRANSFORM); 
    if (globals.current_transform)
	free_instance(globals.current_transform);
    globals.current_transform = i;
}
void set_current_heuristic(instance *i)     { 
    assert(i && i->componant_class->type == COMPONANT_TYPE_HEURISTIC); 
    if (globals.current_heuristic)
	free_instance(globals.current_heuristic);
    globals.current_heuristic = i;
}
void set_current_fitness(instance *i)       { 
    assert(i && i->componant_class->type == COMPONANT_TYPE_FITNESS); 
    if (globals.current_fitness)
	free_instance(globals.current_fitness);
    globals.current_fitness = i;
}
void set_current_gui_transform(instance *i) { 
    assert(i && i->componant_class->type == COMPONANT_TYPE_GUI);
    if (globals.current_gui_transform)
	free_instance(globals.current_gui_transform);
    globals.current_gui_transform = i;
}
void set_current_gui_heuristic(instance *i) {
    assert(i && i->componant_class->type == COMPONANT_TYPE_GUI); 
    if (globals.current_gui_heuristic)
	free_instance(globals.current_gui_heuristic);
    globals.current_gui_heuristic = i;
}
void set_current_gui_fitness(instance *i)  {
    assert(i && i->componant_class->type == COMPONANT_TYPE_GUI);
    if (globals.current_gui_fitness)
	free_instance(globals.current_gui_fitness);
    globals.current_gui_fitness = i;
}

componant *get_componant_list(void) { return globals.componant_list; }
void set_componant_list(componant *componant_list) { assert(componant_list); globals.componant_list = componant_list;}

int get_number_of_componants(void) { return globals.number_of_componants; }
void set_number_of_componants(int number_of_componants) {assert(number_of_componants >= 0); globals.number_of_componants = number_of_componants; }

void init_globals(void) { return; }
