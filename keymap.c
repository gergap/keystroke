#include <stdio.h>
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

void loadmap(const char *filename)
{
    FILE *f = fopen(filename, "r");
    int i;
    int ret;

    if (f == 0) return;

    while (i < NUM_SYMBOLS) {
        ret = fscanf(f, "%s %s %s %s", map[i].symbol, map[i].key,
                     map[i].key_shift, map[i].key_altgr);
        if (ret == 4)
            i++;
        else
            break;
    }

    fclose(f);
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

char* key_lookup(int keycode, int shift, int altgr)
{
    const char *symbol;
    int index;

    if (keycode < 0 || keycode >KEY_MAX) return NULL;
    symbol = keycodes[keycode];

    index = key_translation_lookup(symbol);
    if (index != -1) {
        if (shift == 0 && altgr == 0)
            return map[index].key;
        else if (shift == 1 && altgr == 0)
            return map[index].key_shift;
        else if (shift == 0 && altgr == 1)
            return map[index].key_altgr;
        else
            return map[index].key;
    }

    return symbol;
}

