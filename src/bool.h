#ifndef BOOL_H
#define BOOL_H

#include <stdint.h>

#define bool uint8_t
#define false 0
#define true 1


void bool_to_str(bool b, char *str);

#endif
