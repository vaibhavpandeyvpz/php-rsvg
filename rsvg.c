/*
  +----------------------------------------------------------------------+
  | RSVG PHP extension                                                   |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_rsvg.h"
#include "zend_exceptions.h"
#include "ext/standard/info.h"
#include "librsvg/rsvg.h"
#include "librsvg/rsvg-cairo.h"
#include "cairo-ps.h"
#include "cairo-pdf.h"
#include "cairo-svg.h"

#if HAVE_RSVG

ZEND_BEGIN_ARG_INFO_EX(arginfo_rsvg_convert, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, src, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_rsvg_convert_file, 0, 0, 3)
    ZEND_ARG_TYPE_INFO(0, src, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, dest, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry functions[] = {
    PHP_FE(rsvg_convert, arginfo_rsvg_convert)
    PHP_FE(rsvg_convert_file, arginfo_rsvg_convert_file)
    PHP_FE_END
};

zend_module_entry rsvg_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_RSVG_EXTNAME,
    functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_RSVG_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_RSVG
ZEND_GET_MODULE(rsvg)
#endif

static cairo_status_t cairo_write_to_file (void *ptr, const unsigned char *data, unsigned int length) {
    if (fwrite(data, 1, length, (FILE *) ptr) == length) {
        return CAIRO_STATUS_SUCCESS;
    }

    return CAIRO_STATUS_WRITE_ERROR;
}

static bool rsvg_convert_file_internal(RsvgHandle *src, FILE *dest, zend_string *format) {
    RsvgDimensionData dim;
    rsvg_handle_get_dimensions(src, &dim);

    cairo_surface_t *surface;

    if (!format || !strcmp(ZSTR_VAL(format), "png")) {
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                             dim.width, dim.height);
    } else if (!strcmp(ZSTR_VAL(format), "pdf")) {
        surface = cairo_pdf_surface_create_for_stream(cairo_write_to_file, dest,
                                                      dim.width, dim.height);
    } else if (!strcmp(ZSTR_VAL(format), "eps")) {
        surface = cairo_ps_surface_create_for_stream(cairo_write_to_file, dest,
                                                     dim.width, dim.height);
    } else if (!strcmp(ZSTR_VAL(format), "svg")) {
        surface = cairo_svg_surface_create_for_stream(cairo_write_to_file, dest,
                                                      dim.width, dim.height);
    } else {
        return false;
    }

    cairo_t *cr;
    cr = cairo_create(surface);

    rsvg_handle_render_cairo(src, cr);

    cairo_status_t status;
    status = cairo_status(cr);

    if (status != CAIRO_STATUS_SUCCESS) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);

        return false;
    }

    if (!format || !strcmp(ZSTR_VAL(format), "png")) {
        cairo_surface_write_to_png_stream(surface, cairo_write_to_file, dest);
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return true;
}

PHP_FUNCTION(rsvg_convert) {
    zend_string *src;
    zend_string *format;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
        Z_PARAM_STR(src)
        Z_PARAM_STR(format)
    ZEND_PARSE_PARAMETERS_END();

    rsvg_init();
    rsvg_set_default_dpi(72.0);

    GError *error = NULL;
    RsvgHandle *handle;

    handle = rsvg_handle_new_from_data(ZSTR_VAL(src), ZSTR_LEN(src), &error);
    if (error != NULL) {
        rsvg_term();
        g_error_free(error);

        zend_string_release(src);
        zend_string_release(format);

        RETVAL_BOOL(0);

        return;
    }

    FILE *dest;
    dest = tmpfile();

    bool ok;
    ok = rsvg_convert_file_internal(handle, dest, format);

    if (ok) {
        fseek(dest, 0, SEEK_END);

        long size;
        size = ftell(dest);
        rewind(dest);

        char *buffer;
        buffer = (char *)malloc(size * sizeof(char));

        fread(buffer, size, 1, dest);

        RETVAL_STR(zend_string_init(buffer, size, 0));
    } else {
        RETVAL_BOOL(0);
    }

    fclose(dest);

    rsvg_handle_close(handle, &error);
    rsvg_term();
    g_object_unref(handle);
    if (error != NULL) {
        g_error_free(error);
    }

    zend_string_release(src);
    zend_string_release(format);
}

PHP_FUNCTION(rsvg_convert_file) {
    zend_string *src;
    zend_string *dest;
    zend_string *format;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
        Z_PARAM_STR(src)
        Z_PARAM_STR(dest)
        Z_PARAM_STR(format)
    ZEND_PARSE_PARAMETERS_END();

    rsvg_init();
    rsvg_set_default_dpi(72.0);

    GError *error = NULL;
    RsvgHandle *handle;

    handle = rsvg_handle_new_from_file(ZSTR_VAL(src), &error);
    if (error != NULL) {
        rsvg_term();
        g_error_free(error);

        zend_string_release(src);
        zend_string_release(dest);
        zend_string_release(format);

        RETVAL_BOOL(0);

        return;
    }

    FILE *dest_file;
    dest_file = fopen(ZSTR_VAL(dest), "wb");

    bool ok;
    ok = rsvg_convert_file_internal(handle, dest_file, format);

    fclose(dest_file);

    rsvg_handle_close(handle, &error);
    rsvg_term();
    g_object_unref(handle);
    if (error != NULL) {
        g_error_free(error);
    }

    zend_string_release(src);
    zend_string_release(dest);
    zend_string_release(format);

    RETVAL_BOOL(ok ? 1 : 0);
}

#endif
