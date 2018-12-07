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

extern int isrepeated(void);

UTST(isrepeated_NOP)
{
    control.func = FN_NOP;

    UASRT(!isrepeated());

    return UPASS;
}

UTST(isrepeated_ADD)
{
    control.func = FN_ADD;

    UASRT(!isrepeated());

    return UPASS;
}

UTST(isrepeated_SUB)
{
    control.func = FN_SUB;

    UASRT(!isrepeated());

    return UPASS;
}

UTST(isrepeated_MUL)
{
    control.func = FN_MUL;

    UASRT(!isrepeated());

    return UPASS;
}

UTST(isrepeated_DIV)
{
    control.func = FN_DIV;

    UASRT(!isrepeated());

    return UPASS;
}

UTST(isrepeated_REP_ADD)
{
    control.func = FN_REP_ADD;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_REP_SUB)
{
    control.func = FN_REP_SUB;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_REP_MUL)
{
    control.func = FN_REP_MUL;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_REP_DIV)
{
    control.func = FN_REP_DIV;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_PCT_ADD)
{
    control.func = FN_PCT_ADD;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_PCT_SUB)
{
    control.func = FN_PCT_SUB;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_PCT_MUL)
{
    control.func = FN_PCT_MUL;

    UASRT(isrepeated());

    return UPASS;
}

UTST(isrepeated_PCT_DIV)
{
    control.func = FN_PCT_DIV;

    UASRT(isrepeated());

    return UPASS;
}
