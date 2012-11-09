%module crank_swig
%{
#include "gtk/gtk.h"
#include "crank.h"
#include "componant.h"
#include "parameter.h"
#include "files.h"

/* Return new instance of a componant */
instance *make_new_instance(struct componant *componant_class);

/* Return a copy of the instance */
instance *duplicate_instance(instance *i);

/* Deallocate instance */
void free_instance(instance *i); 

/* Change a parameter of an instance */
void poke_param(instance *i, int param_index, void *value_ptr);

/* Query a parameter of an instance */
void *peek_param(instance *i, int param_index);

/* Request a parameter dump from an instance */
char *dump_parameters(instance *i);
    
/* Set an instance from a parameter set */
instance *instantiate_parameters(char *parameter_string);

/** transform componant specific *******/

char *transform(instance *transform, char *text);

/** fitness componant specific *******/

double fitness(instance *fitness, char *text);

/** gui componant specific *******/

gui_item *build_gui_item(instance *gui, instance *i); 

int fact(int n);
componant *lookup_componant(componant *, int n);
const char *componant_type_lookup(componant_type type);
void free_componant(componant *componant_record);
void free_componant_list(componant *componant_list);

instance *get_current_transform(void);
instance *get_current_heuristic(void);
instance *get_current_fitness(void);
instance *get_current_gui_transform(void);
instance *get_current_gui_heuristic(void);
instance *get_current_gui_fitness(void);
void set_current_transform(instance *i);
void set_current_heuristic(instance *i);
void set_current_fitness(instance *i);
void set_current_gui_transform(instance *i);
void set_current_gui_heuristic(instance *i);
void set_current_gui_fitness(instance *i);

componant *get_componant_list(void);
void set_componant_list(componant *componant_list);

int get_number_of_componants(void);
void set_number_of_componants(int number_of_componants);

void clear_gui_globals(void);

GtkWidget *get_heuristic_log(void);
void set_heuristic_log(GtkWidget *heuristic_log);

int get_stop_heuristic(void);
void set_stop_heuristic(int stop_heuristic);

GtkWidget *get_current_transform_gui(void);
void set_current_transform_gui(GtkWidget *current_transform_gui);
GtkWidget *get_current_heuristic_gui(void);
void set_current_heuristic_gui(GtkWidget *current_heuristic_gui);
GtkWidget *get_current_fitness_gui(void);
void set_current_fitness_gui(GtkWidget *current_fitness_gui);


GtkWidget *get_main_window(void);
void set_main_window(GtkWidget *main_window);

instance **get_componant_choice_install_here(void);
void set_componant_choice_install_here(char *id_string);

componant *get_componant_choice_clist_selected_componant(void);
void set_componant_choice_clist_selected_componant(componant *);

void lock_callbacks(void);
void unlock_callbacks(void);
int islocked(void);

char *parameter_enum_value_name(parameter_description *param_descrip, int value_index);
const char *parameter_type_lookup(parameter_type type);

char *file_load_text(char *filename);
int file_save_text(char *filename, char *text);

void enter_gui(void);
void start_gui(void);
void flush_gui(void);
void post_cleanup_gui(void);

void *int2void(int i);
void *double2void(double d);
void *string2void(char *txt);

int void2int(void *v);
double void2double(void *v);
char *void2string(void *v);

componant *lookup_componant_by_name(componant *componant_list, char *name) ;

int parameter_get_default_int_or_enum(parameter_description *param_descrip);
double parameter_get_default_double(parameter_description *param_descrip);
char *parameter_get_default_string(parameter_description *param_descrip);

void set_returned_instance(instance *i);
instance *get_returned_instance(void);

char *generate_patch(instance *transform, instance *heuristic, instance *fitness,
		     instance *gui_transform, instance *gui_heuristic, instance *gui_fitness,
		     char *name, char *description);

%}

/* Return new instance of a componant */
instance *make_new_instance(struct componant *componant_class);

/* Return a copy of the instance */
instance *duplicate_instance(instance *i);

/* Deallocate instance */
void free_instance(instance *i); 

/* Change a parameter of an instance */
void poke_param(instance *i, int param_index, void *value_ptr);

/* Query a parameter of an instance */
void *peek_param(instance *i, int param_index);

/* Request a parameter dump from an instance */
char *dump_parameters(instance *i);
    
/* Set an instance from a parameter set */
instance *instantiate_parameters(char *parameter_string);

/** transform componant specific *******/

char *transform(instance *transform, char *text);

/** fitness componant specific *******/

double fitness(instance *fitness, char *text);

/** gui componant specific *******/

gui_item *build_gui_item(instance *gui, instance *i); 

struct parameter_description {
    enum parameter_type type;
    char *name;
    char *data_one;
    char *data_two;
    char *default_value;
    char *description;
};

struct instance {

    /* The componant class for the instance */
    struct componant *componant_class;

    /* The parameter values associated with an instance, stored as an array of void pointers */
    void **parameters;

    /* Whatever information the instance wants to store in itself */
    void *data; 

};

/* Record for componant information */
struct componant {
    
    /* Filename associated with componant (or else "hardcoded") */
    char *filename;
    
    /* Unique string identifying componant */
    char *name;          
    
    /* A componant's type determines its use by Crank */
    enum componant_type type;

    /* String user can read as a summary of componant's behaviour */
    char *description; 
    
    /* Number of parameters in description table */
    int number_of_parameters;

    /* Description of parameters taken by componant */
    parameter_description *parameter_description_table; 
    
    /* Next pointer for use when record is in linked list */
    struct componant *next;

};


componant *lookup_componant(componant *componant_list, int n);
const char *componant_type_lookup(enum componant_type type);
void free_componant(componant *componant_record);
void free_componant_list(componant *componant_list);

instance *get_current_transform(void);
instance *get_current_heuristic(void);
instance *get_current_fitness(void);
instance *get_current_gui_transform(void);
instance *get_current_gui_heuristic(void);
instance *get_current_gui_fitness(void);
void set_current_transform(instance *i);
void set_current_heuristic(instance *i);
void set_current_fitness(instance *i);
void set_current_gui_transform(instance *i);
void set_current_gui_heuristic(instance *i);
void set_current_gui_fitness(instance *i);

componant *get_componant_list(void);
void set_componant_list(componant *componant_list);

int get_number_of_componants(void);
void set_number_of_componants(int number_of_componants);

void clear_gui_globals(void);

GtkWidget *get_heuristic_log(void);
void set_heuristic_log(GtkWidget *heuristic_log);

int get_stop_heuristic(void);
void set_stop_heuristic(int stop_heuristic);

GtkWidget *get_current_transform_gui(void);
void set_current_transform_gui(GtkWidget *current_transform_gui);
GtkWidget *get_current_heuristic_gui(void);
void set_current_heuristic_gui(GtkWidget *current_heuristic_gui);
GtkWidget *get_current_fitness_gui(void);
void set_current_fitness_gui(GtkWidget *current_fitness_gui);


GtkWidget *get_main_window(void);
void set_main_window(GtkWidget *main_window);

instance **get_componant_choice_install_here(void);
void set_componant_choice_install_here(char *id_string);

componant *get_componant_choice_clist_selected_componant(void);
void set_componant_choice_clist_selected_componant(componant *);

void lock_callbacks(void);
void unlock_callbacks(void);
int islocked(void);

char *parameter_enum_value_name(parameter_description *param_descrip, int value_index);
const char *parameter_type_lookup(enum parameter_type type);

char *file_load_text(char *filename);
int file_save_text(char *filename, char *text);

void enter_gui(void);
void start_gui(void);
void flush_gui(void);
void post_cleanup_gui(void);

void *int2void(int i);
void *double2void(double d);
void *string2void(char *txt);

int void2int(void *v);
double void2double(void *v);
char *void2string(void *v);

componant *lookup_componant_by_name(componant *componant_list, char *name);

int parameter_get_default_int_or_enum(parameter_description *param_descrip);
double parameter_get_default_double(parameter_description *param_descrip);
char *parameter_get_default_string(parameter_description *param_descrip);

void set_returned_instance(instance *i);
instance *get_returned_instance(void);

char *generate_patch(instance *transform, instance *heuristic, instance *fitness,
		     instance *gui_transform, instance *gui_heuristic, instance *gui_fitness,
		     char *name, char *description);
