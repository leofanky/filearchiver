
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFileSize(FILE *fp);

//Creates archive file from a set of individual files.
void archive(char** fileNames, int numFiles, char* archiveName){
  //Declare local variables
  int i; //counter
  FILE *archive = fopen(archiveName, "w"); //archive file pointer
  FILE *fp; //text files (temp for each loop iteration)
  char *fName; //to store each file name
  char l; //to store length of each file name
  int fSize; //to store size of each file in bytes
  char *contents; //to store contents of each file

  //If file does not open, print error and quit
  if (archive == NULL){
    fprintf(stderr, "Error: File %s cannot be opened to write\n", (char *)archiveName);
    return;
  }

  //fwrite the number of files to the archive binary file (4-byte unsigned integer)
  fwrite((const void *)&numFiles, BYTE_SIZE_INT, 1, archive);
  printf("Number of files: %d\n", numFiles);

  //Loop through the files to be archived, file 0 through numFiles
  for(i = 0; i < numFiles; i++){
    //Set file name
    fName = fileNames[i];

    //If file does not open, print error and quit
    fp = fopen((const char *)fName, "r");
   if (fp == NULL){
      fprintf(stderr, "Error: File %s cannot be opened to read\n", fName);
      return;
    }

    //Set length of the file name
    l = (char)strlen((const char *)fName);
    //fwrite the length of filename to archive binary file (1-byte unsigned char)
    fwrite((const void *)&l, BYTE_SIZE_CHAR, 1, archive);
    printf("Length of %d file name: %d\n", i, l);

    //fwrite the file name to archive binary file ((l+1)-bytes)
    fwrite((const void *)fName, (l+1), 1, archive);
    printf("Name of file: %s\n", fName);

    //Set size of file in bytes
    fSize = getFileSize(fp);

    //fwrite the size of the file in bytes to archive binary file (4-bytes)
    fwrite((const void *)&fSize, BYTE_SIZE_INT, 1, archive);
    printf("File size: %d\n", fSize);
    //Allocate memory for contents
    contents = (char *)malloc(sizeof(char)*fSize);

    //fwrite contents from file to archive binary file (fSize-bytes)
    fread((void *)contents, BYTE_SIZE_CHAR, fSize, fp);
    fwrite((const void *)contents, BYTE_SIZE_CHAR, fSize, archive);
    printf("File contents: %s\n", contents);

    //Free the memory for contents
    free(contents);
  }

  fclose(archive);
  fclose(fp);
}

void unarchive(char* archiveFile) {
  //Declare local variables
  int numFile; //Store the number of files in the archive
  char lenFileName; //Store the length of each file name
  char *fileName = malloc(sizeof(char *)); //Store each file name
  FILE *fp; //Store each file
  int numBytes; //Store the number of bytes contained in each file
  char *fileContents; //Store the contents of each file

  FILE *archive = fopen(archiveFile, "rb");
  if (archive == NULL){
    fprintf(stderr, "Error: File %s cannot be opened to read\n", archiveFile);
    return;
  }

  fread((void *)&numFile, BYTE_SIZE_INT, 1, archive);
  printf("Num files: %d\n", numFile);

  //Loop through the files in the archive file, file 0 through numFile
  int i;
  for (i = 0; i < (int)numFile; i++){
    //fread the length of each file name (1-byte unsigned char)
    fread((void *)&lenFileName, BYTE_SIZE_CHAR, 1, archive);
    printf("Len file name: %d\n", lenFileName);

    //fread the file name of each file (lenFileName + 1)
    fread(fileName, (lenFileName + 1), 1, archive);
    printf("File name: %s\n", fileName);

    //fread the number of bytes of the contents of each file (4-byte unsigned integer)
    fread(&numBytes, BYTE_SIZE_INT, 1, archive);
    printf("Num file bytes: %d\n", numBytes);

    //Allocate memory for fileContents
    fileContents = (char *)malloc(sizeof(char)*numBytes);

    //fread the contents of each file (numBytes bytes)
    fread(fileContents, numBytes, 1, archive);
    printf("File contents: %s\n", fileContents);

    //Open the file for writing (creates a new file each time)
    fp = fopen(fileName, "w");
    //If file does not open, print error and quit
    if (fp == NULL){
      fprintf(stderr, "Error: File %s cannot be opened to write\n", fileName);
      return;
    }

    //fprintf the file's contents to the file
    fprintf(fp, fileContents);

    //Free the memory for fileContents
    free(fileContents);
    }

  fclose(fp);
  fclose(archive);
}

//creates an archive file of specified size from a set of files
//If the desired size doesn't suffice, create as many archives as needed
void archiveSpecial(char** filenames, int numFiles, char* archiveName, int archiveSize){
  //Declare local variables
  int totalfSize = 4; //store the total file size, starting at 4 for unsigned int of num files
  FILE *fp; //text files for each loop iteration
  char *fName; //file name for each iteration
  int i;
  for(i = 0; i < numFiles; i++){
    totalfSize += BYTE_SIZE_CHAR; //add length of file name, 1-byte char;

    //Set file name
    fName = filenames[i];

    //If file does not open, print error and quit
    fp = fopen((const char *)fName, "r");
    if (fp == NULL){
      fprintf(stderr, "Error: File %s cannot be opened to read\n", fName);
      return;
    }

    totalfSize += strlen((const char *)fName) + 1; //add length of file name + 1
    totalfSize += BYTE_SIZE_INT; //add size of contents, an unsigned int
    totalfSize += getFileSize(fp); //
  }

  //If archiveSize suffices, call archive
  if (archiveSize > totalfSize){
    archive(filenames, numFiles, archiveName);
    return;
  }
}

