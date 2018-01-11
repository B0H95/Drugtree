#pragma once

#include <mysql/mysql.h>

int database_init();
void database_deinit();
MYSQL_RES* database_create_query(const char* query);
void database_free_result(MYSQL_RES* result);