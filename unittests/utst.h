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

#ifndef UTST_H_
#define UTST_H_

#define UPASS  (0)
#define USKIP  (-1)
#define UFAIL  (__LINE__)

#define UASRT(_expr)  do { if (!(_expr)) return UFAIL; } while(0)

#define UTST_DECL(_name)\
        extern int utst__##_name(void);

#define UTST_DEFN(_name)\
        int utst__##_name(void)

struct usuit_s {
    const char *name;
    int (*utst)(void);
    int failed;
    int skipped;
};

#define UGRP_INST(_name)\
        { _name, (int (*)(void))0, 0, 0 },

#define UTST_INST(_name)\
        { #_name, utst__##_name, 0, 0 },

#undef UGRP
#define UGRP(_name)

#undef UTST
#define UTST(_name)  UTST_DEFN(_name)

#endif /* UTST_H_ */
