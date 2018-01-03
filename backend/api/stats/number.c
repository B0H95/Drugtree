#include <fcgiapp.h>
#include "helper_macros.h"

void api_stats_number_get(FCGX_Request* const request) {
    HTTP_OUT("{");
    HTTP_OUT("\"number\":\"100\"");
    HTTP_OUT("}");
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