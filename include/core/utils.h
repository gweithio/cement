#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <core/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* time_now_create() {
  u8         BUF_SIZE = 26;
  time_t     timer    = time(NULL);
  struct tm* tm_info  = localtime(&timer);

  char  buffer[BUF_SIZE];
  char* result = malloc(sizeof(buffer) + 1);

  strftime(buffer, BUF_SIZE, "%Y-%m-%d", tm_info);

  return strcpy(result, buffer);
}

void time_now_destroy(char* str) {
  free(str);
}

#endif
