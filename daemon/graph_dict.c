/* -*- Mode: C ; c-basic-offset: 2 -*- */
/*
 * LADI Session Handler (ladish)
 *
 * Copyright (C) 2009 Nedko Arnaudov <nedko@arnaudov.name>
 *
 **************************************************************************
 * This file contains interface to the D-Bus graph dict interface helpers
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

#include "graph_dict.h"
#include "../dbus/error.h"
#include "../dbus_constants.h"
#include "graph.h"
#include "dict.h"

#define graph_handle ((ladish_graph_handle)call_ptr->iface_context)

bool find_dict(struct dbus_method_call * call_ptr, uint32_t object_type, uint64_t object_id, ladish_dict_handle * dict_handle_ptr)
{
  ladish_client_handle client;
  ladish_port_handle port;
  ladish_dict_handle dict;

  switch (object_type)
  {
  case GRAPH_DICT_OBJECT_TYPE_GRAPH:
    *dict_handle_ptr = ladish_graph_get_dict(graph_handle);
    return true;
  case GRAPH_DICT_OBJECT_TYPE_CLIENT:
    client = ladish_graph_find_client_by_id(graph_handle, object_id);
    if (client == NULL)
    {
      lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "cannot find client %"PRIu64".", object_id);
      return false;
    }
    *dict_handle_ptr = ladish_client_get_dict(client);
    return true;
  case GRAPH_DICT_OBJECT_TYPE_PORT:
    port = ladish_graph_find_port_by_id(graph_handle, object_id);
    if (port == NULL)
    {
      lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "cannot find port %"PRIu64".", object_id);
      return false;
    }
    *dict_handle_ptr = ladish_port_get_dict(port);
    return true;
  case GRAPH_DICT_OBJECT_TYPE_CONNECTION:
    dict = ladish_graph_get_connection_dict(graph_handle, object_id);
    if (dict == NULL)
    {
      lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "cannot find connection %"PRIu64".", object_id);
    }

    *dict_handle_ptr = dict;
    return false;
  }

  lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "find_dict() not implemented for object type %"PRIu32".", object_type);
  return false;
}

#undef graph_handle

void ladish_dict_set_dbus(struct dbus_method_call * call_ptr)
{
  uint32_t object_type;
  uint64_t object_id;
  ladish_dict_handle dict;
  const char * key;
  const char * value;

  if (!dbus_message_get_args(
        call_ptr->message,
        &g_dbus_error,
        DBUS_TYPE_UINT32, &object_type,
        DBUS_TYPE_UINT64, &object_id,
        DBUS_TYPE_STRING, &key,
        DBUS_TYPE_STRING, &value,
        DBUS_TYPE_INVALID))
  {
    lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s",  call_ptr->method_name, g_dbus_error.message);
    dbus_error_free(&g_dbus_error);
    return;
  }

  if (!find_dict(call_ptr, object_type, object_id, &dict))
  {
    return;
  }

  log_info("%s <- %s", key, value);

  if (!ladish_dict_set(dict, key, value))
  {
    lash_dbus_error(call_ptr, LASH_DBUS_ERROR_GENERIC, "ladish_dict_set(\"%s\", \"%s\") failed.");
    return;
  }

  method_return_new_void(call_ptr);
}

void ladish_dict_get_dbus(struct dbus_method_call * call_ptr)
{
  uint32_t object_type;
  uint64_t object_id;
  ladish_dict_handle dict;
  const char * key;
  const char * value;

  if (!dbus_message_get_args(
        call_ptr->message,
        &g_dbus_error,
        DBUS_TYPE_UINT32, &object_type,
        DBUS_TYPE_UINT64, &object_id,
        DBUS_TYPE_STRING, &key,
        DBUS_TYPE_INVALID))
  {
    lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s",  call_ptr->method_name, g_dbus_error.message);
    dbus_error_free(&g_dbus_error);
    return;
  }

  if (!find_dict(call_ptr, object_type, object_id, &dict))
  {
    return;
  }

  value = ladish_dict_get(dict, key);
  if (value == NULL)
  {
    lash_dbus_error(call_ptr, LASH_DBUS_ERROR_KEY_NOT_FOUND, "Key '%s' not found",  key);
    return;
  }

  method_return_new_single(call_ptr, DBUS_TYPE_STRING, &value);
}

void ladish_dict_drop_dbus(struct dbus_method_call * call_ptr)
{
  uint32_t object_type;
  uint64_t object_id;
  ladish_dict_handle dict;
  const char * key;

  if (!dbus_message_get_args(
        call_ptr->message,
        &g_dbus_error,
        DBUS_TYPE_UINT32, &object_type,
        DBUS_TYPE_UINT64, &object_id,
        DBUS_TYPE_STRING, &key,
        DBUS_TYPE_INVALID))
  {
    lash_dbus_error(call_ptr, LASH_DBUS_ERROR_INVALID_ARGS, "Invalid arguments to method \"%s\": %s",  call_ptr->method_name, g_dbus_error.message);
    dbus_error_free(&g_dbus_error);
    return;
  }

  if (!find_dict(call_ptr, object_type, object_id, &dict))
  {
    return;
  }

  ladish_dict_drop(dict, key);

  method_return_new_void(call_ptr);
}

METHOD_ARGS_BEGIN(Set, "Set value for specified key")
  METHOD_ARG_DESCRIBE_IN("object_type", "u", "Type of object, 0 - graph, 1 - client, 2 - port, 3 - connection")
  METHOD_ARG_DESCRIBE_IN("object_id", "t", "ID of the object")
  METHOD_ARG_DESCRIBE_IN("key", "s", "Key to set")
  METHOD_ARG_DESCRIBE_IN("value", "s", "Value to set")
METHOD_ARGS_END

METHOD_ARGS_BEGIN(Get, "Get value for specified key")
  METHOD_ARG_DESCRIBE_IN("object_type", "u", "Type of object, 0 - graph, 1 - client, 2 - port, 3 - connection")
  METHOD_ARG_DESCRIBE_IN("object_id", "t", "ID of the object")
  METHOD_ARG_DESCRIBE_IN("key", "s", "Key to query")
  METHOD_ARG_DESCRIBE_OUT("value", "s", "Value associated with the key")
METHOD_ARGS_END

METHOD_ARGS_BEGIN(Drop, "Drop entry, if key exists")
  METHOD_ARG_DESCRIBE_IN("object_type", "u", "Type of object, 0 - graph, 1 - client, 2 - port, 3 - connection")
  METHOD_ARG_DESCRIBE_IN("object_id", "t", "ID of the object")
  METHOD_ARG_DESCRIBE_IN("key", "s", "Key of the entry to drop")
METHOD_ARGS_END

METHODS_BEGIN
  METHOD_DESCRIBE(Set, ladish_dict_set_dbus)
  METHOD_DESCRIBE(Get, ladish_dict_get_dbus)
  METHOD_DESCRIBE(Drop, ladish_dict_drop_dbus)
METHODS_END

INTERFACE_BEGIN(g_iface_graph_dict, IFACE_GRAPH_DICT)
  INTERFACE_DEFAULT_HANDLER
  INTERFACE_EXPOSE_METHODS
INTERFACE_END