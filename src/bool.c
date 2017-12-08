#include <string.h>

#include "bool.h"


void bool_to_str(bool b, char *str) {
  if (b) {
    memcpy(str, "true", 5);
  }
  else {
    memcpy(str, "false", 6);
  }
}
