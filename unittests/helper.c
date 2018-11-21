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

#include "helper.h"

#include "utst.h"

#include <stdio.h>
#include <stdlib.h>

static void halt(const char msg[], const char s[], int pos)
{
    fprintf(stderr, "\nHALT: %s\n+ '%s'\n+  %*s\n",
            msg, s, pos + 1, "^");
}

int set_reg(struct reg_s *reg, const char s[])
{
    /* Indexes over the destination register mantissa. */
    int ia;     /* index of the next most significant digit */
    int ib;     /* index of the next least significant digit */

    /* Indexes over the source pattern string. */
    int jm;     /* index of a symbol next to the leading '+/-' */
    int jl;     /* index of '[' if present, or equal to ip */
    int jr;     /* index of ']' if present, or equal to im */
    int jp;     /* index of 'p' if present, or equal to iz */
    int jz;     /* index of the trailing '\0' */

    int i, j;
    char c;

    for (i = 0; i < WIDTH; ++i) {
        reg->d[i] = 0;
    }
    reg->exp = -1;  /* unassigned */
    c = s[0];
    reg->neg = (c == '-');

    /* Locate mantissa, exponent, and '[..]' part. */
    jm = (c == '+' || c == '-');
    for (jz = jm; s[jz] != '\0'; ++jz);
    for (jp = jm; s[jp] != 'p' && jp < jz; ++jp);
    for (jl = jm; s[jl] != '[' && jl < jp; ++jl);
    for (jr = jp - 1; s[jr] != ']' && jr >= jm; --jr);

    if (jm == jp) {
        halt("empty mantissa, digit expected", s, jm);
        exit(EXIT_FAILURE);
    }

    if (jr < jl && jm <= jr) {
        halt("closing ']' without opening '['", s, jr);
        exit(EXIT_FAILURE);
    }
    if (jr < jl && jl < jp) {
        halt("opening '[' without closing ']'", s, jl);
        exit(EXIT_FAILURE);
    }

    /* Process mantissa digits right to the optional '[..]' part. */
    for (ib = 0, j = jp - 1; j > jr; --j) {
        c = s[j];
        if (c >= '0' && c <= '9') {
            if (ib >= WIDTH) {
                return USKIP;
            }
            reg->d[ib++] = c - '0';
        } else if (c == '.') {
            if (jp < jz) {
                halt("found '.' while exponent given", s, j);
                exit(EXIT_FAILURE);
            }
            if (reg->exp >= 0) {
                halt("repeated '.' found", s, j);
                exit(EXIT_FAILURE);
            }
            reg->exp = ib;
        } else {
            halt("invalid symbol, digit or '.' expected", s, j);
            exit(EXIT_FAILURE);
        }
    }

    if (jl < jr) {
        /* Process mantissa digits left to the '[..]' part. */
        for (ia = WIDTH - 1, j = jm; j < jl; ++j) {
            c = s[j];
            if (c >= '0' && c <= '9') {
                if (ia < ib) {
                    return USKIP;
                }
                reg->d[ia--] = c - '0';
            } else if (c == '.') {
                if (jp < jz) {
                    halt("found '.' while exponent given", s, j);
                    exit(EXIT_FAILURE);
                }
                if (reg->exp >= 0) {
                    halt("repeated '.' found", s, j);
                    exit(EXIT_FAILURE);
                }
                reg->exp = ia + 1;
            } else {
                halt("invalid symbol, digit or '.' expected", s, j);
                exit(EXIT_FAILURE);
            }
        }

        /* Process the auto-fill '[..]' part. */
        if (jr - jl == 2) {
            c = s[jl + 1];
            if (c < '0' || c > '9') {
                halt("invalid auto-fill, digit expected", s, jl + 1);
                exit(EXIT_FAILURE);
            }
            for (i = ib; i <= ia; ++i) {
                reg->d[i] = c - '0';
            }

        } else if (jr - jl == 3) {
            char c1 = s[jl + 1];
            char c2 = s[jl + 2];
            int d;      /* starting digit 1..9 */
            char inc;   /* increment: '+' or '-' */
            int dir;    /* direction: <- (1) or -> (0) */

            if (c1 >= '0' && c1 <= '9') {
                d = c1 - '0';
                inc = c2;
                dir = 0;
            } else if (c2 >= '0' && c2 <= '9') {
                d = c2 - '0';
                inc = c1;
                dir = 1;
            } else {
                halt("invalid auto-fill, digit missed", s, jl + 1);
                exit(EXIT_FAILURE);
            }
            if (d == 0) {
                halt("invalid starting digit, '1' to '9' expected ",
                        s, jl + 1 + dir);
                exit(EXIT_FAILURE);
            }
            if (inc != '+' && inc != '-') {
                halt("invalid auto-fill direction, '+' or '-' expected",
                        s, jl + 1 + (1 - dir));
                exit(EXIT_FAILURE);
            }

            if (dir) {
                for (i = ib; i <= ia; ++i) {
                    reg->d[i] = d;
                    if (inc == '+') {
                        if (++d > 9) d = 1;     /* [+D] */
                    } else {
                        if (--d < 1) d = 9;     /* [-D] */
                    }
                }
            } else {
                for (i = ia; i >= ib; --i) {
                    reg->d[i] = d;
                    if (inc == '+') {
                        if (++d > 9) d = 1;     /* [D+] */
                    } else {
                        if (--d < 1) d = 9;     /* [D-] */
                    }
                }
            }

        } else {
            halt("invalid auto-fill, digit and '+' or '-' expected",
                    s, jl + 1);
            exit(EXIT_FAILURE);
        }
    }

    if (jp < jz) {
        int exp, neg;
        j = jp + 1;

        /* Process exponent, 'w' part if given. */
        c = s[j];
        neg = (c == '-');
        j += (c == '+' || c == '-');
        for (exp = 0; j < jz; ++j) {
            if (s[j] == 'w') {
                exp += WIDTH;
            } else {
                break;
            }
        }
        reg->exp = neg ? -exp : +exp;

        /* Process exponent, numeric part if given. */
        if (j < jz) {
            if (exp != 0) {
                c = s[j];
                if (c != '+' && c != '-') {
                    halt("invalid sign, '+' or '-' expected", s, j);
                    exit(EXIT_FAILURE);
                }
                neg = (c == '-');
                j += 1;
            }
            if (j == jz) {
                halt("empty exponent, digit expected", s, j);
                exit(EXIT_FAILURE);
            }
            for (exp = 0; j < jz; ++j) {
                char c = s[j];
                if (c < '0' || c > '9') {
                    halt("invalid exponent, digit expected", s, j);
                    exit(EXIT_FAILURE);
                }
                exp *= 10;
                if (exp >= 100) {
                    halt("maximum two digits in exponent", s, j);
                    exit(EXIT_FAILURE);
                }
                exp += c - '0';
            }
            reg->exp += neg ? -exp : +exp;

        } else if (exp == 0 /* the 'w' part is also omitted */) {
            halt("empty exponent, digit or 'w' expected", s, j);
            exit(EXIT_FAILURE);
        }

    } else if (reg->exp == -1 /* unassigned */) {
        reg->exp = 0;
    }

    return UPASS;
}

int match_reg(struct reg_s *reg, const char s[])
{
    struct reg_s reg_match;
    int i;

    if (set_reg(&reg_match, s) != UPASS) {
        return USKIP;
    }

    for (i = 0; i < WIDTH; ++i) {
        if (reg->d[i] != reg_match.d[i]) {
            return UFAIL;
        }
    }
    if (reg->exp != reg_match.exp) {
        return UFAIL;
    }
    if (reg->neg != reg_match.neg) {
        return UFAIL;
    }

    return UPASS;
}
