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

extern int sub(struct reg_s *reg_dst, struct reg_s *reg_src);

UTST(sub_0_0)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "0");
    USET(&reg_src, "0");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "0");
    UMATCH(&reg_src, "0");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_3_2)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "3");
    USET(&reg_src, "2");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "1");
    UMATCH(&reg_src, "2");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_15_8)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "15");
    USET(&reg_src, "8");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "7");
    UMATCH(&reg_src, "8");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_30_20)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "30");
    USET(&reg_src, "20");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "10");
    UMATCH(&reg_src, "20");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_12_2)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "12");
    USET(&reg_src, "2");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "10");
    UMATCH(&reg_src, "2");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_69_57)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "69");
    USET(&reg_src, "57");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "12");
    UMATCH(&reg_src, "57");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_70_58)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "70");
    USET(&reg_src, "58");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "12");
    UMATCH(&reg_src, "58");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_71_59)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "71");
    USET(&reg_src, "59");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "12");
    UMATCH(&reg_src, "59");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_156_89)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "156");
    USET(&reg_src, "89");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "67");
    UMATCH(&reg_src, "89");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_33333333_22222222)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[3]");
    USET(&reg_src, "[2]");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]");
    UMATCH(&reg_src, "[2]");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_88888890_77777779)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[8]90");
    USET(&reg_src, "[7]9");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]");
    UMATCH(&reg_src, "[7]9");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_100000000_88888889)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[0]");
    USET(&reg_src, "[8]9");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]");
    UMATCH(&reg_src, "[8]9");

    UASRT(borrow == 1);

    return UPASS;
}

UTST(sub_100000009_88888898)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[0]9");
    USET(&reg_src, "[8]98");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]");
    UMATCH(&reg_src, "[8]98");

    UASRT(borrow == 1);

    return UPASS;
}

UTST(sub_88889090_77777979)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[8]9090");
    USET(&reg_src, "[7]979");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]");
    UMATCH(&reg_src, "[7]979");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_111111110_23456789)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[1]0");
    USET(&reg_src, "[-9]");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[+1]");
    UMATCH(&reg_src, "[-9]");

    UASRT(borrow == 1);

    return UPASS;
}

UTST(sub_33333333_n22222222)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "+[3]");
    USET(&reg_src, "-[2]");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "+[1]");
    UMATCH(&reg_src, "-[2]");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_n33333333_22222222)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "-[3]");
    USET(&reg_src, "+[2]");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "-[1]");
    UMATCH(&reg_src, "+[2]");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_33333333_2222222p2)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[3]p0");
    USET(&reg_src, "[2]p1");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]p0");
    UMATCH(&reg_src, "[2]p1");

    UASRT(borrow == 0);

    return UPASS;
}

UTST(sub_3333333p3_22222222)
{
    struct reg_s reg_dst, reg_src;
    int borrow;

    USET(&reg_dst, "[3]p1");
    USET(&reg_src, "[2]p0");

    borrow = sub(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]p1");
    UMATCH(&reg_src, "[2]p0");

    UASRT(borrow == 0);

    return UPASS;
}
