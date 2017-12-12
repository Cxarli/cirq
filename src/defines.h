#ifndef DEFINES_H
#define DEFINES_H

#define BUF_SIZE 256

#define DEBUG ;

#ifndef DEBUG
  #define DEBUG printf("DEBUG %s:%i\r", __FILE__, __LINE__)
#endif

#endif
