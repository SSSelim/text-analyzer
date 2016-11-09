/**
 * Text Analyzer finds the number of
 * paragraphs, sentences, words, and non-alphabetical words
 * in a file. Prints the output to the sout and a file.
 *
 * Author: Selim
 * Date: 2013
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
  char fname[50];
  int pNo; // paragraph count
  int sNo; // sentence count
  int wNo; // word count
  int nNo; // non-alphabetical word
} FSPEC;

int calWorNo(FILE *file){
  int count=0;
  int ch;

  ch = fgetc(file);
  while( ch != EOF ){
    if( ch == ' ' ){
      count++;
    }
    ch = fgetc(file);
  }

  return count+1;
}

int calSenNo(FILE *file){
  int count=0;
  int ch;

  ch = fgetc(file);
  while( ch != EOF ){
    if( ch == '.' ){
      count++;
    }
    ch = fgetc(file);
  }

  return count;
}

int calParNo(FILE *file){
  int count=0;
  int ch;

  ch = fgetc(file);
  while( ch != EOF ){
    if( ch == '.' ){
      ch = fgetc(file);
      if( ch == '\n' ){
        count++;
      }
    }
    ch = fgetc(file);
  }

  return count;
}

int calNawNo(FILE *file){
  int count=0;
  int ch;

  ch = fgetc(file);
  while( ch != EOF ){
    if( isdigit(ch) != 0){
      count++;
      do{ // next word
        ch = fgetc(file);
      }while( ch != ' ' );
    }
    ch = fgetc(file);
  }
  return count;
}


int main(){
  FILE *filelist, *f1;
  FSPEC files[4];
  int i,j;
  int ch;

  // open the filelist file
  filelist = fopen("filelist.txt", "r");
  // check if successfull
  if( filelist == NULL ){
    printf("filelist.txt could not be found!\n");
    return 1;
  }

  // get the files' name
  for( i=0; i<4; i++ ){
    ch = getc(filelist);
    j=0;
    // assumed the names of files written line by line
    while( ch != '\n' ){
      files[i].fname[j] = ch;
      j++;
      ch = getc(filelist);
    }
    files[i].fname[j] = '\0'; // add the terminator character
  }

  // the filelist.txt doesnot need to be open anymore
  fclose(filelist);

  // Print the names of the files
  for(i=0; i<4; i++){
    printf("the name of #%d file: %s\n", i+1,files[i].fname);
  }

  for( i=0; i<4; i++ ){
    f1 = fopen(files[i].fname, "r");
    if( f1 == NULL ){ printf("couldnot be opened\n"); return 1; }

    files[i].sNo = calSenNo(f1);
    rewind(f1); // go back the beginning of the file

    files[i].wNo = calWorNo(f1);
    rewind(f1);

    files[i].pNo = calParNo(f1);
    rewind(f1);

    files[i].nNo = calNawNo(f1);
    fclose(f1);
  }

  f1 = fopen("filespec.txt", "w");
  if( f1 == NULL ){ printf("Couldnot create \"filespec.txt\"\n"); return 1; }
  // Print the specs of the files to the screen
  for(i=0; i<4; i++){
    // sceen output
    printf("\n------------------------------\n");
    printf("The name of the file : %s\n", files[i].fname);
    printf("The number of words : %d\n", files[i].wNo);
    printf("The number of sentences : %d\n", files[i].sNo);
    printf("The number of paragraphs : %d\n", files[i].pNo);
    printf("The number of non-alphabetical words : %d\n", files[i].nNo);
    // file output
    fprintf(f1,"\n------------------------------\n");
    fprintf(f1,"The name of the file : %s\n", files[i].fname);
    fprintf(f1,"The number of words : %d\n", files[i].wNo);
    fprintf(f1,"The number of sentences : %d\n", files[i].sNo);
    fprintf(f1,"The number of paragraphs : %d\n", files[i].pNo);
    fprintf(f1,"The number of non-alphabetical words : %d\n", files[i].nNo);
  }
  fclose(f1);

  return 0;
}
