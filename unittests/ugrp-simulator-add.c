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

extern int add(struct reg_s *reg_dst, struct reg_s *reg_src);

UTST(add_0_0)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "0");
    USET(&reg_src, "0");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "0");
    UMATCH(&reg_src, "0");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_1_2)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "1");
    USET(&reg_src, "2");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "3");
    UMATCH(&reg_src, "2");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_7_8)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "7");
    USET(&reg_src, "8");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "15");
    UMATCH(&reg_src, "8");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_10_20)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "10");
    USET(&reg_src, "20");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "30");
    UMATCH(&reg_src, "20");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_10_2)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "10");
    USET(&reg_src, "2");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "12");
    UMATCH(&reg_src, "2");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_12_57)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "12");
    USET(&reg_src, "57");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "69");
    UMATCH(&reg_src, "57");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_12_58)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "12");
    USET(&reg_src, "58");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "70");
    UMATCH(&reg_src, "58");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_12_59)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "12");
    USET(&reg_src, "59");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "71");
    UMATCH(&reg_src, "59");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_67_89)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "67");
    USET(&reg_src, "89");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "156");
    UMATCH(&reg_src, "89");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_11111111_22222222)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]");
    USET(&reg_src, "[2]");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[3]");
    UMATCH(&reg_src, "[2]");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_11111111_77777779)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]");
    USET(&reg_src, "[7]9");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[8]90");
    UMATCH(&reg_src, "[7]9");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_11111111_88888889)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]");
    USET(&reg_src, "[8]9");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[0]");
    UMATCH(&reg_src, "[8]9");

    UASRT(carry == 1);

    return UPASS;
}

UTST(add_11111111_88888898)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]");
    USET(&reg_src, "[8]98");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[0]9");
    UMATCH(&reg_src, "[8]98");

    UASRT(carry == 1);

    return UPASS;
}

UTST(add_11111111_77777979)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]");
    USET(&reg_src, "[7]979");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[8]9090");
    UMATCH(&reg_src, "[7]979");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_87654321_23456789)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[+1]");
    USET(&reg_src, "[-9]");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[1]0");
    UMATCH(&reg_src, "[-9]");

    UASRT(carry == 1);

    return UPASS;
}

UTST(add_11111111_n22222222)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "+[1]");
    USET(&reg_src, "-[2]");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "+[3]");
    UMATCH(&reg_src, "-[2]");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_n11111111_22222222)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "-[1]");
    USET(&reg_src, "+[2]");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "-[3]");
    UMATCH(&reg_src, "+[2]");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_11111111_2222222p2)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]p0");
    USET(&reg_src, "[2]p1");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[3]p0");
    UMATCH(&reg_src, "[2]p1");

    UASRT(carry == 0);

    return UPASS;
}

UTST(add_1111111p1_22222222)
{
    struct reg_s reg_dst, reg_src;
    int carry;

    USET(&reg_dst, "[1]p1");
    USET(&reg_src, "[2]p0");

    carry = add(&reg_dst, &reg_src);

    UMATCH(&reg_dst, "[3]p1");
    UMATCH(&reg_src, "[2]p0");

    UASRT(carry == 0);

    return UPASS;
}
