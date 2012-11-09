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

#ifndef __COMMON_MONOALPHABETIC_H__
#define __COMMON_MONOALPHABETIC_H__

#define UPPER_KEY_BOUND ((int) ('Z' + 1))
typedef char key[UPPER_KEY_BOUND];

/*
 * apply_key_text() applies a monoalphabetic transformation to some text 
 * Arguments: k    - key to use 
 *            text - string to transform
 * Returns:   newly allocated string as a result of the transform 
 */
char *apply_key_text(key *k, char *text);

/* 
 * key_identity() turns a key into a identity transformation
 * Arguments: k - key to work on 
 */
void key_identity(key *k);

/*
 * key_copy() copies one key into another
 * Arguments: source_key      - key to read from
 *            destination_key - key to write into
 */
void key_copy(key *source_key, key *destination_key);

/* 
 * key_swap() swaps the values of a key at two indices 
 * Arguments: k      - key to swap values for
 *            index1 - from 'A' to 'Z'
 *            index2 - from 'A' to 'Z'
 */
void key_swap(key *k, int index1, int index2);

/* 
 * key_shift_L() and key_shift_R() both take a key and move the values 
 * corresponding to the alphabet one place to the left and right, wrapping
 * round if needed. So val(Z) <= val(A), val(A) <= val(B) etc. would 
 * be produced by a left shift.
 * Arguments: k - key to work on
 */
void key_shift_L(key *k);
void key_shift_R(key *k);

/* 
 * key_reverse() reverses the order of the values corresponding to 
 * the alphabet in a key, so val(A) <= val(Z), val(B) <= val(Y) and so
 * on.
 * Arguments: k - key to work on
 */
void key_reverse(key *k);  

/* 
 * key_invert() produces the key corresponding to the inverse 
 * transformation specified by the given argument. 
 * Arguments: k - key to invert
 */
void key_invert(key *k);

/* 
 * key_clear() maps the entire alphabet onto the blank character 
 * Arguments: k - key to clear 
 */
void key_clear (key *k);

/* key_complete() fills up any letters that map to blank characters
 * with whatever letters are spare, and makes sure no letters are
 * mapped to twice. In other words, it tweaks the key to make it
 * a bijection.
 * Arguments: k - key to complete
 */ 
void key_complete (key *k);

#endif  __COMMON_MONOALPHABETIC_H__
