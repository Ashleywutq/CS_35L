#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[]){
  //check argument numbers
  if (argc != 3){
    fprintf(stderr,"not 2 arguments");
    exit(1);
  }

  //check argument length
  char* from = argv[1];
  char* to = argv[2];
  if (strlen(from) != strlen(to)){
    fprintf(stderr, "arguments not same length");
    exit(1);
  }

  //check duplicated characters in from
  int i;
  int j;
  for (i=0; i<strlen(from);i++){
    for (j=i+1; j<strlen(from);j++){
      if (from[j] == from[i]){
	fprintf(stderr,"duplicated characters in from");
	exit(1);
      }
    }
  }

  //output using read/write
  char current[2];
  ssize_t errorcheck = read(0,current,1);
  while (errorcheck !=0){
    if (errorcheck < 0){
      fprintf(stderr,"read error");
      exit(1);
    }
    //check if this character need to be changed
    for (i=0; i<strlen(from); i++){
      if (current[0] == from[i]){
	current[0] = to[i];
	break;
      }
    }
    write(1,current,1);
    errorcheck = read(0,current,1);
  }

  return 0;
  
}
