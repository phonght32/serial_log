#ifndef _LOG_H_
#define _LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdarg.h>

typedef void (*func_log)(uint8_t *data, uint16_t len, uint32_t timeout_ms);
typedef uint32_t (*func_get_tick)(void);

/*
 * Log level output.
 */
typedef enum {
    SERIAL_LOG_NONE = 0,   /*!< No log output */
    SERIAL_LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    SERIAL_LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    SERIAL_LOG_INFO,       /*!< Information messages which describe normal flow of events */
    SERIAL_LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    SERIAL_LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} serial_log_level_t;

/*
 * @brief   Set log function.
 *
 * @param   tag Description tag.
 * @param   level Log level output.
 *
 * @return  None.
 */
void serial_log_function_set(func_log log, func_get_tick get_tick);

/*
 * @brief   Set log level for given tag.
 *
 * @param   tag Description tag.
 * @param   level Log level output.
 *
 * @return  None.
 */
void serial_log_level_set(const char *tag, serial_log_level_t level);

/*
 * @brief   Get FreeRTOS tick count.
 *
 * @param   None.
 *
 * @return  timestamp in miliseconds.
 */
uint32_t serial_log_timestamp(void);

/*
 * @brief   Write message into the log. This function is not recommended to be
 *          use directly. Instead, use one of SERIAL_LOGE, SERIAL_LOGW, SERIAL_LOGI,
 *          SERIAL_LOGD, SERIAL_LOGV macros.
 *
 * @param   level Log level.
 * @param   tag Tag description.
 * @param   format Display format
 * @param   ... Arguments.
 *
 * @return  None.
 */
void serial_log_write(serial_log_level_t level, const char *tag, const char *format, ...);

/** @cond */
#include "serial_log_internal.h"
/** @endcond */

/*
 * Log local level.
 */
#define LOG_LOCAL_LEVEL     5

/*
 * @brief   Log a buffer of hex bytes at specified level, separated into 16 bytes each line.
 *
 * @param   tag Description tag.
 * @param   buffer Pointer to the buffer array.
 * @param   buff_len Length of buffer in bytes.
 * @param   level Level of the log.
 *
 */
#define SERIAL_LOG_BUFFER_HEX_LEVEL(tag, buffer, buff_len, level)              \
    do {                                                                    \
        if ( LOG_LOCAL_LEVEL >= level ) {                                   \
            serial_log_buffer_hex_internal(tag, buffer, buff_len, level);      \
        }                                                                   \
    } while(0)

/**
 * @brief   Log a buffer of characters at specified level, separated into 16 bytes each line.
 *          Buffer should contain only printable characters.
 *
 * @param   tag Description tag.
 * @param   buffer Pointer to the buffer array.
 * @param   buff_len Length of buffer in bytes.
 * @param   level Level of the log.
 *
 */
#define SERIAL_LOG_BUFFER_CHAR_LEVEL(tag, buffer, buff_len, level)             \
    do {                                                                    \
        if(LOG_LOCAL_LEVEL >= level) {                                      \
            serial_log_buffer_char_internal(tag, buffer, buff_len, level);     \
        }                                                                   \
    } while(0)

/*
 * @brief  Log a buffer of hex bytes at Info level.
 *
 * @param  tag Description tag.
 * @param  buffer Pointer to the buffer array.
 * @param  buff_len Length of buffer in bytes.
 *
 * @see    ``serial_log_buffer_hex_level``.
 */
#define SERIAL_LOG_BUFFER_HEX(tag, buffer, buff_len)                           \
    do {                                                                    \
        if(LOG_LOCAL_LEVEL >= SERIAL_LOG_INFO) {                               \
            SERIAL_LOG_BUFFER_HEX_LEVEL(tag, buffer, buff_len, SERIAL_LOG_INFO);  \
        }                                                                   \
    } while(0)

/*
 * @brief   Log a buffer of characters at Info level. Buffer should contain only printable characters.
 *
 * @param   tag Description tag.
 * @param   buffer Pointer to the buffer array.
 * @param   buff_len Length of buffer in bytes.
 *
 * @see     ``serial_log_buffer_char_level``.
 */
#define SERIAL_LOG_BUFFER_CHAR(tag, buffer, buff_len)                          \
    do {                                                                    \
        if(LOG_LOCAL_LEVEL >= SERIAL_LOG_INFO) {                               \
            SERIAL_LOG_BUFFER_CHAR_LEVEL(tag, buffer, buff_len, SERIAL_LOG_INFO); \
        }                                                                   \
    } while(0)

/*
 * Compatible macros in lowcase.
 */
#define serial_log_buffer_hex  SERIAL_LOG_BUFFER_HEX
#define serial_log_buffer_char SERIAL_LOG_BUFFER_CHAR

/*
 * This macro color base on ANSI Format. You can display your log in terminals
 * which support ANSI or VT100.
 */
#define LOG_COLOR_BLACK     "30"        /*!< Black color */
#define LOG_COLOR_RED       "31"        /*!< Red color */
#define LOG_COLOR_GREEN     "32"        /*!< Green color */
#define LOG_COLOR_YELLOW    "33"        /*!< Yellow color */
#define LOG_COLOR_BLUE      "34"        /*!< Blue color */
#define LOG_COLOR_PURPLE    "35"        /*!< Purple color */
#define LOG_COLOR_CYAN      "36"        /*!< Cyan color */
#define LOG_COLOR_WHITE     "37"        /*!< White color */

#define LOG_COLOR(COLOR)    "\033[0;" COLOR "m"             /*!< Log with color */
#define LOG_BOLD(COLOR)     "\033[1;" COLOR "m"             /*!< Log with color and bold */
#define LOG_RESET_COLOR     "\033[0m"                       /*!< Reset log output type */

/*
 * Log output color.
 */
#define LOG_COLOR_E         LOG_COLOR(LOG_COLOR_RED)        /*!< Log error color */
#define LOG_COLOR_W         LOG_COLOR(LOG_COLOR_YELLOW)     /*!< Log warning color */
#define LOG_COLOR_I         LOG_COLOR(LOG_COLOR_WHITE)      /*!< Log information color */
#define LOG_COLOR_D         LOG_COLOR(LOG_COLOR_GREEN)      /*!< Log debug color */
#define LOG_COLOR_V         LOG_COLOR(LOG_COLOR_BLUE)       /*!< Log verbose color */

/*
 * Macros to output logs.
 */
#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%d) %s: " format LOG_RESET_COLOR "\r\n"

/* Macro to out put log at ERROR level */
#define SERIAL_LOGE(tag, format, ...)  SERIAL_LOG_LEVEL_LOCAL(SERIAL_LOG_ERROR  , tag, format, ##__VA_ARGS__)
/* Macro to out put log at WARNNING level */
#define SERIAL_LOGW(tag, format, ...)  SERIAL_LOG_LEVEL_LOCAL(SERIAL_LOG_WARN   , tag, format, ##__VA_ARGS__)
/* Macro to out put log at INFO  level */
#define SERIAL_LOGI(tag, format, ...)  SERIAL_LOG_LEVEL_LOCAL(SERIAL_LOG_INFO   , tag, format, ##__VA_ARGS__)
/* Macro to out put log at DEBUG level */
#define SERIAL_LOGD(tag, format, ...)  SERIAL_LOG_LEVEL_LOCAL(SERIAL_LOG_DEBUG  , tag, format, ##__VA_ARGS__)
/* Macro to out put log at VERBOSE level */
#define SERIAL_LOGV(tag, format, ...)  SERIAL_LOG_LEVEL_LOCAL(SERIAL_LOG_VERBOSE, tag, format, ##__VA_ARGS__)

/*
 * Macros to output logs at specified level.
 */
#define SERIAL_LOG_LEVEL(level, tag, format, ...) do {                                                                                                     \
        if      (level==SERIAL_LOG_ERROR )     { serial_log_write(SERIAL_LOG_ERROR,      tag, LOG_FORMAT(E, format), serial_log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==SERIAL_LOG_WARN )      { serial_log_write(SERIAL_LOG_WARN,       tag, LOG_FORMAT(W, format), serial_log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==SERIAL_LOG_DEBUG )     { serial_log_write(SERIAL_LOG_DEBUG,      tag, LOG_FORMAT(D, format), serial_log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==SERIAL_LOG_VERBOSE )   { serial_log_write(SERIAL_LOG_VERBOSE,    tag, LOG_FORMAT(V, format), serial_log_timestamp(), tag, ##__VA_ARGS__); } \
        else                                { serial_log_write(SERIAL_LOG_INFO,       tag, LOG_FORMAT(I, format), serial_log_timestamp(), tag, ##__VA_ARGS__); } \
    } while(0)

/*
 * Runtime macro to output logs at a specified level. Also check the
 * level with ``LOG_LOCAL_LEVEL``.
 */
#define SERIAL_LOG_LEVEL_LOCAL(level, tag, format, ...) do {                                   \
        if ( LOG_LOCAL_LEVEL >= level ) SERIAL_LOG_LEVEL(level, tag, format, ##__VA_ARGS__);   \
    } while(0)


#ifdef __cplusplus
}
#endif

#endif /* _LOG_H_ */