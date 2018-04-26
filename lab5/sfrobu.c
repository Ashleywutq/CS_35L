
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

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

int frobcmp2 (char const* a, char const* b){
    for (;;a++, b++){
        int inta = (*a)^42;
        int intb = (*b)^42;
        if (*a==' ' && *b == ' '){return 0;}
        else if ((*a == ' ')||(toupper(inta)<toupper(intb))) {return -1;}
        else if ((*b == ' ')||(toupper(inta)>toupper(intb))) {return 1;}
    }
}

int cmp2(const void* a, const void* b){
    const char* w1= *(const char **)a;
    const char* w2= *(const char **)b;
    return frobcmp2(w1,w2);
}

void checkreaderr(ssize_t state){
    if (state < 0){
        fprintf(stderr, "read failed");
        exit(1);
    }
}

void checkwriteerr(ssize_t state){
    if (state < 0){
        fprintf(stderr, "write failed");
        exit(1);
    }
}


int main(int argc, char* argv[]){
    struct stat buf;
    
    //if error is returned when checking file type
    if (fstat(0,&buf)<0){
        fprintf(stderr,"Error with fstat");
        exit(1);
    }
    
    char* fileword; //point to an array of characters
    char** line; //point to an array of word pointers
    int wordnum=0; //index of words in the line
    
    //if the file is regular file, allocate memory
    if (S_ISREG(buf.st_mode)){
        fileword = (char*)malloc ((buf.st_size+1) * sizeof(char));
        
        //read from stdin to fileword
        ssize_t state = read(0,fileword,buf.st_size);
        checkreaderr(state);
        
        //count how many words are in the file
        size_t i;
        size_t addsize=0;
        int wordcount = 0;
        for (i = 0; i<buf.st_size; i++){
            //if the last character is not ' ', add ' '
            if (i == buf.st_size - 1 && fileword[i] != ' '){
                addsize=1;
                fileword[i+1]=' ';
                wordcount++;
            }
            
            //if we encounter a ' ', then it's a word
            if (fileword[i] == ' '){
                wordcount++;
            }
        }
        
        //add words to line, add wordnum
        line = (char**)malloc(wordcount*sizeof(char*));
        int charcount=0;
        for (i=0; i<buf.st_size+addsize;i++){
            charcount++;
            if (fileword[i] == ' '){
                char* newword;
                newword = (char*) malloc (charcount * sizeof(char));
                int l;
                for (l=0;l<charcount;l++){
                    newword[l] = fileword[i-charcount+1+l];
                }
                line[wordnum]=newword;
                wordnum++;
                charcount = 0;
            }
        }
    }
    
    line = (char**) malloc ((wordnum+1) * sizeof(char*));
    char* word;
    word = (char*) malloc(sizeof(char));
    
    //check if it's empty
    if (feof(stdin)){
        exit(0);
    }
    
    //make a buffer to store current character
    char curr[1];
    ssize_t currstate = read(0,curr,1);
    checkreaderr(currstate);
    
    //the next character in input
    char next[1];
    ssize_t nextstate = read(0,next,1);
    checkreaderr(nextstate);
    
    int charnum=0; //index of characters in a word
    
    
    while (currstate!=0){
        //put curr in word and reallocate word
        word[charnum]=curr[0];
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
        if (nextstate == 0){
            if (curr[0] != ' '){
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
            curr[0] = next[0];
            break;
            
        }else{
            //if we reach the end of word
            if (curr[0] == ' '){
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
            curr[0]=next[0];
            currstate = nextstate;
            nextstate = read(0,next,1);
            checkreaderr(nextstate);
        }
    }
    
    //sort with or without -f option
    if (argc == 1) {
        qsort(line,wordnum+1,sizeof(char*),cmp);
    }else{
        qsort(line,wordnum+1,sizeof(char*),cmp2);
    }
    
    //print sorted line
    size_t j,k;
    for (j=0; j<=wordnum;j++){
        char* printword= line[j];
        
        //get word size
        int size = 0;
        for (k=0;;k++){
            size++;
            if (printword[k] == ' '){break;}
        }
        
        ssize_t writestate = write(1,printword,size);
        checkwriteerr(writestate);
        
    }
    
    //deallocate memory
    for (size_t i=0; i<=wordnum;i++){
        free(line[i]);
    }
    free(line);
    
    return 0;
    
}
