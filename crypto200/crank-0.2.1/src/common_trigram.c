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
 * common_trigram.c
 *
 * FUNCTION: 
 * Use of trigram and below frequency data 
 */

#include "crank.h"
#include "common_trigram.h"
#include <ctype.h>
#include "error.h"

double slft_error(double *slft_std, double *slft_sample) {
    int i; double error = 0.0, diff;
    for (i = 'A'; i <= 'Z'; i++) {
	diff = slft_std[i] - slft_sample[i];
	error += diff * diff;
    }
    return error;
}

double bift_error(double *bift_std, double *bift_sample) {
    int i, j; double error = 0.0, diff;
    for (i = 'A'; i <= 'Z'; i++) {    
	for (j = 'A'; j <= 'Z'; j++) {
	diff = (bift_std + 26 * i)[j] - (bift_sample + 26 * i)[j]; 
	error += diff * diff;
	}
    }
    return error;
}

double trift_error(double *trift_std, double *trift_sample) {
    int i, j, k; double error = 0.0, diff;
    for (i = 'A'; i <= 'Z'; i++) {    
	for (j = 'A'; j <= 'Z'; j++) {
	    for (k = 'A'; k <= 'Z'; k++) {
		diff = (trift_std + 26 * 26 * i + 26 * j)[k] - (trift_sample + 26 * 26 * i + 26 * j)[k]; 
		error += diff * diff;
	    }
	}
    }
    return error;
}

/* Make frequency tables */
int make_ft(char *text, double **slft, double **bift, double **trift) {
    
    int length = strlen(text), i, j, k, slft_total = 0, bift_total = 0, trift_total = 0;
    char c, pc = 0, ppc = 0;
    int islft[(int) 'Z' + 1];
    int ibift[(int) 'Z' + 1][(int) 'Z' + 1];
    int itrift[(int) 'Z' + 1][(int) 'Z' + 1][(int) 'Z' + 1];

    *slft = malloc(((int) 'Z' + 1) * sizeof(double));
    *bift = malloc(((int) 'Z' + 1) * ((int) 'Z' + 1)  * sizeof(double));
    *trift = malloc(((int) 'Z' + 1) * ((int) 'Z' + 1) * ((int) 'Z' + 1) * sizeof(double));

    for (i = (int) 'A'; i <= (int) 'Z'; i++) {
	for (j = (int) 'A'; j <= (int) 'Z'; j++) {
	    for (k = (int) 'A'; k <= (int) 'Z'; k++)
		itrift[i][j][k] = 0;
	    ibift[i][j] = 0;
	}
	islft[i] = 0;
    }
    for (i = 0; i < length; i++) {
	c = text[i];
	if (!isalpha(c))
	    continue;
	c = toupper(c);
	
	islft[(int) c] += 1; slft_total++;
	if (pc) {
	    ibift[(int) pc][(int) c] += 1;
	    bift_total++;
	}
	if (pc & ppc) {
	    itrift[(int) ppc][(int) pc][(int) c] += 1;
	    trift_total++;
	}
	ppc = pc; pc = c;
    }
    for (i = (int) 'A'; i <= (int) 'Z'; i++) {
	for (j = (int) 'A'; j <= (int) 'Z'; j++) {
	    for (k = (int) 'A'; k <= (int) 'Z'; k++) 
		(*trift + 26 * 26 * i + 26 * j)[k] = (double) itrift[i][j][k] / (double) trift_total;
	    (*bift + 26 * i)[j] = (double) ibift[i][j] / (double) bift_total;
	}
	(*slft)[i] = (double) islft[i] / (double) slft_total;
    }	
    return slft_total; /* i.e. letter_count */
}


/* Stats file IO */
/* ------------- */

/* Load default fts */
double *load_slft(char *filename) { 
    FILE *inf;
    int i;
    double *slft = malloc(((int) 'Z' + 1) * sizeof(double));
    
    inf = fopen(filename, "r");
    if (!inf) {
	warn("Error opening default 1-gram frequency table: %s\n", filename);
	return NULL;
    } else {
	for (i = 'A'; i <= 'Z'; i++) {
	    if(!(fscanf(inf, "%lf", &(slft[i])) == 1)) {
		warn("Error opening default 1-gram frequency table: %s\n", filename);
		fclose(inf);
		return NULL;
	    }
	}
	fclose(inf);
    }

    return slft;
}

double *load_bift(char *filename) { 
    FILE *inf;
    int i, j;
    double *bift = malloc(((int) 'Z' + 1) * ((int) 'Z' + 1) * sizeof(double));
    
    inf = fopen(filename, "r");
    if (!inf) {
	warn("Error opening default 2-gram frequency table: %s\n", filename);
	return NULL;
    } else {
	
	for (i = 'A'; i <= 'Z'; i++) {
	    for (j = 'A'; j <= 'Z'; j++) {
		if(!(fscanf(inf, "%lf", &((bift + 26 * i)[j])) == 1)) {
		    warn("Error opening default 2-gram frequency table: %s\n", filename);
		    fclose(inf);
		    return NULL;
		}
	    }
	}
    }
    fclose(inf);
    return bift;
}

double *load_trift(char *filename) { 
    FILE *inf;
    int i, j, k;
    double *trift = malloc(((int) 'Z' + 1) * ((int) 'Z' + 1) * ((int) 'Z' + 1) * sizeof(double));
    
    inf = fopen(filename, "r");
    if (!inf) {
	warn("Error opening default 3-gram frequency table: %s\n", filename);
	return NULL;
    } else {
	for (i = 'A'; i <= 'Z'; i++) {
	    for (j = 'A'; j <= 'Z'; j++) {
		for (k = 'A'; k <= 'Z'; k++) {
		    if(!(fscanf(inf, "%lf", &((trift + 26 * 26 * i + 26 * j)[k])) == 1)) {
			warn("Error opening default 3-gram frequency table: %s\n", filename);
			fclose(inf);
			return NULL;
		    }
		}
	    }
	}
	fclose(inf);
    }
    
    return trift;
}
