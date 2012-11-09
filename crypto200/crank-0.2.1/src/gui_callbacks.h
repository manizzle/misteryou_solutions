#include <gtk/gtk.h>


void
on_open3_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_exit2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_choose_componant_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_componant_choice_list_select_row    (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_componant_choice_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_componant_choice_ok_button_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_source_text_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_equate                              (GtkButton       *button,
                                        gpointer         user_data);

void
on_start_heuristic                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_about_ok_button_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_open                                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save                                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open_file_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_open_file_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_save_file_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_save_file_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_stop_heuristic                      (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_heuristic_log_delete_event          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_guile_shell_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_patch_combo_entry_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_patch_apply_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);
