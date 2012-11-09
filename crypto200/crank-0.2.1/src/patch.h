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
 * patch.h
 *
 * FUNCTION: 
 * Handling of patches (group of componant settings)
 */

#ifndef __PATCH_H__
#define __PATCH_H__

#include "crank.h"
#include "componant.h"
#include <glib.h>

char *generate_patch(instance *transform, instance *heuristic, instance *fitness,
		     instance *gui_transform, instance *gui_heuristic, instance *gui_fitness,
		     char *name, char *description);

void init_patches(void);

char *lookup_patch_by_name(GList *patch_list, char *name);
char *get_patch_name(char *patch) ;
char *get_patch_description(char *patch);
void apply_patch(char *patch_name);

#endif __PATCH_H__
