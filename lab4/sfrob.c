
#include <stdio.h>
#include <stdlib.h>

int frobcmp (char const* a, char const* b){
    for (;;a++, b++){
        if (*a==' ' && *b == ' '){return 0;}
        else if ((*a == ' ')||(((*a)^42)<((*b)^42))) {return -1;}
        else if ((*b == ' ')||(((*a)^42)>((*b)^42))) {return 1;}
    }
}

int cmp(const void* a, const void* b){
  const char* w1= *(const char **)a;
  const char* w2= *(const char **)b;
  return frobcmp(w1,w2);
}

void checkreaderr(){
    if (ferror(stdin)){
        fprintf(stderr, "read failed");
        exit(1);
    }
}

void checkwriteerr(){
    if (ferror(stdout)){
        fprintf(stderr, "write failed");
        exit(1);
    }
}


int main(){
    char* word; //point to an array of characters
    char** line; //point to an array of word pointers
    word = (char*) malloc	(sizeof(char));
    line = (char**) malloc (sizeof(char*));
    
    char curr = getchar(); //the current character in input
    //check if it's empty file
    if (feof(stdin)){
        printf("empty file");
        exit(0);
    }
    checkreaderr();
    
    char next = getchar(); //the next character in input
    checkreaderr();
    
    int charnum=0; //index of characters in a word
    int wordnum=0; //index of words in the line
    
    while (curr!=EOF){
        //put curr in word and reallocate word
        word[charnum]=curr;
        char* temp = realloc(word, sizeof(char)*(charnum+2));
        if (temp == NULL){
            free(word);
            free(line);
            fprintf(stderr,"allocation for word failed");
            exit(1);
        }else{
            word = temp;
        }
        
        //if next is EOF
        if (next == EOF){
            if (curr != ' '){
                //add ' ' to word first
                charnum++;
                word[charnum]=' ';
                char* temp = realloc(word, sizeof(char)*(charnum+2));
                if (temp == NULL){
                    free(word);
                    free(line);
                    fprintf(stderr,"allocation for word failed");
                    exit(1);
                }else{
                    word = temp;
                }
            }
            
            //add the last word to line
            line[wordnum]=word;

            curr = next;
            
        }else{
            //if we reach the end of word
            if (curr == ' '){
                //add word to line and reallocate line
                line[wordnum]=word;
                char** temp = realloc(line, sizeof(char*)*(wordnum+2));
                if (temp == NULL){
                    free(word);
                    free(line);
                    fprintf(stderr,"allocation for line failed");
                    exit(1);
                }else{
                    line = temp;
                }
                wordnum++;
                
                //create new word
                char* nextword;
                nextword = (char*) malloc (sizeof(char));
                charnum=-1;
                word = nextword;
            }
            
            charnum++;
            curr=next;
            next = getchar();
            checkreaderr();
        }
    }
    
    //sort line
    qsort(line,wordnum+1,sizeof(char*),cmp);
    
    //print sorted line
    for (size_t i=0; i<=wordnum;i++){
        char* printword= line[i];
        for (;;){
            putchar(*printword);
            printword++;
            if (*printword == ' '){
                putchar(' ');
                break;
            }
        }
    }
    
    //deallocate memory
    for (size_t i=0; i<=wordnum;i++){
        free(line[i]);
    }
    free(line);
    
    return 0;
    
}
