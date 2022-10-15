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

  if (!query_create_table(new_db, "CREATE TABLE IF NOT EXISTS cement_people "
                                  "(person_id INTEGER PRIMARY KEY "
                                  "AUTOINCREMENT,"
                                  "person_fname TEXT NOT NULL, "
                                  "person_lname TEXT NOT NULL, "
                                  "person_email TEXT NOT NULL, "
                                  "created_at DATETIME NOT NULL)")) {
    return 0;
  }

  if (!query_create_table(new_db, "CREATE TABLE IF NOT EXISTS cement_messages "
                                  "(message_id INTEGER PRIMARY KEY "
                                  "AUTOINCREMENT,"
                                  "message TEXT NOT NULL, "
                                  "message_person INTEGER NOT NULL, "
                                  "created_at DATETIME NOT NULL)")) {
    return 0;
  }

  char* time = time_now_create();

  char* insert_person =
      "INSERT INTO cement_people (person_fname, person_lname, "
      "person_email, created_at) VALUES ('%s', '%s', '%s', '%s')";
  char insert_person_string[256];

  sprintf(insert_person_string, insert_person, "Jack", "Marston",
          "jackmarston@gmail.com", time);

  if (!query_exec(new_db, insert_person_string, NULL)) {
    return 0;
  }

  u8 person_id = (u8)sqlite3_last_insert_rowid(new_db->db);

  char* insert_message =
      "INSERT INTO cement_messages (message, message_person, "
      "created_at) VALUES ('%s', '%d', '%s')";

  char insert_message_string[256];

  sprintf(insert_message_string, insert_message, "Hello, Im jack!", person_id,
          time);

  if (!query_exec(new_db, insert_message_string, NULL)) {
    return 0;
  }

#if 1
  if (!query_exec(new_db,
                  "SELECT * FROM cement_people LEFT JOIN cement_messages ON "
                  "message_person = person_id",
                  select_cb)) {
    return 0;
  }
#endif

  time_now_destroy(time);
  builder_destroy_db(new_db);

  return 0;
}
