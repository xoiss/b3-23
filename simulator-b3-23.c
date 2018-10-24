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

#include "simulator-b3-23.h"                                                    /* TODO: (K&R), (RT-11) limit file names to 6 symbols */

struct reg_s reg_1;                                                             /* TODO: rename to rg_; use descriptive names; maybe rename to D (display) or K (keyboard) or A (accumulator) */
struct reg_s reg_2;                                                             /* TODO: rename to rg_; use descriptive names; maybe rename to K or C (constant) */
                                                                                /* TODO: introduce the 3d register named N or C (counter) or R (result) */
struct control_s control;

enum mode_e { MD_EQU, MD_PCT };
                                                                                /* TODO: (K&R), (RT-11) limit name to 6 symbols; (K&R) remove parameters; (PDP-11) integrate */
static void process_clear(void);
static void process_number(enum key_e key);
static void process_point(void);
static void process_function(enum key_e key);
static void process_equal(void);
static void process_percent(void);                                              /* TODO: maybe combine with process_equal */
                                                                                /* TODO: (K&R), (RT-11) limit name to 6 symbols; (K&R) remove parameters; (PDP-11) integrate, except calculate */
static void clear_all(void);
static void clear_display(void);
static void enter_number(int digit);
static void justify_display(void);
static void push_argument(void);
static void exchange_arguments(void);
static int calculate(enum mode_e mode);
static int isrepeated(void);                                                    /* TODO: (PDP-11) make macro */
static int ispercentage(void);                                                  /* TODO: (PDP-11) make macro */
static enum func_e getfunc(void);                                               /* TODO: (PDP-11) make macro */
static void setmode(enum mode_e mode);                                          /* TODO: (PDP-11) make macro */
                                                                                /* TODO: (K&R), (RT-11) limit name to 6 symbols; (K&R) remove parameters */
static int calculate_add(void);
static int calculate_sub(void);                                                 /* TODO: (PDP-11) integrate */
static int calculate_mul(enum mode_e mode);
static int calculate_div(enum mode_e mode);
                                                                                /* TODO: (K&R), (RT-11) limit name to 6 symbols; (K&R) remove parameters */
static int iszero(struct reg_s *reg);                                           /* TODO: const struct reg_s *reg */
static void clear(struct reg_s *reg);
static void justify_right(struct reg_s *reg);
static void justify_left(struct reg_s *reg);
static int normalize(struct reg_s *reg);
static void trim(struct reg_s *reg);                                            /* TODO: argument is reg_1 in all cases */
static void align(struct reg_s *reg_a, struct reg_s *reg_b);                    /* TODO: arguments are reg_1, reg_2b in all cases */
static int compare(struct reg_s *reg_a, struct reg_s *reg_b);                   /* TODO: first argument is reg_1 in all cases; consider reducing functionality to greater_than_or_equal; const struct reg_s *reg_a, reg_b */
static void exchange(struct reg_s *reg_a, struct reg_s *reg_b);                 /* TODO: first argument is reg_1 in all cases */
static int add(struct reg_s *reg_dst, struct reg_s *reg_src);                   /* TODO: rework so that the first argument is reg_1 in all cases; const struct reg_s *reg_src */
static int sub(struct reg_s *reg_dst, struct reg_s *reg_src);                   /* TODO: first argument is reg_1 in all cases, maybe combine with add; const struct reg_s *reg_src */
static int islimit_left(struct reg_s *reg);                                     /* TODO: const struct reg_s *reg; (PDP-11) make macro */
static int islimit_right(struct reg_s *reg);                                    /* TODO: const struct reg_s *reg; (PDP-11) make macro */
static void shift_left(struct reg_s *reg);
static void shift_right(struct reg_s *reg);

void key_pressed(enum key_e key)                                                /* TODO: (K&R) move type specification out */
{
    if (key == KEY_C) {
        process_clear();
        return;
    }
    if (control.state == ST_ERROR) {
        return;
    }
    switch (key) {                                                              /* TODO: (PDP-11) consider using if-else */
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
    default:                                                                    /* TODO: (K&R) refuse of enums, remove unnecessary cases */
        break;
    }
}

static void process_clear(void)
{
    switch (control.state) {                                                    /* TODO: (PDP-11) consider using if-else */
    case ST_READY:
        clear_all();
        break;
    case ST_INT: case ST_FRAC:
        clear_display();
        break;
    case ST_ERROR:                                                              /* TODO: (K&R) refuse of enums, remove unnecessary cases */
        break;
    }
    control.state = ST_READY;
}

static void process_number(enum key_e key)                                      /* TODO: (K&R) move type specification out */
{
    if (control.state == ST_READY) {
        clear_display();
        control.state = ST_INT;
    }
    enter_number((int)(key - KEY_0));                                           /* TODO: (K&R) refuse of enums, remove unnecessary type-casts */
}

static void process_point(void)
{
    if (control.state == ST_READY) {
        clear_display();
    }
    control.state = ST_FRAC;
}

static void process_function(enum key_e key)                                    /* TODO: (K&R) move type specification out */
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
    justify_display();
    if (!isrepeated() && control.func != FN_NOP) {
        exchange_arguments();
    }
    error = calculate(MD_EQU);
    control.state = error ? ST_ERROR : ST_READY;
}

static void process_percent(void)
{
    int error;
    justify_display();
    if (control.func == FN_MUL || control.func == FN_DIV) {
        exchange_arguments();
    }
    error = calculate(MD_PCT);
    control.state = error ? ST_ERROR : ST_READY;
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

static void enter_number(int digit)                                             /* TODO: (K&R) move type specification out */
{
    if (!islimit_left(&reg_1)) {
        shift_left(&reg_1);
        reg_1.d[0] = digit;
        reg_1.exp += (control.state == ST_FRAC);
    }
}

static void justify_display(void)
{
    justify_right(&reg_1);
}

static void push_argument(void)
{
    reg_2 = reg_1;                                                              /* TODO: introduce a function for copying registers; (PDP-11) make such function a macro */
}

static void exchange_arguments(void)
{
    exchange(&reg_1, &reg_2);
}

static int calculate(enum mode_e mode)                                          /* TODO: (K&R) move type specification out */
{
    int error;
    if (mode == MD_EQU) {
        switch (getfunc()) {                                                    /* TODO: (PDP-11) consider using if-else */
        case FN_ADD:
            error = calculate_add();
            break;
        case FN_SUB:
            error = calculate_sub();
            reg_1.neg ^= ispercentage();                                        /* TODO: (PDP-11) consider using != instead of ^ */
            break;
        case FN_MUL:
            if (!ispercentage()) {
                error = calculate_mul(MD_EQU);
            } else {
                error = calculate_div(MD_PCT);                                  /* TODO: use a build-key to enable this modified behavior */
            }
            break;
        case FN_DIV:
            if (!ispercentage()) {
                error = calculate_div(MD_EQU);
            } else {
                error = calculate_mul(MD_PCT);                                  /* TODO: use a build-key to enable this modified behavior */
            }
            break;
        default:
            return 0;
        }
    } else {
        switch (getfunc()) {                                                    /* TODO: (PDP-11) consider using if-else */
        case FN_ADD: case FN_SUB: case FN_MUL:
            error = calculate_mul(MD_PCT);
            break;
        case FN_DIV:
            error = calculate_div(MD_PCT);
            break;
        default:
            return 0;
        }
    }
    setmode(mode);
    if (!error) {
        justify_display();
    }
    return error;
}

static int isrepeated(void)
{
    return control.func >= FN_REP_ADD;
}

static int ispercentage(void)
{
    return control.func >= FN_PCT_ADD;
}

static enum func_e getfunc(void)
{
    enum func_e func = control.func;
    if (ispercentage()) {
        func -= (FN_PCT_ADD - FN_ADD);
    } else if (isrepeated()) {
        func -= (FN_REP_ADD - FN_ADD);
    }
    return func;
}

static void setmode(enum mode_e mode)                                           /* TODO: (K&R) move type specification out */
{
    enum func_e func = getfunc();
    if (mode == MD_PCT) {
        func += (FN_PCT_ADD - FN_ADD);
    } else {
        func += (FN_REP_ADD - FN_ADD);
    }
    control.func = func;
}

static int calculate_add(void)
{
    int carry, borrow, reg_1b;
    struct reg_s reg_2b = reg_2;                                                /* TODO: use the 3d static register; introduce a function for copying registers; (PDP-11) make such function a macro */
    justify_left(&reg_1);
    justify_left(&reg_2b);
    if (reg_1.neg == reg_2b.neg) {
        align(&reg_1, &reg_2b);
        carry = add(&reg_1, &reg_2b);
        if (carry != 0) {
            shift_right(&reg_1);
            reg_1.d[WIDTH - 1] = carry;
            reg_1.exp -= 1;
            if (reg_1.exp < 0) {
                reg_1.exp += WIDTH;                                             /* TODO: keep exp negative until error is cleared */
                return 1;  /* overflow */
            }
        }
    } else {
        if (reg_1.exp != reg_2b.exp) {                                          /* TODO: use a build-key to enable this improvement */
            if (reg_1.exp > reg_2b.exp) {
                exchange(&reg_1, &reg_2b);
            }
            reg_1b = reg_1.d[WIDTH - 1];
            shift_left(&reg_1);
            reg_1.exp += 1;
            align(&reg_1, &reg_2b);
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

static int calculate_mul(enum mode_e mode)                                      /* TODO: (K&R) move type specification out */
{
    int i, digit, carry = 0, exp_2 = reg_2.exp;
    struct reg_s reg_p;                                                         /* TODO: use the 3d static register */
    clear(&reg_p);
    reg_p.exp = normalize(&reg_1) + normalize(&reg_2) - (WIDTH - 1);
    reg_p.neg = reg_1.neg ^ reg_2.neg;                                          /* TODO: consider moving this out of the function; (PDP-11) consider using != instead of ^ */
    for (i = 0; i < WIDTH; ++i) {
        shift_right(&reg_p);
        reg_p.d[WIDTH - 1] = carry;
        carry = 0;
        for (digit = reg_2.d[i]; digit > 0; --digit) {
            carry += add(&reg_p, &reg_1);                                       /* TODO: rework in such a way that reg_1 became the first argument */
        }
    }
    if (carry != 0) {
        shift_right(&reg_p);
        reg_p.d[WIDTH - 1] = carry;
        reg_p.exp -= 1;
    }
    justify_right(&reg_2);
    reg_2.exp = exp_2;
    reg_1 = reg_p;                                                              /* TODO: introduce a function for copying registers; (PDP-11) make such function a macro */
    if (mode == MD_PCT) {                                                       /* TODO: consider moving this out of the function, modify reg_1.exp before the function is called */
        reg_1.exp += 2;
    }
    if (reg_1.exp < 0) {
        reg_1.exp += WIDTH;                                                     /* TODO: keep exp negative until error is cleared */
        return 1;  /* overflow */
    }
    trim(&reg_1);                                                               /* TODO: consider moving this out of the function and making a shared code */
    return 0;
}

static int calculate_div(enum mode_e mode)                                      /* TODO: (K&R) move type specification out */
{
    int i, digit, borrow, reg_1b = 0, exp_2 = reg_2.exp;
    struct reg_s reg_q;                                                         /* TODO: use the 3d static register */
    if (iszero(&reg_2)) {                                                       /* TODO: consider integrating this into the common case by limiting the number of calls to sub */
        clear(&reg_1);
        reg_1.exp = (WIDTH - 1);                                                /* TODO: keep exp negative until error is cleared */
        return 1;  /* overflow */
    }
    clear(&reg_q);
    reg_q.exp = normalize(&reg_1) - normalize(&reg_2) + (WIDTH - 1);
    reg_q.neg = reg_1.neg ^ reg_2.neg;                                          /* TODO: consider moving this out of the function; (PDP-11) consider using != instead of ^ */
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
    digit = 0;
    while (reg_1b != 0 || compare(&reg_1, &reg_2) >= 0) {                       /* TODO: use a build-key to enable this rounding */
        borrow = sub(&reg_1, &reg_2);
        reg_1b -= borrow;
        digit += 1;
    }
    if (digit >= 5) {                                                           /* TODO: introduce a separate function for adding 1 to a register (here only reg_1) */
        clear(&reg_1);
        reg_1.d[0] = 1;
        add(&reg_q, &reg_1);
    }
    if (mode == MD_PCT) {                                                       /* TODO: consider moving this out of the function, modify reg_1.exp before the function is called */
        reg_q.exp -= 2;
    }
    justify_right(&reg_2);
    reg_2.exp = exp_2;
    reg_1 = reg_q;                                                              /* TODO: introduce a function for copying registers; (PDP-11) make such function a macro */
    if (reg_1.exp < 0) {
        reg_1.exp += WIDTH;                                                     /* TODO: keep exp negative until error is cleared */
        if (reg_1.exp < 0) {
            reg_1.exp += WIDTH;
        }
        return 1;  /* overflow */
    }
    trim(&reg_1);                                                               /* TODO: consider moving this out of the function and making a shared code */
    return 0;
}

static int iszero(struct reg_s *reg)                                            /* TODO: (K&R) move type specification out */
{
    int i;                                                                      /* TODO: (PDP-11) use register modifier */
    for (i = 0; i < WIDTH; ++i) {                                               /* TODO: (PDP-11) use do-while loop */
        if (reg->d[i] != 0) {                                                   /* TODO: (PDP-11) use pointer with post-increment */
            return 0;
        }
    }
    return 1;
}

static void clear(struct reg_s *reg)                                            /* TODO: (K&R) move type specification out */
{
    int i;                                                                      /* TODO: (PDP-11) use register modifier */
    for (i = 0; i < WIDTH; ++i) {                                               /* TODO: (PDP-11) use do-while loop */
        reg->d[i] = 0;                                                          /* TODO: (PDP-11) use pointer with post-increment */
    }
    reg->exp = 0;                                                               /* TODO: consider moving these out of the function */
    reg->neg = 0;
}

static void justify_right(struct reg_s *reg)                                    /* TODO: (K&R) move type specification out */
{
    while (!islimit_right(reg)) {
        shift_right(reg);
        reg->exp -= 1;
    }
    if (iszero(reg)) {
        reg->neg = 0;
    }
}

static void justify_left(struct reg_s *reg)                                     /* TODO: (K&R) move type specification out */
{
    while (!islimit_left(reg)) {
        shift_left(reg);
        reg->exp += 1;
    }
}

static int normalize(struct reg_s *reg)                                         /* TODO: (K&R) move type specification out */
{
    int exp = reg->exp;
    reg->exp = 0;
    justify_left(reg);                                                          /* TODO: consider reworking this without justify_left, embed and simplify */
    return exp + reg->exp;
}

static void trim(struct reg_s *reg)                                             /* TODO: (K&R) move type specification out */
{
    while (reg->exp >= WIDTH) {
        shift_right(reg);
        reg->exp -= 1;
    }
}

static void align(struct reg_s *reg_a, struct reg_s *reg_b)                     /* TODO: (K&R) move type specification out */
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

static int compare(struct reg_s *reg_a, struct reg_s *reg_b)                    /* TODO: (K&R) move type specification out */
{
    int i;                                                                      /* TODO: (PDP-11) use register modifier */
    for (i = WIDTH - 1; i >= 0; --i) {                                          /* TODO: (PDP-11) use do-while loop */
        if (reg_a->d[i] > reg_b->d[i]) {                                        /* TODO: (PDP-11) use pointers with pre-decrement; (PDP-11) use local variables */
            return 1;                                                           /* TODO: just break if reduced to greater_than_or_equal */
        }
        if (reg_a->d[i] < reg_b->d[i]) {
            return -1;                                                          /* TODO: return 0 if reduced to greater_than_or_equal */
        }
    }
    return 0;                                                                   /* TODO: return 1 if reduced to greater_than_or_equal */
}

static void exchange(struct reg_s *reg_a, struct reg_s *reg_b)                  /* TODO: (K&R) move type specification out */
{
    struct reg_s reg_x = *reg_b;                                                /* TODO: avoid using additional register, exchange digits one-by-one */
    *reg_b = *reg_a;
    *reg_a = reg_x;
}

static int add(struct reg_s *reg_dst, struct reg_s *reg_src)                    /* TODO: (K&R) move type specification out */
{
    int i, digit, carry = 0;                                                    /* TODO: (PDP-11) use register modifier */
    for (i = 0; i < WIDTH; ++i) {                                               /* TODO: (PDP-11) use do-while loop */
        digit = reg_dst->d[i] + reg_src->d[i] + carry;                          /* TODO: (PDP-11) use pointers with/without post-increment */
        if (digit < 10) {
            reg_dst->d[i] = digit;
            carry = 0;
        } else {
            reg_dst->d[i] = digit - 10;                                         /* TODO: (PDP-11) move saving to the array out of the if-else */
            carry = 1;
        }
    }
    return carry;
}

static int sub(struct reg_s *reg_dst, struct reg_s *reg_src)                    /* TODO: consider reworking with addition of the complementary value; (K&R) move type specification out */
{
    int i, digit, borrow = 0;                                                   /* TODO: (PDP-11) use register modifier */
    for (i = 0; i < WIDTH; ++i) {                                               /* TODO: (PDP-11) use do-while loop */
        digit = reg_dst->d[i] - reg_src->d[i] - borrow;                         /* TODO: (PDP-11) use pointers with/without post-increment */
        if (digit >= 0) {
            reg_dst->d[i] = digit;
            borrow = 0;
        } else {
            reg_dst->d[i] = digit + 10;                                         /* TODO: (PDP-11) move saving to the array out of the if-else */
            borrow = 1;
        }
    }
    return borrow;
}

static int islimit_left(struct reg_s *reg)                                      /* TODO: (K&R) move type specification out */
{
    return reg->d[WIDTH - 1] != 0 || reg->exp == WIDTH - 1;
}

static int islimit_right(struct reg_s *reg)                                     /* TODO: (K&R) move type specification out */
{
    return reg->d[0] != 0 || reg->exp == 0;
}

static void shift_left(struct reg_s *reg)                                       /* TODO: (K&R) move type specification out */
{
    int i;                                                                      /* TODO: (PDP-11) use register modifier */
    for (i = WIDTH - 1; i > 0; --i) {                                           /* TODO: (PDP-11) use do-while loop */
        reg->d[i] = reg->d[i - 1];                                              /* TODO: (PDP-11) use pointers with pre-decrement */
    }
    reg->d[0] = 0;
}

static void shift_right(struct reg_s *reg)                                      /* TODO: consider decrementing exp also in this function; (K&R) move type specification out */
{
    int i, digit, carry;                                                        /* TODO: (PDP-11) use register modifier */
    carry = (reg->d[0] >= 5);                                                   /* TODO: use a build-key to enable rounding in shift_right, by default value is truncated */
    for (i = 0; i < WIDTH - 1; ++i) {                                           /* TODO: (PDP-11) use do-while loop */
        digit = reg->d[i + 1] + carry;
        if (digit < 10) {                                                       /* TODO: introduce a separate function for adding 1 to a register (here arbitrary register), call it when necessary after shift is completed */
            reg->d[i] = digit;                                                  /* TODO: (PDP-11) use pointers with post-increment */
            carry = 0;
        } else {
            reg->d[i] = 0;
            carry = 1;
        }
    }
    reg->d[WIDTH - 1] = carry;
}
