#ifndef __SKADI_H_
#define __SKADI_H_

#define MAX_CMD_NAME_SIZE 256
#define MAX_CMD_DESCRIPTION_SIZE 256
#define MAX_NB_ARGUMENTS 5 

#define ERROR_WRONG_NUMBER_ARGUMENTS -1000
#define ERROR_UNKNOWN_COMMANDE -1001

#include <stdlib.h>

typedef void skadiCommandProc();

typedef struct SkadiCommand {
  char *name;                   // The name to be used when calling the command ex: help
  skadiCommandProc *proc;       // The actual function pointer
  int arity;                    // The number of arguments the function takes
  char *description;            // The description (to be used by help)
} SkadiCommand;

typedef struct SkadiArray {
  size_t length;
  SkadiCommand * elements;
} SkadiArray;

typedef struct SkadiArgs {
  size_t length;
  char* elements[MAX_NB_ARGUMENTS];
} SkadiArgs;


typedef struct Skadi{
  SkadiArray externalCommandTable;  
} Skadi;


int skadi_process_command(Skadi* skadi, const char* command);
int validate_arguments(SkadiCommand * sCommand, SkadiArgs * skadi_args);
void split_command_line (const char * command_line, char ** cmd_name, SkadiArgs * skadi_args);
int skadi_init(Skadi* skadi, SkadiCommand* external_command_table, size_t len);
SkadiCommand* skadi_lookup_command(Skadi* skadi, const char* command);

#endif // __SKADI_H_
