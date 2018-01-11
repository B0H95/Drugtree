#include <fcgiapp.h>
#include <mysql/mysql.h>
#include "database.h"
#include "helper_macros.h"

void api_stats_items_get(FCGX_Request* const request) {
    HTTP_OUT("{");
    MYSQL_RES* result = database_create_query("SELECT * FROM items;");
    if (!result) {
        HTTP_OUT("\"error\": \"Could not select items!\"}");
        return;
    }
    HTTP_OUT("\"result\":[");
    int column_count = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < column_count; ++i) {
            HTTP_OUT("\"");
            HTTP_OUT(row[i] ? row[i] : "NULL");
            HTTP_OUT("\",");
        }
    }
    HTTP_OUT("\"\"]}");
    database_free_result(result);
}

void api_stats_items_post(FCGX_Request* const request) {
    char input[100];
    HTTP_OUT("{\"results\": [ ");
    while (FCGX_GetLine(input, 100, request->in)) {
        for (char* c = input; *c != '\0'; ++c) {
            if (*c == '\n') {
                *c = '\0';
                break;
            }
        }
        HTTP_OUT("\"%s\",", input);
    }
    HTTP_OUT("\"\"]}");
}

void api_stats_items_put(FCGX_Request* const request) {
    (void) request;
}

void api_stats_items_delete(FCGX_Request* const request) {
    (void) request;
}