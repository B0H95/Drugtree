#pragma once

#include <fcgiapp.h>

typedef struct json_write_state {
    FCGX_Request* request;
    unsigned int props_written;
} json_write_state;

void json_write_start(json_write_state* json,
                      FCGX_Request* request);

void json_write_end(json_write_state* json);

void json_write_obj_start(json_write_state* json);

void json_write_obj_end(json_write_state* json);

void json_write_int_prop(json_write_state* json,
                         const char* key,
                         int value);

void json_write_str_prop(json_write_state* json,
                         const char* key,
                         const char* value);

void json_write_null_prop(json_write_state* json,
                          const char* key);

void json_write_prop_start(json_write_state* json,
                           const char* key);

void json_write_prop_end(json_write_state* json);

typedef struct json_read_obj_state {
    FCGX_Request* request;
    int saved_endings;
} json_read_obj_state;

void json_read_obj_start(json_read_obj_state* json,
                         FCGX_Request* request);

void json_read_obj_end(json_read_obj_state* json);

int json_read_obj_prop(json_read_obj_state* json,
                       char* buffer,
                       int max_chars);

int json_read_obj_int(json_read_obj_state* json,
                      int* number);

int json_read_obj_str(json_read_obj_state* json,
                      char* buffer,
                      int max_chars);