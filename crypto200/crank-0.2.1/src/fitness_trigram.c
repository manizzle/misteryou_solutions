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
 * fitness_trigram.c
 *
 * FUNCTION: 
 * fitness function using expected statistical properties of clumps of letters of width 3 (trigrams) 
 */


#include "crank.h"
#include "componant.h"
#include "error.h"
#include "common_trigram.h"
#include "instance.h"
#include <assert.h>
#include <string.h>

#ifdef BUILD_DYNAMIC
#define SYM(symbol) symbol
#else  BUILD_DYNAMIC
#define SYM(symbol) fitness_trigram_ ## symbol
#endif BUILD_DYNAMIC

/* Componant-wide state */
static double *slft_std;    /* Standard unigram table */
static double *bift_std;    /* Standard bigram table */
static double *trift_std;   /* Standard trigram table */

/** Common componant interface **********************/

const componant_type SYM(type) = COMPONANT_TYPE_FITNESS;
const char SYM(name)[] = "trigram";
const char SYM(description)[] = "A fitness function using the expected statistical properties of clumps of 3 letters (trigrams)";

#define NUM_PARAMS 3
#define PARAM_UNIGRAM_WEIGHT 0
#define PARAM_BIGRAM_WEIGHT  1
#define PARAM_TRIGRAM_WEIGHT 2

const int SYM(number_of_parameters) = NUM_PARAMS;
const parameter_description SYM(parameter_description_table)[NUM_PARAMS] = { 

/*  |Parameter Type |Label | Names of values (in enum)                              |na|default|Description          | */
/*  |---------------|------|--------------------------------------------------------|--|-------|---------------------| */
    {PARAM_TYPE_FLOAT, "Weight-1", "0.0", "", "1.0", "Weight assigned to unigrams (n=1)"},
    {PARAM_TYPE_FLOAT, "Weight-2", "0.0", "", "1.0", "Weight assigned to bigrams  (n=2)"},
    {PARAM_TYPE_FLOAT, "Weight-3", "0.0", "", "1.0", "Weight assigned to trigrams (n=3)"}
/*  |---------------|------|--------------------------------------------------------|--|------|----------------------| */

};

int SYM(boot)(void) { 

    /* Load 3-gram tables */
    slft_std = load_slft(DATADIR "/slft.dat");
    if (!slft_std) return FALSE;
    bift_std = load_bift(DATADIR "/bift.dat");
    if (!bift_std) return FALSE;
    trift_std = load_trift(DATADIR "/trift.dat");
    if (!trift_std) return FALSE;

    return TRUE; 
}

/** Fitness specific interface ********************/

double SYM(fitness)(instance *fitness, char *text) {
    double *slft, *bift, *trift, unigram_weight, bigram_weight, trigram_weight;
    double fitness_value;
    assert(fitness); assert(text); assert(fitness->componant_class->type == COMPONANT_TYPE_FITNESS);

    unigram_weight = * (double *) peek_param(fitness, PARAM_UNIGRAM_WEIGHT);
    bigram_weight  = * (double *) peek_param(fitness, PARAM_BIGRAM_WEIGHT);
    trigram_weight = * (double *) peek_param(fitness, PARAM_TRIGRAM_WEIGHT);
    
    make_ft(text, &slft, &bift, &trift);
    
    fitness_value =    unigram_weight * slft_error(slft_std, slft)
                     + bigram_weight  * bift_error(bift_std, bift)
                     + trigram_weight * trift_error(trift_std, trift);
    free(slft); free(bift); free(trift);
    return fitness_value;
}
