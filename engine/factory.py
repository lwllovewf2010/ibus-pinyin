# vim:set et sts=4 sw=4:
#
# ibus-tmpl - The Input Bus template project
#
# Copyright (c) 2007-2008 Huang Peng <shawn.p.huang@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

import ibus
import pinyin

FACTORY_PATH = "/com/redhat/IBus/engines/PinYin/Factory"
ENGINE_PATH = "/com/redhat/IBus/engines/PinYin/Engine/"

class EngineFactory(ibus.EngineFactoryBase):
    NAME = "PinYin"
    LANG = "zh_CN"
    ICON = "/usr/share/ibus-pinyin/ibus-pinyin.svg"
    AUTHORS = "Huang Peng <shawn.p.huang@gmail.com>"
    CREDITS = "GPLv2"

    def __init__(self, bus):
        self.__info = [
            self.NAME,
            self.LANG,
            self.ICON,
            self.AUTHORS,
            self.CREDITS
        ]
        self.__bus = bus
        pinyin.PinYinEngine.reload_config(bus)
        super(EngineFactory, self).__init__(self.__info, pinyin.PinYinEngine, ENGINE_PATH, bus, FACTORY_PATH)

        self.__bus.connect("config-reloaded", self.__config_reloaded_cb)
        self.__bus.config_add_watch("/engine/PinYin")
        self.__bus.connect("config-value-changed", self.__config_value_changed_cb)


    def __config_reloaded_cb(self, bus):
        pinyin.PinYinEngine.reload_config(self.__bus)

    def __config_value_changed_cb(self, bus, key, value):
        pinyin.PinYinEngine.config_value_changed(bus, key, value)
