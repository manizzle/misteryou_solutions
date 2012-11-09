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
 * main.c
 *
 * FUNCTION: 
 * location of main()
 */

#include "crank.h"
#include "error.h"
#include "register_componant.h"
#include "componant.h"
#include "instance.h"
#include "plugin.h"
#include "gui_support.h"
#include "gui_interface.h"
#include "gui_init.h"
#include "globals.h"
#ifdef HAVE_LIBGUILE
#include <libguile.h>
#endif /* HAVE_LIBGUILE */
#include "scheme_interface.h"
#include <gtk/gtk.h>
#include "patch.h"

static void init_componants(componant *initial_transform_componant,
			    componant *initial_heuristic_componant,
			    componant *initial_fitness_componant,
                            componant *initial_gui_componant) {
    set_current_transform(make_new_instance(initial_transform_componant));
    set_current_heuristic(make_new_instance(initial_heuristic_componant));
    set_current_fitness(make_new_instance(initial_fitness_componant));
    set_current_gui_transform(make_new_instance(initial_gui_componant));
    set_current_gui_heuristic(make_new_instance(initial_gui_componant));
    set_current_gui_fitness(make_new_instance(initial_gui_componant));
}

int main(int argc, char *argv[]) {
    int comp_index;
    componant *componant_list;
    int number_of_componants;

    init_globals();
    init_patches();
    
    number_of_componants = register_componants(&componant_list);
    set_componant_list(componant_list);
    set_number_of_componants(number_of_componants);
    init_componants(lookup_componant_by_name(componant_list, "transform_monoalphabetic"), 
		    lookup_componant_by_name(componant_list, "heuristic_simulated_annealing"), 
		    lookup_componant_by_name(componant_list, "fitness_trigram"), 
		    lookup_componant_by_name(componant_list, "gui_generic"));


#ifndef HAVE_LIBGUILE
    init_gui(argc, argv);
    enter_gui();
#else
    scm_boot_guile(argc, argv, &inner_main, (void *) 0);
#endif
    /* Keep memprof happy */
    for (comp_index = 0; comp_index < number_of_componants; comp_index++) {
	if (componant_list[comp_index].type == COMPONANT_TYPE_TRANSFORM) 
	    free(componant_list[comp_index].type_data.transform);
	if (componant_list[comp_index].type == COMPONANT_TYPE_FITNESS) 
	    free(componant_list[comp_index].type_data.fitness);
	if (componant_list[comp_index].type == COMPONANT_TYPE_HEURISTIC) 
	    free(componant_list[comp_index].type_data.heuristic);
	if (componant_list[comp_index].module)
	    module_close(componant_list[comp_index].module);
	
    }
    free(componant_list);
    return 0;

}
