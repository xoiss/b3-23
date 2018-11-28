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

extern void shift_right(struct reg_s *reg);

UTST(shift_right_87654321)
{
    struct reg_s reg;

    USET(&reg, "[+1]");

    shift_right(&reg);

    UMATCH(&reg, "0[+2]");

    return UPASS;
}

UTST(shift_right_n87654321)
{
    struct reg_s reg;

    USET(&reg, "-[+1]");

    shift_right(&reg);

    UMATCH(&reg, "-0[+2]");

    return UPASS;
}

UTST(shift_right_8765432p1)
{
    struct reg_s reg;

    USET(&reg, "[+1]p1");

    shift_right(&reg);

    UMATCH(&reg, "0[+2]p1");

    return UPASS;
}


UTST(shift_right_10)
{
    struct reg_s reg;

    USET(&reg, "10");

    shift_right(&reg);

    UMATCH(&reg, "1");

    return UPASS;
}

UTST(shift_right_14)
{
    struct reg_s reg;

    USET(&reg, "14");

    shift_right(&reg);

    UMATCH(&reg, "1");

    return UPASS;
}

UTST(shift_right_15)
{
    struct reg_s reg;

    USET(&reg, "15");

    shift_right(&reg);

    UMATCH(&reg, "2");

    return UPASS;
}

UTST(shift_right_19)
{
    struct reg_s reg;

    USET(&reg, "19");

    shift_right(&reg);

    UMATCH(&reg, "2");

    return UPASS;
}

UTST(shift_right_79)
{
    struct reg_s reg;

    USET(&reg, "79");

    shift_right(&reg);

    UMATCH(&reg, "8");

    return UPASS;
}

UTST(shift_right_89)
{
    struct reg_s reg;

    USET(&reg, "89");

    shift_right(&reg);

    UMATCH(&reg, "9");

    return UPASS;
}

UTST(shift_right_199)
{
    struct reg_s reg;

    USET(&reg, "199");

    shift_right(&reg);

    UMATCH(&reg, "20");

    return UPASS;
}

UTST(shift_right_99999999)
{
    struct reg_s reg;

    USET(&reg, "[9]");

    shift_right(&reg);

    UMATCH(&reg, "1[0]");

    return UPASS;
}

UTST(shift_right_99999989)
{
    struct reg_s reg;

    USET(&reg, "[9]89");

    shift_right(&reg);

    UMATCH(&reg, "0[9]");

    return UPASS;
}
