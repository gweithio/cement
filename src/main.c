#include <cement/query.h>
#include <stdio.h>
#include <cement/builder.h>
#include <core/utils.h>

static int select_cb(void* data, int argc, char** argv, char** columnName) {
  fprintf(stderr, "%s\n", (const char*)data);

  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", columnName[i], argv[i] ? argv[i] : "NULL");
  }

  return 0;
}

int main(void) {
  builder_db_t* new_db = builder_create_db("test.db");

  builder_get_db_size(new_db);

  if (!query_create_table(
          new_db, "CREATE TABLE IF NOT EXISTS hello (id INTEGER PRIMARY KEY "
                  "AUTOINCREMENT,"
                  "text TEXT NOT NULL, "
                  "created_at DATETIME NOT NULL)")) {
    return 0;
  }

  char* sql  = "INSERT INTO hello (text, created_at) VALUES ('%s', '%s')";
  char* time = time_now();
  char  insert_string[256];

  sprintf(insert_string, sql, "HELLO!!!", time);

  free(time);

  if (!query_exec(new_db, insert_string, NULL)) {
    return 0;
  }

  if (!query_exec(new_db, "SELECT * FROM hello", select_cb)) {
    return 0;
  }

  builder_destroy_db(new_db);

  return 0;
}
