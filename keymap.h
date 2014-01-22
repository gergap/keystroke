#ifndef KEYMAP_H
#define KEYMAP_H

void loadmap(const char *filename);
char* key_lookup(int keycode, int shift, int altgr);

#endif /* end of include guard: KEYMAP_H */

