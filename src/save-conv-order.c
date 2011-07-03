/*
 * Pidgin Save Conversation Order
 * Copyright (C) 2010 Konrad Gräfe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1301, USA.
 */

#include "save-conv-order.h"

#include <gtkplugin.h>
#include <version.h>
#include <util.h>
#include <prefs.h>

#include "conv_placement.h"

PurplePlugin *plugin;

static gboolean plugin_load(PurplePlugin *_plugin) {
	plugin = _plugin;

	conv_placement_init();
	
	return TRUE;
}

static gboolean plugin_unload(PurplePlugin *_plugin) {
	conv_placement_uninit();

	return TRUE;
}

static PidginPluginUiInfo ui_info = {
        get_config_frame,
        0,   /* page_num (Reserved) */
        /* Padding */
        NULL,
        NULL,
        NULL,
        NULL
};

static PurplePluginInfo info = {
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,			/**< type           */
	PIDGIN_PLUGIN_TYPE,			/**< ui_requirement */
	0,					/**< flags          */
	NULL,					/**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,		/**< priority       */

	PLUGIN_ID,				/**< id             */
	NULL,					/**< name           */
	PLUGIN_VERSION,				/**< version        */
	NULL,					/**  summary        */
				
	NULL,					/**  description    */
	PLUGIN_AUTHOR,				/**< author         */
	PLUGIN_WEBSITE,				/**< homepage       */

	plugin_load,				/**< load           */
	plugin_unload,				/**< unload         */
	NULL,					/**< destroy        */

	&ui_info,				/**< ui_info        */
	NULL,					/**< extra_info     */
	NULL,					/**< prefs_info     */
	NULL,					/**< actions        */
	/* padding */
	NULL,
	NULL,
	NULL,
	NULL
};

static void init_plugin(PurplePlugin *plugin) {
	const char *str = "Save Conversation Order";
	gchar *plugins_locale_dir;

#ifdef ENABLE_NLS
	plugins_locale_dir = g_build_filename(purple_user_dir(), "locale", NULL);

	bindtextdomain(GETTEXT_PACKAGE, plugins_locale_dir);
	if(str == _(str)) {
		bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	}
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

	g_free(plugins_locale_dir);
#endif /* ENABLE_NLS */

	info.name        = _("Save Conversation Order");
	info.summary     = _("This plugin saves the order of chats and IMs and restores it the next time you open a conversation.");
	info.description = _("This plugin saves the order of chats and IMs and restores it the next time you open a conversation.");

	init_prefs();
}

PURPLE_INIT_PLUGIN(PLUGIN_STATIC_NAME, init_plugin, info)

