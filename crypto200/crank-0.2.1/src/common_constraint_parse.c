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
 * common_constraint_parse.c
 *
 * FUNCTION: 
 * Parsing of constraint strings for use in heuristics
 */

/* Hmm, now I realise why Perl was invented. This parsing routine could really do with a rewrite... */

#include "crank.h"
#include "common_constraint_parse.h"
#include "parameter.h"
#include <string.h>
#include <ctype.h>
#include <error.h>
#include <assert.h>

typedef struct _command_parse {
    constraint_type type;
    int *params;
    int number_of_params;
    int *values;
    int number_of_values;
    struct _command_parse *next;
} command_parse;

#define MAX_ARRAY 4096 /* Faff-saving */

command_parse *parse_compact_single(char *constraints) {
    int length;
    char *parse_pos = constraints, *value_string, *param_string, *number_string;
    command_parse *command = malloc(sizeof(command_parse));
    length = strlen(constraints);
    value_string = malloc(sizeof(char) * (length + 1));
    param_string = malloc(sizeof(char) * (length + 1));
    if (length > MAX_ARRAY) {warn("Array bounds approached."); }

    if (!*constraints)
	return NULL;

    switch ((int) *parse_pos) {
    case 'R':
    case 'r':
	command->type = CONSTRAINT_TYPE_RESTRICT;
	break;
    case 'P':
    case 'p':
	command->type = CONSTRAINT_TYPE_PERMUTE;
	break;
    default:
	warn("Parse error: command %s\n", constraints);
	return NULL;
    }
    /* This would segfault if the string isn't formatted correctly */
    parse_pos += 2;
    *(strrchr(parse_pos, ':')) = '\0';
    strcpy(param_string, parse_pos);
    while(*(parse_pos++)) ;
    strcpy(value_string, parse_pos);
    command->params = malloc(sizeof(int) * (1 + strlen(param_string) / 2));
    command->values = malloc(sizeof(int) * (1 + strlen(param_string) / 2));
    command->number_of_params = 0;
    command->number_of_values = 0;
    parse_pos = param_string;
    number_string = strtok(parse_pos, ",");
    if (!number_string)
	warn("Handle me!\n");
    command->params[command->number_of_params++] = atoi(number_string);
    while((number_string = strtok(NULL, ","))) {
	command->params[command->number_of_params] = atoi(number_string);
	command->number_of_params++;
    }

    parse_pos = value_string;
    number_string = strtok(parse_pos, ",");
    if (!number_string)
	warn("Handle me!\n");
    command->values[command->number_of_values++] = atoi(number_string);
    while((number_string = strtok(NULL, ","))) {
	command->values[command->number_of_values] = atoi(number_string);
	command->number_of_values++;
    }
    free(value_string);
    free(param_string);
    return command;
}

static command_parse *parse_commands(char *constraints) {
    int constraints_length = strlen(constraints);
    char *compact_constraints, *scan_char, *write_char,  *remainder;
    command_parse *this_parse;
    
    /* Get rid of whitespace and split into compact_constraints and remainder */
    compact_constraints = malloc(sizeof(char) * (constraints_length + 1));
    scan_char = constraints;
    write_char = compact_constraints;
    while (*scan_char != '\0' && *scan_char != '\n') {
	if (isalnum(*scan_char) || ispunct(*scan_char)) {
	    *(write_char++) = *scan_char;
	}
	scan_char++;
    }
    *write_char = '\0';
    
    if (*scan_char == '\0')
	remainder = write_char; /* Null char */
    else 
	remainder = ++scan_char;

    /* parse contents of compact_constraints */
    this_parse = parse_compact_single(compact_constraints);
    if (!this_parse)
	return NULL;

    /* make `next' = parse_commands(remainder_char); */
    if (*remainder) 
	this_parse->next = parse_commands(remainder);
    else
	this_parse->next = NULL;
    
    free(compact_constraints);
    return this_parse;
}

static void free_command_parse(command_parse *commands) {
    if (!commands)
	return;
    free_command_parse(commands->next);
    if (commands->params)
	free(commands->params);
    if (commands->values)
	free(commands->values);
    free(commands);
}

static int *make_int_array(int size) {
    int i, *array = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++ ) 
	array[i] = i;
    return array;
}

static int *copy_int_array(int size, int *from_array) {
    int i, *array = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++ ) 
	array[i] = from_array[i];
    return array;
}

static int *copy_int_array_except(int size, int *from_array, int except) {
    int i,j, *array = malloc(sizeof(int) * size);
    i = 0; j = 0;
    while (i < size) {
	if (from_array[i] != except)
	    array[j++] = from_array[i];
	i++;
    }
	
    return array;
}

static int count_char(char *string, char this_char) {
    char tmp;
    int count = 0;

    while ((tmp = (*(string++))))
	if (tmp == this_char)
	    count++;
    return count;
}

parameter_constraint_parse *parse_constraints(char *constraints, parameter_description *parameter_description_table, int number_of_parameters) {
    int param, *tmp_values;
    command_parse *commands, *this_command;
    parameter_constraint_parse *parse = malloc(sizeof(parameter_constraint_parse) * number_of_parameters);
    
    commands = parse_commands(constraints);
    
    /* First fill up the parse with the default parameters */
    for (param = 0; param < number_of_parameters; param++) {
	parse[param].type = parameter_description_table[param].type;
	parse[param].constraint_type = CONSTRAINT_TYPE_NONE;
	parse[param].permute_parameters = NULL;
	parse[param].utility_flag = 0;
	if (parameter_description_table[param].type == PARAM_TYPE_ENUM) {
	    parse[param].num_values = count_char(parameter_description_table[param].data_one, '|') + 1;
	    parse[param].values = make_int_array(parse[param].num_values);
	} else {
	    parse[param].num_values = 0;
	    parse[param].values = NULL;
	}
    }

    /* Now override them with parse commands */
    this_command = commands;
    while (this_command) {
	switch (this_command->type) {
	case CONSTRAINT_TYPE_RESTRICT:
	    for (param = 0; param < this_command->number_of_params; param++) {
		parse[this_command->params[param]].constraint_type = CONSTRAINT_TYPE_RESTRICT;
		parse[this_command->params[param]].num_values = this_command->number_of_values;
		if ((tmp_values = parse[this_command->params[param]].values))
		    free(tmp_values);
		parse[this_command->params[param]].values = copy_int_array(this_command->number_of_values, this_command->values);
	    }
	    break;
	case CONSTRAINT_TYPE_PERMUTE:
	    if (this_command->number_of_params != this_command->number_of_values) { warn("Discrepancy in permute command\n");}
	    for (param = 0; param < this_command->number_of_params; param++) {
		parse[this_command->params[param]].constraint_type = CONSTRAINT_TYPE_PERMUTE;
		parse[this_command->params[param]].num_values = this_command->number_of_values;
		if ((tmp_values = parse[this_command->params[param]].values))
		    free(tmp_values);
		parse[this_command->params[param]].values = copy_int_array(this_command->number_of_values, this_command->values);
		parse[this_command->params[param]].permute_parameters = copy_int_array_except(this_command->number_of_params, this_command->params, this_command->params[param]);
	    }
	    break;
	default:
	    warn("Unknown constraint command type %d.\n", this_command->type);
	    break;


	}
       	this_command = this_command->next;
    }
    free_command_parse(commands);
    return parse;
}

void free_constraint_parse(parameter_constraint_parse *parse, int number_of_parameters) {
    int param;
    if (!parse) {
	warn("NULL parse attempted to be freed.\n"); 
	return;
    }
    
    for (param = 0; param < number_of_parameters; param++) {
	if (parse[param].values)
	    free(parse[param].values);
	if (parse[param].permute_parameters)
	    free(parse[param].permute_parameters);
    }
    
    free(parse);
}

static int construct_free_permute_value_set(componant *componant, instance *i, parameter_constraint_parse *parse, int param_number, int *construct_it_here) {
    int num_used_permutes, num_free_permutes, *permutes_used, *permutes_free, perm_index, number_of_values, other_permute_value, value_index, found, value_here;
    assert(componant); assert(i); assert(parse); assert(param_number >= 0); assert(param_number < componant->number_of_parameters);

    number_of_values = parse[param_number].num_values;
    num_used_permutes = 0; 
    num_free_permutes = 0;
    permutes_used = calloc(number_of_values, sizeof(int));
    permutes_free = calloc(number_of_values, sizeof(int));

    /* Count permutation values used, and place them in the permutes_used array */
    for (perm_index = 0; perm_index < number_of_values - 1; perm_index++) { /* number_of_values - 1 because this parameter itself is excluded from the permute list */
	other_permute_value = * (int *) peek_param(i, parse[param_number].permute_parameters[perm_index]);
	/* This other permute value could be invalid for the permute range, but this does not matter here */
	
	permutes_used[num_used_permutes++] = other_permute_value;
    }

    /* Now go through the parameter values[] and find those which don't match any in the permutes_used[] array. Place these into permutes_free */
    for (value_index = 0; value_index < number_of_values; value_index++) {
	found = FALSE;
	value_here = parse[param_number].values[value_index];
	for (perm_index = 0; perm_index < num_used_permutes; perm_index++) 
	    if (permutes_used[perm_index] == value_here) {
		found = TRUE; 
		break;
	    }
	if (!found) 
	    permutes_free[num_free_permutes++] = value_here;
    }
    assert(num_free_permutes == number_of_values - num_used_permutes);
    assert(num_free_permutes);

    free(permutes_used);
    construct_it_here = permutes_free;
    return num_free_permutes;
} 

int enforce_constraints(instance *i, parameter_constraint_parse *parse) {
    int param_index, value_index, value_index_max, value_found_flag, current_value, all_ok_flag, *free_permute_value_set = NULL, size_free_permute_value_set, permute_index, the_permute_param_index, the_permute_value, ZERO = 0, number_of_parameters;
    componant *componant;
    assert(parse);
    assert(i);
    componant = i->componant_class;
    assert(componant);
    number_of_parameters = componant->number_of_parameters;

    assert(number_of_parameters >= 0);

    all_ok_flag = TRUE;

    for (param_index = 0; param_index < number_of_parameters; param_index++) {

	switch (parse[param_index].type) {

	case PARAM_TYPE_ENUM:

	    assert(parse[param_index].constraint_type == CONSTRAINT_TYPE_PERMUTE 
                   || parse[param_index].constraint_type == CONSTRAINT_TYPE_RESTRICT
		   || parse[param_index].constraint_type == CONSTRAINT_TYPE_NONE);

	    /* First check if the value of the componant is in the value set */
	    current_value = *(int *) peek_param(i, param_index);

	    value_index_max = parse[param_index].num_values;

	    value_found_flag = FALSE;
	    for (value_index = 0; value_index < value_index_max; value_index++) {
		if (parse[param_index].values[value_index] == current_value) {
		    value_found_flag = TRUE;
		    break;
		}
	    }

	    /* If the value of the instance parameter is not an element of the set of parse values, then make up a random one */
	    if (!value_found_flag) {
		switch (parse[param_index].constraint_type) {
		case CONSTRAINT_TYPE_RESTRICT:
		case CONSTRAINT_TYPE_NONE:
		    current_value = parse[param_index].values[rand() % value_index_max];
		    break;
		case CONSTRAINT_TYPE_PERMUTE:
		    /* Things are a bit more complicated for choosing a random permute value. At this stage we choose a random one
                     *  from the set of values not currently in use by anyone else in the permute group. */
		    size_free_permute_value_set = construct_free_permute_value_set(componant, i, parse, param_index, free_permute_value_set);
		    current_value = free_permute_value_set[rand() % size_free_permute_value_set];
		    free(free_permute_value_set);
		    break;
		default:
		    warn("Unknown constraint type %d\n", parse[param_index].constraint_type);
		    break;
		}
		poke_param(i, param_index, &current_value); 
	    }
	    
	    
	    /* For permutes, need to remove other instances of this value from the permute_params set, but only for higher param nums.
	     *  This is because we know there are no duplicates before this param index
	     */
	    if  (parse[param_index].constraint_type == CONSTRAINT_TYPE_PERMUTE) {
		for (permute_index = 0; permute_index < number_of_parameters - 1; permute_index++) {
		    the_permute_param_index = parse[param_index].permute_parameters[permute_index];
		    assert(the_permute_param_index != param_index);
		    if (the_permute_param_index < param_index)
			break;
		    the_permute_value = * (int *) peek_param(i, the_permute_param_index);
		    if (the_permute_value == current_value) { /* Constraints are violated, so correct to 0 - it will be picked up the next time round by the previous section*/
			poke_param(i, the_permute_param_index, &ZERO);
			all_ok_flag = FALSE;
		    }
		}
	    }

	    break;
	    
	case PARAM_TYPE_INT:
	case PARAM_TYPE_FLOAT:
	case PARAM_TYPE_STRING:
	    warn("Unchecked parameter type: %d\n", parse[param_index].type);
	    break;
	default:
	    warn("Unknown parameter type: %d\n", parse[param_index].type);
	    break;
	}

    }

    return all_ok_flag;
}
int randomise_parameter(instance *i, parameter_constraint_parse *parse, int param_index, int allow_no_change) {
    int new_value, old_value, value_index_max, rand_permute_index, permute_param_index, have_to_allow_no_change;
    componant *componant;
    assert(i);
    componant = i->componant_class;
    assert(componant);
    assert(parse);
    assert(enforce_constraints(i, parse));

    have_to_allow_no_change = allow_no_change;
    value_index_max = parse[param_index].num_values;
    /* If there's only one possible value, then the parameter cannot change */
    if (value_index_max <= 1) {
	have_to_allow_no_change = TRUE;
    }
    
    old_value = * (int *) peek_param(i, param_index);

    new_value = old_value;
    do {
	switch (parse[param_index].constraint_type) {
	case CONSTRAINT_TYPE_RESTRICT:
	case CONSTRAINT_TYPE_NONE:
	    new_value = parse[param_index].values[rand() % value_index_max];
	    break;
	case CONSTRAINT_TYPE_PERMUTE:
	    /* We can randomise by swapping within the permute set */
	    rand_permute_index = rand() % (value_index_max - 1);
	    permute_param_index = parse[param_index].permute_parameters[rand_permute_index];
	    new_value = * (int *) peek_param(i, permute_param_index);
	    poke_param(i, permute_param_index, &old_value); 

	    break;
	default:
	    warn("Unknown constraint type %d\n", parse[param_index].constraint_type);
	    break;
	}
	
    } while (!have_to_allow_no_change && new_value == old_value);
    poke_param(i, param_index, &new_value); 
	
    return TRUE;
}
