/* common.transpostions.rectangular.h - common rectangular tranpositions
 * 
 * This program is part of Crank, a cryptanalysis tool
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
 * common_transposition_grid.c
 *
 * FUNCTION: 
 * Routines for reading in and out of a grid
 */
#include "crank.h"
#include "error.h"
#include "common_transposition_grid.h"

const char *grid_path_names[MAX_GRIDPATH_ARRAY] = {
    "Straight Horizontals TL",              
    "Straight Horizontals BL",
    "Reverse Horizontals TR", 
    "Reverse Horizontals BR", 
    "Alternate Horizontals TL",
    "Alternate Horizontals TR",
    "Alternate Horizontals BR",
    "Alternate Horizontals BL", 
    
    "Descending Verticals TL",
    "Descending Verticals TR",
    "Ascending Verticals BL",
    "Ascending Verticals BR",
    "Alternate Verticals TL",
    "Alternate Verticals TR",
    "Alternate Verticals BR",
    "Alternate Verticals BL",

    "Clockwise Spiral in TL", 
    "Clockwise Spiral in TR", 
    "Clockwise Spiral in BR", 
    "Clockwise Spiral in BL", 

    "Anticlockwise Spiral in TL", 
    "Anticlockwise Spiral in TR", 
    "Anticlockwise Spiral in BR", 
    "Anticlockwise Spiral in BL", 

    "Clockwise Spiral out TL", 
    "Clockwise Spiral out TR", 
    "Clockwise Spiral out BR", 
    "Clockwise Spiral out BL", 

    "Anticlockwise Spiral out TL", 
    "Anticlockwise Spiral out TR", 
    "Anticlockwise Spiral out BR", 
    "Anticlockwise Spiral out BL"

};

#define DIRECTION_UP    0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3
#define ROTATE_CLOCKWISE(d)       (((d) + 1) % 4)
#define ROTATE_ANTICLOCKWISE(d)   (((d) + 3) % 4)
#define DIR_TO_ROW_CHANGE(d) \
                                  (  ((d) == DIRECTION_UP)      ? -1 : \
                                  (  ((d) == DIRECTION_DOWN)    ? 1  : \
                                   0))
#define DIR_TO_COL_CHANGE(d) \
                                  (  ((d) == DIRECTION_LEFT)    ? -1 : \
                                  (  ((d) == DIRECTION_RIGHT)   ? 1  : \
				     0))

#define CASE_SPIRAL(NAME, R, C, DIRECTION, ROTATE, ACTION) \
    case NAME: \
        counter = 0; \
        r = R; \
        c = C; \
        direction = DIRECTION; \
        while (counter < length - 1) { \
           counter++; \
 	   ACTION; \
           (marker_grid + r * cols)[c] = TRUE; \
           if (  (r + DIR_TO_ROW_CHANGE(direction) < 0) || \
                 (c + DIR_TO_COL_CHANGE(direction) < 0) || \
                 (r + DIR_TO_ROW_CHANGE(direction) >= rows) || \
                 (c + DIR_TO_COL_CHANGE(direction) >= cols) || \
                 (marker_grid + (DIR_TO_ROW_CHANGE(direction) + r) * cols)[DIR_TO_COL_CHANGE(direction) + c]) \
              direction = ROTATE(direction); \
           r += DIR_TO_ROW_CHANGE(direction); \
           c += DIR_TO_COL_CHANGE(direction); \
       } \
       ACTION; \
       break

/* Macro to share code between make_new_grid and extract_from_grid, which perform different operations along
   the same routes */
#define DO_PATH(ACTION, ACTION_REVERSE) \
    switch (path) { \
    case HORIZONTALS_STRAIGHT_TL: \
	for (r = 0; r < rows; r++)  \
	    for (c = 0; c < cols; c++) \
		ACTION; \
	break; \
    case HORIZONTALS_STRAIGHT_BL: \
	for (r = rows - 1; r >= 0; r--)  \
	    for (c = 0; c < cols; c++) \
		ACTION; \
	break; \
    case HORIZONTALS_REVERSE_TR: \
	for (r = 0; r < rows; r++)  \
	    for (c = cols - 1; c >= 0; c--) \
		ACTION; \
	break; \
    case HORIZONTALS_REVERSE_BR: \
	for (r = rows - 1; r >= 0; r--)  \
	    for (c = cols - 1; c >= 0; c--) \
		ACTION; \
	break; \
    case HORIZONTALS_ALTERNATE_TL: \
        for (r = 0; r < rows; r++) \
           if ((r + 1) % 2) \
              for (c = 0; c < cols; c++) \
                ACTION; \
           else \
              for (c = cols - 1; c >= 0; c--) \
                ACTION; \
        break; \
    case HORIZONTALS_ALTERNATE_TR: \
        for (r = 0; r < rows; r++) \
           if (r % 2) \
              for (c = 0; c < cols; c++) \
                ACTION; \
           else \
              for (c = cols - 1; c >= 0; c--) \
                ACTION; \
        break; \
    case HORIZONTALS_ALTERNATE_BL: \
        for (r = rows - 1; r >= 0; r--) \
           if ((rows - r) % 2) \
              for (c = 0; c < cols; c++) \
                ACTION; \
           else \
              for (c = cols - 1; c >= 0; c--) \
                ACTION; \
        break; \
    case HORIZONTALS_ALTERNATE_BR: \
        for (r = rows - 1; r >= 0; r--) \
           if ((rows - r + 1) % 2) \
              for (c = 0; c < cols; c++) \
                ACTION; \
           else \
              for (c = cols - 1; c >= 0; c--) \
                ACTION; \
        break; \
    case VERTICALS_DESCENDING_TL: \
	for (c = 0; c < cols; c++) \
	    for (r = 0; r < rows; r++)  \
		ACTION; \
	break; \
    case VERTICALS_DESCENDING_TR: \
	for (c = cols - 1; c >= 0; c--) \
	    for (r = 0; r < rows; r++)  \
		ACTION; \
	break; \
    case VERTICALS_ASCENDING_BL: \
	for (c = 0; c < cols; c++) \
	    for (r = rows - 1; r >= 0; r--)  \
		ACTION; \
	break; \
    case VERTICALS_ASCENDING_BR: \
	for (c = cols - 1; c >= 0; c--) \
	    for (r = rows - 1; r >= 0; r--)  \
		ACTION; \
	break; \
    case VERTICALS_ALTERNATE_TL: \
        for (c = 0; c < cols; c++) \
           if ((c + 1) % 2) \
              for (r = 0; r < rows; r++) \
                ACTION; \
           else \
              for (r = rows - 1; r >= 0; r--) \
                ACTION; \
        break; \
    case VERTICALS_ALTERNATE_BL: \
        for (c = 0; c < cols; c++) \
           if (c % 2) \
              for (r = 0; r < rows; r++) \
                ACTION; \
           else \
              for (r = rows - 1; r >= 0; r--) \
                ACTION; \
        break; \
    case VERTICALS_ALTERNATE_TR: \
        for (c = cols - 1; c >= 0; c--) \
           if ((cols - c) % 2) \
              for (r = 0; r < rows; r++) \
                ACTION; \
           else \
              for (r = rows - 1; r >= 0; r--) \
                ACTION; \
        break; \
    case VERTICALS_ALTERNATE_BR: \
        for (c = cols - 1; c >= 0; c--) \
           if ((cols - c + 1) % 2) \
              for (r = 0; r < rows; r++) \
                ACTION; \
           else \
              for (r = rows - 1; r >= 0; r--) \
                ACTION; \
        break; \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_IN_TL,      0,        0,        DIRECTION_RIGHT, ROTATE_CLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_IN_TR,      0,        cols - 1, DIRECTION_DOWN,  ROTATE_CLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_IN_BR,      rows - 1, cols - 1, DIRECTION_LEFT,  ROTATE_CLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_IN_BL,      rows - 1, 0,        DIRECTION_UP,    ROTATE_CLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_IN_TL,  0,        0,        DIRECTION_DOWN,  ROTATE_ANTICLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_IN_TR,  0,        cols - 1, DIRECTION_LEFT,  ROTATE_ANTICLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_IN_BR,  rows - 1, cols - 1, DIRECTION_UP,    ROTATE_ANTICLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_IN_BL,  rows - 1, 0,        DIRECTION_RIGHT, ROTATE_ANTICLOCKWISE, ACTION); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_OUT_TL,      0,        0,        DIRECTION_RIGHT, ROTATE_CLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_OUT_TR,      0,        cols - 1, DIRECTION_DOWN,  ROTATE_CLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_OUT_BR,      rows - 1, cols - 1, DIRECTION_LEFT,  ROTATE_CLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_ANTICLOCKWISE_OUT_BL,      rows - 1, 0,        DIRECTION_UP,    ROTATE_CLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_OUT_TL,  0,        0,        DIRECTION_DOWN,  ROTATE_ANTICLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_OUT_TR,  0,        cols - 1, DIRECTION_LEFT,  ROTATE_ANTICLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_OUT_BR,  rows - 1, cols - 1, DIRECTION_UP,    ROTATE_ANTICLOCKWISE, ACTION_REVERSE); \
    CASE_SPIRAL(SPIRAL_CLOCKWISE_OUT_BL,  rows - 1, 0,        DIRECTION_RIGHT, ROTATE_ANTICLOCKWISE, ACTION_REVERSE); \
    default: \
	warn("Unknown gridpath type."); \
	break; \
}


Grid make_new_grid(int rows, int cols, char *text, gridpath path) {
    Grid grid, marker_grid;
    char *pos = text, *end_pos;
    int r, c, length = rows * cols, counter = 0, direction;
    end_pos = text + length;
    grid = malloc(sizeof(char) * length);
    marker_grid = malloc(sizeof(char) * length);
    for (r = 0; r < rows; r++)
	for (c = 0; c < cols; c++)
	    (marker_grid + r * cols)[c] = FALSE;

    DO_PATH((grid + r * cols)[c] = *(pos++), (grid + r * cols)[c] = *(--end_pos));
    free(marker_grid);
    return grid;
}
char *extract_from_grid(Grid grid, int rows, int cols, gridpath path) {
    char *pos, *end_pos, *text;
    int r, c, length = rows * cols, counter = 0, direction;
    Grid marker_grid;
    marker_grid = malloc(sizeof(char) * length);
    for (r = 0; r < rows; r++)
	for (c = 0; c < cols; c++)
	    (marker_grid + r * cols)[c] = FALSE;
    text = malloc(sizeof(char) * (length + 1));
    pos = text;
    end_pos = text + length;
    DO_PATH(*(pos++) = (grid + r * cols)[c], *(--end_pos) = (grid + r * cols)[c]);
    
    *(text + length) = '\0';
    free(marker_grid);
    return text;
}
void free_grid(Grid grid) {
    free(grid);
}

char *transform_with_grid(int rows, int cols, char *text, gridpath writepath, gridpath readpath) {
    Grid tempgrid;
    char *newtext, *gridful, *returned_gridful;
    int i, pos = 0, grid_length = cols * rows, length = strlen(text);
    newtext = malloc(sizeof(char) * (length + grid_length + 1));
    while (pos < length) {
	gridful = malloc(sizeof(char) * (grid_length + 1));
	for (i = 0; i < grid_length; i++) 
	    if (pos + i < length) 
		gridful[i] = text[pos + i];
	    else
		gridful[i] = NULL_CHARACTER;
	gridful[i] = '\0';
	tempgrid = make_new_grid(rows, cols, gridful, writepath);
	returned_gridful = extract_from_grid(tempgrid, rows, cols, readpath);
	for (i = 0; i < grid_length; i++) 
	    newtext[pos + i] = returned_gridful[i];
	free(tempgrid);
	free(gridful);
	free(returned_gridful);
	pos += grid_length;
    }
    newtext[pos] = '\0';
    return newtext;
}
