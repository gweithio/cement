#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <time.h>
#include <string.h>

char* time_now() {
  time_t     timer;
  char       buffer[26];
  struct tm* tm_info;
  char*      final = NULL;

  timer   = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%Y-%m-%d", tm_info);

  memmove(final, buffer, strlen(buffer));

  return final;
}

#endif
