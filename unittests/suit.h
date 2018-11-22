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
