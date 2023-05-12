# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
#include $(TOP)/extmod/extmod.mk

FROZEN ?= 1

# Set CFLAGS and libraries.
CFLAGS += -I. -I$(BUILD) -I$(TOP)
CFLAGS += -Os -DNDEBUG
#CFLAGS += -Wall -Werror
CFLAGS += -fdata-sections -ffunction-sections
LIBS += -lm

CC = patmos-clang

# Define the required source files.
SRC_C = \
    main.c \
    mphalport.c \
    shared/runtime/stdout_helpers.c \
    shared/runtime/pyexec.c \
    shared/readline/readline.c \
#    shared/runtime/gchelper_generic.c \
#    mphalport.c \
#    shared/libc/printf.c \


SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c
#SRC_QSTR += shared/runtime/pyexec.c

ifeq ($(FROZEN), 1)
	SRC_C += $(BUILD)/_frozen_mpy.c
endif

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
PART_FILES = $(addprefix $(TOP)/, $(subst .o,.c,$(PY_CORE_O_BASENAME))) $(SRC_C)
FILES = $(subst shared,$(TOP)/shared,$(PART_FILES))

# Define the top-level target, the main firmware.
all: clean $(BUILD)/firmware.elf

quick: $(BUILD)/firmware.elf

# Compile all .py files
mpy:
	$(foreach var, $(wildcard py/*.py), ./$(TOP)/mpy-cross/build/mpy-cross $(var);)

# Frozen bytecode
$(BUILD)/_frozen_mpy.c: py/frozen.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $(wildcard py/*.mpy) > $@

# Run emulation build on a POSIX system with suitable terminal settings
run:
	@saved_=`stty -g`; \
	stty raw opost -echo; \
          $(BUILD)/firmware.elf; \
          echo "Exit status: $$?"; \
          stty $$saved_

patmosRun:
	@saved_=`stty -g`; \
        stty raw opost -echo; \
          pasim $(BUILD)/firmware.elf; \
          echo "Exit status: $$?"; \
          stty $$saved_

# Define how to build the firmware.
#$(BUILD)/firmware.elf: $(OBJ)
$(BUILD)/firmware.elf: $(HEADER_BUILD)/qstrdefs.generated.h $(HEADER_BUILD)/mpversion.h $(HEADER_BUILD)/moduledefs.h $(HEADER_BUILD)/root_pointers.h $(BUILD)/_frozen_mpy.c
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(CFLAGS) $(FILES) -o $@
	$(Q)$(SIZE) $@
#	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
