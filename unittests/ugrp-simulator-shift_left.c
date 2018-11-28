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

extern void shift_left(struct reg_s *reg);

UTST(shift_left_87654321)
{
    struct reg_s reg;

    USET(&reg, "[+1]");

    shift_left(&reg);

    UMATCH(&reg, "[+1]0");

    return UPASS;
}

UTST(shift_left_n87654321)
{
    struct reg_s reg;

    USET(&reg, "-[+1]");

    shift_left(&reg);

    UMATCH(&reg, "-[+1]0");

    return UPASS;
}

UTST(shift_left_8765432p1)
{
    struct reg_s reg;

    USET(&reg, "[+1]p1");

    shift_left(&reg);

    UMATCH(&reg, "[+1]0p1");

    return UPASS;
}
