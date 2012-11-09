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
 * parameter.h
 *
 * FUNCTION: 
 * Routines for componant parameters
 */

#ifndef __PARAMETER_H__
#define __PARAMETER_H__
/* The set of possible parameter types */
typedef enum {
    PARAM_TYPE_ENUM,  /* An enumeration type */
    PARAM_TYPE_INT,   /* Integer valued */
    PARAM_TYPE_FLOAT, /* Floating point valued */  
    PARAM_TYPE_STRING /* String valued */
} parameter_type;

const char *parameter_type_lookup(parameter_type type);

/* Record describing one parameter in a componant */
typedef struct parameter_description {
    parameter_type type;
    char *name;
    char *data_one;
    char *data_two;
    char *default_value;
    char *description;
} parameter_description;

char *parameter_enum_value_name(parameter_description *param_descrip, int value_index);
//int parameter_enum_name_value(parameter_description *param_descrip, char *name);

int parameter_get_default_int_or_enum(parameter_description *param_descrip);
double parameter_get_default_double(parameter_description *param_descrip);
char *parameter_get_default_string(parameter_description *param_descrip);

#endif __PARAMETER_H__

//P:0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25:0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25
