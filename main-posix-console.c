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

#undef __STRICT_ANSI__
#define _POSIX_SOURCE

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "adapter-b3-23-console.h"

enum message_e { HELLO, BYE, PROMPT };

#if __linux__ || __unix__
#define SEND_EOF "Ctrl+D at a new line, or "
#elif __WINNT__  && __MINGW32__
#define SEND_EOF "Ctrl+Z at a new line and then ENTER, or "
#else
#define SEND_EOF ""
#endif

static const char *const messages[] = {

    /* HELLO */
    TARGET " simulator.\n"
    "Type in a sequence of keystrokes and hit ENTER to confirm.\n"
    "The following keys are recognized:\n"
    "  " KEYS "\n"
    "Simulator will process them one-by-one and print the state:\n"
    "  " STATE "\n"
    "To cancel press " SEND_EOF "Ctrl+C, or whatever you have.\n"
    "Enjoy! Best regards, xoiss, Moscow, 2018.\n",

    /* BYE */
    "\nSee you!\n"
    "And visit: http://www.phantom.sannata.ru/forum/\n",

    /* PROMPT */
    "> "
};

static int hide_dialogs;

static int isinteractive(void);
static int isendofstream(void);

static void print_message(enum message_e message_id);
static void process_input(void);

int main(void)
{
    hide_dialogs = !isinteractive();
    print_message(HELLO);
    while (!isendofstream()) {
        print_message(PROMPT);
        process_input();
    }
    print_message(BYE);
    return EXIT_SUCCESS;
}

static int isinteractive(void)
{
    if (isatty(fileno(stdin)) == 0) {
#if __linux__ || __unix__
        if (errno != EINVAL && errno != ENOTTY) {
            perror("isatty");
            exit(EXIT_FAILURE);
        }
#endif
        return 0;
    }
    return 1;
}

static int isendofstream(void)
{
    return ferror(stdin) || feof(stdin);
}

static void print_message(enum message_e message_id)
{
    if (!hide_dialogs) {
        fputs(messages[message_id], stdout);
        fflush(stdout);
    }
}

static void process_input(void)
{
    char s[256], *p, c;
    while ((p = fgets(s, sizeof s, stdin)) != NULL) {
        while ((c = *p++) != '\0') {
            if (c == '\n') {
                return;
            }
            if (process_key(&c)) {
                fprintf(stdout, "[%c] => %s\n", c, print_state());
                fflush(stdout);
            }
        }
    }
}
