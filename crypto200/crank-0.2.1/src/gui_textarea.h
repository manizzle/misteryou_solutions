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
 * gui_textarea.h
 *
 * FUNCTION: 
 * Accessing the gui text areas
 *
 */

#ifndef  __GUI_TEXTAREA_H__
#define  __GUI_TEXTAREA_H__

#include "crank.h"

void set_source_text_gui(gui_item *source_text_gui);
void set_source_text(char *text);
char *get_source_text(void);

void set_view_text_gui(gui_item *view_text_gui);
void set_view_text(char *text);
char *get_view_text(void);

#endif  /* __GUI_TEXTAREA_H__ */
