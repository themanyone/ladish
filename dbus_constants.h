/* -*- Mode: C ; c-basic-offset: 2 -*- */
/*
 * LADI Session Handler (ladish)
 *
 * Copyright (C) 2009 Nedko Arnaudov <nedko@arnaudov.name>
 *
 **************************************************************************
 * This file contains constants for D-Bus service and interface names and for D-Bus object paths
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

#ifndef DBUS_CONSTANTS_H__C21DE0EE_C19C_42F0_8D63_D613E4806C0E__INCLUDED
#define DBUS_CONSTANTS_H__C21DE0EE_C19C_42F0_8D63_D613E4806C0E__INCLUDED

#define JACKDBUS_SERVICE_NAME    "org.jackaudio.service"
#define JACKDBUS_OBJECT_PATH     "/org/jackaudio/Controller"
#define JACKDBUS_IFACE_CONTROL   "org.jackaudio.JackControl"
#define JACKDBUS_IFACE_CONFIGURE "org.jackaudio.Configure"
#define JACKDBUS_IFACE_PATCHBAY  "org.jackaudio.JackPatchbay"

#define SERVICE_NAME             DBUS_NAME_BASE
#define CONTROL_OBJECT_PATH      DBUS_BASE_PATH "/Control"
#define IFACE_CONTROL            DBUS_NAME_BASE ".Control"
#define STUDIO_OBJECT_PATH       DBUS_BASE_PATH "/Studio"
#define IFACE_STUDIO             DBUS_NAME_BASE ".Studio"
#define IFACE_ROOM               DBUS_NAME_BASE ".Room"
#define LAUNCHER_OBJECT_PATH     DBUS_BASE_PATH "/Launcher"
#define IFACE_LAUNCHER           DBUS_NAME_BASE ".Launcher"
#define APPLICATION_OBJECT_PATH  DBUS_BASE_PATH "/Application"
#define IFACE_APPLICATION        DBUS_NAME_BASE ".App"

#endif /* #ifndef DBUS_CONSTANTS_H__C21DE0EE_C19C_42F0_8D63_D613E4806C0E__INCLUDED */