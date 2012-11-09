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
 * error.h
 *
 * FUNCTION: 
 * Error warnings and messages
 */

#ifndef  __ERROR_H__
#define  __ERROR_H__

#include "crank.h"
#include <stdio.h>

/*
 * TODO: Replace these macros
 * These macros aren't valid C - they use a GCC extension 
 */

#ifdef DISPLAY_DEBUG
#define debug(args...) printf(__FILE__":%d\n\t", __LINE__); printf(" "args)
#else  DISPLAY_DEBUG
#define debug(args...) 
#endif DISPLAY_DEBUG

#ifdef DISPLAY_INFO
#define info(args...) printf  (args)
#else  DISPLAY_INFO
#define info(args...) 
#endif DISPLAY_INFO

#ifdef DISPLAY_WARN
#define warn(args...) printf  ("Warning: " args)
#else  DISPLAY_WARN
#define warn(args...) 
#endif DISPLAY_WARN

#endif  __ERROR_H__ 
