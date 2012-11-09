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
 * common_monoalphabetic.h
 *
 * FUNCTION: 
 * Manipulation of monoalphabetic keys
 */

#include "crank.h"
#include "common_monoalphabetic.h"
#include <ctype.h>

char *apply_key_text(key *k, char *text) {
    char c, new_c;
    int i;
    char *newtext;
    int length = strlen(text);
    newtext = (char *) malloc((length + 1)  * sizeof(char));
    for (i = 0; i < length; i++) {
	c = text[i];
        if (!isalpha(c)) {
	    newtext[i] = c;
            continue;
        }
	c = toupper(c);
	new_c = (*k)[(int) c];
	if (new_c)
	    newtext[i] = new_c;
	else
	    newtext[i] = c;
    }
    newtext[i] = '\0';
    return newtext;
}


void key_identity(key *k) {
    char letter;
    for (letter = 'A'; letter <= 'Z'; letter++)
	(*k)[(int)letter] =  tolower(letter);
}

void key_copy(key *source_key, key *destination_key) {
    int i, j;
    for (i = 'A', j = 'A'; i <= 'Z'; (*destination_key)[i++] = (*source_key)[j++]) ; 
}

void key_swap(key *k, int index1, int index2) {
    char temp = (*k)[index1];
    (*k)[index1] = (*k)[index2];
    (*k)[index2] = temp;
}

void key_shift_L(key *k) {
    int i;
    char wrapchar = (*k)['A'];
    for (i = 1; i < 26; i++)
	(*k)[i + 'A' - 1] = (*k)[i + 'A'];
    (*k)['Z'] = wrapchar;
}

void key_shift_R(key *k) {
    int i;
    char wrapchar = (*k)['Z'];
    for (i = 24; i >=0 ; i--)
	(*k)[i + 'A' + 1] = (*k)[i + 'A'];
    (*k)['A'] = wrapchar;
}

void key_reverse(key *k) {
    int i;
    for (i = 0; i < 13; i++)
	key_swap(k, i + 'A', 25 - i + 'A');
}

void key_invert(key *k) {
    int i;
    key k2;
    int to_upper = 'A' - 'a';
    /* initialise k2 */
    for (i = 0; i < 26; i++)
	k2[i + 'A'] = 0;
    /* reverse pairs across k into k2 */
    for (i = 0; i < 26; i++) 
        if ((*k)[i + 'A'])
	    k2[((*k)[i + 'A']) + to_upper] = i + 'a';
    /* copy k2 into k */
    for (i = 0; i < 26; i++)
	(*k)[i + 'A'] = k2[i + 'A'];
}

void key_clear (key *k) {
    int i;
    for (i = 0; i < 26; i++)
	(*k)[i + 'A'] = 0;
}

void key_complete (key *k) {

    key to_count_list;
    int i;
    key from, to;
    int from_count = 0, to_count = 0;
    char fc, tc;
    
    /* Two inversions will make the key injective*/
    key_invert(k);
    key_invert(k);

    /* Now need to make it surjective */

    /* Blank to_count_list */
    for (i = 0; i < 26; i++)
	to_count_list[i] = 0;
    
    /* Construct from[], which lists all the unmapped 'from' letters */
    for (i = 0; i < 26; i++) {
	fc = i + 'A';
	tc = (*k)[(int)fc];
	if (tc)
	    to_count_list[(int)tc - 'a'] = TRUE;
	else {
	    from[from_count] = fc;
	    from_count++;
	}
    }
    /* From to_count_list, construct the unmapped 'to' letters */
    for (i = 0; i < 26; i ++) 
	if (!to_count_list[i]) {
	    to[to_count] = 'a' + i;
	    to_count++;
	}

    for (i = 0; i < to_count; i++)
	(*k)[(int)from[i]] = to[i];
}
