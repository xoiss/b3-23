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

#include "krport.h"

#if NIX_POSIX || WIN_POSIX
#undef __STRICT_ANSI__
#define _POSIX_SOURCE
#endif

#if NIX_POSIX || WIN_POSIX
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#endif

#include <stdio.h>

#include "adcon.h"

#if NIX_POSIX
#define SEND_EOF "Ctrl+D at a new line, or Ctrl+C, or"
#endif
#if WIN_POSIX
#define SEND_EOF "Ctrl+Z at a new line and then ENTER, or Ctrl+C, or"
#endif
#if RT11_LEGACY
#define SEND_EOF "CTRL/Z at a new line, or CTRL/C, or"
#endif
#ifndef SEND_EOF
#define SEND_EOF "... hmmm,"
#endif

static int hide_dialogs;

static int isinteractive();
static int isendofstream();

static void print_hello();
static void print_prompt();
static void print_bye();
static void prc_input();

int main(void)
{
    hide_dialogs = !isinteractive();
    print_hello();
    while (!isendofstream()) {
        print_prompt();
        prc_input();
    }
    print_bye();
    return EXIT_SUCCESS;
}

static int isinteractive(void)
{
#if NIX_POSIX || WIN_POSIX
    if (isatty(fileno(stdin)) == 0) {
#if NIX_POSIX
        if (errno != EINVAL && errno != ENOTTY) {
            perror("isatty");
            exit(EXIT_FAILURE);
        }
#endif
        return 0;
    }
#endif
    return 1;
}

static int isendofstream(void)
{
    return ferror(stdin) || feof(stdin);
}

static void print_hello(void)
{
    if (!hide_dialogs) {
        fputs(TARGET, stdout);
        fputs(" simulator.\n\
Type in a sequence of keystrokes and hit ENTER to confirm.\n\
The following keys are recognized:\n  ", stdout);
        fputs(KEYS, stdout);
        fputs("\n\
Simulator will process them one-by-one and print the state:\n  ",
stdout);
        fputs(STATE, stdout);
        fputs("\nTo cancel press ", stdout);
        fputs(SEND_EOF, stdout);
        fputs(" whatever you have.\n\
Enjoy! Best regards, xoiss, Moscow, 2018.\n", stdout);
        fflush(stdout);
    }
}

static void print_prompt(void)
{
    if (!hide_dialogs) {
        fputs("> ", stdout);
        fflush(stdout);
    }
}

static void print_bye(void)
{
    if (!hide_dialogs) {
        fputs("\n\
See you!\n\
And visit: http://www.phantom.sannata.ru/forum/\n", stdout);
        fflush(stdout);
    }
}

static void prc_input(void)
{
    char s[256], *p, c;
    while ((p = fgets(s, sizeof s, stdin)) != NULL) {
        while ((c = *p++) != '\0') {
            if (c == '\n') {
                return;
            }
            if (prc_key(&c)) {
                fprintf(stdout, "[%c] => %s\n", c, print_state());
                fflush(stdout);
            }
        }
    }
}
