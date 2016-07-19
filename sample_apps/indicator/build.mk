# Copyright (C) 2008-2016 Marvell International Ltd.
# All Rights Reserved.
#

exec-y += indicator
indicator-objs-y := src/main.c src/wc.c
indicator-cflags-y := -I$(d)/src -DAPPCONFIG_DEBUG_ENABLE=1

# Applications could also define custom linker files if required using following:
#indicator-ld-y := /path/to/ldscript

# Applications could also define custom board files if required using following:
#indicator-board-y := /path/to/boardfile
