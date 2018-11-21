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

#include "utst.h"
#include "misc.h"

#include "simulator-b3-23.h"

/* Header shall allow repeated inclusion. */
#include "simulator-b3-23.h"

UTST(enum_key_e)
{
    UASRT(sizeof (enum key_e));

    UASRT(KEY_C == 0);
    UASRT(KEY_0 == 1);
    UASRT(KEY_1 == 2);
    UASRT(KEY_2 == 3);
    UASRT(KEY_3 == 4);
    UASRT(KEY_4 == 5);
    UASRT(KEY_5 == 6);
    UASRT(KEY_6 == 7);
    UASRT(KEY_7 == 8);
    UASRT(KEY_8 == 9);
    UASRT(KEY_9 == 10);
    UASRT(KEY_P == 11);
    UASRT(KEY_ADD == 12);
    UASRT(KEY_SUB == 13);
    UASRT(KEY_MUL == 14);
    UASRT(KEY_DIV == 15);
    UASRT(KEY_EQU == 16);
    UASRT(KEY_PCT == 17);

    return UPASS;
}

UTST(define_WIDTH)
{
    UASRT(WIDTH >= 2);

    return UPASS;
}

UTST(struct_reg_s)
{
    UASRT(alen(sfld(struct reg_s, d)) == WIDTH);
    UASRT(sizeof sfld(struct reg_s, exp));
    UASRT(sizeof sfld(struct reg_s, neg));

    return UPASS;
}

UTST(extern_reg_1)
{
    UASRT(alen(reg_1.d) == WIDTH);
    UASRT(sizeof reg_1.exp);
    UASRT(sizeof reg_1.neg);

    return UPASS;
}

UTST(extern_reg_2)
{
    UASRT(alen(reg_2.d) == WIDTH);
    UASRT(sizeof reg_2.exp);
    UASRT(sizeof reg_2.neg);

    return UPASS;
}

UTST(enum_state_e)
{
    UASRT(sizeof (enum state_e));

    UASRT(ST_READY == 0);
    UASRT(ST_INT == 1);
    UASRT(ST_FRAC == 2);
    UASRT(ST_ERROR == 3);

    return UPASS;
}

UTST(enum_func_e)
{
    UASRT(sizeof (enum func_e));

    UASRT(FN_NOP == 0);
    UASRT(FN_ADD == 1);
    UASRT(FN_SUB == 2);
    UASRT(FN_MUL == 3);
    UASRT(FN_DIV == 4);
    UASRT(FN_REP_ADD == 5);
    UASRT(FN_REP_SUB == 6);
    UASRT(FN_REP_MUL == 7);
    UASRT(FN_REP_DIV == 8);
    UASRT(FN_PCT_ADD == 9);
    UASRT(FN_PCT_SUB == 10);
    UASRT(FN_PCT_MUL == 11);
    UASRT(FN_PCT_DIV == 12);

    return UPASS;
}

UTST(struct_control_s)
{
    UASRT(sizeof sfld(struct control_s, state));
    UASRT(sizeof sfld(struct control_s, func));

    return UPASS;
}

UTST(extern_control)
{
    UASRT(sizeof control.state);
    UASRT(sizeof control.func);

    return UPASS;
}

UTST(extern_key_pressed)
{
    UASRT(sizeof &key_pressed);

    return UPASS;
}
