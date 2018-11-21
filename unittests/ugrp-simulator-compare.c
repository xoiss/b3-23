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

extern int compare(struct reg_s *reg_a, struct reg_s *reg_b);

UTST(compare_0_0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "0");
    USET(&reg_b, "0");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_1_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "1");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_10_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "10");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_12_12)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "12");
    USET(&reg_b, "12");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_10000000_10000000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1[0]");
    USET(&reg_b, "1[0]");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_1_0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "0");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_0_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "0");
    USET(&reg_b, "1");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_2_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "2");
    USET(&reg_b, "1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_1_2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "2");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10_0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "0");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_0_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "0");
    USET(&reg_b, "10");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_1_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "10");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10_2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "2");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_2_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "2");
    USET(&reg_b, "10");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_12_11)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "12");
    USET(&reg_b, "11");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_11_12)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "11");
    USET(&reg_b, "12");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_41_32)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "41");
    USET(&reg_b, "32");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_32_41)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "32");
    USET(&reg_b, "41");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10000000_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1[0]0");
    USET(&reg_b, "1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_1_10000000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "1[0]0");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10000000_2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1[0]0");
    USET(&reg_b, "2");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_2_10000000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "2");
    USET(&reg_b, "1[0]0");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10000002_10000001)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1[0]2");
    USET(&reg_b, "1[0]1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_10000001_10000002)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1[0]1");
    USET(&reg_b, "1[0]2");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_1_n1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "+1");
    USET(&reg_b, "-1");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_n1_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "-1");
    USET(&reg_b, "+1");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_2_n1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "+2");
    USET(&reg_b, "-1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_n2_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "-2");
    USET(&reg_b, "+1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_1_n2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "+1");
    USET(&reg_b, "-2");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_n1_2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "-1");
    USET(&reg_b, "+2");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_10_1p0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "10p1");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_1p0_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10p1");
    USET(&reg_b, "10");

    UASRT(compare(&reg_a, &reg_b) == 0);

    return UPASS;
}

UTST(compare_10_0p1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "1p1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_1p0_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10p1");
    USET(&reg_b, "1");

    UASRT(compare(&reg_a, &reg_b) > 0);

    return UPASS;
}

UTST(compare_1_1p0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "10p1");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}

UTST(compare_0p1_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1p1");
    USET(&reg_b, "10");

    UASRT(compare(&reg_a, &reg_b) < 0);

    return UPASS;
}
