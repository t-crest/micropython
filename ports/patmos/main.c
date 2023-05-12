/*
#include "py/builtin.h"
#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
*/

//#include <stdint.h>
//#include <stdio.h>
//#include <string.h>

#include "py/builtin.h"
#include "py/compile.h"
#include "py/mperrno.h"
#include "mphalport.h"

//#include "py/runtime.h"
#include "shared/runtime/pyexec.h"

//#include "shared/runtime/stdout_helpers.c"

#if MICROPY_HELPER_REPL
#include "py/runtime.h"
#include "py/repl.h"
#include "shared/runtime/pyexec.h"
#endif
// Allocate memory for the MicroPython GC heap.
#if MICROPY_ENABLE_GC
#include "py/gc.h"
#include "shared/runtime/gchelper.h"
//#include "py/stackctrl.h"
static char heap[8192];
#endif

int main(int argc, char **argv) {
    // Initialise the MicroPython runtime.
#if MICROPY_ENABLE_GC
//    mp_stack_ctrl_init();
    gc_init(heap, heap + sizeof(heap));
#endif
    mp_init();
//    pyexec_friendly_repl();
#if MICROPY_MODULE_FROZEN_MPY
    mp_hal_stdout_tx_strn("Running frozen.py:\n", 19);
    pyexec_frozen_module("py/frozen.py", false);
    mp_hal_stdout_tx_strn("Running frozen2.py:\n", 20);
    pyexec_frozen_module("py/frozen2.py", false);
#endif
    //printf("%s\n", "Running");
    // Start a normal REPL; will exit when ctrl-D is entered on a blank line.
#if MICROPY_HELPER_REPL
    pyexec_friendly_repl();
#endif
    // Deinitialise the runtime.
#if MICROPY_ENABLE_GC
    gc_sweep_all();
#endif
    mp_deinit();
    return 0;
}

// Handle uncaught exceptions (should never be reached in a correct C implementation).
void nlr_jump_fail(void *val) {
    for (;;) {
    }
}

// Do a garbage collection cycle.
void gc_collect(void) {
#if MICROPY_ENABLE_GC
    gc_collect_start();
    gc_helper_collect_regs_and_stack();
    gc_collect_end();
#endif
}


// There is no filesystem so stat'ing returns nothing.
mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}

// There is no filesystem so opening a file raises an exception.
mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}

