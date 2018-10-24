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

#ifndef ADAPTER_B3_23_CONSOLE_H_                                                /* TODO: (K&R), (RT-11) limit file names to 6 symbols */
#define ADAPTER_B3_23_CONSOLE_H_

#define TARGET "Elektronika B3-23"                                              /* TODO: prepend with AD_ */
#define KEYS "C 0 1 2 3 4 5 6 7 8 9 . , + - * / % ="
#define STATE "indicator and second registers, operational triggers"

extern int process_key(char *c);                                                /* TODO: (PDP-11) return char or NULL, don't modify the argument */
extern const char *print_state(void);                                           /* TODO: (K&R) remove const; (PDP-11) publish the buffer, don't return a pointer */
                                                                                /* TODO: (K&R), (RT-11) limit identifiers to 6 symbols; (K&R) remove parameters */
#endif /* ADAPTER_B3_23_CONSOLE_H_ */
