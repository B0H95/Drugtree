#pragma once

#define HTTP_OUT(...) FCGX_FPrintF(request->out, __VA_ARGS__)