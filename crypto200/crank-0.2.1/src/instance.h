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
 * instance.h
 *
 * FUNCTION: 
 * Functions dealing with individual instances
 */

#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#ifndef __COMPONANT_H__
#include "componant.h"
#endif __COMPONANT_H__

#include "parameter.h"

/* Record for componant instance */
typedef struct instance {

    /* The componant class for the instance */
    struct componant *componant_class;

    /* The parameter values associated with an instance, stored as an array of void pointers */
    void **parameters;

    /* Whatever information the instance wants to store in itself */
    void *data; 

} instance;

/* Return new instance of a componant */
instance *make_new_instance(struct componant *componant_class);

/* Return a copy of the instance */
instance *duplicate_instance(instance *i);

/* Deallocate instance */
void free_instance(instance *i); 

/* Change a parameter of an instance */
void poke_param(instance *i, int param_index, void *value_ptr);

/* Query a parameter of an instance */
void *peek_param(instance *i, int param_index);

/* Request a parameter dump from an instance */
char *dump_parameters(instance *i);
    
/* Set an instance from a parameter set */
instance *instantiate_parameters(char *parameter_string);

/** transform componant specific *******/

char *transform(instance *transform, char *text);

/** heuristic componant specific *******/
instance *heuristic(instance *i, char *text, struct componant *transform_class_void, instance *initial, instance *fitness, 
                            int (*yield)(char *, double), 
		            void (*improvement_found)(instance *, double));

/** fitness componant specific *******/

double fitness(instance *fitness, char *text);

/** gui componant specific *******/

gui_item *build_gui_item(instance *gui, instance *i); 

#endif  __INSTANCE_H__
