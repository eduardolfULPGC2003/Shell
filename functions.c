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

void pasar_a_minusculas(char* str){
	for (size_t i = 0; i < strlen(str); ++i)
		str[i] = tolower((unsigned char) str[i]);
}

void show_args(char* prompt, char* argv[]){
  printf("[%s] args:\n",prompt);
  for(size_t i=0; argv[i]; i++) printf("[%s] --> %lu: \"%s\"\n",prompt,i,argv[i]);
}

bool parse_command(char* command,char* argv[],size_t max_args){
  if(!argv || !max_args) return false;
  
  size_t token_nbr=0;

  char* token=strtok(command,SPACE_CHARS);
  while(token!=NULL)
  {
    if(token_nbr==max_args-1) 
    { argv[token_nbr]=NULL; return false; }
		char *str = token;
		pasar_a_minusculas(str);
    argv[token_nbr++]=token;
    //printf("--> %d: \"%s\"\n",token_nbr,token); 
    token=strtok(NULL,SPACE_CHARS);
		}
  
  argv[token_nbr]=NULL;
  return true;
}
