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
 * scheme_interface.c
 *
 * FUNCTION: 
 * Interface for Guile to work with
 */

/* NOTE: This is just me experimenting with Guile, and so sucks much.
 * It will get replaced as soon as I figure out how everything works.
 * (or else I'll use a wrapper generator)
 */

#include "scheme_interface.h"
#include "crank.h"
#include "error.h"
#include <gtk/gtk.h>
#ifdef HAVE_LIBGUILE
#include <libguile.h>
#endif /* HAVE_LIBGUILE */
#include "componant.h"
#include "gui_init.h"
#include "globals.h"
#include "gui_globals.h"
#include "instance.h"
#include <assert.h>
#include <guile/gh.h>

extern void SWIG_init(void);

/* Store these away in case we want to enter the GUI */
static int store_argc;
static char **store_argv;

/* Is the GUI active? */
int is_gui_active = FALSE;

void start_gui(void) {
    init_gui(store_argc, store_argv);
}

void flush_gui(void) {
    while (gtk_events_pending())
	gtk_main_iteration();
}

void post_cleanup_gui(void) {
    if (get_main_window())
	gtk_widget_destroy(get_main_window());
    if (get_heuristic_log())
	gtk_widget_destroy(get_heuristic_log());

    clear_gui_globals();
    flush_gui();
}

void enter_shell(void) {
    info("\nCrank via Guile\n");
    info("---------------\n\n");
    info("(run-gui) - builds the graphical user interface and enters it\n");
    info("(enter-gui) - leaves Guile and (re)enters GUI \n");
    info("(post-cleanup-gui) - removes any windows etc\n");
    info("(quit) - stops Crank\n");
    info("\n");
    scm_shell(store_argc, store_argv);

}

void inner_main(void *closure, int argc, char **argv) {
    store_argc = argc;
    store_argv = argv;

    SWIG_init();

    gh_eval_file(DATADIR "/scheme/crank.scm");
    
    enter_shell();
    return;
}


void *int2void(int i) { int *i_p = malloc(sizeof(int)); *i_p = i; return i_p; }
void *double2void(double d) { double *d_p = malloc(sizeof(double)); *d_p = d; return d_p; }
void *string2void(char *txt) { char *copy = malloc(strlen(txt) + 1); return strcpy(copy, txt); }

int void2int(void *v) { assert(v); return * (int *) v; }
double void2double(void *v) { assert(v); return * (double *) v; }
char *void2string(void *v) { return (char *) v; }

static instance *returned_instance;

void set_returned_instance(instance *i) {
    assert(i);
    returned_instance = i;
}
instance *get_returned_instance(void) {
    return(returned_instance);
}
