#include <fcgiapp.h>
#include "json.h"
#include <string.h>

void api_welcome_text_get(FCGX_Request* const request) {
    json_write_state json;
    json_write_start(&json, request);
    json_write_obj_start(&json);
    json_write_str_prop(&json, "result", "Nu kommer vi ha knark i all evighet!");
    json_write_int_prop(&json, "result2", 2323);
    json_write_str_prop(&json, "re3", "wgjgg");
    json_write_obj_end(&json);
    json_write_end(&json);
}

void api_welcome_text_post(FCGX_Request* const request) {
    int first = 1;
    int second = 1;
    char str[50];
    str[49] = '\0';

    json_read_obj_state jsonread;
    json_read_obj_start(&jsonread, request);
    char buffer[50];
    while (json_read_obj_prop(&jsonread, buffer, 50)) {
        if (!strncmp(buffer, "first", 5)) {
            json_read_obj_int(&jsonread, &first);
        } else if (!strncmp(buffer, "second", 6)) {
            json_read_obj_int(&jsonread, &second);
        } else if (!strncmp(buffer, "str", 3)) {
            json_read_obj_str(&jsonread, str, 50);
        }
    }
    json_read_obj_end(&jsonread);

    first = first << 1;
    second = second << 2;

    json_write_state jsonwrite;
    json_write_start(&jsonwrite, request);
    json_write_obj_start(&jsonwrite);
    json_write_int_prop(&jsonwrite, "the_first", first);
    json_write_int_prop(&jsonwrite, "the_second", second);
    json_write_str_prop(&jsonwrite, "the_str", str);
    json_write_obj_end(&jsonwrite);
    json_write_end(&jsonwrite);
}

void api_welcome_text_put(FCGX_Request* const request) {
    (void) request;
}

void api_welcome_text_delete(FCGX_Request* const request) {
    (void) request;
}