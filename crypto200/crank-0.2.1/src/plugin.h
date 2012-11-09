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
 * plugin.h
 *
 * FUNCTION: 
 * Wrap dynamic loading of modules, in case something other than GLIB
 * is wanted to be used.
 */

#ifndef  __PLUGIN_H__
#define  __PLUGIN_H__

#include <gmodule.h>

typedef GModule Module;
typedef gpointer pointer;
#define module_supported()       g_module_supported()
#define module_open(a, b)        g_module_open(a, b)
#define module_symbol(a, b, c)   g_module_symbol(a, b, c)
#define module_close(a)          g_module_close(a)
#define module_error()           g_module_error()


#endif  __PLUGIN_H__












