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

extern void align(struct reg_s *reg_a, struct reg_s *reg_b);

UTST(align_0_0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "0");
    USET(&reg_b, "0");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "0");
    UMATCH(&reg_b, "0");

    return UPASS;
}

UTST(align_1_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "1");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1");
    UMATCH(&reg_b, "1");

    return UPASS;
}

UTST(align_1_2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "2");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1");
    UMATCH(&reg_b, "2");

    return UPASS;
}

UTST(align_2_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "2");
    USET(&reg_b, "1");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2");
    UMATCH(&reg_b, "1");

    return UPASS;
}

UTST(align_11111111_22222222)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "[1]");
    USET(&reg_b, "[2]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "[1]");
    UMATCH(&reg_b, "[2]");

    return UPASS;
}

UTST(align_22222222_11111111)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "[2]");
    USET(&reg_b, "[1]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "[2]");
    UMATCH(&reg_b, "[1]");

    return UPASS;
}

UTST(align_1_10)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "10");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1");
    UMATCH(&reg_b, "10");

    return UPASS;
}

UTST(align_10_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "10");
    USET(&reg_b, "1");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "10");
    UMATCH(&reg_b, "1");

    return UPASS;
}

UTST(align_1_10000000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "1[0]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1");
    UMATCH(&reg_b, "1[0]");

    return UPASS;
}

UTST(align_10000000_1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1[0]");
    USET(&reg_b, "1");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1[0]");
    UMATCH(&reg_b, "1");

    return UPASS;
}

UTST(align_0p1_1p0)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "0.1");
    USET(&reg_b, "1.0");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "0.1");
    UMATCH(&reg_b, "1.0");

    return UPASS;
}

UTST(align_1p0_0p1)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.0");
    USET(&reg_b, "0.1");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1.0");
    UMATCH(&reg_b, "0.1");

    return UPASS;
}

UTST(align_0p0000001_1p0000000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "0.[0]1");
    USET(&reg_b, "1.[0]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "0.[0]1");
    UMATCH(&reg_b, "1.[0]");

    return UPASS;
}

UTST(align_1p0000000_0p0000001)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.[0]");
    USET(&reg_b, "0.[0]1");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1.[0]");
    UMATCH(&reg_b, "0.[0]1");

    return UPASS;
}

UTST(align_1p4_7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.4");
    USET(&reg_b, "7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1");
    UMATCH(&reg_b, "7");

    return UPASS;
}

UTST(align_7_1p4)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7");
    USET(&reg_b, "1.4");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7");
    UMATCH(&reg_b, "1");

    return UPASS;
}

UTST(align_1p5_7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.5");
    USET(&reg_b, "7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2");
    UMATCH(&reg_b, "7");

    return UPASS;
}

UTST(align_7_1p5)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7");
    USET(&reg_b, "1.5");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7");
    UMATCH(&reg_b, "2");

    return UPASS;
}

UTST(align_1p49_7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.49");
    USET(&reg_b, "7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2");                                                        /* FIXME: UMATCH(&reg_a, "1"); */
    UMATCH(&reg_b, "7");

    return UPASS;
}

UTST(align_7_1p49)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7");
    USET(&reg_b, "1.49");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7");
    UMATCH(&reg_b, "2");                                                        /* FIXME: UMATCH(&reg_b, "1"); */

    return UPASS;
}

UTST(align_1p50_7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.50");
    USET(&reg_b, "7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2");
    UMATCH(&reg_b, "7");

    return UPASS;
}

UTST(align_7_1p50)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7");
    USET(&reg_b, "1.50");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7");
    UMATCH(&reg_b, "2");

    return UPASS;
}

UTST(align_1p4999999_7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.49[9]");                                                    /* FIXME: USET(&reg_a, "1.4[9]"); */
    USET(&reg_b, "7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2");                                                        /* FIXME: UMATCH(&reg_a, "1"); */
    UMATCH(&reg_b, "7");

    return UPASS;
}

UTST(align_7_1p4999999)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7");
    USET(&reg_b, "1.49[9]");                                                    /* FIXME: USET(&reg_b, "1.4[9]"); */

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7");
    UMATCH(&reg_b, "2");                                                        /* FIXME: UMATCH(&reg_b, "1"); */

    return UPASS;
}

UTST(align_1p5000000_7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.5[0]");
    USET(&reg_b, "7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2");
    UMATCH(&reg_b, "7");

    return UPASS;
}

UTST(align_7_1p5000000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7");
    USET(&reg_b, "1.5[0]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7");
    UMATCH(&reg_b, "2");

    return UPASS;
}

UTST(align_1p9499999_7p7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.949[9]");                                                   /* FIXME: USET(&reg_a, "1.94[9]"); */
    USET(&reg_b, "7.7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2.0");                                                      /* FIXME: UMATCH(&reg_a, "1.9"); */
    UMATCH(&reg_b, "7.7");

    return UPASS;
}

UTST(align_7p7_1p9499999)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7.7");
    USET(&reg_b, "1.949[9]");                                                   /* FIXME: USET(&reg_b, "1.94[9]"); */

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7.7");
    UMATCH(&reg_b, "2.0");                                                      /* FIXME: UMATCH(&reg_b, "1.9"); */

    return UPASS;
}

UTST(align_1p9500000_7p7)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.95[0]");
    USET(&reg_b, "7.7");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2.0");
    UMATCH(&reg_b, "7.7");

    return UPASS;
}

UTST(align_7p7_1p9500000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7.7");
    USET(&reg_b, "1.95[0]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7.7");
    UMATCH(&reg_b, "2.0");

    return UPASS;
}

UTST(align_1p9949999_7p77)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.9949[9]");                                                  /* FIXME: USET(&reg_a, "1.994[9]"); */
    USET(&reg_b, "7.77");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2.00");                                                     /* FIXME: UMATCH(&reg_a, "1.99"); */
    UMATCH(&reg_b, "7.77");

    return UPASS;
}

UTST(align_7p77_1p9949999)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7.77");
    USET(&reg_b, "1.9949[9]");                                                  /* FIXME: USET(&reg_b, "1.994[9]"); */

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7.77");
    UMATCH(&reg_b, "2.00");                                                     /* FIXME: UMATCH(&reg_b, "1.99"); */

    return UPASS;
}

UTST(align_1p9950000_7p77)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.995[0]");
    USET(&reg_b, "7.77");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "2.00");
    UMATCH(&reg_b, "7.77");

    return UPASS;
}

UTST(align_7p77_1p9950000)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "7.77");
    USET(&reg_b, "1.995[0]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "7.77");
    UMATCH(&reg_b, "2.00");

    return UPASS;
}

UTST(align_1p9999994_77p777777)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.[9]4");
    USET(&reg_b, "77.[7]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "01.[9]");
    UMATCH(&reg_b, "77.[7]");

    return UPASS;
}

UTST(align_77p777777_1p9999994)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "77.[7]");
    USET(&reg_b, "1.[9]4");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "77.[7]");
    UMATCH(&reg_b, "01.[9]");

    return UPASS;
}

UTST(align_1p9999995_77p777777)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.[9]5");
    USET(&reg_b, "77.[7]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "02.[0]");
    UMATCH(&reg_b, "77.[7]");

    return UPASS;
}

UTST(align_77p777777_1p9999995)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "77.[7]");
    USET(&reg_b, "1.[9]5");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "77.[7]");
    UMATCH(&reg_b, "02.[0]");

    return UPASS;
}

UTST(align_n1_2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "-1");
    USET(&reg_b, "2");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "-1");
    UMATCH(&reg_b, "2");

    return UPASS;
}

UTST(align_1_n2)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1");
    USET(&reg_b, "-2");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1");
    UMATCH(&reg_b, "-2");

    return UPASS;
}

UTST(align_n1p1111111_9p9)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "-1.[1]");
    USET(&reg_b, "9.9");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "-1.1");
    UMATCH(&reg_b, "9.9");

    return UPASS;
}

UTST(align_1p1111111_n9p9)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "1.[1]");
    USET(&reg_b, "-9.9");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "1.1");
    UMATCH(&reg_b, "-9.9");

    return UPASS;
}

UTST(align_n9p9_1p1111111)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "-9.9");
    USET(&reg_b, "1.[1]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "-9.9");
    UMATCH(&reg_b, "1.1");

    return UPASS;
}

UTST(align_9p9_n1p1111111)
{
    struct reg_s reg_a, reg_b;

    USET(&reg_a, "9.9");
    USET(&reg_b, "-1.[1]");

    align(&reg_a, &reg_b);

    UMATCH(&reg_a, "9.9");
    UMATCH(&reg_b, "-1.1");

    return UPASS;
}
