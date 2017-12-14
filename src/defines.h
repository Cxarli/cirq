#ifndef DEFINES_H
#define DEFINES_H

#define BUF_SIZE 256

#define DEBUG

#ifndef DEBUG
  #define DEBUG printf("DEBUG %s:%i %s\n", __FILE__, __LINE__, __FUNCTION__)
#endif


// Scope a variable for the following block
#define with(statement) \
  for (char x##__LINE__ = 1; x##__LINE__;) \
    for (statement; x##__LINE__; x##__LINE__ = 0) \


// Easier string switch'ing
#define switch_str(x) \
  char *SWITCH_STR = (x);

#define case_str(y) \
  if ( strcmp(SWITCH_STR, (y)) == 0 )

// use it like:
/*
{ switch_str(name)

  case_str("foo") {

  }

  case_str("bar") {

  }
}
*/

#endif
