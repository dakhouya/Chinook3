#include "skadi.h"

#include <stdio.h>
#include <string.h>

static void helpCommand();

SkadiCommand skadiInternalCommandTableElements[] = {
  {"help", helpCommand, 0, "Affiche la liste des commandes disponibles."}
};

SkadiArray skadiInternalCommandTable = {1, skadiInternalCommandTableElements};

int skadi_init(Skadi* skadi, SkadiCommand * extCommandTable, size_t len) {
  skadi->externalCommandTable.length = len;
  skadi->externalCommandTable.elements = extCommandTable;

  return 0;
}


SkadiCommand* skadi_lookup_command(Skadi* skadi, const char* commandName) { 
  // Look in the extern command list (if a command is in both list, the extern
  // command is returned.)
  int i;

  for (i = 0; i < skadi->externalCommandTable.length; i++) {
    if (!strncmp(commandName, skadi->externalCommandTable.elements[i].name, MAX_CMD_NAME_SIZE)) {
      return &(skadi->externalCommandTable.elements[i]);
    }
  }

  // Look in the default command list
  for (i = 0; i < skadiInternalCommandTable.length; i++) {
    if (!strncmp(commandName, skadiInternalCommandTable.elements[i].name, MAX_CMD_NAME_SIZE)) {
        return &(skadiInternalCommandTable.elements[i]);
    }
  }

  return 0;
}

int validate_arguments(SkadiCommand * sCommand, SkadiArgs * skadi_args) {
  return (sCommand->arity == skadi_args->length || 
      (sCommand->arity < 0 && abs(sCommand->arity) <= skadi_args->length));
}

void split_command_line (const char * command_line, char ** cmd_name, SkadiArgs * skadi_args) {
  char commandCopy[strlen(command_line) + 1];

  // strtok modify the content of command 
  // so we make a copy to not affect the calling function
  strncpy(commandCopy, command_line, strlen(command_line) + 1);
  *cmd_name = strtok(commandCopy, " ");

  skadi_args->length = 0;
  skadi_args->elements[skadi_args->length] = strtok(NULL, " ");
  while(skadi_args->elements[skadi_args->length] != NULL && skadi_args->length <= MAX_NB_ARGUMENTS) {
    skadi_args->length ++;
    skadi_args->elements[skadi_args->length] = strtok(NULL, " ");
  }
}

int skadi_process_command(Skadi* skadi, const char* command_line) {
  char * cmd_name;
  SkadiArgs skadi_args;

  split_command_line(command_line, &cmd_name, &skadi_args);
  SkadiCommand * sCommand = skadi_lookup_command(skadi, cmd_name);

  if (sCommand) {
    int args_valid = validate_arguments(sCommand, &skadi_args);
    if (args_valid) {
      sCommand->proc(skadi, skadi_args);
      return 1;
    }
    return ERROR_WRONG_NUMBER_ARGUMENTS;
  }
  return ERROR_UNKNOWN_COMMANDE;
}

static void helpCommand(Skadi* skadi) {
  int i;
  printf("\n--- Commandes d\u00e9finis dans le PCB ---\n");
  for (i = 0; i < skadi->externalCommandTable.length; i++) {
    printf("  %s - %s\n", skadi->externalCommandTable.elements[i].name,  skadi->externalCommandTable.elements[i].description);
  }

  printf("\n--- Commandes par d\u00e9faults (peut \u00eatre red\u00e9finit) ---\n");
  for (i = 0; i < skadiInternalCommandTable.length; i++) {
    printf("  %s - %s\n", skadiInternalCommandTable.elements[i].name,  skadiInternalCommandTable.elements[i].description);
  }
}
