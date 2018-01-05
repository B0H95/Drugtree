#include <fcgiapp.h>
#include <mysql/mysql.h>
#include "database.h"
#include "helper_macros.h"

void api_stats_items_get(FCGX_Request* const request) {
    HTTP_OUT("{");
    MYSQL_RES* result = database_query("SELECT * FROM items;");
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
}

void api_stats_items_post(FCGX_Request* const request) {
    (void) request;
}

void api_stats_items_put(FCGX_Request* const request) {
    (void) request;
}

void api_stats_items_delete(FCGX_Request* const request) {
    (void) request;
}