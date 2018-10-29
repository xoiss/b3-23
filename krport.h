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

#ifndef KRPORT_H_
#define KRPORT_H_

#if __linux__ || __unix__
#define NIX_POSIX (1)
#endif
#if __WINNT__ && __MINGW32__
#define WIN_POSIX (1)
#endif
#if __RT11__ && __PDP11__
#define RT11_LEGACY (1)
#endif

#ifdef __STDC__
#define void void
#define const const
#else
#define void
#define const
#define fgetc getc
#if RT11_LEGACY
#define EXIT_SUCCESS (1)
#define EXIT_FAILURE (4)
#else
#define EXIT_SUCCESS
#define EXIT_FAILURE
#endif
#endif

#endif /* KRPORT_H_ */
