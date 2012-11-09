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
 * register-componant.h
 *
 * FUNCTION: 
 * Build up list of componants from plugin directory or otherwise
 */

#include "crank.h"
#include "plugin.h"
#include "error.h"
#include "register_componant.h"
#include "componant.h"
#include "instance.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
 
/*
 *                        WARNING !! 
 * This code makes extensive use of macros, mainly for the purposes
 * of saving loads of mindless repetition. Some things can't be easily passed
 * to a function - like types, or symbols.
 */

/*
 * DECLARE_COMPONANT() textually substitutes the declarations needed to deal with a
 * hardcoded componant in register_componants()
 * Arguments: COMPONANT - hardcoded componant to declare member symbols of
 */
#define DECLARE_COMPONANT(COMPONANT)							\
extern char                   COMPONANT ## _name[];					\
extern componant_type         COMPONANT ## _type;					\
extern char                   COMPONANT ## _description[];				\
extern int                    COMPONANT ## _number_of_parameters;                       \
extern parameter_description  COMPONANT ## _parameter_description_table;		\
extern int                    COMPONANT ## _boot(void);					

/* 
 * DECLARE_TRANSFORM() is similar to DECLARE_COMPONANT, but declares transform-specific
 * symbols instead.
 */
#define DECLARE_TRANSFORM(COMPONANT)						\
extern char                  *COMPONANT ## _transform(instance *, char *);	\
DECLARE_COMPONANT(COMPONANT)

#define DECLARE_FITNESS(COMPONANT)							\
extern double                  COMPONANT ## _fitness(instance *, char *);	\
DECLARE_COMPONANT(COMPONANT)

#define DECLARE_HEURISTIC(COMPONANT)							\
extern instance              *COMPONANT ## _heuristic(instance *, char *, componant *, instance *, instance *, int (*)(char *, double), void(*)(instance *, double));	\
DECLARE_COMPONANT(COMPONANT)

#define DECLARE_GUI(COMPONANT)								\
extern componant_type         COMPONANT ## _componant_target_type; 			\
extern char                  *COMPONANT ## _componant_target_name;			\
extern gui_item              *COMPONANT ## _build_gui_item(instance *, instance *);	\
extern void                   COMPONANT ## _update_gui_item(instance *, instance *);	\
DECLARE_COMPONANT(COMPONANT)



/* ******************************** *
 * Hardcoded componant declarations *
 * ******************************** */

DECLARE_TRANSFORM(transform_monoalphabetic);
DECLARE_TRANSFORM(transform_transposition_grid);
DECLARE_FITNESS(fitness_trigram);
DECLARE_HEURISTIC(heuristic_random);
DECLARE_HEURISTIC(heuristic_hillclimbing);
DECLARE_HEURISTIC(heuristic_simulated_annealing);
DECLARE_GUI(gui_generic);

DECLARE_FITNESS(fitness_null);
DECLARE_HEURISTIC(heuristic_null);
DECLARE_TRANSFORM(transform_null);
DECLARE_GUI(gui_null);


/*
 * LOAD_SYMBOL() loads a symbol from the plugin into the identically named element 
 * of a componant data structure casting it appropriately along the way. 
 * If an error is encountered, the loop is continued to the next directory entry 
 * Arguments: SYMBOL - symbol to load from a module and place in a structure
 *            CAST   - cast (or dereferencing) needed to 'fit' symbol into predeclared
 *                     componant structure
 */
#define LOAD_SYMBOL(SYMBOL, CAST)     if (!module_symbol(plugin, #SYMBOL, plugin_symbol)) {					\
                         	         warn("Error loading plugin `%s' - symbol '" #SYMBOL "' not found\n", filename);	\
                                         free_componant(current_componant);      						\
                                         free(plugin_symbol);                                                                    \
				         return NULL;										\
                                      }												\
                                      current_componant->SYMBOL = CAST (*plugin_symbol)

/* 
 * LOAD_SPECIFIC_SYMBOL() is identical to LOAD_SYMBOL, except that it deals with componant-type -specific
 * symbols, hence the need for the TYPE argument.
 * Arguments: TYPE - type of componant the specific symbol is being loaded from
 */
#define LOAD_SPECIFIC_SYMBOL(SYMBOL, CAST, TYPE)     if (!module_symbol(plugin, #SYMBOL, plugin_symbol)) {					\
                         	                         warn("Error loading plugin `%s' - symbol '" #SYMBOL "' not found\n", filename);	\
                                                         free_componant(current_componant);							\
                                                         free(plugin_symbol);                                                                    \
                      				         return NULL;										\
                                                     }												\
                                                     current_componant->type_data. TYPE -> SYMBOL = CAST (*plugin_symbol)

/* 
 * register_plugin() gets the componant specified in the
 * dynamically loaded filenmae.
 * Arguments: filename - name of file containing a componant plugin
 * Returns:   The corresponding componant
 */
static componant *register_plugin(char *filename) {
    Module *plugin;
    componant *current_componant;
    pointer *plugin_symbol;

    debug("Opening `%s'\n", filename);

    plugin_symbol = malloc(sizeof(pointer));
    if (!(plugin = module_open(filename, 0))) {
	debug("Error loading plugin - `%s' \n", module_error());
	free(plugin_symbol);
	return NULL;
    }
    
    current_componant = malloc(sizeof(componant));					
    current_componant->module = plugin;    
    current_componant->filename = malloc((strlen(filename) + 1) * sizeof(char));
    strcpy(current_componant->filename, filename);

    /*
     *          Symbol              Type to cast into (or dereference)
     *          ------              ----------------------------------
     */
    LOAD_SYMBOL(name,               (char *)                 );
    LOAD_SYMBOL(description,        (char *)                 );
    LOAD_SYMBOL(type,               * (componant_type *)     );
    LOAD_SYMBOL(number_of_parameters,  * (int *)             );
    LOAD_SYMBOL(parameter_description_table, (parameter_description *));
    LOAD_SYMBOL(boot,               (int (*)(void))          );

    switch (current_componant->type) {

    case (COMPONANT_TYPE_TRANSFORM):
	current_componant->type_data.transform = malloc(sizeof(componant_type_transform));
	LOAD_SPECIFIC_SYMBOL(transform, (char *(*)(instance *, char *)), transform);
	break;

    case (COMPONANT_TYPE_FITNESS):
	current_componant->type_data.fitness = malloc(sizeof(componant_type_fitness));
	LOAD_SPECIFIC_SYMBOL(fitness, (double (*)(instance *, char *)), fitness);
	break;

    case (COMPONANT_TYPE_HEURISTIC):
	current_componant->type_data.heuristic = malloc(sizeof(componant_type_heuristic));
	LOAD_SPECIFIC_SYMBOL(heuristic, (instance *(*)(instance *, char *, componant *, instance *, instance *, int (*)(char *, double), void(*)(instance *, double))), heuristic);
	break;

    case (COMPONANT_TYPE_GUI):
	current_componant->type_data.gui = malloc(sizeof(componant_type_data));
	LOAD_SPECIFIC_SYMBOL(componant_target_type, * (componant_type *), gui);
	LOAD_SPECIFIC_SYMBOL(componant_target_name, (char *)            , gui);
	LOAD_SPECIFIC_SYMBOL(build_gui_item, (gui_item *(*)(instance *, instance *)), gui);
	LOAD_SPECIFIC_SYMBOL(update_gui_item, (void (*)(instance *, instance *)), gui);
	break;

    default:
	warn("Unknown plugin type %d in `%s'\n", current_componant->type, filename);
    }
    free(plugin_symbol);
    return current_componant;
}

/* Limit on file name size */
#define BUFFER_SIZE 1024 

static componant *register_plugin_directory(componant *componant_list) {
    DIR *plugin_dir;
    struct dirent *d;
    char filename[BUFFER_SIZE];
    componant *current_componant;
    if (!module_supported()) {
	warn("Dynamic loading of modules not supported on this platform\n");
    } else if (!(plugin_dir = opendir(PLUGINDIR))) {
	warn("Could not open plugin directory `%s' - %s\n", PLUGINDIR, strerror(errno));
    } else {
	while ((d = readdir(plugin_dir))) {
	    
	    if (d->d_name[0] == '.') /* Skip dotfiles, dirup etc. */
	    continue;
	    
	    sprintf(filename, "%s%c%s", PLUGINDIR, G_DIR_SEPARATOR, d->d_name);
	    
	    if (!(current_componant = register_plugin(filename)))
	    continue;
	    info("%s_%s ", componant_type_lookup(current_componant->type), current_componant->name);
	    current_componant->next = componant_list;
	    componant_list = current_componant;
	}
	info("\n");
	closedir(plugin_dir);
    }
    return componant_list;
}

/*
 * remove_duplicates() - removes any duplicated entries in a componant list, matching by the `name' field 
 * only (may need to check type field in addition in future)
 * Arguments: componant_list - list to be uniqified
 */
static void remove_duplicates(componant *componant_list) {
    componant *delete_candidate, *compare_componant, *previous;

    /* Iterate over the list, removing any duplicates later on in the list with each position checked */
    for (compare_componant = componant_list; compare_componant; compare_componant = compare_componant->next) {
	delete_candidate = compare_componant->next;
	previous = compare_componant;
	    
	while (delete_candidate) {
	    if (delete_candidate->type == compare_componant->type && !strcmp(delete_candidate->name, compare_componant->name)) {
		previous->next = delete_candidate->next;
		free_componant(delete_candidate);
		delete_candidate = previous->next;
	    } else {
		
		previous = delete_candidate;
		delete_candidate = delete_candidate->next;
	    }
	}
    }
    return;
}

/*
 * boot_componants() runs the boot() function for each componant in the list.
 * If the boot() function does not return TRUE, the componant is removed from the list.
 * Arguments: componant_list - list to boot()
 * Returns: those which boot OK
 */
static componant *boot_componants(componant *componant_list) {
    if (!componant_list) 
	return NULL;
    if (componant_list->boot()) {
	info("   [ OK ]\t%s_%s\n", componant_type_lookup(componant_list->type), componant_list->name);
	componant_list->next = boot_componants(componant_list->next);
	return componant_list;
    } else {
	info("   [FAIL]\t%s_%s\n", componant_type_lookup(componant_list->type), componant_list->name);
	return boot_componants(componant_list->next);
    }
}

/* 
 * count_componants() simply counts length of the componant_list
 * Arguments: componant_list - list to count
 * Returns: length of list
 */
static int count_componants(componant *componant_list) {
    int count = 0;
    componant *current = componant_list;
    if (current) {
	count++;
	while ((current = current->next)) 
	    count++;
    }
    return count;
}

/* 
 * REGISTER_COMPONANT() is a textual replacement macro for use only in the function register_componants()
 * It simply grabs a new componant record off the top of the list, and fills it with the information from
 * the hardcoded componant specified in the argument.
 * Arguments: COMPONANT - hardcoded componant to register 
 */
#define REGISTER_COMPONANT(COMPONANT)									\
    current_componant = malloc(sizeof(componant));							\
    current_componant->next = componant_list;								\
    componant_list = current_componant;									\
    current_componant->name                  = COMPONANT ## _name;					\
    current_componant->type                  = COMPONANT ## _type;					\
    current_componant->description           = COMPONANT ## _description;				\
    current_componant->number_of_parameters  = COMPONANT ## _number_of_parameters;			\
    current_componant->parameter_description_table = &COMPONANT ## _parameter_description_table;	\
    current_componant->boot                  = COMPONANT ## _boot;					\
    current_componant->module                = NULL;							\
    current_componant->filename              = "hardcoded";						\
    info("%s_%s ", componant_type_lookup(current_componant->type), current_componant->name);

/*
 * REGISTER_TRANSFORM() is for use only in register_componants(). It acts similarly to
 * REGISTER_COMPONANT(), by augmenting its actions with transform specific assignments.
 */
#define REGISTER_TRANSFORM(COMPONANT)							\
    REGISTER_COMPONANT(COMPONANT)							\
    current_componant->type_data.transform = malloc(sizeof(componant_type_transform));	\
    current_componant->type_data.transform->transform = COMPONANT ## _transform

#define REGISTER_FITNESS(COMPONANT)							\
    REGISTER_COMPONANT(COMPONANT)							\
    current_componant->type_data.fitness = malloc(sizeof(componant_type_fitness));	\
    current_componant->type_data.fitness->fitness = COMPONANT ## _fitness

#define REGISTER_HEURISTIC(COMPONANT) \
    REGISTER_COMPONANT(COMPONANT);							\
    current_componant->type_data.heuristic = malloc(sizeof(componant_type_heuristic));	\
    current_componant->type_data.heuristic->heuristic = COMPONANT ## _heuristic
     
#define REGISTER_GUI(COMPONANT) 										\
    REGISTER_COMPONANT(COMPONANT); 										\
    current_componant->type_data.gui = malloc(sizeof(componant_type_gui));				\
    current_componant->type_data.gui->componant_target_type = COMPONANT ## _componant_target_type; 	\
    current_componant->type_data.gui->componant_target_name = COMPONANT ## _componant_target_name; 	\
    current_componant->type_data.gui->build_gui_item = COMPONANT ## _build_gui_item; 			\
    current_componant->type_data.gui->update_gui_item = COMPONANT ## _update_gui_item
    

int register_componants(componant **output_list) {
    componant *componant_list = NULL, *current_componant; // *output_builder;
    int count; //, num;

#ifndef BUILD_DYNAMIC

    /* Register hardcoded internal componants */
    info("Registering hardcoded componants: ");

    REGISTER_TRANSFORM(transform_monoalphabetic);
    REGISTER_TRANSFORM(transform_transposition_grid);
    REGISTER_FITNESS(fitness_trigram);
    REGISTER_HEURISTIC(heuristic_random);
    REGISTER_HEURISTIC(heuristic_hillclimbing);
    REGISTER_HEURISTIC(heuristic_simulated_annealing);
    REGISTER_GUI(gui_generic);
    
    info("\n");

#endif BUILD_DYNAMIC

    /* Register from plugin directory */
    info("Registering plugin componants: ");
    componant_list = register_plugin_directory(componant_list);

    /* Add null componants here so that they end up at the start of the componant list */
    info("Registering null componants: ");
    REGISTER_FITNESS(fitness_null);
    REGISTER_HEURISTIC(heuristic_null);
    REGISTER_TRANSFORM(transform_null);
    REGISTER_GUI(gui_null);
    info("\n");

    /* Remove duplicates */
    info("Checking for duplicates \n");
    remove_duplicates(componant_list);
        
    /* Run boot() on each componant */
    info("Booting componants\n");
    componant_list = boot_componants(componant_list);

    /* Count componants */
    count = count_componants(componant_list);
    info("%d componants registered\n", count);

    /* Convert linked list to an array */
//    output_builder = *output_list = malloc(sizeof(componant) * count);
//    num = 0;
//    for (current_componant = componant_list; current_componant; current_componant = current_componant->next) {
//	memcpy(output_builder++, current_componant, sizeof(componant));
//	current_componant->id = num++;
//    }
//    assert(num == count);
//    free_componant_list(componant_list);
    *output_list = componant_list;
    return count;
}
