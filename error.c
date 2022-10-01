#include <errno.h>
#include <stdio.h>
#include <stdarg.h>

#include "error.h"

void print_error_warning_msg(
    const char* prefix,
    const char* func,
    const char* file,
    int line,
    const char* format,
    ...
)
{
  fprintf(stderr,"[%s] -----------------------------------------\n",prefix);
  fprintf(stderr,"[%s] ",prefix);

  va_list args;
  va_start(args,format);
  vfprintf(stderr,format,args);
  va_end(args);

  if(func) fprintf(stderr,"\n[%s] In %s():%s:%d\n",prefix,func,file,line);
  else fprintf(stderr,"\n[%s] In %s:%d\n",prefix,file,line);
  fprintf(stderr,"[%s] -----------------------------------------\n",prefix);
}

//void print_error(
//    const char* func,
//    const char* file,
//    int line,
//    int error_code
//); // declaration for inline function in this TU

void print_error(
    const char* func,
    const char* file,
    int line,
    int error_code
)
{
  print_error_warning_msg(
    "ERROR",
    func,file,line,
    "(error code: %d) %s",
    error_code,strerror(error_code) 
  );
}


