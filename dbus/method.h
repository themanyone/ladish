/* -*- Mode: C ; c-basic-offset: 2 -*- */
/*
 * LADI Session Handler (ladish)
 *
 * Copyright (C) 2008, 2009 Nedko Arnaudov <nedko@arnaudov.name>
 * Copyright (C) 2008 Juuso Alasuutari <juuso.alasuutari@gmail.com>
 *
 **************************************************************************
 * This file contains interface to D-Bus methods helpers
 **************************************************************************
 *
 * Licensed under the Academic Free License version 2.1
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

#ifndef __LASH_DBUS_METHOD_H__
#define __LASH_DBUS_METHOD_H__

struct dbus_method_call
{
  DBusConnection * connection;
  const char * method_name;
  DBusMessage * message;
  DBusMessage * reply;
  const struct dbus_interface_descriptor * iface;
  void * iface_context;
};

struct dbus_method_arg_descriptor
{
  const char * name;
  const char * type;
  const bool direction_in;      /* false == out, true == in */
};

typedef void (* dbus_method_handler)(struct dbus_method_call * call_ptr);

struct dbus_method_descriptor
{
  const char * name;
  const dbus_method_handler handler;
  const struct dbus_method_arg_descriptor * args;
};

void method_return_new_void(struct dbus_method_call * call_ptr);
void method_return_new_single(struct dbus_method_call * call_ptr, int type, const void * arg);
void method_return_new_valist(struct dbus_method_call * call_ptr, int type, ...);
bool method_return_verify(DBusMessage * msg, const char ** str);
bool method_iter_append_variant(DBusMessageIter *iter, int type, const void * arg);
bool method_iter_append_dict_entry(DBusMessageIter *iter, int type, const char * key, const void * value, int length);
void method_return_send(struct dbus_method_call * call_ptr);
void method_default_handler(DBusPendingCall * pending, void * data);
bool method_iter_get_dict_entry(DBusMessageIter * iter, const char ** key_ptr, void * value_ptr, int * type_ptr, int * size_ptr);

#define METHOD_ARGS_BEGIN(method_name, descr) \
static const struct dbus_method_arg_descriptor method_name ## _args_dtor[] = \
{

#define METHOD_ARG_DESCRIBE_IN(arg_name, arg_type, descr)       \
        {                                                       \
                .name = arg_name,                               \
                .type = arg_type,                               \
                .direction_in = true                            \
        },

#define METHOD_ARG_DESCRIBE_OUT(arg_name, arg_type, descr)      \
        {                                                       \
                .name = arg_name,                               \
                .type = arg_type,                               \
                .direction_in = false                           \
        },

#define METHOD_ARGS_END                                         \
        {                                                       \
                .name = NULL,                                   \
        }                                                       \
};

#define METHODS_BEGIN                                           \
static const struct dbus_method_descriptor methods_dtor[] =     \
{

#define METHOD_DESCRIBE(method_name, handler_name)              \
        {                                                       \
                .name = # method_name,                          \
                .handler = handler_name,                        \
                .args = method_name ## _args_dtor               \
        },

#define METHODS_END                                             \
        {                                                       \
                .name = NULL,                                   \
                .handler = NULL,                                \
                .args = NULL                                    \
        }                                                       \
};

#endif /* __LASH_DBUS_METHOD_H__ */
