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

FORCE_TARGET := b3-23

ifneq (,$(FORCE_TARGET))
    TARGET := $(FORCE_TARGET)
else
    TARGET := $(lastword $(subst /, ,$(CURDIR)))
endif

ifneq (,$(WINDIR))
    TARGET := $(TARGET).exe
endif

SOURCES := $(shell ls *.c 2>/dev/null)

CC = gcc

CFLAGS = -ansi -pedantic -pedantic-errors\
        -Wall -Wconversion -Wextra -Werror\
        -O0 -g3 -fmessage-length=0

.PHONY: all clean

ifneq (,$(SOURCES))
all: $(TARGET)
$(TARGET): $(SOURCES)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
else
all:
	@echo No source files found.
endif

clean:
	$(RM) *.o $(TARGET)
