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

