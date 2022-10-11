#include <cement/query.h>
#include <cement/builder.h>
#include <stdio.h>

u8 query_exec(builder_db_t* builder, const char* query, query_callback cb) {
  char* errorMsg;

  u8 rec = (u8)sqlite3_exec(builder->db, query, cb, NULL, &errorMsg);

  if (rec != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n", errorMsg);
    sqlite3_free(errorMsg);
  }

  return rec;
}
