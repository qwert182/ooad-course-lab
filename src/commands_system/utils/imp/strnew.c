#include "../strnew.h"


#include <string.h>
#include <malloc.h>
#include <memory.h>

char * strnew(const char *str) {
  size_t size = strlen(str) + 1;
  char *new_str = malloc(size * sizeof*str);
	return memcpy(new_str, str, size);
}

