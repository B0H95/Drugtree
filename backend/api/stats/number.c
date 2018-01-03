#include <fcgiapp.h>

void api_stats_number_get(FCGX_Request* const request) {
    FCGX_FPrintF(request->out, "{");
    FCGX_FPrintF(request->out, "\"number\":\"100\"");
    FCGX_FPrintF(request->out, "}");
}

void api_stats_number_post(FCGX_Request* const request) {
    (void) request;
}

void api_stats_number_put(FCGX_Request* const request) {
    (void) request;
}

void api_stats_number_delete(FCGX_Request* const request) {
    (void) request;
}