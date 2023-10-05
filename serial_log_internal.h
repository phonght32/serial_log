#ifndef _SERIAL_LOG_INTERNAL_H_
#define _SERIAL_LOG_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 * @brief   Output log buffer hex.
 *
 * @param   tag Tag description.
 * @param   buffer Buffer.
 * @param   buff_len length.
 * @param   log_level Log output level.
 *
 * @return  None.
 */
void serial_log_buffer_hex_internal(const char *tag,
                                 const char *buffer,
                                 uint16_t buff_len,
                                 serial_log_level_t log_level);

/*
 * @brief   Output log buffer char.
 *
 * @param   tag Tag description.
 * @param   buffer Buffer.
 * @param   buff_len length.
 * @param   log_level Log output level.
 *
 * @return  None.
 */
void serial_log_buffer_char_internal(const char *tag,
                                  const char *buffer,
                                  uint16_t buff_len,
                                  serial_log_level_t log_level);

#ifdef __cplusplus
}
#endif

#endif /* _SERIAL_LOG_INTERNAL_H_ */