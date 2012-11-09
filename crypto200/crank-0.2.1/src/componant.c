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
 * componant.c
 *
 * FUNCTION: 
 * General componant handling
 */

#include "crank.h"
#include "componant.h"
#include "plugin.h"
#include "error.h"
#include <assert.h>

const char *componant_type_lookup(componant_type type) {
    switch (type) {
    case COMPONANT_TYPE_TRANSFORM:
	return "transform";
	break;
    case COMPONANT_TYPE_FITNESS:
	return "fitness";
	break;
    case COMPONANT_TYPE_HEURISTIC:
	return "heuristic";
	break;
    case COMPONANT_TYPE_GUI:
	return "gui";
	break;
    default:
	return "ERROR! UNKNOWN COMPONANT TYPE";
    }
}

void free_componant(componant *componant_record) {
    if (componant_record->module)
	module_close(componant_record->module);

    free(componant_record);
}

void free_componant_list(componant *componant_record) {
    if (!componant_record)
	return;
    if (componant_record->next)
	free_componant_list(componant_record->next);
    free(componant_record);
}

componant *lookup_componant(componant *componant_list, int number) {
    int i;
    componant *result = componant_list;
    assert(componant_list);
    for (i = 0; i < number; i++) 
	if (!(result = result->next)) {
	    warn("No such componant %d\n", number);
	    return NULL;
	}
    return result;
}

componant *lookup_componant_by_name(componant *componant_list, char *name) {
    componant *c = componant_list;
    char buf[1024];
    assert(c); assert(name);
    
    while (c) {
	sprintf(buf, "%s_%s", componant_type_lookup(c->type), c->name);
	if (!strcmp(buf, name))
	    return c;
	c = c->next;
    }
    return NULL;
}
