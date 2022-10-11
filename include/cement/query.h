#ifndef QUERY_HEADER
#define QUERY_HEADER

#include <cement/builder.h>

typedef int (*query_callback)(void* data, int argc, char** argv,
                              char** columnName);

u8 query_exec(builder_db_t* builder, const char* query, query_callback cb);

#endif
