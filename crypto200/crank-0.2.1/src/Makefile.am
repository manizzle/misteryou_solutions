## Process this file with automake to produce Makefile.in

SUBDIRS = scheme

bin_PROGRAMS = crank

EXTRA_DIST = crank.glade crank.i

## Source files needed just by Crank, no componants
common_crank_sources = main.c register_componant.c parameter.c componant.c instance.c null_componant.c globals.c files.c \
                       crank.h componant.h error.h parameter.h register_componant.h plugin.h instance.h globals.h files.h \
                       gui_callbacks.c gui_interface.c gui_support.c gui_init.c gui_globals.c gui_textarea.c \
                       gui_callbacks.h gui_interface.h gui_support.h gui_init.h gui_globals.h gui_textarea.h \
                       patch.c patch.h 

## The sources used by componants
componant_sources =  transform_monoalphabetic.c \
                common_monoalphabetic.c common_monoalphabetic.h \
                fitness_trigram.c \
                common_trigram.c common_trigram.h \
                heuristic_random.c \
                common_constraint_parse.c common_constraint_parse.h \
                heuristic_hillclimbing.c \
                heuristic_simulated_annealing.c \
                gui_generic.c gui_generic_interface.h gui_generic_interface.c  gui_generic_callbacks.h gui_generic_callbacks.c \
                transform_transposition_grid.c \
                common_transposition_grid.c common_transposition_grid.h 

## The sources that are totally Guile dependant
guile_only_sources = crank_wrap.c scheme_interface.c scheme_interface.h

if BUILD_DYNAMIC	

plugin_LTLIBRARIES = libtransform_monoalphabetic.la  \
                     libfitness_trigram.la           \
                     libheuristic_random.la          \
                     libheuristic_hillclimbing.la    \
                     libgui_generic.la               \
                     libheuristic_simulated_annealing.la \
                     libtransform_transposition_grid.la
libtransform_monoalphabetic_la_SOURCES = transform_monoalphabetic.c common_monoalphabetic.c common_monoalphabetic.h crank.h componant.h
libfitness_trigram_la_SOURCES = fitness_trigram.c common_trigram.c common_trigram.h crank.h componant.h
libheuristic_random_la_SOURCES = heuristic_random.c common_constraint_parse.c common_constraint_parse.h crank.h componant.h
libheuristic_hillclimbing_la_SOURCES = heuristic_hillclimbing.c common_constraint_parse.c common_constraint_parse.h crank.h componant.h
libgui_generic_la_SOURCES = gui_generic.c crank.h componant.h gui_generic_interface.h gui_generic_interface.c gui_generic_callbacks.h gui_generic_callbacks.c 
libheuristic_simulated_annealing_la_SOURCES = heuristic_hillclimbing.c common_constraint_parse.c common_constraint_parse.h crank.h componant.h
libtransform_transposition_grid_la_SOURCES = transform_transposition_grid.c common_transposition_grid.c common_transposition_grid.h crank.h componant.h
if WITH_GUILE
crank_SOURCES = $(common_crank_sources) $(guile_only_sources)
else
crank_SOURCES = $(common_crank_sources)
endif

else

## Crank + componants
if WITH_GUILE
crank_SOURCES = $(common_crank_sources) $(guile_only_sources) $(componant_sources)
else
crank_SOURCES = $(common_crank_sources) $(componant_sources)
endif

endif

plugindir = $(pkglibdir)/plugins
INCLUDES = -DPLUGINDIR=\""$(plugindir)"\" -DDATADIR=\""$(pkgdatadir)"\"
CFLAGS = @CFLAGS@ @GTK_CFLAGS@ -Wall
##CFLAGS = @GTK_CFLAGS@ -Wall -g
LIBS = @LIBS@ @GTK_LIBS@