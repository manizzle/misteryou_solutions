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
 * transform_monoalphabetic.c
 *
 * FUNCTION: 
 * monoalphabetic cipher transformation componant
 */

#include "crank.h"
#include "componant.h"
#include "common_monoalphabetic.h"
#include <assert.h>
#include <string.h>

#ifdef BUILD_DYNAMIC
#define SYM(symbol) symbol
#else  BUILD_DYNAMIC
#define SYM(symbol) transform_monoalphabetic_ ## symbol
#endif BUILD_DYNAMIC

/** Common componant interface **********************/

const componant_type SYM(type) = COMPONANT_TYPE_TRANSFORM;
const char SYM(name)[] = "monoalphabetic";
const char SYM(description)[] = "A simple monoalphabetic transformation using a permutation of the letters 'a' - 'z'.";

#define NUM_PARAMS 26
#define PARAM_A 0
/* ... */
#define PARAM_Z 25
#define PARAM_VALUE_NULL 26
#define NULL_CHARACTER ('*')

const int SYM(number_of_parameters) = NUM_PARAMS;
const parameter_description SYM(parameter_description_table)[NUM_PARAMS] = { 

/*  |Parameter Type |Label | Names of values (in enum)                              |na|default|Description          | */
/*  |---------------|------|--------------------------------------------------------|--|-------|---------------------| */
    {PARAM_TYPE_ENUM, "A", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "0", "Letter replacing 'A'"},
    {PARAM_TYPE_ENUM, "B", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "1", "Letter replacing 'B'"},
    {PARAM_TYPE_ENUM, "C", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "2", "Letter replacing 'C'"},
    {PARAM_TYPE_ENUM, "D", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "3", "Letter replacing 'D'"},
    {PARAM_TYPE_ENUM, "E", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "4", "Letter replacing 'E'"},
    {PARAM_TYPE_ENUM, "F", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "5", "Letter replacing 'F'"},
    {PARAM_TYPE_ENUM, "G", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "6", "Letter replacing 'G'"},
    {PARAM_TYPE_ENUM, "H", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "7", "Letter replacing 'H'"},
    {PARAM_TYPE_ENUM, "I", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "8", "Letter replacing 'I'"},
    {PARAM_TYPE_ENUM, "J", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "9", "Letter replacing 'J'"},
    {PARAM_TYPE_ENUM, "K", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "10", "Letter replacing 'K'"},
    {PARAM_TYPE_ENUM, "L", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "11", "Letter replacing 'L'"},
    {PARAM_TYPE_ENUM, "M", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "12", "Letter replacing 'M'"},
    {PARAM_TYPE_ENUM, "N", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "13", "Letter replacing 'N'"},
    {PARAM_TYPE_ENUM, "O", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "14", "Letter replacing 'O'"},
    {PARAM_TYPE_ENUM, "P", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "15", "Letter replacing 'P'"},
    {PARAM_TYPE_ENUM, "Q", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "16", "Letter replacing 'Q'"},
    {PARAM_TYPE_ENUM, "R", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "17", "Letter replacing 'R'"},
    {PARAM_TYPE_ENUM, "S", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "18", "Letter replacing 'S'"},
    {PARAM_TYPE_ENUM, "T", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "19", "Letter replacing 'T'"},
    {PARAM_TYPE_ENUM, "U", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "20", "Letter replacing 'U'"},
    {PARAM_TYPE_ENUM, "V", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "21", "Letter replacing 'V'"},
    {PARAM_TYPE_ENUM, "W", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "22", "Letter replacing 'W'"},
    {PARAM_TYPE_ENUM, "X", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "23", "Letter replacing 'X'"},
    {PARAM_TYPE_ENUM, "Y", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "24", "Letter replacing 'Y'"},
    {PARAM_TYPE_ENUM, "Z", "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|*", "27", "25", "Letter replacing 'Z'"}
/*  |---------------|------|-------------------------------------------------------|--|------|----------------------| */

};

int SYM(boot)(void) { return TRUE; }

/** Transform specific interface ********************/

char *SYM(transform)(instance *transform, char *text) {
    key k;
    int param;
    int key_value;

    assert(transform); assert(text); assert(transform->componant_class->type == COMPONANT_TYPE_TRANSFORM);

    for (param = PARAM_A; param <= PARAM_Z; param++) {
	key_value = * (int *) transform->parameters[param];
	if (key_value == PARAM_VALUE_NULL) 
	    k[param + 'A'] = NULL_CHARACTER;
	else
	    k[param + 'A'] = key_value + 'a';
    }
    return apply_key_text(&k, text);
}
