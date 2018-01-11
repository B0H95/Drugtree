#include "json.h"

#include <stddef.h>

void json_write_start(json_write_state* json,
                      FCGX_Request* request) {
    json->request = request;
    json->props_written = 0;
}

void json_write_end(json_write_state* json) {
    (void) json;
}

void json_write_obj_start(json_write_state* json) {
    FCGX_FPrintF(json->request->out, "{");
}

void json_write_obj_end(json_write_state* json) {
    FCGX_FPrintF(json->request->out, "}");
}

void json_write_int_prop(json_write_state* json,
                         const char* key,
                         int value) {
    if (json->props_written != 0) {
        FCGX_FPrintF(json->request->out, ",");
    }
    FCGX_FPrintF(json->request->out, "\"%s\":%d", key, value);
    json->props_written++;
}

void json_write_str_prop(json_write_state* json,
                         const char* key,
                         const char* value) {
    if (json->props_written != 0) {
        FCGX_FPrintF(json->request->out, ",");
    }
    FCGX_FPrintF(json->request->out, "\"%s\":\"%s\"", key, value);
    json->props_written++;
}

void json_write_null_prop(json_write_state* json,
                          const char* key) {
    if (json->props_written != 0) {
        FCGX_FPrintF(json->request->out, ",");
    }
    FCGX_FPrintF(json->request->out, "\"%s\":null", key);
    json->props_written++;
}

void json_write_prop_start(json_write_state* json,
                           const char* key) {
    if (json->props_written != 0) {
        FCGX_FPrintF(json->request->out, ",");
    }
    FCGX_FPrintF(json->request->out, "\"%s\":", key);
}

void json_write_prop_end(json_write_state* json) {
    json->props_written++;
}

static int json_read_obj_consume_until(json_read_obj_state* json,
                                       char c) {
    if (!json->request) {
        return 0;
    }
    char in;
    int bytes_consumed = 0;
    while ((in = FCGX_GetChar(json->request->in))) {
        ++bytes_consumed;
        if (in == c) {
            break;
        } else if (in == -1 || in == '\0' || in == '}') {
            json->request = NULL;
            return 0;
        }
    }
    return bytes_consumed;
}

void json_read_obj_start(json_read_obj_state* json,
                         FCGX_Request* request) {
    json->request = request;
    json->saved_endings = 0;
    json_read_obj_consume_until(json, '{');
}

void json_read_obj_end(json_read_obj_state* json) {
    if (json->saved_endings) {
        json->saved_endings--;
        json->request = NULL;
        return;
    }
}

int json_read_obj_prop(json_read_obj_state* json,
                       char* buffer,
                       int max_chars) {
    if (!json_read_obj_consume_until(json, '"')) {
        return 0;
    }
    int i;
    for (i = 0; i < max_chars; ++i) {
        buffer[i] = FCGX_GetChar(json->request->in);
        if (buffer[i] == '\0' || buffer[i] == -1) {
            buffer[i] = '\0';
            json->request = NULL;
            return i;
        } else if (buffer[i] == '"') {
            buffer[i] = '\0';
            json_read_obj_consume_until(json, ':');
            return i;
        }
    }
    buffer[i] = '\0';
    json_read_obj_consume_until(json, ':');
    return i;
}

int json_read_obj_int(json_read_obj_state* json,
                      int* number) {
    if (!json->request) {
        return 0;
    }
    
    *number = 0;
    int multiplier = 1;
    char c;
    int chars_read = 0;

    while ((c = FCGX_GetChar(json->request->in))) {
        if (c == '\0' || c == -1) {
            json->request = NULL;
            return 0;
        } else if (c == '-') {
            multiplier = -1;
            ++chars_read;
        } else if (c == ',') {
            break;
        } else if (c == '}') {
            json->saved_endings++;
            break;
        } else if (c >= '0' && c <= '9') {
            ++chars_read;
            *number = ((*number) * 10) + (int)(c - '0');
        }
    }
    if (c == 0) {
        json->request = NULL;
        return 0;
    }

    *number = (*number) * multiplier;
    return chars_read;
}

int json_read_obj_str(json_read_obj_state* json,
                      char* buffer,
                      int max_chars) {
    if (!json_read_obj_consume_until(json, '"')) {
        return 0;
    }
    int i;
    for (i = 0; i < max_chars; ++i) {
        buffer[i] = FCGX_GetChar(json->request->in);
        if (buffer[i] == '\0' || buffer[i] == -1) {
            buffer[i] = '\0';
            json->request = NULL;
            return i;
        } else if (buffer[i] == '"') {
            buffer[i] = '\0';
            return i;
        }
    }
    buffer[i] = '\0';
    json_read_obj_consume_until(json, '"');
    return i;
}