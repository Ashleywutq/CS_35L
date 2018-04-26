#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
  //check argument number
  if (argc != 3){
    fprintf(stderr,"not 2 arguments.");
    exit(1);
  }

  //check argument length
  char* from = argv[1];
  char* to = argv[2];
  if (strlen(from) != strlen(to)) {
    fprintf(stderr, "from and to not same length.");
    exit(1);
  }

  //check if input has duplicated words
  int i;
  int j;
  for (i=0; i<strlen(from);i++){
    for (j=i+1;j<strlen(from);j++){
      if (from[i]==from[j]){
	fprintf(stderr,"input has duplicated words");
	exit(1);
      }
    }
  }

  //tr
  char current = getchar();
  while (current != EOF){
    //search if we need to change the word                                      
    for (i=0;i<strlen(from);i++){
      if (current == from[i]){
        current = to[i];
        break;
      }
    }
    putchar(current);
    current = getchar();
  }

  return 0;
}

