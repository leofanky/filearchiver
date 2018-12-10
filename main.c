
#include <stdio.h>
#include "prototypes1.h"
#include "prototypes2.h"
#include "constants.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int isNumber(char number[]);

int main(int argc, char *argv[]){
  //If there are no arguments present besides the executable version name, print error and stop
  if (argc < 2){
    fprintf(stderr, "Error: Invalid number of arguments\n" );
    return 0;
  }

  //char double pointer to store list of file names
  char **files;

  //If the flag (argv[1]) is "-a"
  if (strcmp(argv[1],"-a") == 0){
    //Must be at least 4 arguments with "-a" flag
    if (argc < 4){
      fprintf(stderr, "Error: Inavlid number of arguments with \"-a\" flag\n");
      return 0;
    }
    //If the third argument is a number
    if (isNumber(argv[3])){
      files = argv + 4;
      archiveSpecial(files, (argc-4), argv[2], atoi(argv[3]));
    }
    //Otherwise, create an archive file from the set of individual files
    else{
      //Create a double pointer representing the set of individual files
     files = argv + 3;
      archive(files, (argc-3), argv[2]);
    }
  }

  //If the flag (argv[1]) is "-u"
  else if (strcmp(argv[1],"-u") == 0){
    //Must be exactly 3 arguments with "-u" flag
    if (argc != 3){
      fprintf(stderr, "Error: Inavlid number of arguments with \"-u\" flag\n" );
      return 0;
    }
    //Otherwise, unpack archive file and create the original individual files
    unarchive(argv[2]);
  }

  //If the flag (argv[1]) is "-l"
  else if (strcmp(argv[1],"-l") == 0){
    //Must be exactly 3 arguments "-l" flag
    if (argc != 3){
      fprintf(stderr, "Error: Inavlid number of arguments with \"-l\" flag\n");
      return 0;
    }
    //Otherwise, print total size of archive, # files in archive, and each filename w/ corresponding file size
    printFileInfo(argv[2]);
  }

  //If the flag (argv[1]) is "-v"
  else if (strcmp(argv[1],"-v") == 0){
    //Must be at least 4 arguments with "-v" flag
    if (argc < 4){
      fprintf(stderr, "Error: Inavlid number of arguments with \"-v\" flag\n");
      return 0;
    }
    //Create a double pointer representing the set of individual files
    char **files = argv + 3;
    //Otherwise, determine whether or not the specified archive is damaged
    isDamaged(files, (argc-3), argv[2]);
  }
  else{
    fprintf(stderr, "Error: Unknown switch provided\n");
    return 0;
  }
  return 0;
}

int isNumber(char number[]){
  int i = 0;

  if (number[0] == '-')
    i = 1;
  for (; number[i] != 0; i++){
    if (!isdigit(number[i]))
      return FALSE;
  }
  return TRUE;
}

