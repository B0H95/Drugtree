#include <stdlib.h>
#include <fcgiapp.h>
#include "generated/routes.h"

int main() {
    FCGX_Request request;
    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);
    while (1) {
        FCGX_Accept_r(&request);
        FCGX_FPrintF(request.out, "Content-Type: application/json\n\r");
        FCGX_FPrintF(request.out, "\n\r");
        send_request_to_handler(&request);
        FCGX_FPrintF(request.out, "\n\r");
        FCGX_Finish_r(&request);
    }
    return EXIT_SUCCESS;
}