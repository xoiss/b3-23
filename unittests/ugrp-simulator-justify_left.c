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

#include "helper.h"

extern void justify_left(struct reg_s *reg);

UTST(justify_left_0)
{
    struct reg_s reg;

    USET(&reg, "0");

    justify_left(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(justify_left_1)
{
    struct reg_s reg;

    USET(&reg, "1");

    justify_left(&reg);

    UMATCH(&reg, "1.[0]");

    return UPASS;
}

UTST(justify_left_12)
{
    struct reg_s reg;

    USET(&reg, "12");

    justify_left(&reg);

    UMATCH(&reg, "12.[0]");

    return UPASS;
}

UTST(justify_left_01234567)
{
    struct reg_s reg;

    if (WIDTH == 1) return USKIP;

    USET(&reg, "0[1+]");

    justify_left(&reg);

    UMATCH(&reg, "[1+].0");

    return UPASS;
}

UTST(justify_left_12345678)
{
    struct reg_s reg;

    USET(&reg, "[1+]");

    justify_left(&reg);

    UMATCH(&reg, "[1+]");

    return UPASS;
}

UTST(justify_left_0p0)
{
    struct reg_s reg;

    USET(&reg, "0.0");

    justify_left(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(justify_left_00p000000)
{
    struct reg_s reg;

    USET(&reg, "00.[0]");

    justify_left(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(justify_left_0p0000000)
{
    struct reg_s reg;

    USET(&reg, "0.[0]");

    justify_left(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(justify_left_0p1)
{
    struct reg_s reg;

    USET(&reg, "0.1");

    justify_left(&reg);

    UMATCH(&reg, "0.1[0]");

    return UPASS;
}

UTST(justify_left_00p000001)
{
    struct reg_s reg;

    USET(&reg, "00.[0]1");

    justify_left(&reg);

    UMATCH(&reg, "0.[0]10");

    return UPASS;
}

UTST(justify_left_0p0000001)
{
    struct reg_s reg;

    USET(&reg, "0.[0]1");

    justify_left(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(justify_left_00p100000)
{
    struct reg_s reg;

    USET(&reg, "00.1[0]");

    justify_left(&reg);

    UMATCH(&reg, "0.1[0]");

    return UPASS;
}

UTST(justify_left_0p1000000)
{
    struct reg_s reg;

    USET(&reg, "0.1[0]");

    justify_left(&reg);

    UMATCH(&reg, "0.1[0]");

    return UPASS;
}

UTST(justify_left_1p0)
{
    struct reg_s reg;

    USET(&reg, "1.0");

    justify_left(&reg);

    UMATCH(&reg, "1.[0]");

    return UPASS;
}

UTST(justify_left_01p000000)
{
    struct reg_s reg;

    USET(&reg, "01.[0]");

    justify_left(&reg);

    UMATCH(&reg, "1.[0]");

    return UPASS;
}

UTST(justify_left_1p0000000)
{
    struct reg_s reg;

    USET(&reg, "1.[0]");

    justify_left(&reg);

    UMATCH(&reg, "1.[0]");

    return UPASS;
}

UTST(justify_left_10p0)
{
    struct reg_s reg;

    USET(&reg, "10.0");

    justify_left(&reg);

    UMATCH(&reg, "10.[0]");

    return UPASS;
}

UTST(justify_left_10p000000)
{
    struct reg_s reg;

    USET(&reg, "10.[0]");

    justify_left(&reg);

    UMATCH(&reg, "10.[0]");

    return UPASS;
}

UTST(justify_left_n1)
{
    struct reg_s reg;

    USET(&reg, "-1");

    justify_left(&reg);

    UMATCH(&reg, "-1.[0]");

    return UPASS;
}

UTST(justify_left_n12345678)
{
    struct reg_s reg;

    USET(&reg, "-[1+]");

    justify_left(&reg);

    UMATCH(&reg, "-[1+]");

    return UPASS;
}
