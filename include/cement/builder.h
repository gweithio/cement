#ifndef BUILDER_HEADER
#define BUILDER_HEADER

#include <core/types.h>
#include <sqlite3.h>

typedef struct {
  const char* name;
  sqlite3*    db;
} builder_db_t;

builder_db_t* builder_create_db(const char* name);
u8            builder_get_db_size(builder_db_t* builder);
u8            builder_destroy_db(builder_db_t* builder);

#endif
