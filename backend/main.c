#include <stdlib.h>
#include <fcgiapp.h>
#include "generated/routes.h"
#include "helper_macros.h"
#include "database.h"

int main() {
    if (!database_init()) {
        return EXIT_FAILURE;
    }
    FCGX_Request req;
    FCGX_Request* request = &req;
    FCGX_Init();
    FCGX_InitRequest(request, 0, 0);
    while (1) {
        FCGX_Accept_r(request);
        HTTP_OUT("Content-Type: application/json\n\r");
        HTTP_OUT("\n\r");
        send_request_to_handler(request);
        HTTP_OUT("\n\r");
        FCGX_Finish_r(request);
    }
    database_deinit();
    return EXIT_SUCCESS;
}