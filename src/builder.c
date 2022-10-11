#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <sqlite3.h>
#include <cement/builder.h>

static u8 _builder_create_empty_db(const char* name) {
  struct stat buffer;

  // using stat, we can check if the file exists
  if (stat(name, &buffer) == 0) {
    return 1;
  }

  FILE* db_file = fopen(name, "w");

  if (!db_file) {
    fclose(db_file);
    return 0;
  }

  fclose(db_file);
  return 1;
}

static int _stats_callback(void* data, int argc, char** argv,
                           char** columnName) {
  fprintf(stderr, "%s\n", (const char*)data);

  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", columnName[i], argv[i] ? argv[i] : "NULL");
  }

  return 0;
}

u8 builder_get_db_size(builder_db_t* builder) {
  char*       errorMsg = 0;
  const char* data     = "stats function called";
  const char* query =
      "SELECT (page_count - freelist_count) * page_size as size FROM "
      "pragma_page_count(), pragma_freelist_count(), pragma_page_size();";

  u8 rec = (u8)sqlite3_exec((sqlite3*)builder->db, query, _stats_callback,
                            (void*)data, &errorMsg);
  if (rec != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n", errorMsg);
    sqlite3_free(errorMsg);
  }

  return rec;
}

builder_db_t* builder_create_db(const char* name) {
  builder_db_t* builder = malloc(sizeof(builder_db_t));
  builder->name         = name;

  if (!_builder_create_empty_db(builder->name)) {
    return NULL;
  }

  if (sqlite3_open_v2(builder->name, &builder->db, SQLITE_OPEN_READWRITE,
                      NULL) != SQLITE_OK) {
    fprintf(stderr, "Failed to open %s\n", builder->name);
    return NULL;
  }

  return builder;
}

u8 builder_destroy_db(builder_db_t* builder) {
  u8 error = 1;
  if (sqlite3_close(builder->db) != SQLITE_OK) {
    error = 0;
    fprintf(stderr, "Failed to close DB\n");
  }

  free(builder);
  return error;
}
