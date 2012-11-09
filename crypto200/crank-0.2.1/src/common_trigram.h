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
 * common_trigram.h
 *
 * FUNCTION: 
 * Use of trigram and below frequency data 
 */

#ifndef __COMMON_TRIGRAM_H__
#define __COMMON_TRIGRAM_H__

double slft_error(double *slft_std, double *slft_sample);
double bift_error(double *bift_std, double *bift_sample);
double trift_error(double *trift_std, double *trift_sample);
int make_ft(char *text, double **slft, double **bift, double **trift);
double *load_slft(char *filename);
double *load_bift(char *filename);
double *load_trift(char *filename);

#endif __COMMON_TRIGRAPH_H__
