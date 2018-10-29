/*
 * Copyright 2018 Alexander A. Strelets. All rights reserved.
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

#ifndef ADCON_H_
#define ADCON_H_

#include "krport.h"

#define TARGET "Elektronika B3-23"
#define KEYS "C 0 1 2 3 4 5 6 7 8 9 . , + - * / % ="
#define STATE "indicator and second registers, operational triggers"

extern int process_key();
extern const char *print_state();

#endif /* ADCON_H_ */
