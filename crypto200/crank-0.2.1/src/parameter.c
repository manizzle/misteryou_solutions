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
 * parameter.c
 *
 * FUNCTION: 
 * Routines for componant parameters
 */

#include "crank.h"

#include "parameter.h"
#include "error.h"
#include <assert.h>
#include <string.h>

char *parameter_enum_value_name(parameter_description *param_descrip, int value_index) {
    char *value_string, *p, *output;
    int i;
    assert(param_descrip); assert(value_index >= 0);
    value_string = malloc(strlen(param_descrip->data_one) + 1);
    strcpy(value_string, param_descrip->data_one);
    p = strtok(value_string, "|");
    for (i = 0; i < value_index; i++)
	p = strtok(NULL, "|");
    assert(p);
    output = malloc(strlen(p) + 1);
    strcpy(output, p);
    free(value_string);
    return output;
}

const char *parameter_type_lookup(parameter_type type) {
    switch (type) {
    case PARAM_TYPE_FLOAT:
	return "floating point number";
	break;
    case PARAM_TYPE_INT:
	return "integer";
	break;
    case PARAM_TYPE_ENUM:
	return "enumeration";
	break;
    case PARAM_TYPE_STRING:
	return "string";
	break;
    default:
	warn("Unknown parameter type %d\n", type);
	return "Unknown parameter type";
	break;

    }
}

int parameter_get_default_int_or_enum(parameter_description *param_descrip) {
    assert(param_descrip);
    assert(param_descrip->type == PARAM_TYPE_STRING);
    return atoi(param_descrip->default_value);
    
}
double parameter_get_default_double(parameter_description *param_descrip) {
    assert(param_descrip);
    assert(param_descrip->type == PARAM_TYPE_STRING);
    return atof(param_descrip->default_value);
}

char *parameter_get_default_string(parameter_description *param_descrip) {
    assert(param_descrip);
    assert(param_descrip->type == PARAM_TYPE_STRING);
    return param_descrip->default_value;
}
