/*
 * Copyright 2018 Alexander A. Strelets. All rights reserved.
 *
 * Author: Alexander A. Strelets
 * e-mail: streletsaa@gmail.com
 *
 * This program is the proprietary software of the Author and/or his
 * licensors, and may only be used, duplicated, modified or distributed
 * pursuant to the terms and conditions of a separate, written license
 * agreement executed between you and the Author (an "Authorized
 * License"). Except as set forth in an Authorized License, the Author
 * grants no license (express or implied), right to use, or waiver of
 * any kind with respect to the Software, and the Author expressly
 * reserves all rights in and to the Software and all intellectual
 * property rights therein.
 *
 * IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS
 * SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY THE AUTHOR AND
 * DISCONTINUE ALL USE OF THE SOFTWARE.
 */

#include "adapter-b3-23-console.h"

#include "simulator-b3-23.h"

static const struct { char c; enum key_e key; } char2key[] = {
    { 'C', KEY_C }, { 'c', KEY_C }, { '%', KEY_PCT }, { '+', KEY_ADD },
    { '7', KEY_7 }, { '8', KEY_8 }, { '9', KEY_9 },   { '-', KEY_SUB },
    { '4', KEY_4 }, { '5', KEY_5 }, { '6', KEY_6 },   { '*', KEY_MUL },
    { '1', KEY_1 }, { '2', KEY_2 }, { '3', KEY_3 },   { '/', KEY_DIV },
    { '0', KEY_0 }, { '.', KEY_P }, { ',', KEY_P },   { '=', KEY_EQU },
};

int process_key(char *c)
{
    enum key_e key;
    unsigned i;
    for (i = 0; i < sizeof char2key / sizeof char2key[0]; ++i) {
        if (char2key[i].c == *c) {
            key = char2key[i].key;
            /* TODO: process key */
            while (i-- > 0) {
                if (char2key[i].key == key) {
                    *c = char2key[i].c;
                }
            }
            return 1;
        }
    }
    return 0;
}

const char *print_state(void)
{
    static char s[256];
    char *p = s;
    /* TODO: print state */
    *p++ = '.';
    *p++ = '.';
    *p++ = '.';
    *p++ = 's';
    *p++ = 't';
    *p++ = 'a';
    *p++ = 't';
    *p++ = 'e';
    *p++ = '.';
    *p++ = '.';
    *p++ = '.';
    *p++ = '\0';
    return s;
}
