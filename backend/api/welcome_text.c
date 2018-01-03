#include <fcgiapp.h>
#include "helper_macros.h"

void api_welcome_text_get(FCGX_Request* const request) {
    HTTP_OUT("{");
    HTTP_OUT("\"path\":\"%s\"", FCGX_GetParam("REQUEST_URI", request->envp));
    HTTP_OUT(",\"method\":\"%s\"", FCGX_GetParam("REQUEST_METHOD", request->envp));
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