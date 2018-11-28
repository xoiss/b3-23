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

extern int islimit_right(struct reg_s *reg);

UTST(islimit_right_0p)
{
    struct reg_s reg;

    USET(&reg, "0.");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_1p)
{
    struct reg_s reg;

    USET(&reg, "1.");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_10p)
{
    struct reg_s reg;

    USET(&reg, "10.");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_12p)
{
    struct reg_s reg;

    USET(&reg, "12.");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_10000000p)
{
    struct reg_s reg;

    USET(&reg, "1[0].");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_0p0)
{
    struct reg_s reg;

    USET(&reg, "0.0");

    UASRT(!islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_0p1)
{
    struct reg_s reg;

    USET(&reg, "0.1");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_1p0)
{
    struct reg_s reg;

    USET(&reg, "1.0");

    UASRT(!islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_1000000p0)
{
    struct reg_s reg;

    USET(&reg, "1[0].0");

    UASRT(!islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_0p0000000)
{
    struct reg_s reg;

    USET(&reg, "0.[0]0");

    UASRT(!islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_0p0000001)
{
    struct reg_s reg;

    USET(&reg, "0.[0]1");

    UASRT(islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_0p0000010)
{
    struct reg_s reg;

    USET(&reg, "0.[0]10");

    UASRT(!islimit_right(&reg));

    return UPASS;
}

UTST(islimit_right_1p0000000)
{
    struct reg_s reg;

    USET(&reg, "1.[0]0");

    UASRT(!islimit_right(&reg));

    return UPASS;
}
