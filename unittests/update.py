# Copyright 2018 Alexander A. Strelets. All rights reserved.
#
# Author: Alexander A. Strelets
# e-mail: streletsaa@gmail.com
#
# This program is the proprietary software of the Author and/or his
# licensors, and may only be used, duplicated, modified or distributed
# pursuant to the terms and conditions of a separate, written license
# agreement executed between you and the Author (an "Authorized
# License"). Except as set forth in an Authorized License, the Author
# grants no license (express or implied), right to use, or waiver of
# any kind with respect to the Software, and the Author expressly
# reserves all rights in and to the Software and all intellectual
# property rights therein.
#
# IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS
# SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY THE AUTHOR AND
# DISCONTINUE ALL USE OF THE SOFTWARE.


import errno
import os
import re
import shutil
import subprocess
import sys


args = sys.argv[1:]
if not args:
    raise SystemExit("HALT: missing compiler name and options")


# Scan the current folder for unit-test groups and tests definitions.

# Will process all C source files in the current directory having names
# starting with "ugrp-". Each file describes a single unit-tests group.
re_ugrp = re.compile(r"^ugrp-([\w-]+)\.c$", re.MULTILINE)

# Inside a unit-test file will search for functions defined with UTST().
# Each function defines a single unit-test.
re_utst = re.compile(r"^\s*int utst__(\w+)\(void\)", re.MULTILINE)

for dir_scan in os.walk(os.curdir):
    file_names = dir_scan[2]
    break
else:
    raise SystemExit("HALT: directory %r not found" % os.curdir)

ugrp_names = re_ugrp.findall("\n".join(file_names))

ugrps = {ugrp_name: "ugrp-" + ugrp_name + ".c"
         for ugrp_name in ugrp_names}

# Finally ugrps dictionary will contain unit-test group names in the set
# of its keys and lists ot tests in each group as values of their keys.
# The set of groups is unordered. But each list of tests in a group
# inherits the order of tests from the order of UTST-functions as they
# are defined (occured) in the corresponding ugrp- source file.
all_utst_names = []
for (ugrp_name, file_name) in ugrps.items():
    try:
        out = subprocess.check_output(args=args + [file_name])
    except subprocess.CalledProcessError:
        raise SystemExit("HALT: failed to preprocess file %r"
                         % file_name)
    except OSError as e:
        if e.args[0] == errno.ENOENT:
            raise SystemExit("HALT: compiler %r not found" % args[0])
        else:
            raise SystemExit("CRIT: OS error %r" % e.args[0])

    utst_names = re_utst.findall(out.decode())

    ugrps[ugrp_name] = utst_names
    all_utst_names += utst_names

uniq_names = set(all_utst_names)
if len(uniq_names) != len(all_utst_names):
    conflicting_names = []
    for name in all_utst_names:
        if name in uniq_names:
            uniq_names.remove(name)
        else:
            conflicting_names.append(name)
    raise SystemExit("HALT: conflicting unit-tests defined: %s"
                     % ", ".join(sorted(set(conflicting_names))))


# Take the ordered list of unit-test groups from the suit header file.

try:
    fsuit = open("suit.h", "r")
except:
    raise SystemExit("HALT: missed unit-tests suit header file")

re_ugrp = re.compile(r'UGRP\("(.+)"\)')

ugrps_index = []
fline = 0
for s in fsuit:
    fline += 1
    m = re_ugrp.search(s)
    if m:
        ugrp_name = m.group(1)
        ugrps_index.append((fline, ugrp_name))

if not ugrps_index:
    ugrps_index.append((None, "dummy"))


# Update the unit-test suit header file.

try:
    fsuit_new = open("suit.h.new", "w")
except:
    raise SystemExit("HALT: failed to create suit header file")

fsuit.seek(0)
fline = 0
banner = True
empty = True
for (ugrp_line, ugrp_name) in ugrps_index:
    for s in fsuit:
        fline += 1
        if fline == ugrp_line:
            banner = False
            break
        if banner:
            if s.strip("\n \t"):
                fsuit_new.write(s)
            else:
                banner = False
    else:
        if ugrp_line is not None:
            raise SystemExit("HALT: can't locate indexed group %r"
                             % ugrp_name)

    if ugrp_name == "dummy":
        continue

    empty = False
    fsuit_new.write('\nUGRP("%s")\n' % ugrp_name)
    if ugrp_name in ugrps:
        for utst_name in ugrps[ugrp_name]:
            fsuit_new.write("UTST(%s)\n" % utst_name)
        del ugrps[ugrp_name]

fsuit.close()


# Append newly defined unit-test groups.

for ugrp_name in sorted(ugrps):
    empty = False
    fsuit_new.write('\nUGRP("%s")\n' % ugrp_name)
    for utst_name in ugrps[ugrp_name]:
        fsuit_new.write("UTST(%s)\n" % utst_name)

if empty:
    fsuit_new.write('\nUGRP("dummy")\n')

fsuit_new.close()


# Commit results.

shutil.move("suit.h.new", "suit.h")
