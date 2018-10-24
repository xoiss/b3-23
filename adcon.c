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

#include "adcon.h"

#include "simul.h"

static const struct { char c; enum key_e key; } char2key[] = {
    { 'C', KEY_C }, { 'c', KEY_C }, { '%', KEY_PCT }, { '+', KEY_ADD },
    { '7', KEY_7 }, { '8', KEY_8 }, { '9', KEY_9 },   { '-', KEY_SUB },
    { '4', KEY_4 }, { '5', KEY_5 }, { '6', KEY_6 },   { '*', KEY_MUL },
    { '1', KEY_1 }, { '2', KEY_2 }, { '3', KEY_3 },   { '/', KEY_DIV },
    { '0', KEY_0 }, { '.', KEY_P }, { ',', KEY_P },   { '=', KEY_EQU },
};

static const struct { enum state_e state; char c; } state2char[] = {
    { ST_READY, 'R' },
    { ST_INT, 'I' },
    { ST_FRAC, 'F' },
    { ST_ERROR, 'E' },
};

static const struct { enum func_e func; char c; } func2char[] = {
    { FN_NOP, ' ' },
    { FN_ADD, '+' }, { FN_SUB, '-' }, { FN_MUL, '*' }, { FN_DIV, '/' },
    { FN_REP_ADD, '+' }, { FN_REP_SUB, '-' },
    { FN_REP_MUL, '*' }, { FN_REP_DIV, '/' },
    { FN_PCT_ADD, '+' }, { FN_PCT_SUB, '-' },
    { FN_PCT_MUL, '*' }, { FN_PCT_DIV, '/' },
};

static const struct { enum func_e func; char c; } mode2char[] = {
    { FN_NOP, ' ' },
    { FN_ADD, ' ' }, { FN_SUB, ' ' }, { FN_MUL, ' ' }, { FN_DIV, ' ' },
    { FN_REP_ADD, 'K' }, { FN_REP_SUB, 'K' },
    { FN_REP_MUL, 'K' }, { FN_REP_DIV, 'K' },
    { FN_PCT_ADD, '%' }, { FN_PCT_SUB, '%' },
    { FN_PCT_MUL, '%' }, { FN_PCT_DIV, '%' },
};

static void print_display(char **p);
static void print_register(char **p, struct reg_s *reg);

int process_key(char *c)
{
    enum key_e key;
    unsigned i;
    for (i = 0; i < sizeof char2key / sizeof char2key[0]; ++i) {
        if (char2key[i].c == *c) {
            key = char2key[i].key;
            key_pressed(key);
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
    char state_c = '?', func_c ='?', mode_c = '?';
    unsigned i;
    for (i = 0; i < sizeof state2char / sizeof state2char[0]; ++i) {
        if (state2char[i].state == control.state) {
            state_c = state2char[i].c;
        }
    }
    for (i = 0; i < sizeof func2char / sizeof func2char[0]; ++i) {
        if (func2char[i].func == control.func) {
            func_c = func2char[i].c;
        }
    }
    for (i = 0; i < sizeof mode2char / sizeof mode2char[0]; ++i) {
        if (mode2char[i].func == control.func) {
            mode_c = mode2char[i].c;
        }
    }
    *p++ = '[';
    *p++ = ' ';
    print_display(&p);
    *p++ = ']';
    *p++ = ' ';
    *p++ = ' ';
    *p++ = '[';
    *p++ = ' ';
    print_register(&p, &reg_1);
    *p++ = ' ';
    print_register(&p, &reg_2);
    *p++ = ' ';
    *p++ = state_c;
    *p++ = ' ';
    *p++ = func_c;
    *p++ = ' ';
    *p++ = mode_c;
    *p++ = ' ';
    *p++ = ']';
    *p++ = '\0';
    return s;
}

static void print_display(char **p)
{
    /* "-  0. 0. 0. 0. 0. 0. 0. 0. " */
    int e = 0;
    int i;
    *(*p)++ = reg_1.neg ? '-' : ' ';
    *(*p)++ = ' ';
    *(*p)++ = ' ';
    for (i = WIDTH - 1; i >= 0; --i) {
        if (reg_1.d[i] != 0 || i == reg_1.exp) {
            e = 1;
        }
        *(*p)++ = e ? (char)(reg_1.d[i] + '0') : ' ';
        *(*p)++ = (i == reg_1.exp || control.state == ST_ERROR)
                ? '.' : ' ';
        *(*p)++ = ' ';
    }
}

static void print_register(char **p, struct reg_s *reg)
{
    /* "+0000000." */
    int i;
    *(*p)++ = reg->neg ? '-' : '+';
    for (i = WIDTH - 1; i >= 0; --i) {
        *(*p)++ = (char)(reg->d[i] + '0');
        if (i == reg->exp) {
            *(*p)++ = '.';
        }
    }
}
