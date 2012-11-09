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
 * patch.c
 *
 * FUNCTION: 
 * Handling of patches (group of componant settings)
 */


#include "crank.h"
#include "patch.h"
#include "globals.h"
#include "componant.h"
#include <string.h>
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include "files.h"
#include "error.h"
#ifdef HAVE_LIBGUILE
#include <libguile.h>
#endif /* HAVE_LIBGUILE */

#define PATCH_HEADER_STR      ";; This is an automatically generated Crank patch file\n"
#define PATCH_NAME_STR        ";; Name: "
#define PATCH_DESCRIPTION_STR ";; Description: "
#define PATCH_SET_CURRENT_STR(instance_position) "  (set-current-" #instance_position " i))\n"

char *generate_patch(instance *transform, instance *heuristic, instance *fitness,
		     instance *gui_transform, instance *gui_heuristic, instance *gui_fitness,
		     char *name, char *description) {
    char *patch, *dump;
    int size;
    assert(transform); assert(heuristic); assert(fitness);
    assert(gui_transform); assert(gui_heuristic); assert(gui_fitness);
    assert(name); assert(description);

    /* Header */
    size = strlen(name) 
	+ strlen(description) 
	+ strlen(PATCH_HEADER_STR) 
	+ strlen(PATCH_NAME_STR) 
	+ strlen(PATCH_DESCRIPTION_STR) 
	+ 3 /* Newlines needed */
	+ 1 /* Null terminator */;
    patch = malloc(size);
    sprintf(patch, PATCH_HEADER_STR PATCH_NAME_STR "%s\n" PATCH_DESCRIPTION_STR "%s\n", name, description);
    
    /* Instance dumps */
    dump = dump_parameters(transform);     
    size += strlen(PATCH_SET_CURRENT_STR(transform)); size += strlen(dump); patch = realloc(patch, size);  
    strcat(patch, dump); strcat(patch, PATCH_SET_CURRENT_STR(transform));
    free(dump);
    dump = dump_parameters(heuristic);     
    size += strlen(PATCH_SET_CURRENT_STR(heuristic)); size += strlen(dump); patch = realloc(patch, size);  
    strcat(patch, dump); strcat(patch, PATCH_SET_CURRENT_STR(heuristic));
    free(dump);
    dump = dump_parameters(fitness);     
    size += strlen(PATCH_SET_CURRENT_STR(fitness)); size += strlen(dump); patch = realloc(patch, size);  
    strcat(patch, dump); strcat(patch, PATCH_SET_CURRENT_STR(fitness));
    free(dump);
    dump = dump_parameters(gui_transform);     
    size += strlen(PATCH_SET_CURRENT_STR(gui-transform)); size += strlen(dump); patch = realloc(patch, size);  
    strcat(patch, dump); strcat(patch, PATCH_SET_CURRENT_STR(gui-transform));
    free(dump);
    dump = dump_parameters(gui_heuristic);     
    size += strlen(PATCH_SET_CURRENT_STR(gui-heuristic)); size += strlen(dump); patch = realloc(patch, size);  
    strcat(patch, dump); strcat(patch, PATCH_SET_CURRENT_STR(gui-heuristic));
    free(dump);
    dump = dump_parameters(gui_fitness);     
    size += strlen(PATCH_SET_CURRENT_STR(gui-fitness)); size += strlen(dump); patch = realloc(patch, size);  
    strcat(patch, dump); strcat(patch, PATCH_SET_CURRENT_STR(gui-fitness));
    free(dump);
    return patch;
}

#define BUFFER_SIZE 1024
static GList *add_patch_directory(char *directory_name, GList *list) {
    DIR *patch_dir;
    GList *return_list = list;
    struct dirent *d;
    char filename[BUFFER_SIZE], *patch;
    if (!(patch_dir = opendir(directory_name))) {
	warn("Could not open patch directory `%s' - %s\n", directory_name, strerror(errno));
    } else {
	while ((d = readdir(patch_dir))) {
	    
	    if (d->d_name[0] == '.') /* Skip dotfiles, dirup etc. */
	    continue;
	    
	    sprintf(filename, "%s%c%s", directory_name, G_DIR_SEPARATOR, d->d_name);
	    patch = file_load_text(filename);
	    if (patch && strstr(patch, PATCH_HEADER_STR))
		return_list = g_list_append(return_list, patch);
	}    
	closedir(patch_dir);
    }
    return return_list;
}

void init_patches(void) {
    GList *patch_list = NULL;
    patch_list = add_patch_directory(DATADIR "/patch", patch_list);
    set_patch_list(patch_list);
}

char *lookup_patch_by_name(GList *patch_list, char *name) {
    GList *patch;
    char *patch_name;
    patch = patch_list;
    if (!patch) { warn("NULL patch_list\n"); }
    while (patch) {
	patch_name = get_patch_name( (char *) patch->data);
	if (!strcmp(name, patch_name)) {
	    free(patch_name);
	    return (char *) patch->data;
	}
	free(patch_name);
	patch = g_list_next(patch);
    }
    return NULL;
}


char *get_patch_name(char *patch) {
    char *name_ptr, *name = malloc(strlen(patch) + 1);
    assert(strstr(patch, PATCH_HEADER_STR));
    name_ptr = strstr(patch, PATCH_NAME_STR);
    name_ptr += strlen(PATCH_NAME_STR);
    sscanf(name_ptr, "%[^\n;]", name);
    name = realloc(name, strlen(name) + 1);
    return name;
}
char *get_patch_description(char *patch) {
    char *description_ptr, *description = malloc(strlen(patch) + 1);
    assert(strstr(patch, PATCH_HEADER_STR));
    description_ptr = strstr(patch, PATCH_DESCRIPTION_STR);
    description_ptr += strlen(PATCH_DESCRIPTION_STR);
    sscanf(description_ptr, "%[^\n;]", description);
    description = realloc(description, strlen(description) + 1);
    return description;
}

void apply_patch(char *patch_name) {
    char *patch;
    patch = lookup_patch_by_name(get_patch_list(), patch_name);
    if (!patch) { warn("Patch not found to apply %s\n", patch_name); }
#ifdef HAVE_LIBGUILE
    scm_eval_0str(patch);
#endif HAVE_LIBGUILE
}
