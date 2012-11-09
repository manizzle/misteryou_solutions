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
 * heuristic_random.c
 *
 * FUNCTION: 
 * Randomly select points from the transform space, see how they do ;-)
 */

#include "crank.h"
#include "componant.h"
#include "error.h"
#include "common_constraint_parse.h"
#include <time.h>
#include <assert.h>

#ifdef BUILD_DYNAMIC
#define SYM(symbol) symbol
#else  BUILD_DYNAMIC
#define SYM(symbol) heuristic_random_ ## symbol
#endif BUILD_DYNAMIC

/** Common componant interface **********************/

const componant_type SYM(type) = COMPONANT_TYPE_HEURISTIC;
const char SYM(name)[] = "random";
const char SYM(description)[] = "Randomly selects points from the transform space, to see how they do ;-))";

#define NUM_PARAMS 2
#define PARAM_ITERATIONS  0
#define PARAM_CONSTRAINTS 1

const int SYM(number_of_parameters) = NUM_PARAMS;
const parameter_description SYM(parameter_description_table)[NUM_PARAMS] = { 

/*  |Parameter Type |Label | Names of values (in enum)                              |na|default|Description          | */
/*  |---------------|------|--------------------------------------------------------|--|-------|---------------------| */
    {PARAM_TYPE_INT,   "Iterations", "1", "", "10000", "Number of iterations"},
    {PARAM_TYPE_STRING, "Transform Contraints", "", "", "", "Constraints on the values of the transformation"}
/*  |---------------|------|--------------------------------------------------------|--|------|----------------------| */

};

int SYM(boot)(void) { 
    srand(time(NULL));
    return TRUE; 
}

/** Fitness specific interface ********************/

instance *SYM(heuristic)(instance *i, char *text, componant *transform_class_void, instance *initial, instance *fitness, 
                         int (*yield)(char *, double), 
                         void (*improvement_found)(instance *, double)) {
    int iter, param_index, iterations;
    double current_fitness, best_fitness;
    char *transformed_text, *constraints;
    parameter_constraint_parse *parse;
    componant *transform_class, *fitness_class;
    instance *xform, *best_instance;

    iterations = * (int *) peek_param(i, PARAM_ITERATIONS);
    constraints = (char *) peek_param(i, PARAM_CONSTRAINTS);

    assert(transform_class_void); assert(fitness); assert(text); assert(i); assert(yield); assert(improvement_found);

    assert(transform_class_void->type == COMPONANT_TYPE_TRANSFORM);
    assert(fitness->componant_class->type == COMPONANT_TYPE_FITNESS);
    assert(i->componant_class->type == COMPONANT_TYPE_HEURISTIC);
    fitness_class = fitness->componant_class;
    transform_class = (componant *) transform_class_void;

    parse = parse_constraints(constraints, transform_class->parameter_description_table, transform_class->number_of_parameters);


    /* If initial is present, grap a copy, if not we stick to the default */   
    if (initial) {
	assert(transform_class == initial->componant_class);
	xform = duplicate_instance(initial);
    }  else {
	xform = make_new_instance(transform_class);
    }

    enforce_constraints(xform, parse);

    /* Get an initial reading on the best parameters and fitness */
    best_instance = duplicate_instance(xform);
    transformed_text = transform_class->type_data.transform->transform(xform, text);
    best_fitness = fitness_class->type_data.fitness->fitness(fitness, transformed_text);
    free(transformed_text);

    /* Main loop */
    for (iter = 0; iter < iterations; iter++) {

	/* Loop over the parameters, selecting each value randomly in accordance with the constraints */
	if (!transform_class->number_of_parameters)
	    continue;
	for (param_index = 0; param_index < transform_class->number_of_parameters; param_index++) {
	    
	    assert(parse[param_index].values);
	    
	    switch (transform_class->parameter_description_table[param_index].type) {

	    case PARAM_TYPE_ENUM:
		randomise_parameter(xform, parse, param_index, TRUE);
		break;

	    case PARAM_TYPE_INT:
	    case PARAM_TYPE_FLOAT:
	    case PARAM_TYPE_STRING:
		warn("BUG! PARAM_TYPE_%d needs to be supported in heuristic_random\n", transform_class->parameter_description_table[param_index].type);
		break;
	    default: 
		warn("Unsupported parameter type %d\n", transform_class->parameter_description_table[param_index].type);
		break;
	    }
	}

	/* Check to see if this new transform is better than the previous best */
	transformed_text = transform_class->type_data.transform->transform(xform, text);
	current_fitness = fitness_class->type_data.fitness->fitness(fitness, transformed_text);
	free(transformed_text);
	if (current_fitness < best_fitness) {
	    best_fitness = current_fitness;
	    free_instance(best_instance);
	    best_instance = duplicate_instance(xform);
	    improvement_found(duplicate_instance(xform), best_fitness);
	}
	if (yield("", (double) iter / (double) iterations)) {
	    free_instance(xform);
	    free_constraint_parse(parse, transform_class->number_of_parameters);
	    return best_instance;
	}
    }
    
    free_instance(xform);
    free_constraint_parse(parse, transform_class->number_of_parameters);
    return best_instance;
}
