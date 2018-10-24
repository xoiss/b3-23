/* Copyright 2018 Alexander A. Strelets. All rights reserved.
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

#include "adapter-b3-23-console.h"                                              /* TODO: (K&R), (RT-11) limit file names to 6 symbols */

#include "simulator-b3-23.h"                                                    /* TODO: (K&R), (RT-11) limit file names to 6 symbols */

static const struct { char c; enum key_e key; } char2key[] = {                  /* TODO: (K&R) make field names globally unique; (K&R), (RT-11) limit identifiers to 6 symbols */
    { 'C', KEY_C }, { 'c', KEY_C }, { '%', KEY_PCT }, { '+', KEY_ADD },         /* TODO: (PDP-11) consider replacing with const string literal */
    { '7', KEY_7 }, { '8', KEY_8 }, { '9', KEY_9 },   { '-', KEY_SUB },
    { '4', KEY_4 }, { '5', KEY_5 }, { '6', KEY_6 },   { '*', KEY_MUL },
    { '1', KEY_1 }, { '2', KEY_2 }, { '3', KEY_3 },   { '/', KEY_DIV },
    { '0', KEY_0 }, { '.', KEY_P }, { ',', KEY_P },   { '=', KEY_EQU },
};

static const struct { enum state_e state; char c; } state2char[] = {            /* TODO: (K&R) make field names globally unique; (K&R), (RT-11) limit identifiers to 6 symbols */
    { ST_READY, 'R' },                                                          /* TODO: (PDP-11) consider replacing with const string literal */
    { ST_INT, 'I' },
    { ST_FRAC, 'F' },
    { ST_ERROR, 'E' },
};

static const struct { enum func_e func; char c; } func2char[] = {               /* TODO: (K&R) make field names globally unique; (K&R), (RT-11) limit identifiers to 6 symbols */
    { FN_NOP, ' ' },                                                            /* TODO: (PDP-11) consider replacing with const string literal */
    { FN_ADD, '+' }, { FN_SUB, '-' }, { FN_MUL, '*' }, { FN_DIV, '/' },
    { FN_REP_ADD, '+' }, { FN_REP_SUB, '-' },
    { FN_REP_MUL, '*' }, { FN_REP_DIV, '/' },
    { FN_PCT_ADD, '+' }, { FN_PCT_SUB, '-' },
    { FN_PCT_MUL, '*' }, { FN_PCT_DIV, '/' },
};

static const struct { enum func_e func; char c; } mode2char[] = {               /* TODO: (K&R) make field names globally unique; (K&R), (RT-11) limit identifiers to 6 symbols */
    { FN_NOP, ' ' },                                                            /* TODO: (PDP-11) consider replacing with const string literal */
    { FN_ADD, ' ' }, { FN_SUB, ' ' }, { FN_MUL, ' ' }, { FN_DIV, ' ' },
    { FN_REP_ADD, 'K' }, { FN_REP_SUB, 'K' },
    { FN_REP_MUL, 'K' }, { FN_REP_DIV, 'K' },
    { FN_PCT_ADD, '%' }, { FN_PCT_SUB, '%' },
    { FN_PCT_MUL, '%' }, { FN_PCT_DIV, '%' },
};

static void print_display(char **p);                                            /* TODO: (K&R), (RT-11) limit identifiers to 6 symbols; (K&R) remove parameters; (PDP-11) return modified pointer, don't modify the argument */
static void print_register(char **p, struct reg_s *reg);                        /* TODO: (K&R), (RT-11) limit identifiers to 6 symbols; (K&R) remove parameters; (PDP-11) return modified pointer, don't modify the argument */

int process_key(char *c)                                                        /* TODO: (K&R) move type specification out; (PDP-11) return char or NULL, don't modify the argument */
{
    enum key_e key;
    unsigned i;                                                                 /* TODO: (K&R) use unsigned int */
    for (i = 0; i < sizeof char2key / sizeof char2key[0]; ++i) {
        if (char2key[i].c == *c) {
            key = char2key[i].key;
            key_pressed(key);
            while (i-- > 0) {
                if (char2key[i].key == key) {
                    *c = char2key[i].c;                                         /* TODO: (PDP-11) don't modify the argument */
                }
            }
            return 1;                                                           /* TODO: (PDP-11) return modified char */
        }
    }
    return 0;                                                                   /* TODO: (PDP-11) return NULL */
}

const char *print_state(void)                                                   /* TODO: (K&R) remove const; (PDP-11) publish the buffer, don't return a pointer */
{
    static char s[256];                                                         /* TODO: (PDP-11) publish the buffer */
    char *p = s;
    char state_c = '?', func_c ='?', mode_c = '?';                              /* TODO: (PDP-11) omit initialization if lookup tables are replaced with const string literals */
    unsigned i;                                                                 /* TODO: (K&R) use unsigned int */
    for (i = 0; i < sizeof state2char / sizeof state2char[0]; ++i) {            /* TODO: (PDP-11) integrate into the *p++ sequence below */
        if (state2char[i].state == control.state) {
            state_c = state2char[i].c;
        }
    }
    for (i = 0; i < sizeof func2char / sizeof func2char[0]; ++i) {              /* TODO: (PDP-11) integrate into the *p++ sequence below */
        if (func2char[i].func == control.func) {
            func_c = func2char[i].c;
        }
    }
    for (i = 0; i < sizeof mode2char / sizeof mode2char[0]; ++i) {              /* TODO: (PDP-11) integrate into the *p++ sequence below */
        if (mode2char[i].func == control.func) {
            mode_c = mode2char[i].c;
        }
    }
    *p++ = '[';
    *p++ = ' ';
    print_display(&p);                                                          /* TODO: (PDP-11) will return modified pointer, will not modify the argument */
    *p++ = ']';
    *p++ = ' ';
    *p++ = ' ';
    *p++ = '[';
    *p++ = ' ';
    print_register(&p, &reg_1);                                                 /* TODO: (PDP-11) will return modified pointer, will not modify the argument */
    *p++ = ' ';
    print_register(&p, &reg_2);                                                 /* TODO: (PDP-11) will return modified pointer, will not modify the argument */
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

static void print_display(char **p)                                             /* TODO: (K&R) move type specification out; (PDP-11) return modified pointer, don't modify the argument */
{
    /* "-  0. 0. 0. 0. 0. 0. 0. 0. " */
    int e = 0;
    int i;
    *(*p)++ = reg_1.neg ? '-' : ' ';                                            /* TODO: (PDP-11) consider using arithmetic: '-' 0x2D, ' ' 0x20 */
    *(*p)++ = ' ';
    *(*p)++ = ' ';
    for (i = WIDTH - 1; i >= 0; --i) {                                          /* TODO: (PDP-11) use do-while cycle */
        if (reg_1.d[i] != 0 || i == reg_1.exp) {                                /* TODO: (PDP-11) consider evaluating these out of and before the cycle start, just start the cycle with the proper index */
            e = 1;                                                              /* TODO: (PDP-11) ... or alternatively, evaluate these out of and after the cycle ends, override those places with blanks */
        }
        *(*p)++ = e ? (char)(reg_1.d[i] + '0') : ' ';                           /* TODO: (PDP-11) use pointers instead of indexes */
        *(*p)++ = (i == reg_1.exp || control.state == ST_ERROR)                 /* TODO: (PDP-11) put decimal point into the dedicated place out of the cycle; for error fill with dots in a separate cycle */
                ? '.' : ' ';
        *(*p)++ = ' ';                                                          /* TODO: (PDP-11) consider filling with blanks out of the cycle */
    }
}

static void print_register(char **p, struct reg_s *reg)                         /* TODO: (K&R) move type specification out; (PDP-11) return modified pointer, don't modify the argument */
{
    /* "+0000000." */
    int i;
    *(*p)++ = reg->neg ? '-' : '+';                                             /* TODO: (PDP-11) consider using arithmetic: '-' 0x2D, '+' 0x2B */
    for (i = WIDTH - 1; i >= 0; --i) {                                          /* TODO: (PDP-11) use do-while cycle */
        *(*p)++ = (char)(reg->d[i] + '0');                                      /* TODO: (PDP-11) use pointers instead of indexes */
        if (i == reg->exp) {                                                    /* TODO: (PDP-11) consider using local variable that counts from reg->exp down to zero */
            *(*p)++ = '.';
        }
    }
}
