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

#include <stdio.h>
#include <stdlib.h>

#include "utst.h"
#include "misc.h"

#undef UTST
#define UTST(_name)  UTST_DECL(_name)
#include "suit.h"

struct usuit_s usuit[] = {
    #undef UGRP
    #define UGRP(_name)  UGRP_INST(_name)
    #undef UTST
    #define UTST(_name)  UTST_INST(_name)
    #include "suit.h"
};

int main(void)
{
    unsigned i, igrp = (unsigned)-1;
    int skipped = 0;
    int failed = 0;

    for (i = 0; i < alen(usuit); ++i) {
        if (!usuit[i].utst) {
            /* It's a group entry. */
            if (igrp == (unsigned)-1) {
                fputs("Legend: . - passed, - - skipped, ! - failed\n",
                        stdout);
            } else {
                skipped += usuit[igrp].skipped;
                failed += usuit[igrp].failed;
                fputc('\n', stdout);
            }
            fputs(usuit[igrp = i].name, stdout);
            fputs(": ", stdout);

        } else {
            /* It's a test entry. */
            int status;
            if (igrp == (unsigned)-1) {
                fputs("HALT: unit-tests without a group\n", stderr);
                return EXIT_FAILURE;
            }
            status = usuit[i].utst();
            if (status == UPASS) {
                fputc('.', stdout);
            } else if (status == USKIP) {
                usuit[igrp].skipped += 1;
                fputc('-', stdout);
            } else {
                usuit[i].failed = status;  /* save the line number */
                usuit[igrp].failed += 1;
                fputc('!', stdout);
            }
        }

        fflush(stdout);
    }

    if (igrp == (unsigned)-1) {
        fputs("NOTE: unit-tests suit is empty\n", stderr);
        return EXIT_SUCCESS;
    }

    /* Close the last tests group. */
    skipped += usuit[igrp].skipped;
    failed += usuit[igrp].failed;
    fputc('\n', stdout);
    fflush(stdout);

    if (failed == 0) {
        if (skipped != 0) {
            fputs("NOTE: some of unit-tests were skipped\n", stderr);
        }
        fputs("INFO: all unit-tests passed\n", stderr);
        return EXIT_SUCCESS;
    }

    fputs("The following unit-tests failed:\n", stdout);
    for (i = 0; i < alen(usuit); ++i) {
        if (usuit[i].failed == 0) {
            continue;
        }
        fprintf(stdout, !usuit[i].utst
                    ? "- group '%s', %u failed:\n"
                    : "  - test '%s', at line %u\n",
                usuit[i].name, usuit[i].failed);
    }
    fflush(stdout);

    fputs("WARN: some of unit-tests failed\n", stderr);
    return EXIT_SUCCESS;
}
