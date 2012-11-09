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
 * componant.h
 *
 * FUNCTION: 
 * General componant handling
 */

#ifndef __COMPONANT_H__
#define __COMPONANT_H__

#include "instance.h"
#include "parameter.h"
#include "plugin.h"

/* The list of componant types */
typedef enum {
    COMPONANT_TYPE_ANY,        /* Used to denote any componant type */
    COMPONANT_TYPE_SPECIFIC,   /* Used to denote a specific componant */
    COMPONANT_TYPE_TRANSFORM,  /* A string->string candidate decryption function */
    COMPONANT_TYPE_FITNESS,    /* A measure of a text's closeness to plaintext   */
    COMPONANT_TYPE_HEURISTIC,  /* An algorithm for optimising a transformation's performance over some text wrt a fitness measure */
    COMPONANT_TYPE_GUI         /* A user interface to the parameters of a componant */
} componant_type;

typedef int componant_id;

/* Type specific data for a transform componant */
typedef struct {

    /* Transformation function represented by the componant class */
    char *(*transform)(struct instance *, char *);

} componant_type_transform;

/* Type specific data for a fitness componant */
typedef struct {
    
    /* Fitness function represented by the componant class */
    double (*fitness)(struct instance *, char *);

} componant_type_fitness;

/* Type specific data for a heuristic componant */
typedef struct {

    struct instance *(*heuristic)(struct instance *, char *, struct componant *, struct instance *, struct instance *,
			   int (*)(char *, double),
			   void (*)(struct instance *, double));
} componant_type_heuristic;

/* Type specific data for a gui componant */
typedef struct {
    componant_type componant_target_type;
    char *componant_target_name;
    gui_item *(*build_gui_item)(struct instance *, struct instance *);
    void (*update_gui_item)(struct instance *, struct instance *);

} componant_type_gui;

/* Allows different componant-types to share common data structure */
typedef union {
    componant_type_transform *transform;
    componant_type_fitness   *fitness;
    componant_type_heuristic *heuristic;
    componant_type_gui       *gui;
} componant_type_data;

/* Record for componant information */
typedef struct componant {
    
    /* Module associated with componant (NULL if hardcoded) */
    Module *module;

    /* Filename associated with componant (or else "hardcoded") */
    char *filename;
    
    /* Unique string identifying componant */
    char *name;          
    
    /* A componant's type determines its use by Crank */
    componant_type type;

    /* String user can read as a summary of componant's behaviour */
    char *description; 
    
    /* Number of parameters in description table */
    int number_of_parameters;

    /* Description of parameters taken by componant */
    parameter_description *parameter_description_table; 
    
    /* Function called at initialisation of a componant */
    int (*boot)(void);

    /* Pointer to specific componant data */
    componant_type_data type_data;

    /* Next pointer for use when record is in linked list */
    struct componant *next;

} componant;

/*
 * componant_type_lookup() names the enumeration type used for the componant_type
 * Arguments: type - type to name
 * Returns: constant string name
 */ 
const char *componant_type_lookup(componant_type type);

/* 
 * free_componant() frees the memory associated with a componant record
 * Arguments: componant_record - componant to deallocate
 */
void free_componant(componant *componant_record);

/*
 * free_componant_list() recurses down a linked componant list, freeing associated memory 
 * Arguments: componant_list - list to free 
 */
void free_componant_list(componant *componant_list);

componant *lookup_componant(componant *componant_list, int number);

componant *lookup_componant_by_name(componant *componant_list, char *name);

#endif  __COMPONANT_H__
