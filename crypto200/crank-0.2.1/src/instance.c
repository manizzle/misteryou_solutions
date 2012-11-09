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
 * instance.c
 *
 * FUNCTION: 
 * Functions dealing with individual instances
 */

#include "crank.h"
#include "componant.h"
#include "error.h"
#include <limits.h>
#include <float.h>
#include <assert.h>
#include <string.h>
#ifdef HAVE_LIBGUILE
#include <libguile.h>
#endif /* HAVE_LIBGUILE */
#include "scheme_interface.h"

instance *make_new_instance(componant *componant_class) {
    parameter_description *param_table;
    int param_index, number_of_parameters, param_type, *int_value;
    char *value_string, *string_value;
    double *double_value;
    instance *new_instance = malloc(sizeof(instance));
    void **parameters;

    assert(componant_class);

    param_table = componant_class->parameter_description_table;
    number_of_parameters = componant_class->number_of_parameters;
    
    assert(param_table); assert(number_of_parameters >= 0);

    if (number_of_parameters)
	parameters = malloc(number_of_parameters * sizeof(void *));
    else
	parameters = NULL;

    for (param_index = 0; param_index < number_of_parameters; param_index++) {

	param_type = param_table[param_index].type;
	value_string = param_table[param_index].default_value;

	switch (param_type) {
	case PARAM_TYPE_ENUM:
	case PARAM_TYPE_INT:
	    int_value = malloc(sizeof(int));
	    *int_value = atoi(value_string);
	    parameters[param_index] = int_value;
	    break;
	case PARAM_TYPE_STRING:
	    string_value = malloc((strlen(value_string) + 1) * sizeof(char));
	    strcpy(string_value, value_string);
	    parameters[param_index] = string_value;
	    break;
	case PARAM_TYPE_FLOAT:
	    double_value = malloc(sizeof(double));
	    *double_value = atof(value_string);
	    parameters[param_index] = double_value;
	    break;
	default:
	    warn("Unknown parameter type %d\n", param_type);
	    break;
	}

    }

    new_instance->parameters = parameters;
    new_instance->componant_class = componant_class;
    new_instance->data = NULL;
    return new_instance;
}

instance *duplicate_instance(instance *i) {
    parameter_description *param_table;
    int param_index, number_of_parameters, param_type, *int_value;
    char *string_value;
    double *double_value;
    instance *new_instance = malloc(sizeof(instance));
    void **parameters;

    assert(i); assert(i->componant_class); assert(i->parameters);

    param_table = i->componant_class->parameter_description_table;
    number_of_parameters = i->componant_class->number_of_parameters;
    
    assert(param_table); assert(number_of_parameters >= 0);

    parameters = malloc(number_of_parameters * sizeof(void *));
    
    for (param_index = 0; param_index < number_of_parameters; param_index++) {

	param_type = param_table[param_index].type;

	switch (param_type) {
	case PARAM_TYPE_ENUM:
	case PARAM_TYPE_INT:
	    int_value = malloc(sizeof(int));
	    *int_value = * (int *) i->parameters[param_index];
	    parameters[param_index] = int_value;
	    break;
	case PARAM_TYPE_STRING:
	    string_value = malloc((strlen((char *) i->parameters[param_index]) + 1) * sizeof(char));
	    strcpy(string_value, (char *) i->parameters[param_index]);
	    parameters[param_index] = string_value;
	    break;
	case PARAM_TYPE_FLOAT:
	    double_value = malloc(sizeof(double));
	    *double_value = * (double *) i->parameters[param_index];
	    parameters[param_index] = double_value;
	    break;
	default:
	    warn("Unknown parameter type %d\n", param_type);
	    break;
	}

    }

    new_instance->parameters = parameters;
    new_instance->componant_class = i->componant_class;
    return new_instance;
}

void free_instance(instance *i) {
    int param_index, number_of_parameters;
    assert(i); assert(i->componant_class); assert(i->parameters);
    number_of_parameters = i->componant_class->number_of_parameters;
    for (param_index = 0; param_index < number_of_parameters; param_index++) {
	assert(i->parameters[param_index]);
	free(i->parameters[param_index]);
    }
    free(i->parameters);
    free(i);
}
void poke_param(instance *i, int param_index, void *value_ptr) {
    parameter_description *param_table;
    int number_of_parameters, param_type, *int_value, int_max, int_min;
    char *string_value;
    double *double_value, double_max, double_min;

    assert(i); assert(i->componant_class); assert(i->parameters); assert(value_ptr);

    param_table = i->componant_class->parameter_description_table;
    number_of_parameters = i->componant_class->number_of_parameters;
    assert(param_table); assert(number_of_parameters > 0);

    if (param_index >= number_of_parameters || param_index < 0) {
	warn("param_index %d out of bounds\n", param_index);
	return;
    }

    param_type = param_table[param_index].type;

    switch (param_type) {

    case PARAM_TYPE_ENUM:
	int_value = malloc(sizeof(int));
	*int_value = * (int *) value_ptr;
	int_max = atoi(param_table[param_index].data_two);
	if (!int_max) 
	    int_max = INT_MAX;
	if (*int_value < 0 || *int_value >= int_max) {
	    warn("parameter %d value %d is out of range\n", param_index, *int_value);
	    free(int_value);
	    return;
	}
	free(i->parameters[param_index]);
	i->parameters[param_index] = int_value;
	break;

    case PARAM_TYPE_INT:
	int_value = malloc(sizeof(int));
	*int_value = * (int *) value_ptr;
	int_min = atoi(param_table[param_index].data_one);
	int_max = atoi(param_table[param_index].data_two);
	if (!int_max) 
	    int_max = INT_MAX;
	if (!int_min) 
	    int_min = INT_MIN;
	if (*int_value < int_min || *int_value > int_max) {
	    warn("parameter %d value %d is out of range\n", param_index,  *int_value);
	    free(int_value);
	    return;
	}
	free(i->parameters[param_index]);
	i->parameters[param_index] = int_value;
	break;

    case PARAM_TYPE_STRING:
	string_value = malloc((strlen((char *) value_ptr) + 1) * sizeof(char));
	strcpy(string_value, (char *) value_ptr);
	free(i->parameters[param_index]);
	i->parameters[param_index] = string_value;
	break;
	
    case PARAM_TYPE_FLOAT:
	double_value = malloc(sizeof(double));
	*double_value = * (double *) value_ptr;
	double_min = atof(param_table[param_index].data_one);
	double_max = atof(param_table[param_index].data_two);
	if (!*param_table[param_index].data_one)
	    double_min = -DBL_MAX;
	if (!*param_table[param_index].data_two) 
	    double_max = DBL_MAX;
	if (*double_value < double_min || *double_value > double_max) {
	    warn("parameter %d value %f is out of range\n", param_index, *double_value);
	    free(double_value);
	    return;

	}
	free(i->parameters[param_index]);
	i->parameters[param_index] = double_value;
	break;

    default:
	warn("Unknown %d parameter type %d\n", param_index, param_type);
	break;
	
    }
}

void *peek_param(instance *i, int param_index) {
    int number_of_parameters;
    assert(i); assert(i->componant_class); assert(i->parameters);     
    number_of_parameters = i->componant_class->number_of_parameters;
    assert(number_of_parameters > 0);

    if (param_index >= number_of_parameters || param_index < 0) {
	warn("param_index %d out of bounds\n", param_index);
	return NULL;
    }
    return i->parameters[param_index];

}

#define INTEGER_STRING_WIDTH 12
#define DOUBLE_STRING_WIDTH   20
#define BUFSIZE 1024 /* Should be bigger than above */
char *dump_parameters(instance *i) {
    int number_of_parameters, param_index, current_size = 1, int_value;
    char buf[BUFSIZE], *string_value;
    double double_value;
    char *dump = malloc(current_size * sizeof(char));
    dump[0] = '\0';
    assert(i); assert(i->componant_class); assert(i->parameters);

    sprintf(buf, "(let ((i (make-new-instance (lookup-componant-by-name (get-componant-list) \"%s_%s\"))))\n",
	    componant_type_lookup(i->componant_class->type), i->componant_class->name);
    current_size += strlen(buf);
    dump = realloc(dump, current_size);
    strcat(dump, buf);

    number_of_parameters = i->componant_class->number_of_parameters;
    for (param_index = 0; param_index < number_of_parameters; param_index++) {
	switch (i->componant_class->parameter_description_table[param_index].type) {
	case PARAM_TYPE_ENUM:
	case PARAM_TYPE_INT:
	    int_value = * (int *) i->parameters[param_index];
	    sprintf(buf, "  (poke-param i %d (int2void %d))\n ", param_index, int_value);
	    current_size += strlen(buf);
	    dump = realloc(dump, current_size);
	    strcat(dump, buf);
	    break;
	case PARAM_TYPE_FLOAT:
	    double_value = * (double *) i->parameters[param_index];
	    sprintf(buf, "  (poke-param i %d (double2void %f))\n ", param_index, double_value);
	    current_size += strlen(buf);
	    dump = realloc(dump, current_size);
	    strcat(dump, buf);
	    break;
	case PARAM_TYPE_STRING:
	    string_value = (char *) i->parameters[param_index];
	    sprintf(buf, "  (poke-param i %d (string2void \"%s\"))\n ", param_index, string_value);
	    current_size += strlen(buf);
	    dump = realloc(dump, current_size);
	    strcat(dump, buf);
	    break;
	default:
	    warn("Unknown param type %d\n", param_index);
	    break;
	}
    }
    return dump;
}
instance *instantiate_parameters(char *parameter_string) {
    const char execute_string[] = "(set-returned-instance i))\n";
    char *eval_string = malloc(strlen(parameter_string) + strlen(execute_string) + 1);
    sprintf(eval_string, "%s%s", parameter_string, execute_string);

    /* Have to rely on the scheme side to recreate instances */
#ifdef HAVE_LIBGUILE
    scm_eval_0str(eval_string);
    free(eval_string);
    return get_returned_instance();
#else /* HAVE_LIBGUILE */
    return NULL;
#endif
}

char *transform(instance *transform, char *text) {
    assert(transform); assert(transform->componant_class); assert(transform->componant_class->type == COMPONANT_TYPE_TRANSFORM); assert(text);
    return(transform->componant_class->type_data.transform->transform(transform, text));
}

instance *heuristic(instance *i, char *text, componant *transform_class_void, instance *initial, instance *fitness, 
                            int (*yield)(char *, double), 
		            void (*improvement_found)(instance *, double)) {
    assert(i); assert(i->componant_class); assert(i->componant_class->type == COMPONANT_TYPE_HEURISTIC); assert(transform_class_void); assert(transform_class_void->type == COMPONANT_TYPE_TRANSFORM);
    if (initial) assert(initial->componant_class && initial->componant_class == transform_class_void);
    assert(fitness); assert(fitness->componant_class); assert(fitness->componant_class->type == COMPONANT_TYPE_FITNESS); assert(yield); assert(improvement_found);
    return i->componant_class->type_data.heuristic->heuristic(i, text, transform_class_void, initial, fitness, yield, improvement_found);

}

double fitness(instance *fitness, char *text) {
    assert(fitness); assert(fitness->componant_class); assert(fitness->componant_class->type == COMPONANT_TYPE_FITNESS); assert(text);
    return(fitness->componant_class->type_data.fitness->fitness(fitness, text));
}

gui_item *build_gui_item(instance *gui, instance *i) {
    assert(gui); assert(i); assert(gui->componant_class); assert(gui->componant_class->type == COMPONANT_TYPE_GUI);
    return gui->componant_class->type_data.gui->build_gui_item(gui, i);
}
