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
 * register-componant.h
 *
 * FUNCTION: 
 * Build up list of componants from plugin directory or otherwise
 */

#ifndef __REGISTER_COMPONANT_H__
#define __REGISTER_COMPONANT_H__

#include "componant.h"

/* 
 * register_componants() scans the plugin directory and loads 
 * internal componants.
 * Arguments: output_list - location to place componant array
 * Returns:   number of componants loaded
 */
int register_componants(componant **output_list);

#endif  __REGISTER_COMPONANT_H__





