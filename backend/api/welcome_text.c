#include <fcgiapp.h>

void api_welcome_text_get(FCGX_Request* const request) {
    FCGX_FPrintF(request->out, "{");
    FCGX_FPrintF(request->out, "\"path\":\"%s\"", FCGX_GetParam("REQUEST_URI", request->envp));
    FCGX_FPrintF(request->out, ",\"method\":\"%s\"", FCGX_GetParam("REQUEST_METHOD", request->envp));
    FCGX_FPrintF(request->out, "}");
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