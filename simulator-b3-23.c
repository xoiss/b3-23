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

static int calculate_add(void);
static int calculate_sub(void);
static int calculate_mul(void);
static int calculate_div(void);

static int iszero(struct reg_s *reg);
static void clear(struct reg_s *reg);
static void normalize(struct reg_s *reg);
static void denormalize(struct reg_s *reg);
static int justify(struct reg_s *reg);
static void round(struct reg_s *reg);
static void equalize(struct reg_s *reg_a, struct reg_s *reg_b);
static int compare(struct reg_s *reg_a, struct reg_s *reg_b);
static void exchange(struct reg_s *reg_a, struct reg_s *reg_b);
static int add(struct reg_s *reg_dst, struct reg_s *reg_src);
static int sub(struct reg_s *reg_dst, struct reg_s *reg_src);
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
    normalize(&reg_1);
}

static void push_argument(void)
{
    reg_2 = reg_1;
}

static void exchange_arguments(void)
{
    exchange(&reg_1, &reg_2);
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
        error = calculate_add();
        break;
    case FN_REP_SUB:
        error = calculate_sub();
        break;
    case FN_REP_MUL:
        error = calculate_mul();
        break;
    case FN_REP_DIV:
        error = calculate_div();
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

static int calculate_add(void)
{
    int carry, borrow, reg_1b;
    struct reg_s reg_2b = reg_2;
    denormalize(&reg_1);
    denormalize(&reg_2b);
    if (reg_1.neg == reg_2b.neg) {
        equalize(&reg_1, &reg_2b);
        carry = add(&reg_1, &reg_2b);
        if (carry != 0) {
            shift_right(&reg_1);
            reg_1.d[WIDTH - 1] = carry;
            reg_1.exp -= 1;
            if (reg_1.exp < 0) {
                reg_1.exp += WIDTH;
                return 1;  /* overflow */
            }
        }
    } else {
        if (reg_1.exp != reg_2b.exp) {
            if (reg_1.exp > reg_2b.exp) {
                exchange(&reg_1, &reg_2b);
            }
            reg_1b = reg_1.d[WIDTH - 1];
            shift_left(&reg_1);
            reg_1.exp += 1;
            equalize(&reg_1, &reg_2b);
            borrow = sub(&reg_1, &reg_2b);
            reg_1b -= borrow;
            if (reg_1b != 0) {
                shift_right(&reg_1);
                reg_1.d[WIDTH - 1] = reg_1b;
                reg_1.exp -= 1;
            }
        } else {
            if (compare(&reg_1, &reg_2b) < 0) {
                exchange(&reg_1, &reg_2b);
            }
            sub(&reg_1, &reg_2b);
        }
    }
    return 0;
}

static int calculate_sub(void)
{
    int error;
    reg_2.neg = !reg_2.neg;
    error = calculate_add();
    reg_2.neg = !reg_2.neg;
    return error;
}

static int calculate_mul(void)
{
    int i, digit, carry = 0, exp_2 = reg_2.exp;
    struct reg_s reg_p;
    clear(&reg_p);
    reg_p.exp = justify(&reg_1) + justify(&reg_2) - (WIDTH - 1);
    reg_p.neg = reg_1.neg ^ reg_2.neg;
    for (i = 0; i < WIDTH; ++i) {
        shift_right(&reg_p);
        reg_p.d[WIDTH - 1] = carry;
        carry = 0;
        for (digit = reg_2.d[i]; digit > 0; --digit) {
            carry += add(&reg_p, &reg_1);
        }
    }
    if (carry != 0) {
        shift_right(&reg_p);
        reg_p.d[WIDTH - 1] = carry;
        reg_p.exp -= 1;
    }
    normalize(&reg_2);
    reg_2.exp = exp_2;
    reg_1 = reg_p;
    if (reg_1.exp < 0) {
        reg_1.exp += WIDTH;
        return 1;  /* overflow */
    }
    round(&reg_1);
    return 0;
}

static int calculate_div(void)
{
    int i, digit, borrow, reg_1b = 0, exp_2 = reg_2.exp;
    struct reg_s reg_q;
    if (iszero(&reg_2)) {
        clear(&reg_1);
        reg_1.exp = (WIDTH - 1);
        return 1;  /* overflow */
    }
    clear(&reg_q);
    reg_q.exp = justify(&reg_1) - justify(&reg_2) + (WIDTH - 1);
    reg_q.neg = reg_1.neg ^ reg_2.neg;
    if (compare(&reg_1, &reg_2) < 0) {
        reg_1b = reg_1.d[WIDTH - 1];
        shift_left(&reg_1);
        reg_q.exp += 1;
    }
    for (i = WIDTH - 1; i >= 0; --i) {
        digit = 0;
        while (reg_1b != 0 || compare(&reg_1, &reg_2) >= 0) {
            borrow = sub(&reg_1, &reg_2);
            reg_1b -= borrow;
            digit += 1;
        }
        reg_q.d[i] = digit;
        reg_1b = reg_1.d[WIDTH - 1];
        shift_left(&reg_1);
    }
    normalize(&reg_2);
    reg_2.exp = exp_2;
    reg_1 = reg_q;
    if (reg_1.exp < 0) {
        reg_1.exp += WIDTH;
        return 1;  /* overflow */
    }
    round(&reg_1);
    return 0;
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

static void normalize(struct reg_s *reg)
{
    while (!islimit_right(reg)) {
        shift_right(reg);
        reg->exp -= 1;
    }
    if (iszero(reg)) {
        reg->neg = 0;
    }
}

static void denormalize(struct reg_s *reg)
{
    while (!islimit_left(reg)) {
        shift_left(reg);
        reg->exp += 1;
    }
}

static int justify(struct reg_s *reg)
{
    int exp = reg->exp;
    reg->exp = 0;
    denormalize(reg);
    return exp + reg->exp;
}

static void round(struct reg_s *reg)
{
    while (reg->exp >= WIDTH) {
        shift_right(reg);
        reg->exp -= 1;
    }
}

static void equalize(struct reg_s *reg_a, struct reg_s *reg_b)
{
    while (reg_a->exp > reg_b->exp) {
        shift_right(reg_a);
        reg_a->exp -= 1;
    }
    while (reg_a->exp < reg_b->exp) {
        shift_right(reg_b);
        reg_b->exp -= 1;
    }
}

static int compare(struct reg_s *reg_a, struct reg_s *reg_b)
{
    int i;
    for (i = WIDTH - 1; i >= 0; --i) {
        if (reg_a->d[i] > reg_b->d[i]) {
            return 1;
        }
        if (reg_a->d[i] < reg_b->d[i]) {
            return -1;
        }
    }
    return 0;
}

static void exchange(struct reg_s *reg_a, struct reg_s *reg_b)
{
    struct reg_s reg_x = *reg_b;
    *reg_b = *reg_a;
    *reg_a = reg_x;
}

static int add(struct reg_s *reg_dst, struct reg_s *reg_src)
{
    int i, digit, carry = 0;
    for (i = 0; i < WIDTH; ++i) {
        digit = reg_dst->d[i] + reg_src->d[i] + carry;
        if (digit < 10) {
            reg_dst->d[i] = digit;
            carry = 0;
        } else {
            reg_dst->d[i] = digit - 10;
            carry = 1;
        }
    }
    return carry;
}

static int sub(struct reg_s *reg_dst, struct reg_s *reg_src)
{
    int i, digit, borrow = 0;
    for (i = 0; i < WIDTH; ++i) {
        digit = reg_dst->d[i] - reg_src->d[i] - borrow;
        if (digit >= 0) {
            reg_dst->d[i] = digit;
            borrow = 0;
        } else {
            reg_dst->d[i] = digit + 10;
            borrow = 1;
        }
    }
    return borrow;
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
    int i, digit, carry;
    carry = (reg->d[0] >= 5);
    for (i = 0; i < WIDTH - 1; ++i) {
        digit = reg->d[i + 1] + carry;
        if (digit < 10) {
            reg->d[i] = digit;
            carry = 0;
        } else {
            reg->d[i] = 0;
            carry = 1;
        }
    }
    reg->d[WIDTH - 1] = carry;
}
