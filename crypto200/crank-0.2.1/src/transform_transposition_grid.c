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
 * transform_transposition_grid.c
 *
 * FUNCTION: 
 * Transposition cipher formed by reading values in and out of a grid
 */

#include "crank.h"
#include "componant.h"
#include "common_transposition_grid.h"
#include <assert.h>
#include <string.h>

#ifdef BUILD_DYNAMIC
#define SYM(symbol) symbol
#else  BUILD_DYNAMIC
#define SYM(symbol) transform_transposition_grid_ ## symbol
#endif BUILD_DYNAMIC

/** Common componant interface **********************/

const componant_type SYM(type) = COMPONANT_TYPE_TRANSFORM;
const char SYM(name)[] = "transposition_grid";
const char SYM(description)[] = "A transposition cipher formed by writing and reading text out of a grid.";

#define NUM_PARAMS 4
#define PARAM_ROWS 0
#define PARAM_COLS 1
#define PARAM_WRITE_PATH 2
#define PARAM_READ_PATH 3

#define PATH_ENUM				\
"HORIZONTALS_STRAIGHT_TL|"			\
"HORIZONTALS_STRAIGHT_BL|"			\
"HORIZONTALS_REVERSE_TR|"			\
"HORIZONTALS_REVERSE_BR|"			\
"HORIZONTALS_ALTERNATE_TL|"			\
"HORIZONTALS_ALTERNATE_TR|"			\
"HORIZONTALS_ALTERNATE_BR|"			\
"HORIZONTALS_ALTERNATE_BL|"			\
"VERTICALS_DESCENDING_TL|"			\
"VERTICALS_DESCENDING_TR|"			\
"VERTICALS_ASCENDING_BL|"			\
"VERTICALS_ASCENDING_BR|"			\
"VERTICALS_ALTERNATE_TL|"			\
"VERTICALS_ALTERNATE_TR|"			\
"VERTICALS_ALTERNATE_BR|"			\
"VERTICALS_ALTERNATE_BL|"			\
"SPIRAL_CLOCKWISE_IN_TL|"			\
"SPIRAL_CLOCKWISE_IN_TR|"			\
"SPIRAL_CLOCKWISE_IN_BR|"			\
"SPIRAL_CLOCKWISE_IN_BL|"			\
"SPIRAL_ANTICLOCKWISE_IN_TL|"			\
"SPIRAL_ANTICLOCKWISE_IN_TR|"			\
"SPIRAL_ANTICLOCKWISE_IN_BR|"			\
"SPIRAL_ANTICLOCKWISE_IN_BL|"			\
"SPIRAL_CLOCKWISE_OUT_TL|"			\
"SPIRAL_CLOCKWISE_OUT_TR|"			\
"SPIRAL_CLOCKWISE_OUT_BR|"			\
"SPIRAL_CLOCKWISE_OUT_BL|"			\
"SPIRAL_ANTICLOCKWISE_OUT_TL|"			\
"SPIRAL_ANTICLOCKWISE_OUT_TR|"			\
"SPIRAL_ANTICLOCKWISE_OUT_BR|"			\
"SPIRAL_ANTICLOCKWISE_OUT_BL"

const int SYM(number_of_parameters) = NUM_PARAMS;
const parameter_description SYM(parameter_description_table)[NUM_PARAMS] = { 

/*  |Parameter Type |Label | Names of values (in enum)                              |na|default|Description          | */
/*  |---------------|------|--------------------------------------------------------|--|-------|---------------------| */
    {PARAM_TYPE_INT,  "rows",       "1",        "",  "5", "Number of rows in grid"} ,
    {PARAM_TYPE_INT,  "columns",    "1",        "",  "5", "Number of columns in grid"}, 
    {PARAM_TYPE_ENUM, "write path", PATH_ENUM, "32", "0", "Path to write text into grid"},
    {PARAM_TYPE_ENUM, "read path",  PATH_ENUM, "32", "0", "Path to read text out of grid"}

/*  |---------------|------|-------------------------------------------------------|--|------|----------------------| */

};

int SYM(boot)(void) { return TRUE; }

/** Transform specific interface ********************/

char *SYM(transform)(instance *i, char *text) {
    int rows, columns;
    gridpath write_path, read_path;

    assert(transform); assert(text);

    rows = * (int *) peek_param(i, PARAM_ROWS);
    columns = * (int *) peek_param(i, PARAM_COLS);
    read_path = * (gridpath *) peek_param(i, PARAM_READ_PATH);
    write_path = * (gridpath *) peek_param(i, PARAM_WRITE_PATH);

    return transform_with_grid(rows, columns, text, read_path, write_path);
}
