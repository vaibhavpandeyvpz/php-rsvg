/*
  +----------------------------------------------------------------------+
  | RSVG PHP extension                                                   |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_RSVG_H
#define PHP_RSVG_H 1

#define PHP_RSVG_VERSION "0.1.0"
#define PHP_RSVG_EXTNAME "rsvg"

#ifdef PHP_WIN32
# define PHP_RSVG_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_RSVG_API __attribute__ ((visibility("default")))
#else
# define PHP_RSVG_API
#endif

typedef enum _php_rsvg_status {
    PHP_RSVG_OK = 1,
    PHP_RSVG_ERR,
} php_rsvg_status_t;

/* Declare all functions and classes of the extension */
static PHP_FUNCTION(rsvg_convert);
static PHP_FUNCTION(rsvg_convert_file);

extern zend_module_entry rsvg_module_entry;

#endif
