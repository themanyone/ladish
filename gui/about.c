/* -*- Mode: C ; c-basic-offset: 2 -*- */
/*
 * LADI Session Handler (ladish)
 *
 * Copyright (C) 2010 Nedko Arnaudov <nedko@arnaudov.name>
 *
 **************************************************************************
 * This file contains the code that implements the about dialog
 **************************************************************************
 *
 * LADI Session Handler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LADI Session Handler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LADI Session Handler. If not, see <http://www.gnu.org/licenses/>
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "about.h"
#include "pixbuf.h"
#include "gtk_builder.h"
#include "version.h"

#define ABOUT_DIALOG_LOGO     "ladish-logo-128x128.png"

static char * read_file_contents(const char * filename)
{
  int fd;
  struct stat st;
  char * buffer;

  if (stat(filename, &st) != 0)
  {
    return NULL;
  }

  fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    return NULL;
  }

  buffer = malloc(st.st_size + 1);
  if (buffer == NULL)
  {
    close(fd);
    return NULL;
  }

  if (read(fd, buffer, (size_t)st.st_size) != (ssize_t)st.st_size)
  {
    free(buffer);
    buffer = NULL;
  }
  else
  {
    buffer[st.st_size] = 0;
  }

  close(fd);

  return buffer;
}

void show_about(void)
{
  GtkWidget * dialog;
  GdkPixbuf * pixbuf;
  const char * authors[] = {"Nedko Arnaudov", "Nikita Zlobin", NULL};
  const char * artists[] = {"Lapo Calamandrei", "Nadejda Pancheva-Arnaudova", NULL};
  char * license;
  struct stat st;
  char timestamp_str[26];
  char built_str[200];

  pixbuf =  load_pixbuf(ABOUT_DIALOG_LOGO);
  license = read_file_contents(DATA_DIR "/COPYING");

  dialog = get_gtk_builder_widget("about_win");

  st.st_mtime = 0;
  stat("/proc/self/exe", &st);
  ctime_r(&st.st_mtime, timestamp_str);
  timestamp_str[24] = 0;

  sprintf(built_str,"gladish is built on %s from %s", timestamp_str, GIT_VERSION);

  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), PACKAGE_VERSION);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), built_str);

  if (pixbuf != NULL)
  {
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf);
  }

  if (license != NULL)
  {
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), license);
    free(license);
  }

  gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
  gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(dialog), artists);

  gtk_widget_show(dialog);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_hide(dialog);
}
