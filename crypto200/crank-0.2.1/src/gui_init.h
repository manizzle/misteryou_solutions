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
 * gui_init.h
 *
 * FUNCTION: 
 * Functions for building the graphic user interface
 *
 */

#ifndef  __GUI_INIT_H__
#define  __GUI_INIT_H__

#include <gtk/gtk.h>
#include "crank.h"
#include "componant.h"

#define UNKNOWN_FITNESS (-1.0)
#define IS_UNKNOWN_FITNESS(x) (x < 0.0)

void rebuild_componant_gui(componant_type componant_type, double fitness_precalculated);
void handle_source_text_change(void);
void init_gui(int argc, char **argv);
void enter_gui(void);
void update_patch_description(void);

#endif  __GUI_INIT_H__
