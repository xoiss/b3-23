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

#ifndef HELPER_H_
#define HELPER_H_

#include "simulator-b3-23.h"

extern int set_reg(struct reg_s *reg, const char s[]);
extern int match_reg(struct reg_s *reg, const char s[]);

#define USET(_reg, _s)\
    do {\
        if (set_reg(_reg, _s) != UPASS) return USKIP;\
    } while(0)

#define UMATCH(_reg, _s)\
    do {\
        int rc = match_reg(_reg, _s);\
        if (rc != UPASS) return rc;\
    } while(0)

#endif /* HELPER_H_ */
