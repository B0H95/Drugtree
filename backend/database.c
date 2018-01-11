#include "database.h"

static MYSQL* connection = NULL;

int database_init() {
    connection = mysql_init(NULL);
    if (!connection) {
        return 0;
    }
    if (!mysql_real_connect(connection, 
                            "localhost", 
                            "drugtreebackend", 
                            "123QWEasdzxc", // Who needs security
                            "drugtree", 
                            0, 
                            NULL, 
                            0)) {
        mysql_close(connection);
        return 0;
    }
    return 1;
}

void database_deinit() {
    if (!connection) {
        return;
    }
    mysql_close(connection);
}

MYSQL_RES* database_create_query(const char* query) {
    // TODO: Lock here
    if (mysql_query(connection, query)) {
        return NULL;
    }
    MYSQL_RES* result = mysql_store_result(connection);
    // TODO: Unlock here
    return result;
}

void database_free_result(MYSQL_RES* result) {
    mysql_free_result(result);
}