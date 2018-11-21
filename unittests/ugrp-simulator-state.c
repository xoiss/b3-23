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
#include "misc.h"

#include "helper.h"

UTST(reg_1)
{
    UASRT(alen(reg_1.d) == WIDTH);
    UASRT(sizeof reg_1.exp);
    UASRT(sizeof reg_1.neg);

    return UPASS;
}

UTST(reg_2)
{
    UASRT(alen(reg_2.d) == WIDTH);
    UASRT(sizeof reg_2.exp);
    UASRT(sizeof reg_2.neg);

    return UPASS;
}

UTST(control)
{
    UASRT(sizeof control.state);
    UASRT(sizeof control.func);

    return UPASS;
}

UTST(initial_state)
{
    UMATCH(&reg_1, "0");
    UMATCH(&reg_2, "0");

    UASRT(control.state == ST_READY);
    UASRT(control.func == FN_NOP);

    return UPASS;
}

UTST(compound_state)
{
    USET(&reg_1, "+[1+]p1");
    USET(&reg_2, "-[9-]p2");

    control.state = ST_ERROR;
    control.func = FN_ADD;

    UMATCH(&reg_1, "+[1+]p1");
    UMATCH(&reg_2, "-[9-]p2");

    UASRT(control.state == ST_ERROR);
    UASRT(control.func == FN_ADD);

    return UPASS;
}
