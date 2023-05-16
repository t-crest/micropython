#include "py/runtime.h"

#include <stdio.h>

#include <machine/spm.h>
#include <machine/patmos.h>
#include <machine/exceptions.h>

#include "modpatmos.h"

static mp_obj_t hooks[22];

void ignore(void) {}

void excHandler(void) {
        exc_prologue();
	int source = exc_get_source();
	switch (source) {
		case 18:
		case 19:
		case 20:
		case 21:
			if (hooks[source]) {
				mp_call_function_0(hooks[source]);
			}
			break;
		default:
			printf("%s %d\n", "Unknown int", source);
			break;
	}
//	printf("%s\n", "Int");
        exc_epilogue();
}

STATIC mp_obj_t patmos_info(void) {
    mp_printf(&mp_plat_print, "Module for interacting with FPGA components\n");
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_0(patmos_info_obj, patmos_info);

STATIC mp_obj_t patmos_getLed(mp_obj_t ledNum) {
	int num = mp_obj_get_int(ledNum);
	if (num > 8) {
		//mp_raise_OSError("Led number out of range");
		return mp_const_none;
	}
	volatile _SPM int *led_ptr = (volatile _SPM int *) (PATMOS_IO_LED);
    	return mp_obj_new_int((*led_ptr & (1 << num)) >> num);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(patmos_getLed_obj, patmos_getLed);

STATIC mp_obj_t patmos_getKey(mp_obj_t keyNum) {
	int num = mp_obj_get_int(keyNum);
	if (num > 3) {
		//mp_raise_OSError("Led number out of range");
		return mp_const_none;
	}
	volatile _SPM int *key_ptr = (volatile _SPM int *) (PATMOS_IO_KEYS);
    	return mp_obj_new_int((*key_ptr & (1 << num)) >> num);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(patmos_getKey_obj, patmos_getKey);

STATIC mp_obj_t patmos_setLed(mp_obj_t ledNum, mp_obj_t toggle) {
	int num = mp_obj_get_int(ledNum);
	int on = mp_obj_get_int(toggle);
	if (num > 8) {
		//mp_raise_OSError("Led number out of range");
		return mp_const_none;
	}
	volatile _SPM int *led_ptr = (volatile _SPM int *) (PATMOS_IO_LED);
	if (on) {
		*led_ptr |= 1<<num;
	} else {
		*led_ptr &= 255-(1<<num);
	}
	return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(patmos_setLed_obj, patmos_setLed);

STATIC mp_obj_t patmos_setLeds(mp_obj_t leds) {
	int num = mp_obj_get_int(leds);
	volatile _SPM int *led_ptr = (volatile _SPM int *) (PATMOS_IO_LED);
	*led_ptr = num;
	return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(patmos_setLeds_obj, patmos_setLeds);

STATIC mp_obj_t patmos_setIntr(mp_obj_t intr, mp_obj_t function) {
	int num = mp_obj_get_int(intr);
	if (num > 21 || num < 0) {
		return mp_const_none;
	}
	hooks[num] = function;
	return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(patmos_setIntr_obj, patmos_setIntr);

STATIC const mp_rom_map_elem_t patmos_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_patmos) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&patmos_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_getLed), MP_ROM_PTR(&patmos_getLed_obj) },
    { MP_ROM_QSTR(MP_QSTR_getKey), MP_ROM_PTR(&patmos_getKey_obj) },
    { MP_ROM_QSTR(MP_QSTR_setLed), MP_ROM_PTR(&patmos_setLed_obj) },
    { MP_ROM_QSTR(MP_QSTR_setLeds), MP_ROM_PTR(&patmos_setLeds_obj) },
    { MP_ROM_QSTR(MP_QSTR_setIntr), MP_ROM_PTR(&patmos_setIntr_obj) },
//KEY constants for interrupts
    { MP_ROM_QSTR(MP_QSTR_KEY0), MP_ROM_INT(18) },
    { MP_ROM_QSTR(MP_QSTR_KEY1), MP_ROM_INT(19) },
    { MP_ROM_QSTR(MP_QSTR_KEY2), MP_ROM_INT(20) },
    { MP_ROM_QSTR(MP_QSTR_KEY3), MP_ROM_INT(21) },
};
STATIC MP_DEFINE_CONST_DICT(patmos_module_globals, patmos_module_globals_table);

const mp_obj_module_t patmos_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&patmos_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_patmos, patmos_module);
