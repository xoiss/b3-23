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

extern int normalize(struct reg_s *reg);

UTST(normalize_0)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0");

    exp = normalize(&reg);

    UMATCH(&reg, "0.[0]");

    UASRT(exp == 0 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_1)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "1");

    exp = normalize(&reg);

    UMATCH(&reg, "1.[0]");

    UASRT(exp == 0 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_12)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "12");

    exp = normalize(&reg);

    UMATCH(&reg, "12.[0]");

    UASRT(exp == 0 + WIDTH - 2);

    return UPASS;
}

UTST(normalize_01234567)
{
    struct reg_s reg;
    int exp;

    if (WIDTH == 1) return USKIP;

    USET(&reg, "0[1+]");

    exp = normalize(&reg);

    UMATCH(&reg, "[1+].0");

    UASRT(exp == 0 + 1);

    return UPASS;
}

UTST(normalize_12345678)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "[1+]");

    exp = normalize(&reg);

    UMATCH(&reg, "[1+]");

    UASRT(exp == 0 + 0);

    return UPASS;
}

UTST(normalize_0p0)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.0");

    exp = normalize(&reg);

    UMATCH(&reg, "0.[0]");

    UASRT(exp == 1 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_0p00)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.00");

    exp = normalize(&reg);

    UMATCH(&reg, "0.[0]");

    UASRT(exp == 2 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_00p000000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "00.[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "0.[0]");

    UASRT(exp == WIDTH - 2 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_0p0000000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "0.[0]");

    UASRT(exp == WIDTH - 1 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_0p1)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.1");

    exp = normalize(&reg);

    UMATCH(&reg, "1.[0]");

    UASRT(exp == 1 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_0p01)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.01");

    exp = normalize(&reg);

    UMATCH(&reg, "1.[0]");

    UASRT(exp == 2 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_00p000001)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "00.[0]1");

    exp = normalize(&reg);

    UMATCH(&reg, "1.[0]");

    UASRT(exp == WIDTH - 2 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_0p0000001)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.[0]1");

    exp = normalize(&reg);

    UMATCH(&reg, "1.[0]");

    UASRT(exp == WIDTH - 1 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_0p10)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.10");

    exp = normalize(&reg);

    UMATCH(&reg, "10.[0]");

    UASRT(exp == 2 + WIDTH - 2);

    return UPASS;
}

UTST(normalize_00p000010)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "00.[0]10");

    exp = normalize(&reg);

    UMATCH(&reg, "10.[0]");

    UASRT(exp == WIDTH - 2 + WIDTH - 2);

    return UPASS;
}

UTST(normalize_0p0000010)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.[0]10");

    exp = normalize(&reg);

    UMATCH(&reg, "10.[0]");

    UASRT(exp == WIDTH - 1 + WIDTH - 2);

    return UPASS;
}

UTST(normalize_00p010000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "00.01[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].000");

    UASRT(exp == WIDTH - 2 + 3);

    return UPASS;
}

UTST(normalize_0p0100000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.01[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].00");

    UASRT(exp == WIDTH - 1 + 2);

    return UPASS;
}

UTST(normalize_00p100000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "00.1[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].00");

    UASRT(exp == WIDTH - 2 + 2);

    return UPASS;
}

UTST(normalize_0p1000000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "0.1[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].0");

    UASRT(exp == WIDTH - 1 + 1);

    return UPASS;
}

UTST(normalize_1p0)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "1.0");

    exp = normalize(&reg);

    UMATCH(&reg, "10.[0]");

    UASRT(exp == 1 + WIDTH - 2);

    return UPASS;
}

UTST(normalize_1p00)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "1.00");

    exp = normalize(&reg);

    UMATCH(&reg, "100.[0]");

    UASRT(exp == 2 + WIDTH - 3);

    return UPASS;
}

UTST(normalize_01p000000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "01.[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].0");

    UASRT(exp == WIDTH - 2 + 1);

    return UPASS;
}

UTST(normalize_1p0000000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "1.[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0]");

    UASRT(exp == WIDTH - 1 + 0);

    return UPASS;
}

UTST(normalize_10p0)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "10.0");

    exp = normalize(&reg);

    UMATCH(&reg, "100.[0]");

    UASRT(exp == 1 + WIDTH - 3);

    return UPASS;
}

UTST(normalize_10p000000)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "10.[0]");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0]");

    UASRT(exp == WIDTH - 2 + 0);

    return UPASS;
}

UTST(normalize_010000p00)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "01[0].00");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].0");

    UASRT(exp == 2 + 1);

    return UPASS;
}

UTST(normalize_100000p00)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "1[0].00");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0]");

    UASRT(exp == 2 + 0);

    return UPASS;
}

UTST(normalize_0100000p0)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "01[0].0");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0].0");

    UASRT(exp == 1 + 1);

    return UPASS;
}

UTST(normalize_1000000p0)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "1[0].0");

    exp = normalize(&reg);

    UMATCH(&reg, "1[0]");

    UASRT(exp == 1 + 0);

    return UPASS;
}

UTST(normalize_n1)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "-1");

    exp = normalize(&reg);

    UMATCH(&reg, "-1.[0]");

    UASRT(exp == 0 + WIDTH - 1);

    return UPASS;
}

UTST(normalize_n12345678)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "-[1+]");

    exp = normalize(&reg);

    UMATCH(&reg, "-[1+]");

    UASRT(exp == 0 + 0);

    return UPASS;
}

UTST(normalize_n1p2345678)
{
    struct reg_s reg;
    int exp;

    USET(&reg, "-[1+]pw-1");

    exp = normalize(&reg);

    UMATCH(&reg, "-[1+]");

    UASRT(exp == WIDTH - 1 + 0);

    return UPASS;
}
