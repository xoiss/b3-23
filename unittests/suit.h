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

UGRP("simulator-interface")
UTST(enum_key_e)
UTST(define_WIDTH)
UTST(struct_reg_s)
UTST(extern_reg_1)
UTST(extern_reg_2)
UTST(enum_state_e)
UTST(enum_func_e)
UTST(struct_control_s)
UTST(extern_control)
UTST(extern_key_pressed)

UGRP("simulator-state")
UTST(reg_1)
UTST(reg_2)
UTST(control)
UTST(initial_state)
UTST(compound_state)

UGRP("simulator-iszero")
UTST(iszero_0)
UTST(iszero_1)
UTST(iszero_10)
UTST(iszero_10000000)
UTST(iszero_n0p0000000)

UGRP("simulator-clear")
UTST(clear)

UGRP("simulator-compare")
UTST(compare_0_0)
UTST(compare_1_1)
UTST(compare_10_10)
UTST(compare_12_12)
UTST(compare_10000000_10000000)
UTST(compare_1_0)
UTST(compare_0_1)
UTST(compare_2_1)
UTST(compare_1_2)
UTST(compare_10_0)
UTST(compare_0_10)
UTST(compare_10_1)
UTST(compare_1_10)
UTST(compare_10_2)
UTST(compare_2_10)
UTST(compare_12_11)
UTST(compare_11_12)
UTST(compare_41_32)
UTST(compare_32_41)
UTST(compare_10000000_1)
UTST(compare_1_10000000)
UTST(compare_10000000_2)
UTST(compare_2_10000000)
UTST(compare_10000002_10000001)
UTST(compare_10000001_10000002)
UTST(compare_1_n1)
UTST(compare_n1_1)
UTST(compare_2_n1)
UTST(compare_n2_1)
UTST(compare_1_n2)
UTST(compare_n1_2)
UTST(compare_10_1p0)
UTST(compare_1p0_10)
UTST(compare_10_0p1)
UTST(compare_1p0_1)
UTST(compare_1_1p0)
UTST(compare_0p1_10)

UGRP("simulator-exchange")
UTST(exchange)

UGRP("simulator-add")
UTST(add_0_0)
UTST(add_1_2)
UTST(add_7_8)
UTST(add_10_20)
UTST(add_10_2)
UTST(add_12_57)
UTST(add_12_58)
UTST(add_12_59)
UTST(add_67_89)
UTST(add_11111111_22222222)
UTST(add_11111111_77777779)
UTST(add_11111111_88888889)
UTST(add_11111111_88888898)
UTST(add_11111111_77777979)
UTST(add_87654321_23456789)
UTST(add_11111111_n22222222)
UTST(add_n11111111_22222222)
UTST(add_11111111_2222222p2)
UTST(add_1111111p1_22222222)

UGRP("simulator-sub")
UTST(sub_0_0)
UTST(sub_3_2)
UTST(sub_15_8)
UTST(sub_30_20)
UTST(sub_12_2)
UTST(sub_69_57)
UTST(sub_70_58)
UTST(sub_71_59)
UTST(sub_156_89)
UTST(sub_33333333_22222222)
UTST(sub_88888890_77777779)
UTST(sub_100000000_88888889)
UTST(sub_100000009_88888898)
UTST(sub_88889090_77777979)
UTST(sub_111111110_23456789)
UTST(sub_33333333_n22222222)
UTST(sub_n33333333_22222222)
UTST(sub_33333333_2222222p2)
UTST(sub_3333333p3_22222222)

UGRP("simulator-islimit_left")
UTST(islimit_left_0)
UTST(islimit_left_1)
UTST(islimit_left_01234567)
UTST(islimit_left_12345678)
UTST(islimit_left_00p000000)
UTST(islimit_left_01p000000)
UTST(islimit_left_10p000000)
UTST(islimit_left_0p0000000)
UTST(islimit_left_0p1000000)
UTST(islimit_left_1p0000000)

UGRP("simulator-islimit_right")
UTST(islimit_right_0p)
UTST(islimit_right_1p)
UTST(islimit_right_10p)
UTST(islimit_right_12p)
UTST(islimit_right_10000000p)
UTST(islimit_right_0p0)
UTST(islimit_right_0p1)
UTST(islimit_right_1p0)
UTST(islimit_right_1000000p0)
UTST(islimit_right_0p0000000)
UTST(islimit_right_0p0000001)
UTST(islimit_right_0p0000010)
UTST(islimit_right_1p0000000)

UGRP("simulator-shift_left")
UTST(shift_left_87654321)
UTST(shift_left_n87654321)
UTST(shift_left_8765432p1)

UGRP("simulator-shift_right")
UTST(shift_right_87654321)
UTST(shift_right_n87654321)
UTST(shift_right_8765432p1)
UTST(shift_right_10)
UTST(shift_right_14)
UTST(shift_right_15)
UTST(shift_right_19)
UTST(shift_right_79)
UTST(shift_right_89)
UTST(shift_right_199)
UTST(shift_right_99999999)
UTST(shift_right_99999989)

UGRP("simulator-justify_left")
UTST(justify_left_0)
UTST(justify_left_1)
UTST(justify_left_12)
UTST(justify_left_01234567)
UTST(justify_left_12345678)
UTST(justify_left_0p0)
UTST(justify_left_00p000000)
UTST(justify_left_0p0000000)
UTST(justify_left_0p1)
UTST(justify_left_00p000001)
UTST(justify_left_0p0000001)
UTST(justify_left_00p100000)
UTST(justify_left_0p1000000)
UTST(justify_left_1p0)
UTST(justify_left_01p000000)
UTST(justify_left_1p0000000)
UTST(justify_left_10p0)
UTST(justify_left_10p000000)
UTST(justify_left_n1)
UTST(justify_left_n12345678)

UGRP("simulator-justify_right")
UTST(justify_right_0)
UTST(justify_right_1)
UTST(justify_right_10)
UTST(justify_right_12)
UTST(justify_right_10000000)
UTST(justify_right_11111111)
UTST(justify_right_0p0)
UTST(justify_right_0p1)
UTST(justify_right_1p0)
UTST(justify_right_1p2)
UTST(justify_right_1000000p0)
UTST(justify_right_1111111p1)
UTST(justify_right_0p0000000)
UTST(justify_right_0p0000001)
UTST(justify_right_0p0000010)
UTST(justify_right_0p1000000)
UTST(justify_right_1p0000000)
UTST(justify_right_1p0000002)
UTST(justify_right_1p1111111)
UTST(justify_right_1p1111110)
UTST(justify_right_n0)
UTST(justify_right_n1)
UTST(justify_right_n0p0)
UTST(justify_right_n1p0)

UGRP("simulator-normalize")
UTST(normalize_0)
UTST(normalize_1)
UTST(normalize_12)
UTST(normalize_01234567)
UTST(normalize_12345678)
UTST(normalize_0p0)
UTST(normalize_0p00)
UTST(normalize_00p000000)
UTST(normalize_0p0000000)
UTST(normalize_0p1)
UTST(normalize_0p01)
UTST(normalize_00p000001)
UTST(normalize_0p0000001)
UTST(normalize_0p10)
UTST(normalize_00p000010)
UTST(normalize_0p0000010)
UTST(normalize_00p010000)
UTST(normalize_0p0100000)
UTST(normalize_00p100000)
UTST(normalize_0p1000000)
UTST(normalize_1p0)
UTST(normalize_1p00)
UTST(normalize_01p000000)
UTST(normalize_1p0000000)
UTST(normalize_10p0)
UTST(normalize_10p000000)
UTST(normalize_010000p00)
UTST(normalize_100000p00)
UTST(normalize_0100000p0)
UTST(normalize_1000000p0)
UTST(normalize_n1)
UTST(normalize_n12345678)
UTST(normalize_n1p2345678)

UGRP("simulator-align")
UTST(align_0_0)
UTST(align_1_1)
UTST(align_1_2)
UTST(align_2_1)
UTST(align_11111111_22222222)
UTST(align_22222222_11111111)
UTST(align_1_10)
UTST(align_10_1)
UTST(align_1_10000000)
UTST(align_10000000_1)
UTST(align_0p1_1p0)
UTST(align_1p0_0p1)
UTST(align_0p0000001_1p0000000)
UTST(align_1p0000000_0p0000001)
UTST(align_1p4_7)
UTST(align_7_1p4)
UTST(align_1p5_7)
UTST(align_7_1p5)
UTST(align_1p49_7)
UTST(align_7_1p49)
UTST(align_1p50_7)
UTST(align_7_1p50)
UTST(align_1p4999999_7)
UTST(align_7_1p4999999)
UTST(align_1p5000000_7)
UTST(align_7_1p5000000)
UTST(align_1p9499999_7p7)
UTST(align_7p7_1p9499999)
UTST(align_1p9500000_7p7)
UTST(align_7p7_1p9500000)
UTST(align_1p9949999_7p77)
UTST(align_7p77_1p9949999)
UTST(align_1p9950000_7p77)
UTST(align_7p77_1p9950000)
UTST(align_1p9999994_77p777777)
UTST(align_77p777777_1p9999994)
UTST(align_1p9999995_77p777777)
UTST(align_77p777777_1p9999995)
UTST(align_n1_2)
UTST(align_1_n2)
UTST(align_n1p1111111_9p9)
UTST(align_1p1111111_n9p9)
UTST(align_n9p9_1p1111111)
UTST(align_9p9_n1p1111111)

UGRP("simulator-trim")
UTST(trim_0)
UTST(trim_1)
UTST(trim_10000000)
UTST(trim_11111111)
UTST(trim_0p0)
UTST(trim_0p1)
UTST(trim_1p0)
UTST(trim_1000000p0)
UTST(trim_1111111p1)
UTST(trim_0p0000000)
UTST(trim_0p0000001)
UTST(trim_0p1000000)
UTST(trim_1p0000000)
UTST(trim_1p1111111)
UTST(trim_p00000000)
UTST(trim_p00000004)
UTST(trim_p00000005)
UTST(trim_p00000010)
UTST(trim_p10000000)
UTST(trim_p99999994)
UTST(trim_p99999995)
UTST(trim_pp00000000)
UTST(trim_pp00000049)
UTST(trim_pp00000050)
UTST(trim_pp00000100)
UTST(trim_pp10000000)
UTST(trim_pp99999949)
UTST(trim_pp99999950)
UTST(trim_7pp00000000)
UTST(trim_7pp04999999)
UTST(trim_7pp05000000)
UTST(trim_7pp10000000)
UTST(trim_7pp94999999)
UTST(trim_7pp95000000)
UTST(trim_8pp00000000)
UTST(trim_8pp49999999)
UTST(trim_8pp50000000)
UTST(trim_9pp99999999)
UTST(trim_12345678pp)
UTST(trim_n11111111)
UTST(trim_np11111111)

UGRP("simulator-isrepeated")
UTST(isrepeated_NOP)
UTST(isrepeated_ADD)
UTST(isrepeated_SUB)
UTST(isrepeated_MUL)
UTST(isrepeated_DIV)
UTST(isrepeated_REP_ADD)
UTST(isrepeated_REP_SUB)
UTST(isrepeated_REP_MUL)
UTST(isrepeated_REP_DIV)
UTST(isrepeated_PCT_ADD)
UTST(isrepeated_PCT_SUB)
UTST(isrepeated_PCT_MUL)
UTST(isrepeated_PCT_DIV)

UGRP("simulator-ispercentage")
UTST(ispercentage_NOP)
UTST(ispercentage_ADD)
UTST(ispercentage_SUB)
UTST(ispercentage_MUL)
UTST(ispercentage_DIV)
UTST(ispercentage_REP_ADD)
UTST(ispercentage_REP_SUB)
UTST(ispercentage_REP_MUL)
UTST(ispercentage_REP_DIV)
UTST(ispercentage_PCT_ADD)
UTST(ispercentage_PCT_SUB)
UTST(ispercentage_PCT_MUL)
UTST(ispercentage_PCT_DIV)

UGRP("simulator-getfunc")
UTST(getfunc_NOP)
UTST(getfunc_ADD)
UTST(getfunc_SUB)
UTST(getfunc_MUL)
UTST(getfunc_DIV)
UTST(getfunc_REP_ADD)
UTST(getfunc_REP_SUB)
UTST(getfunc_REP_MUL)
UTST(getfunc_REP_DIV)
UTST(getfunc_PCT_ADD)
UTST(getfunc_PCT_SUB)
UTST(getfunc_PCT_MUL)
UTST(getfunc_PCT_DIV)

UGRP("simulator-setmode")
UTST(setmode)
