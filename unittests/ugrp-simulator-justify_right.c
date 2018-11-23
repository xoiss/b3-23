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

extern void justify_right(struct reg_s *reg);

UTST(justify_right_0)
{
    struct reg_s reg;

    USET(&reg, "0");

    justify_right(&reg);

    UMATCH(&reg, "0");

    return UPASS;
}

UTST(justify_right_1)
{
    struct reg_s reg;

    USET(&reg, "1");

    justify_right(&reg);

    UMATCH(&reg, "1");

    return UPASS;
}

UTST(justify_right_10)
{
    struct reg_s reg;

    USET(&reg, "10");

    justify_right(&reg);

    UMATCH(&reg, "10");

    return UPASS;
}

UTST(justify_right_12)
{
    struct reg_s reg;

    USET(&reg, "12");

    justify_right(&reg);

    UMATCH(&reg, "12");

    return UPASS;
}

UTST(justify_right_10000000)
{
    struct reg_s reg;

    USET(&reg, "1[0]");

    justify_right(&reg);

    UMATCH(&reg, "1[0]");

    return UPASS;
}

UTST(justify_right_11111111)
{
    struct reg_s reg;

    USET(&reg, "[1]");

    justify_right(&reg);

    UMATCH(&reg, "[1]");

    return UPASS;
}

UTST(justify_right_0p0)
{
    struct reg_s reg;

    USET(&reg, "0.0");

    justify_right(&reg);

    UMATCH(&reg, "0");

    return UPASS;
}

UTST(justify_right_0p1)
{
    struct reg_s reg;

    USET(&reg, "0.1");

    justify_right(&reg);

    UMATCH(&reg, "0.1");

    return UPASS;
}

UTST(justify_right_1p0)
{
    struct reg_s reg;

    USET(&reg, "1.0");

    justify_right(&reg);

    UMATCH(&reg, "1");

    return UPASS;
}

UTST(justify_right_1p2)
{
    struct reg_s reg;

    USET(&reg, "1.2");

    justify_right(&reg);

    UMATCH(&reg, "1.2");

    return UPASS;
}

UTST(justify_right_1000000p0)
{
    struct reg_s reg;

    USET(&reg, "1[0].0");

    justify_right(&reg);

    UMATCH(&reg, "01[0]");

    return UPASS;
}

UTST(justify_right_1111111p1)
{
    struct reg_s reg;

    USET(&reg, "1[1].1");

    justify_right(&reg);

    UMATCH(&reg, "1[1].1");

    return UPASS;
}

UTST(justify_right_0p0000000)
{
    struct reg_s reg;

    USET(&reg, "0.[0]");

    justify_right(&reg);

    UMATCH(&reg, "0");

    return UPASS;
}

UTST(justify_right_0p0000001)
{
    struct reg_s reg;

    USET(&reg, "0.[0]1");

    justify_right(&reg);

    UMATCH(&reg, "0.[0]1");

    return UPASS;
}

UTST(justify_right_0p0000010)
{
    struct reg_s reg;

    USET(&reg, "0.[0]10");

    justify_right(&reg);

    UMATCH(&reg, "00.[0]1");

    return UPASS;
}

UTST(justify_right_0p1000000)
{
    struct reg_s reg;

    USET(&reg, "0.1[0]");

    justify_right(&reg);

    UMATCH(&reg, "0.1");

    return UPASS;
}

UTST(justify_right_1p0000000)
{
    struct reg_s reg;

    USET(&reg, "1.[0]");

    justify_right(&reg);

    UMATCH(&reg, "1");

    return UPASS;
}

UTST(justify_right_1p0000002)
{
    struct reg_s reg;

    USET(&reg, "1.[0]2");

    justify_right(&reg);

    UMATCH(&reg, "1.[0]2");

    return UPASS;
}

UTST(justify_right_1p1111111)
{
    struct reg_s reg;

    USET(&reg, "1.[1]");

    justify_right(&reg);

    UMATCH(&reg, "1.[1]");

    return UPASS;
}

UTST(justify_right_1p1111110)
{
    struct reg_s reg;

    USET(&reg, "1.[1]0");

    justify_right(&reg);

    UMATCH(&reg, "01.[1]");

    return UPASS;
}

UTST(justify_right_n0)
{
    struct reg_s reg;

    USET(&reg, "-0");

    justify_right(&reg);

    UMATCH(&reg, "0");

    return UPASS;
}

UTST(justify_right_n1)
{
    struct reg_s reg;

    USET(&reg, "-1");

    justify_right(&reg);

    UMATCH(&reg, "-1");

    return UPASS;
}

UTST(justify_right_n0p0)
{
    struct reg_s reg;

    USET(&reg, "-0.0");

    justify_right(&reg);

    UMATCH(&reg, "0");

    return UPASS;
}

UTST(justify_right_n1p0)
{
    struct reg_s reg;

    USET(&reg, "-1.0");

    justify_right(&reg);

    UMATCH(&reg, "-1");

    return UPASS;
}
