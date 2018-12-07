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

/* TODO: Extract private header from simulator source file. */
enum mode_e { MD_EQU, MD_PCT };

extern void setmode(enum mode_e mode);

UTST(setmode_ADD_EQU)
{
    control.func = FN_ADD;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_ADD);

    return UPASS;
}

UTST(setmode_SUB_EQU)
{
    control.func = FN_SUB;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_SUB);

    return UPASS;
}

UTST(setmode_MUL_EQU)
{
    control.func = FN_MUL;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_MUL);

    return UPASS;
}

UTST(setmode_DIV_EQU)
{
    control.func = FN_DIV;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_DIV);

    return UPASS;
}

UTST(setmode_ADD_PCT)
{
    control.func = FN_ADD;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_ADD);

    return UPASS;
}

UTST(setmode_SUB_PCT)
{
    control.func = FN_SUB;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_SUB);

    return UPASS;
}

UTST(setmode_MUL_PCT)
{
    control.func = FN_MUL;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_MUL);

    return UPASS;
}

UTST(setmode_DIV_PCT)
{
    control.func = FN_DIV;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_DIV);

    return UPASS;
}

UTST(setmode_REP_ADD_EQU)
{
    control.func = FN_REP_ADD;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_ADD);

    return UPASS;
}

UTST(setmode_REP_SUB_EQU)
{
    control.func = FN_REP_SUB;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_SUB);

    return UPASS;
}

UTST(setmode_REP_MUL_EQU)
{
    control.func = FN_REP_MUL;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_MUL);

    return UPASS;
}

UTST(setmode_REP_DIV_EQU)
{
    control.func = FN_REP_DIV;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_DIV);

    return UPASS;
}

UTST(setmode_REP_ADD_PCT)
{
    control.func = FN_REP_ADD;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_ADD);

    return UPASS;
}

UTST(setmode_REP_SUB_PCT)
{
    control.func = FN_REP_SUB;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_SUB);

    return UPASS;
}

UTST(setmode_REP_MUL_PCT)
{
    control.func = FN_REP_MUL;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_MUL);

    return UPASS;
}

UTST(setmode_REP_DIV_PCT)
{
    control.func = FN_REP_DIV;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_DIV);

    return UPASS;
}

UTST(setmode_PCT_ADD_EQU)
{
    control.func = FN_PCT_ADD;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_ADD);

    return UPASS;
}

UTST(setmode_PCT_SUB_EQU)
{
    control.func = FN_PCT_SUB;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_SUB);

    return UPASS;
}

UTST(setmode_PCT_MUL_EQU)
{
    control.func = FN_PCT_MUL;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_MUL);

    return UPASS;
}

UTST(setmode_PCT_DIV_EQU)
{
    control.func = FN_PCT_DIV;

    setmode(MD_EQU);

    UASRT(control.func == FN_REP_DIV);

    return UPASS;
}

UTST(setmode_PCT_ADD_PCT)
{
    control.func = FN_PCT_ADD;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_ADD);

    return UPASS;
}

UTST(setmode_PCT_SUB_PCT)
{
    control.func = FN_PCT_SUB;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_SUB);

    return UPASS;
}

UTST(setmode_PCT_MUL_PCT)
{
    control.func = FN_PCT_MUL;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_MUL);

    return UPASS;
}

UTST(setmode_PCT_DIV_PCT)
{
    control.func = FN_PCT_DIV;

    setmode(MD_PCT);

    UASRT(control.func == FN_PCT_DIV);

    return UPASS;
}
