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
 * null_componant.c
 *
 * FUNCTION: 
 * "Blank" componants used as defaults
 */


#include "crank.h"
#include "componant.h"
#include "instance.h"

/* 
 * transform_null 
 * ============== 
 */

const componant_type transform_null_type = COMPONANT_TYPE_TRANSFORM;
const char transform_null_name[] = "null";
const char transform_null_description[] = "";
const int transform_null_number_of_parameters = 0;
const parameter_description transform_null_parameter_description_table[0] = {};

int transform_null_boot(void) {return TRUE;}
char *transform_null_transform(instance *transform, char *text) {char *newtext = malloc((strlen(text) + 1)); strcpy(newtext, text); return newtext;}

/* 
 * heuristic_null 
 * ============== 
 */

const componant_type heuristic_null_type = COMPONANT_TYPE_HEURISTIC;
const char heuristic_null_name[] = "null";
const char heuristic_null_description[] = "";
const int heuristic_null_number_of_parameters = 0;
const parameter_description heuristic_null_parameter_description_table[0] = {};

int heuristic_null_boot(void) {return TRUE;}
instance *heuristic_null_heuristic(instance *i, char *text, componant *transform_class_void, instance *initial, instance *fitness, 
                         void (*yield)(char *, double), 
                         void (*improvement_found)(instance *)) {return duplicate_instance(initial);
}
/* 
 * fitness_null 
 * ============== 
 */

const componant_type fitness_null_type = COMPONANT_TYPE_FITNESS;
const char fitness_null_name[] = "null";
const char fitness_null_description[] = "";
const int fitness_null_number_of_parameters = 0;
const parameter_description fitness_null_parameter_description_table[0] = {};

int fitness_null_boot(void) {return TRUE;}
double fitness_null_fitness(instance *fitness, char *text) { return 0.0; }

/* 
 * gui_null 
 * ============== 
 */

#define STR_GUI_NULL_TEXT "None specified"

const componant_type gui_null_type = COMPONANT_TYPE_GUI;
const char gui_null_name[] = "null";
const char gui_null_description[] = "";
const int gui_null_number_of_parameters = 0;
const parameter_description gui_null_parameter_description_table[0] = {};
int gui_null_boot(void) {return TRUE;}

componant_type gui_null_componant_target_type = COMPONANT_TYPE_ANY;
char *gui_null_componant_target_name = "";

gui_item *gui_null_build_gui_item(instance *gui, instance *i) { return gtk_label_new(STR_GUI_NULL_TEXT);}
void gui_null_update_gui_item(instance *gui, instance *i) {return;}
