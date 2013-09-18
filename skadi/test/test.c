#include "skadi.h"
#include "tt_test.h"

#include <stdio.h>
#include <string.h>

void dummy_command(Skadi* skadi, SkadiArgs args){printf("\n\n---%s---\n\n", args.elements[0]);}

SkadiCommand testCommandTable[] = {
  {"test", dummy_command, 1, "test test test test test"} 
};
  
Skadi skadi;

void test_lookupCommand(){
  char* cmdName = "help";
  char* cmdDescription = "Affiche la liste des commandes disponibles.";

  SkadiCommand * sCommand = skadi_lookup_command(&skadi, cmdName);

  if( sCommand == 0) {
    ASSERT("Command introuvable", 0);
    return;
  }

  ASSERT("La commande help a le nom : 'help'", strncmp(sCommand->name, cmdName, MAX_CMD_NAME_SIZE) == 0);
  ASSERT("La commande help a la description : 'Affiche la liste des commandes disponibles.'", strncmp(sCommand->description, cmdDescription, MAX_CMD_DESCRIPTION_SIZE) == 0);
  ASSERT("Aucun param\u00e8tre \u00e0 la commande.", sCommand->arity == 0);

  char* cmdName2  = "test";
  char* cmdDescription2 = "test test test test test";

  sCommand = skadi_lookup_command(&skadi,cmdName2);

  if( sCommand == 0) {
    ASSERT("Command introuvable", 0);
    return;
  }

  ASSERT("La commande test a le nom : 'test'", strncmp(sCommand->name, cmdName2, MAX_CMD_NAME_SIZE) == 0);
  ASSERT("La commande test a la description : 'test test test test test'", strncmp(sCommand->description, cmdDescription2, MAX_CMD_DESCRIPTION_SIZE) == 0);
  ASSERT("Aucun param\u00e8tre \u00e0 la commande.", sCommand->arity == 1);
}

void test_splitCommandLine() {
  char * cmd_line1  = "help";

  char * cmd_name1;
  SkadiArgs skadi_args1;

  split_command_line(cmd_line1, &cmd_name1, &skadi_args1);

  ASSERT("Le nom de la commande est: 'help'.", strncmp("help", cmd_name1, MAX_CMD_NAME_SIZE) == 0);
  ASSERT("Le nombre d'arguments est :0'.", skadi_args1.length == 0);


  char * cmd_name2;
  SkadiArgs skadi_args2;

  char * cmd_line2  = "help arg1 arg2";
  split_command_line(cmd_line2, &cmd_name2, &skadi_args2);
  ASSERT("Le nom de la commande est: 'help'.", strncmp("help", cmd_name2, MAX_CMD_NAME_SIZE) == 0);
  ASSERT("Le nombre d'arguments est :2'.", skadi_args2.length == 2);

  ASSERT("elements[0] = 'arg1'.", strncmp("arg1", skadi_args2.elements[0],MAX_CMD_NAME_SIZE) == 0);
  ASSERT("elements[1] = 'arg2'.", strncmp("arg2", skadi_args2.elements[1],MAX_CMD_NAME_SIZE) == 0);
  ASSERT("elements[2] = NULL.", skadi_args2.elements[2] == NULL);

}


int main(int argc, char **argv) {
  skadi_init(&skadi, testCommandTable,sizeof(testCommandTable)/sizeof(SkadiCommand));

  tt_suite* suite = tt_suite_new();
  tt_add(suite,"lookupCommand",&test_lookupCommand);
  tt_add(suite,"splitCommandLine",&test_splitCommandLine);
  printf("Ex\u00e9cution des tests unitaires.\n");
  int unitTest = tt_run(suite,argc,argv);

  if(unitTest == 0 && argv[1] != NULL) {
    printf("D\u00e9but des tests int\u00e9ratif, saisir 'stop' pour terminer.\n");

    char command[MAX_CMD_NAME_SIZE] = "";
    int retour = 1;
    while ( strncmp (command, "stop", MAX_CMD_NAME_SIZE) != 0) {
      if(retour == ERROR_UNKNOWN_COMMANDE) {
        printf("Commande inconnu.\n"); 
      } else if(retour == ERROR_WRONG_NUMBER_ARGUMENTS) {
        printf("Mauvais nombre d'arguments.\n"); 
      }
      printf("  ->  ");
      if( fgets(command , MAX_CMD_NAME_SIZE, stdin) != NULL ) {
        command[strlen(command)-1] = '\0';
        retour = skadi_process_command(&skadi,command);
      }
    }
  }
  return unitTest;
}
