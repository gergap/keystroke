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

#include <stdio.h>
#include <string.h>
#include "keys.h"

#define SYM_MAX_LEN 16
#define NUM_SYMBOLS 48

struct key_entry {
    char symbol[SYM_MAX_LEN];
    char key[SYM_MAX_LEN];
    char key_shift[SYM_MAX_LEN];
    char key_altgr[SYM_MAX_LEN];
};

struct key_entry map[NUM_SYMBOLS];

int loadmap(const char *filename)
{
    FILE *f = fopen(filename, "r");
    int i = 0;
    int ret;

    if (f == 0) return -1;

    while (i < NUM_SYMBOLS) {
        ret = fscanf(f, "%s %s %s %s", map[i].symbol, map[i].key,
                     map[i].key_shift, map[i].key_altgr);
        if (ret == 4)
            i++;
        else
            break;
    }

    fclose(f);
    return 0;
}

void printmap()
{
    int i;

    for (i = 0; i < NUM_SYMBOLS; ++i) {
        printf("%s\t%s\t%s\t%s\n", map[i].symbol, map[i].key,
               map[i].key_shift, map[i].key_altgr);
    }
}

static int key_translation_lookup(const char *symbol)
{
    int index = 0;

    while (index < NUM_SYMBOLS) {
        if (strcmp(symbol, map[index].symbol) == 0) return index;
        index++;
    }

    return -1;
}

const char *key_lookup(int keycode, int shift, int altgr)
{
    const char *symbol;
    int index;

    if (keycode < 0 || keycode > KEY_MAX) return NULL;
    symbol = keycodes[keycode];

    index = key_translation_lookup(symbol);
    if (index != -1) {
        if (shift == 0 && altgr == 0)
            return map[index].key;
        else if (shift > 0 && altgr == 0)
            return map[index].key_shift;
        else if (shift == 0 && altgr > 0)
            return map[index].key_altgr;
        else
            return map[index].key;
    } else {
        /* some default mappings */
        if (   strcmp(symbol, "LEFTCTRL") == 0
            || strcmp(symbol, "RIGHTCTRL") == 0) {
            symbol = "CTRL";
        } else if (   strcmp(symbol, "LEFTALT") == 0
                   || strcmp(symbol, "RIGHTALT") == 0) {
            symbol = "ALT";
        } else if (   strcmp(symbol, "LEFTSHIFT") == 0
                   || strcmp(symbol, "RIGHTSHIFT") == 0) {
            symbol = "SHIFT";
        } else if (   strcmp(symbol, "LEFTMETA") == 0
                   || strcmp(symbol, "RIGHTMETA") == 0) {
            symbol = "META";
        } else if (strcmp(symbol, "KPENTER") == 0) {
            symbol = "ENTER";
        }
    }

    return symbol;
}

