//void mp_hal_stdout_tx_strn_cooked(const char *str, size_t len) {
static inline void mp_hal_set_interrupt_char(char c) {}
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
