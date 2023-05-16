#include <stdint.h>

// Python internal features.

#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

#define MICROPY_ENABLE_GC                       (0)
#define MICROPY_ENABLE_FINALISER    		(0)
#define MICROPY_STACK_CHECK         		(0)
#define MICROPY_ENABLE_EXTERNAL_IMPORT    	(1)

//REPL
#define MICROPY_HELPER_REPL                     (0)

//FPGA
#define	FPGA					(0)

//Frozen pycode
#define MICROPY_MODULE_FROZEN_MPY         	(1)
#define MICROPY_QSTR_EXTRA_POOL           	mp_qstr_frozen_const_pool

//#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_TERSE)
//#define MICROPY_FLOAT_IMPL                      (MICROPY_FLOAT_IMPL_FLOAT)

#if MICROPY_HELPER_REPL
#define MICROPY_ENABLE_COMPILER			(1)
#endif

// Fine control over Python builtins, classes, modules, etc.
#define MICROPY_PY_ASYNC_AWAIT                  (0)
#define MICROPY_PY_BUILTINS_SET                 (0)
#define MICROPY_PY_ATTRTUPLE                    (0)
#define MICROPY_PY_COLLECTIONS                  (0)
#define MICROPY_PY_MATH                         (0)
#define MICROPY_PY_IO                           (0)
#define MICROPY_PY_STRUCT                       (0)

// Type definitions for the specific machine.

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// Define the port's name and hardware.
#define MICROPY_HW_BOARD_NAME "example-board"
#define MICROPY_HW_MCU_NAME   "unknown-cpu"

#define MP_STATE_PORT MP_STATE_VM
