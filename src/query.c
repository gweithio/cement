#include <cement/query.h>
#include <cement/builder.h>
#include <stdio.h>

u8 query_exec(builder_db_t* builder, const char* query, query_callback cb) {
  char* errorMsg;
  char* data = "Calling function";
  u8    rec  = 0;

  if (cb) {
    rec = (u8)sqlite3_exec(builder->db, query, cb, data, &errorMsg);
  } else {
    rec = (u8)sqlite3_exec(builder->db, query, cb, NULL, &errorMsg);
  }

  if (rec != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n", errorMsg);
    sqlite3_free(errorMsg);
  }

  return 1;
}

u8 query_create_table(builder_db_t* builder, const char* table_str) {
  if (sqlite3_exec(builder->db, table_str, NULL, NULL, NULL) != SQLITE_OK) {
    fprintf(stderr, "Could not create table: %s", sqlite3_errmsg(builder->db));
    return 0;
  }

  return 1;
}
