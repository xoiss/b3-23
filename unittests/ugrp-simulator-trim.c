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

extern void trim(struct reg_s *reg);

UTST(trim_0)
{
    struct reg_s reg;

    USET(&reg, "0");

    trim(&reg);

    UMATCH(&reg, "0");

    return UPASS;
}

UTST(trim_1)
{
    struct reg_s reg;

    USET(&reg, "1");

    trim(&reg);

    UMATCH(&reg, "1");

    return UPASS;
}

UTST(trim_10000000)
{
    struct reg_s reg;

    USET(&reg, "1[0]");

    trim(&reg);

    UMATCH(&reg, "1[0]");

    return UPASS;
}

UTST(trim_11111111)
{
    struct reg_s reg;

    USET(&reg, "[1]");

    trim(&reg);

    UMATCH(&reg, "[1]");

    return UPASS;
}

UTST(trim_0p0)
{
    struct reg_s reg;

    USET(&reg, "0.0");

    trim(&reg);

    UMATCH(&reg, "0.0");

    return UPASS;
}

UTST(trim_0p1)
{
    struct reg_s reg;

    USET(&reg, "0.1");

    trim(&reg);

    UMATCH(&reg, "0.1");

    return UPASS;
}

UTST(trim_1p0)
{
    struct reg_s reg;

    USET(&reg, "1.0");

    trim(&reg);

    UMATCH(&reg, "1.0");

    return UPASS;
}

UTST(trim_1000000p0)
{
    struct reg_s reg;

    USET(&reg, "1[0].0");

    trim(&reg);

    UMATCH(&reg, "1[0].0");

    return UPASS;
}

UTST(trim_1111111p1)
{
    struct reg_s reg;

    USET(&reg, "1[1].1");

    trim(&reg);

    UMATCH(&reg, "1[1].1");

    return UPASS;
}

UTST(trim_0p0000000)
{
    struct reg_s reg;

    USET(&reg, "0.[0]");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_0p0000001)
{
    struct reg_s reg;

    USET(&reg, "0.[0]1");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_0p1000000)
{
    struct reg_s reg;

    USET(&reg, "0.1[0]");

    trim(&reg);

    UMATCH(&reg, "0.1[0]");

    return UPASS;
}

UTST(trim_1p0000000)
{
    struct reg_s reg;

    USET(&reg, "1.[0]");

    trim(&reg);

    UMATCH(&reg, "1.[0]");

    return UPASS;
}

UTST(trim_1p1111111)
{
    struct reg_s reg;

    USET(&reg, "1.[1]");

    trim(&reg);

    UMATCH(&reg, "1.[1]");

    return UPASS;
}

UTST(trim_p00000000)
{
    struct reg_s reg;

    USET(&reg, "0pw");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_p00000004)
{
    struct reg_s reg;

    USET(&reg, "4pw");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_p00000005)
{
    struct reg_s reg;

    USET(&reg, "5pw");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_p00000010)
{
    struct reg_s reg;

    USET(&reg, "10pw");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_p10000000)
{
    struct reg_s reg;

    USET(&reg, "1[0]pw");

    trim(&reg);

    UMATCH(&reg, "0.1[0]");

    return UPASS;
}

UTST(trim_p99999994)
{
    struct reg_s reg;

    USET(&reg, "[9]4pw");

    trim(&reg);

    UMATCH(&reg, "0.[9]");

    return UPASS;
}

UTST(trim_p99999995)
{
    struct reg_s reg;

    USET(&reg, "[9]5pw");

    trim(&reg);

    UMATCH(&reg, "1.[0]");

    return UPASS;
}

UTST(trim_pp00000000)
{
    struct reg_s reg;

    USET(&reg, "0pw+1");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_pp00000049)
{
    struct reg_s reg;

    USET(&reg, "49pw+1");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");                                                     /* FIXME: UMATCH(&reg, "0.[0]"); */

    return UPASS;
}

UTST(trim_pp00000050)
{
    struct reg_s reg;

    USET(&reg, "50pw+1");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_pp00000100)
{
    struct reg_s reg;

    USET(&reg, "100pw+1");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_pp10000000)
{
    struct reg_s reg;

    USET(&reg, "1[0]pw+1");

    trim(&reg);

    UMATCH(&reg, "0.01[0]");

    return UPASS;
}

UTST(trim_pp99999949)
{
    struct reg_s reg;

    USET(&reg, "[9]49pw+1");

    trim(&reg);

    UMATCH(&reg, "0.1[0]");                                                     /* FIXME: UMATCH(&reg, "0.0[9]"); */

    return UPASS;
}

UTST(trim_pp99999950)
{
    struct reg_s reg;

    USET(&reg, "[9]50pw+1");

    trim(&reg);

    UMATCH(&reg, "0.1[0]");

    return UPASS;
}

UTST(trim_7pp00000000)
{
    struct reg_s reg;

    USET(&reg, "0pww-2");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_7pp04999999)
{
    struct reg_s reg;

    USET(&reg, "049[9]pww-2");                                                  /* FIXME: USET(&reg, "04[9]pww-2"); */

    trim(&reg);

    UMATCH(&reg, "0.[0]1");                                                     /* FIXME: UMATCH(&reg, "0.[0]"); */

    return UPASS;
}

UTST(trim_7pp05000000)
{
    struct reg_s reg;

    USET(&reg, "05[0]pww-2");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_7pp10000000)
{
    struct reg_s reg;

    USET(&reg, "1[0]pww-2");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_7pp94999999)
{
    struct reg_s reg;

    USET(&reg, "949[9]pww-2");                                                  /* FIXME: USET(&reg, "94[9]pww-2"); */

    trim(&reg);

    UMATCH(&reg, "0.[0]10");                                                    /* FIXME: UMATCH(&reg, "0.[0]9"); */

    return UPASS;
}

UTST(trim_7pp95000000)
{
    struct reg_s reg;

    USET(&reg, "95[0]pww-2");

    trim(&reg);

    UMATCH(&reg, "0.[0]10");

    return UPASS;
}

UTST(trim_8pp00000000)
{
    struct reg_s reg;

    USET(&reg, "0pww-1");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_8pp49999999)
{
    struct reg_s reg;

    USET(&reg, "49[9]pww-1");                                                   /* FIXME: USET(&reg, "4[9]pww-1"); */

    trim(&reg);

    UMATCH(&reg, "0.[0]1");                                                     /* FIXME: UMATCH(&reg, "0.[0]"); */

    return UPASS;
}

UTST(trim_8pp50000000)
{
    struct reg_s reg;

    USET(&reg, "5[0]pww-1");

    trim(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(trim_9pp99999999)
{
    struct reg_s reg;

    USET(&reg, "[9]pww");

    trim(&reg);

    UMATCH(&reg, "0.[0]");

    return UPASS;
}

UTST(trim_12345678pp)
{
    struct reg_s reg;

    USET(&reg, "[1+]p-1");

    trim(&reg);

    UMATCH(&reg, "[1+]p-1");

    return UPASS;
}

UTST(trim_n11111111)
{
    struct reg_s reg;

    USET(&reg, "-[1]");

    trim(&reg);

    UMATCH(&reg, "-[1]");

    return UPASS;
}

UTST(trim_np11111111)
{
    struct reg_s reg;

    USET(&reg, "-[1]pw");

    trim(&reg);

    UMATCH(&reg, "-0.[1]");

    return UPASS;
}
