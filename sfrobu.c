
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

void errorFunc(){
	if(ferror(stdin)){
		fprintf(stderr, "Error: Can't read file");
		exit(1);
	}
}

void memoryError(void* ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Error: Nullptr\n");
        exit(1);
    }
}

/* Takes in two frobnicated arrays */
int frobcmp(char const *a, char const *b){
	while(1) { //Loop to look at entire words
		if(*a == ' ' && *b == ' ') { return 0; }
		else if (*a == ' ' || ((*a^42) < (*b^42))) { return -1; }
		else if (*b == ' ' || ((*a^42) > (*b^42))) { return 1; }
		a++; b++;
  	}
}

// -f option
int frobcmp_f(char const *a, char const *b){
	if ((*a ^ 42) > 255 || (*a ^ 42) < 0 || (*b ^ 42) > 255 || (*b ^ 42) < 0){ // 0-255 char
		fprintf(stderr, "Invalid use of -f option" );
		exit(1);
	}
	while(1) {
        if(*a == ' ' && *b == ' ') return 0;
        else if(toupper(*a ^ 42) > toupper(*b ^ 42) || *b == ' ') return 1; // toupper converts letter to uppercase
        else if(toupper(*b ^ 42) > toupper(*a ^ 42) || *a == ' ') return -1;
        a++; b++;
    }

}

int compareLetter(const void* lett1, const void* lett2){ // Wrapper
	const char* c1 = *(const char**)lett1;
	const char* c2 = *(const char**)lett2;
	return frobcmp(c1,c2);
}
int compareLetter_f(const void* lett1, const void* lett2){
	const char* c1 = *(const char**)lett1;
	const char* c2 = *(const char**)lett2;
	return frobcmp_f(c1,c2);
}



int main(int argc, const char * argv[]){
	// if f option is enabled do not check case
    int f = 0;
    
    // parse and check arguments
    if(argc > 2) {
        fprintf(stderr, "Invalid arguments: Cannot have more than two arguments.\n");
        exit(1);
    }
    if(argc == 2) {
        if(strcmp(argv[1], "-f") == 0) {
            f = 1;
        } else {
            fprintf(stderr, "Invalid arguments: -f\n");
            exit(1);
        }
    }
	
     // set and check file status
    struct stat fstatus;
    if(fstat(STDIN_FILENO, &fstatus) < 0) {
        fprintf(stderr, "Error in getting file status.\n");
        exit(1);
    }

    // buffer for input
    char* buffer;
    int size, index;

    if(S_ISREG(fstatus.st_mode)){
    	// read entire file, if it's a regular file
    	index = size = fstatus.st_size;
    	buffer = (char*) malloc(sizeof(char) * (size + 1)); // extra slot for space
    	if (read(0, buffer, size) < 0){
    		errorFunc();
    	}
    }
    else{
    	// char by char
    	buffer = (char*) malloc (sizeof(char));
    	size = 1; index = 0;
    	memoryError(buffer);
    	// Pointer to the current one
   		char* curr = (char*) malloc(sizeof(char));
   		while(1){
   			int status = read(0, curr, 1);
   			if (status < 1) 
   				break;
   			errorFunc();
   			
   			buffer[index] = *curr;
   			index++;
   			// If buffer is full, reallocate/expand.
   			if(index == size){
   				size *= 3;
   				buffer = (char*) realloc(buffer, sizeof(char) * size);
   				memoryError(buffer);
   			}
   		}
   		free(curr);
    }
    buffer[index] = ' '; // frobnicate definition





    
    
	// Done: Put characters in the array.
	// TODO: Put pointers to the start of each word. The compare/sort methods will reorder the POINTERS.
	char** startIndexes = (char**) malloc(sizeof(char*)); //[spaceAvailable];
	memoryError(startIndexes);
	int startindex = 0;
	//int* wordsizes = (int*) malloc(sizeof(int) * spaceAvailable);
	char* currentLine = buffer; // This is a placeholder that will make assigning pointers much easier.
	int startIndexesSize = 1;
	int i = 0;
	// First word
	for (; i < index; i++){ // spaces initially
		if(buffer[i] == ' ' || buffer[i] == EOF){
			continue;
		}
		else{
			currentLine = &buffer[i];
			//printf("%s\n",currentLine);
			startIndexes[startindex] = currentLine;
			startindex++; // remember this, arrays are annoying
			i++;
			break; // remember we're only doing this for the FIRST WORD
		}
	}	

	// remaining words
	for (; i < index; i++){
		
		if (buffer[i] == ' ' || buffer[i] == EOF){
			continue;
		}	
		else{
			if (buffer[i-1] == ' ' && buffer[i] != ' '){ // Criteria for next word.
				currentLine = &buffer[i];
				if (startindex == startIndexesSize){
					startIndexesSize *= 3;
	   				char** tmp = (char**) realloc(startIndexes, sizeof(char*) * startIndexesSize);
	   				memoryError(tmp);
	   				startIndexes = tmp;
				}
				
				startIndexes[startindex] = currentLine;
				startindex++;
			}	
		}	
	}	
	/*for (;startindex++;){
		printf("%d", startindex);
	}*/
	// QUICKSORT

	if (f > 0) qsort(startIndexes,startindex, sizeof(char*), compareLetter_f);
	else qsort(startIndexes,startindex, sizeof(char*), compareLetter);


	//printf("%d", startindex);
	// OUTPUT
    
	for (i = 0; i < startindex; i++){
		int j = 0;
        while(startIndexes[i][j] != ' '){
        	j++;
        }
       	int status2 = write(1, startIndexes[i], j + 1);
        if (status2 < 1)
            fprintf(stderr, "Writing Error\n");
	}
	
	// Free everything
	free(startIndexes);
	free(buffer);
	return 0;
}	


