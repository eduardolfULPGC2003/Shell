#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

#include "error.h"
#include "functions.h"

#define MAX_LINE_LENGTH 1024
#define SPACE_CHARS " \t\n\r"
#define MAX_ARGS 128

int main(int argc, char *argv[])
{
  char* program_name=strrchr(argv[0],'/')+1;

  char input_line[MAX_LINE_LENGTH];
  char* args[MAX_ARGS];

  while(true)
  {
    printf("[%s]?: ",program_name);
    if(fgets(input_line,MAX_LINE_LENGTH,stdin)!=NULL)
    {
      //printf("[%s] %s",program_name,input_line);
			//ATENCIÓN: línea comentada. Si desea visualizar lo introducido por teclado, descomente la linea anterior.
      if(parse_command(input_line,args,MAX_ARGS))
      {
        //show_args(program_name,args); 
				//ATENCIÓN: línea comentada. Si desea visualizar los argumentos, descomente la línea anterior.

        if(strcmp(args[0],"exit")==0) 
        { printf("[%s] finishing\n",program_name); break; }
					if (strcmp(args[0], "cd")==0){
						if (args[1]==NULL)
							chdir("");
						else chdir(args[1]);
					}
					else{
						pid_t child_pid;
						pid_t parent_pid=getpid();
						switch(child_pid=fork()) 
						{
						  case -1:
			    		{
							print_error(__func__,__FILE__,__LINE__,errno);
							return EXIT_FAILURE;
			    		}
		
			  			case 0: // the child process
			    		{ 
								//if(strcmp(args[0],"cd")==0)
								//char* tira [] = { "ls", "-s", "&", 0 };
								execvp(args[0], args);
								print_error(__func__,__FILE__,__LINE__,errno);
								return EXIT_FAILURE;
							}
							break;

							default: // the parent process
							{						
								pid_t wait_pid;
								int status;
								if((wait_pid=wait(&status))==-1)
								{
									print_error(__func__,__FILE__,__LINE__,errno);
									return EXIT_FAILURE;
								}
							}
								break;
						}
					}
      }
      else printf("[%s] bad input - unable to parse input line\n",program_name);
    }
    else printf("[%s] bad input - (error code: %d) %s)\n",program_name,errno,strerror(errno));
  }

  return EXIT_SUCCESS;
}
