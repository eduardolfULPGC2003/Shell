#ifndef ERROR_H
#define ERROR_H

#include <string.h>

extern void print_error_warning_msg(
    const char* prefix,
    const char* func,
    const char* file,
    int line,
    const char* format,
    ...
);

//inline void print_error(
extern void print_error(
    const char* func,
    const char* file,
    int line,
    int error_code
);
//{
//  print_error_warning_msg(
//    "ERROR",
//    func,file,line,
//    "(error code: %d) %s",
//    error_code,strerror(error_code) 
//  );
//}

#endif // ERROR_H
