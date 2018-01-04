#include <fcgiapp.h>
#include "helper_macros.h"

void api_welcome_text_get(FCGX_Request* const request) {
    HTTP_OUT("{");
    HTTP_OUT("\"result\":\"Nu kommer vi ha knark i all evighet!\"");
    HTTP_OUT("}");
}

void api_welcome_text_post(FCGX_Request* const request) {
    (void) request;
}

void api_welcome_text_put(FCGX_Request* const request) {
    (void) request;
}

void api_welcome_text_delete(FCGX_Request* const request) {
    (void) request;
}