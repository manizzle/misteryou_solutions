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
 * crank.h
 *
 * FUNCTION: 
 * program-wide definitions
 */

#ifndef __CRANK_H__
#define __CRANK_H__

#include <config.h>
#include <stdlib.h>

/* Shouldn't really be included in everything, but for now...*/
#include <stdio.h>

#ifndef TRUE
#define TRUE  1
#endif /* TRUE */
#ifndef FALSE
#define FALSE 0
#endif /* FALSE */

#define LARGE_FITNESS 1000.0

#ifndef DISPLAY_DEBUG
#define NDEBUG
#endif

#include <gtk/gtk.h>
typedef GtkWidget gui_item;

#endif __CRANK_H__
