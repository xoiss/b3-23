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

#include "simulator-b3-23.h"

struct reg_s reg_1;
struct reg_s reg_2;

struct control_s control;

static void process_clear(void);
static void process_number(enum key_e key);
static void process_point(void);
static void process_function(enum key_e key);
static void process_equal(void);
static void process_percent(void);

static void clear_all(void);
static void clear_display(void);
static void enter_number(int digit);
static void normalize_display(void);
static void push_argument(void);
static void exchange_arguments(void);
static int calculate(void);
static int isrepeated(void);

static int iszero(struct reg_s *reg);
static void clear(struct reg_s *reg);
static int islimit_left(struct reg_s *reg);
static int islimit_right(struct reg_s *reg);
static void shift_left(struct reg_s *reg);
static void shift_right(struct reg_s *reg);

void key_pressed(enum key_e key)
{
    if (key == KEY_C) {
        process_clear();
        return;
    }
    if (control.state == ST_ERROR) {
        return;
    }
    switch (key) {
    case KEY_0: case KEY_1: case KEY_2: case KEY_3: case KEY_4:
    case KEY_5: case KEY_6: case KEY_7: case KEY_8: case KEY_9:
        process_number(key);
        break;
    case KEY_P:
        process_point();
        break;
    case KEY_ADD: case KEY_SUB: case KEY_MUL: case KEY_DIV:
        process_function(key);
        break;
    case KEY_EQU:
        process_equal();
        break;
    case KEY_PCT:
        process_percent();
        break;
    default:
        break;
    }
}

static void process_clear(void)
{
    switch (control.state) {
    case ST_READY:
        clear_all();
        break;
    case ST_INT: case ST_FRAC:
        clear_display();
        break;
    case ST_ERROR:
        break;
    }
    control.state = ST_READY;
}

static void process_number(enum key_e key)
{
    if (control.state == ST_READY) {
        clear_display();
        control.state = ST_INT;
    }
    enter_number((int)(key - KEY_0));
}

static void process_point(void)
{
    if (control.state == ST_READY) {
        clear_display();
    }
    control.state = ST_FRAC;
}

static void process_function(enum key_e key)
{
    if (isrepeated()) {
        control.func = FN_NOP;
    }
    if (control.state != ST_READY) {
        process_equal();
    }
    if (isrepeated() || control.func == FN_NOP) {
        push_argument();
    }
    control.func = (key - KEY_ADD + FN_ADD);
}

static void process_equal(void)
{
    int error;
    normalize_display();
    if (!isrepeated() && control.func != FN_NOP) {
        exchange_arguments();
    }
    error = calculate();
    control.state = error ? ST_ERROR : ST_READY;
}

static void process_percent(void)
{
    /* TODO: implement */
}

static void clear_all(void)
{
    clear(&reg_1);
    clear(&reg_2);
    control.func = FN_NOP;
}

static void clear_display(void)
{
    clear(&reg_1);
}

static void enter_number(int digit)
{
    if (!islimit_left(&reg_1)) {
        shift_left(&reg_1);
        reg_1.d[0] = digit;
        reg_1.exp += (control.state == ST_FRAC);
    }
}

static void normalize_display(void)
{
    while (!islimit_right(&reg_1)) {
        shift_right(&reg_1);
        reg_1.exp -= 1;
    }
    if (iszero(&reg_1)) {
        reg_1.neg = 0;
    }
}

static void push_argument(void)
{
    reg_2 = reg_1;
}

static void exchange_arguments(void)
{
    struct reg_s reg = reg_2;
    reg_2 = reg_1;
    reg_1 = reg;
}

static int calculate(void)
{
    int error = 0;
    if (control.func == FN_NOP) {
        return error;
    }
    if (!isrepeated()) {
        control.func += (FN_REP_ADD - FN_ADD);
    }
    switch (control.func) {
    case FN_REP_ADD:
        /* TODO: implement */
        break;
    case FN_REP_SUB:
        /* TODO: implement */
        break;
    case FN_REP_MUL:
        /* TODO: implement */
        break;
    case FN_REP_DIV:
        /* TODO: implement */
        break;
    default:
        break;
    }
    if (!error) {
        normalize_display();
    }
    return error;
}

static int isrepeated(void)
{
    return control.func >= FN_REP_ADD && control.func <= FN_REP_DIV;
}

static int iszero(struct reg_s *reg)
{
    int i;
    for (i = 0; i < WIDTH; ++i) {
        if (reg->d[i] != 0) {
            return 0;
        }
    }
    return 1;
}

static void clear(struct reg_s *reg)
{
    int i;
    for (i = 0; i < WIDTH; ++i) {
        reg->d[i] = 0;
    }
    reg->exp = 0;
    reg->neg = 0;
}

static int islimit_left(struct reg_s *reg)
{
    return reg->d[WIDTH - 1] != 0 || reg->exp == WIDTH - 1;
}

static int islimit_right(struct reg_s *reg)
{
    return reg->d[0] != 0 || reg->exp == 0;
}

static void shift_left(struct reg_s *reg)
{
    int i;
    for (i = WIDTH - 1; i > 0; --i) {
        reg->d[i] = reg->d[i - 1];
    }
    reg->d[0] = 0;
}

static void shift_right(struct reg_s *reg)
{
    int i;
    for (i = 0; i < WIDTH - 1; ++i) {
        reg->d[i] = reg->d[i + 1];
    }
    reg->d[WIDTH - 1] = 0;
}
