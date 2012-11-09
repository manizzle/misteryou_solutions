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
 * files.c
 *
 * FUNCTION: 
 * File handling code
 *
 */


#include "files.h"
#include "error.h"

char *file_load_text(char *filename) {
    FILE *inf;
    int i = 0;
    int count = 0;
    char *text, c;
    inf = fopen(filename, "r");
    if (!inf) {
	warn("Unable to open file: %s\n", filename);
	return NULL;
    }
    
    /* Calculate size of file */
    while (getc(inf) != EOF)
	count++;
    fseek(inf, 0, 0);
    rewind(inf);

    text = malloc((count + 1) * sizeof(char));

    while ( (c = getc(inf)) != EOF)
	text[i++] = c;
    text[i] = '\0';

    fclose(inf);
    return text;
}

int file_save_text(char *filename, char *text) {
    FILE *otf;
    int i = 0;
    otf = fopen(filename, "w");
    if (!otf) {
	warn("Unable to open file: %s\n", filename);
	return FALSE;
    }
    while (text[i] != '\0')
	putc(text[i++], otf);

    fclose(otf);
    return TRUE;
}
