/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "gui_generic_callbacks.h"
#include "gui_generic_interface.h"
#include "gui_support.h"

GtkWidget*
create_dummy_gui_generic_window (void)
{
  GtkWidget *dummy_gui_generic_window;
  GtkWidget *gui_generic_item;
  GtkWidget *scrolledwindow1;
  GtkWidget *gui_generic_clist;
  GtkWidget *label6;
  GtkWidget *label7;
  GtkWidget *gui_generic_table;
  GtkWidget *label8;
  GtkWidget *label9;
  GtkWidget *gui_generic_title_data_one;
  GtkWidget *gui_generic_title_data_two;
  GtkWidget *label12;
  GtkWidget *hbox2;
  GtkWidget *gui_generic_entry;
  GtkWidget *gui_generic_change_button;
  GtkWidget *gui_generic_description;
  GtkWidget *gui_generic_data_one;
  GtkWidget *gui_generic_data_two;
  GtkWidget *gui_generic_type;
  GtkWidget *label13;
  GtkWidget *gui_generic_default;

  dummy_gui_generic_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (dummy_gui_generic_window, "dummy_gui_generic_window");
  gtk_object_set_data (GTK_OBJECT (dummy_gui_generic_window), "dummy_gui_generic_window", dummy_gui_generic_window);
  gtk_window_set_title (GTK_WINDOW (dummy_gui_generic_window), "ERROR! You should not see this window");

  gui_generic_item = gtk_hbox_new (FALSE, 0);
  gtk_widget_set_name (gui_generic_item, "gui_generic_item");
  gtk_widget_ref (gui_generic_item);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_item", gui_generic_item,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_item);
  gtk_container_add (GTK_CONTAINER (dummy_gui_generic_window), gui_generic_item);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_name (scrolledwindow1, "scrolledwindow1");
  gtk_widget_ref (scrolledwindow1);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "scrolledwindow1", scrolledwindow1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (gui_generic_item), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gui_generic_clist = gtk_clist_new (2);
  gtk_widget_set_name (gui_generic_clist, "gui_generic_clist");
  gtk_widget_ref (gui_generic_clist);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_clist", gui_generic_clist,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_clist);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), gui_generic_clist);
  gtk_widget_set_usize (gui_generic_clist, 260, -2);
  gtk_clist_set_column_width (GTK_CLIST (gui_generic_clist), 0, 77);
  gtk_clist_set_column_width (GTK_CLIST (gui_generic_clist), 1, 80);
  gtk_clist_column_titles_show (GTK_CLIST (gui_generic_clist));

  label6 = gtk_label_new ("Name");
  gtk_widget_set_name (label6, "label6");
  gtk_widget_ref (label6);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "label6", label6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label6);
  gtk_clist_set_column_widget (GTK_CLIST (gui_generic_clist), 0, label6);

  label7 = gtk_label_new ("Value");
  gtk_widget_set_name (label7, "label7");
  gtk_widget_ref (label7);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "label7", label7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label7);
  gtk_clist_set_column_widget (GTK_CLIST (gui_generic_clist), 1, label7);

  gui_generic_table = gtk_table_new (6, 2, FALSE);
  gtk_widget_set_name (gui_generic_table, "gui_generic_table");
  gtk_widget_ref (gui_generic_table);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_table", gui_generic_table,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_table);
  gtk_box_pack_start (GTK_BOX (gui_generic_item), gui_generic_table, FALSE, FALSE, 0);
  gtk_widget_set_sensitive (gui_generic_table, FALSE);

  label8 = gtk_label_new ("Type:");
  gtk_widget_set_name (label8, "label8");
  gtk_widget_ref (label8);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "label8", label8,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label8);
  gtk_table_attach (GTK_TABLE (gui_generic_table), label8, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label8), 1, 0.5);

  label9 = gtk_label_new ("Description:");
  gtk_widget_set_name (label9, "label9");
  gtk_widget_ref (label9);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "label9", label9,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label9);
  gtk_table_attach (GTK_TABLE (gui_generic_table), label9, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label9), 1, 0.5);

  gui_generic_title_data_one = gtk_label_new ("");
  gtk_widget_set_name (gui_generic_title_data_one, "gui_generic_title_data_one");
  gtk_widget_ref (gui_generic_title_data_one);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_title_data_one", gui_generic_title_data_one,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_title_data_one);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_title_data_one, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_title_data_one), 1, 0.5);

  gui_generic_title_data_two = gtk_label_new ("");
  gtk_widget_set_name (gui_generic_title_data_two, "gui_generic_title_data_two");
  gtk_widget_ref (gui_generic_title_data_two);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_title_data_two", gui_generic_title_data_two,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_title_data_two);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_title_data_two, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_title_data_two), 1, 0.5);

  label12 = gtk_label_new ("Edit:");
  gtk_widget_set_name (label12, "label12");
  gtk_widget_ref (label12);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "label12", label12,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label12);
  gtk_table_attach (GTK_TABLE (gui_generic_table), label12, 0, 1, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label12), 1, 0.5);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_set_name (hbox2, "hbox2");
  gtk_widget_ref (hbox2);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "hbox2", hbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox2);
  gtk_table_attach (GTK_TABLE (gui_generic_table), hbox2, 1, 2, 5, 6,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  gui_generic_entry = gtk_entry_new ();
  gtk_widget_set_name (gui_generic_entry, "gui_generic_entry");
  gtk_widget_ref (gui_generic_entry);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_entry", gui_generic_entry,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_entry);
  gtk_box_pack_start (GTK_BOX (hbox2), gui_generic_entry, FALSE, FALSE, 0);

  gui_generic_change_button = gtk_button_new_with_label ("Change");
  gtk_widget_set_name (gui_generic_change_button, "gui_generic_change_button");
  gtk_widget_ref (gui_generic_change_button);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_change_button", gui_generic_change_button,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_change_button);
  gtk_box_pack_start (GTK_BOX (hbox2), gui_generic_change_button, FALSE, FALSE, 0);

  gui_generic_description = gtk_label_new (" n/a");
  gtk_widget_set_name (gui_generic_description, "gui_generic_description");
  gtk_widget_ref (gui_generic_description);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_description", gui_generic_description,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_description);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_description, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_description), 0, 0.5);

  gui_generic_data_one = gtk_label_new (" n/a");
  gtk_widget_set_name (gui_generic_data_one, "gui_generic_data_one");
  gtk_widget_ref (gui_generic_data_one);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_data_one", gui_generic_data_one,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_data_one);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_data_one, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_data_one), 0, 0.5);

  gui_generic_data_two = gtk_label_new (" n/a");
  gtk_widget_set_name (gui_generic_data_two, "gui_generic_data_two");
  gtk_widget_ref (gui_generic_data_two);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_data_two", gui_generic_data_two,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_data_two);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_data_two, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_data_two), 0, 0.5);

  gui_generic_type = gtk_label_new (" n/a");
  gtk_widget_set_name (gui_generic_type, "gui_generic_type");
  gtk_widget_ref (gui_generic_type);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_type", gui_generic_type,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_type);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_type, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_type), 0, 0.5);

  label13 = gtk_label_new ("Default:");
  gtk_widget_set_name (label13, "label13");
  gtk_widget_ref (label13);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "label13", label13,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label13);
  gtk_table_attach (GTK_TABLE (gui_generic_table), label13, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label13), 1, 0.5);

  gui_generic_default = gtk_label_new (" n/a");
  gtk_widget_set_name (gui_generic_default, "gui_generic_default");
  gtk_widget_ref (gui_generic_default);
  gtk_object_set_data_full (GTK_OBJECT (dummy_gui_generic_window), "gui_generic_default", gui_generic_default,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (gui_generic_default);
  gtk_table_attach (GTK_TABLE (gui_generic_table), gui_generic_default, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (gui_generic_default), 0, 0.5);

  gtk_signal_connect (GTK_OBJECT (gui_generic_clist), "select_row",
                      GTK_SIGNAL_FUNC (on_gui_generic_clist_select_row),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (gui_generic_change_button), "clicked",
                      GTK_SIGNAL_FUNC (on_gui_generic_button_clicked),
                      NULL);

  return dummy_gui_generic_window;
}
