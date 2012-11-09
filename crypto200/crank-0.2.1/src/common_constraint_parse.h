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
 * common_constraint_parse.h
 *
 * FUNCTION: 
 * Parsing of constraint strings for use in heuristics
 */

#ifndef __COMMON_CONSTRAINT_PARSE_H__
#define __COMMON_CONSTRAINT_PARSE_H__

#include "componant.h"
#include "crank.h"
#include "parameter.h"

typedef enum {CONSTRAINT_TYPE_NONE, CONSTRAINT_TYPE_RESTRICT, CONSTRAINT_TYPE_PERMUTE} constraint_type;

typedef struct {
    parameter_type type; 
    constraint_type constraint_type;
    int num_values;          /* Number of values a parameter is allowed to take on */
    int *values;             /* Array indexed from 0 to num_values - 1 containing unique acceptable values */
    int *permute_parameters; /* Parameters also in the permute domain (0 to num_values - 2) */
    int utility_flag;        /* Space for the heuristic to 'mark' a constrained parameter, with either a CONSTRAINT_FLAG, or a parameter value */
} parameter_constraint_parse;

parameter_constraint_parse *parse_constraints(char *constraints, parameter_description *parameter_description_table, int number_of_parameters);
void free_constraint_parse(parameter_constraint_parse *parse, int number_of_parameters);
int enforce_constraints(instance *i, parameter_constraint_parse *parse);
int randomise_parameter(instance *i, parameter_constraint_parse *parse, int param_index, int allow_no_change);

/* These need to be negative, because positive and zero denote discrete parameter values */
#define CONSTRAINT_FLAG_UNSEEN    -1
#define CONSTRAINT_FLAG_RESTRICT  -2 
#define CONSTRAINT_FLAG_PERMUTE   -3

#endif __COMMON_CONSTRAINT_PARSE_H__
