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

#ifndef SIMUL_H_
#define SIMUL_H_

enum key_e {
    KEY_C,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
    KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_P,
    KEY_ADD, KEY_SUB, KEY_MUL, KEY_DIV,
    KEY_EQU,
    KEY_PCT
};

#define WIDTH (8)

struct reg_s {
    int d[WIDTH];   /* digits of the value, #0 - the rightmost digit */
    int exp;        /* number of digits to the left of the point */
    int neg;        /* if the value is negative */
};

extern struct reg_s reg_1;  /* displayed argument */
extern struct reg_s reg_2;  /* second argument, the constant */

enum state_e {
    ST_READY = 0,   /* after power-on, clear entry, or calculation */
    ST_INT,         /* entering the integer part of an argument */
    ST_FRAC,        /* entering the fractional part, point is set */
    ST_ERROR        /* error after calculation */
};

enum func_e {
    FN_NOP = 0,                         /* no operation */
    FN_ADD, FN_SUB, FN_MUL, FN_DIV,     /* chained calculations */
    FN_REP_ADD, FN_REP_SUB,             /* repeated calculations */
    FN_REP_MUL, FN_REP_DIV,
    FN_PCT_ADD, FN_PCT_SUB,             /* percentage calculations */
    FN_PCT_MUL, FN_PCT_DIV
};

struct control_s {
    enum state_e    state;
    enum func_e     func;
};

extern struct control_s control;

extern void key_pressed(enum key_e key);

#endif /* SIMUL_H_ */
