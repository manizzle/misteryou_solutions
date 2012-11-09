/* 
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
 * common_transposition_grid.h
 *
 * FUNCTION: 
 * Routines for reading in and out of a grid
 */

#ifndef __COMMON_TRANSPOSITION_GRID_H__
#define __COMMON_TRANSPOSITION_GRID_H__

#define NULL_CHARACTER '#'

typedef char* Grid;

typedef int gridpath;

#define HORIZONTALS_STRAIGHT_TL     0
#define HORIZONTALS_STRAIGHT_BL     1
#define HORIZONTALS_REVERSE_TR      2
#define HORIZONTALS_REVERSE_BR      3
#define	HORIZONTALS_ALTERNATE_TL    4
#define	HORIZONTALS_ALTERNATE_TR    5
#define	HORIZONTALS_ALTERNATE_BR    6
#define	HORIZONTALS_ALTERNATE_BL    7

#define	VERTICALS_DESCENDING_TL     8
#define	VERTICALS_DESCENDING_TR     9 
#define	VERTICALS_ASCENDING_BL      10
#define	VERTICALS_ASCENDING_BR      11
#define	VERTICALS_ALTERNATE_TL      12
#define	VERTICALS_ALTERNATE_TR      13
#define	VERTICALS_ALTERNATE_BR      14
#define	VERTICALS_ALTERNATE_BL      15

#define SPIRAL_CLOCKWISE_IN_TL      16
#define SPIRAL_CLOCKWISE_IN_TR      17
#define SPIRAL_CLOCKWISE_IN_BR      18
#define SPIRAL_CLOCKWISE_IN_BL      19

#define SPIRAL_ANTICLOCKWISE_IN_TL  20
#define SPIRAL_ANTICLOCKWISE_IN_TR  21
#define SPIRAL_ANTICLOCKWISE_IN_BR  22
#define SPIRAL_ANTICLOCKWISE_IN_BL  23 

#define SPIRAL_CLOCKWISE_OUT_TL     24
#define SPIRAL_CLOCKWISE_OUT_TR     25
#define SPIRAL_CLOCKWISE_OUT_BR     26
#define SPIRAL_CLOCKWISE_OUT_BL     27 

#define SPIRAL_ANTICLOCKWISE_OUT_TL 28
#define SPIRAL_ANTICLOCKWISE_OUT_TR 29
#define SPIRAL_ANTICLOCKWISE_OUT_BR 30
#define SPIRAL_ANTICLOCKWISE_OUT_BL 31

#define MAX_GRIDPATH                31 /* Should be last number from above */
#define MAX_GRIDPATH_ARRAY          32 /* Should be one more than MAX_GRIDPATH */

extern const char *grid_path_names[MAX_GRIDPATH_ARRAY];

Grid make_new_grid(int rows, int cols, char *text, gridpath path); /* Makes a new grid - text must contain rows * cols text */
char *extract_from_grid(Grid grid, int rows, int cols, gridpath path);
void free_grid(Grid grid);
char *transform_with_grid(int rows, int cols, char *text, gridpath writepath, gridpath readpath);

#endif /* __COMMON_TRANSPOSITION_GRID_H__ */
