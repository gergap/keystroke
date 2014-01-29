/* This file is part of Keystroke. A keystroke visualization tool.
 * Copyright (C) 2014 Gerhard Gappmeier <gappy1502@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef KEYMAP_H
#define KEYMAP_H

#define KEY_RELEASED 0
#define KEY_PRESSED  1
#define KEY_REPEATED 2

#ifdef __cplusplus
extern "C" {
#endif

    void loadmap(const char *filename);
    const char* key_lookup(int keycode, int shift, int altgr);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KEYMAP_H */

