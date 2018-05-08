#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



void errorFunc(){
	if(ferror(stdin)){
		fprintf(stderr, "Error: Can't read file");
		exit(1);
	}
}

/* Takes in two frobnicated arrays */
int frobcmp(char const *a, char const *b){
	/*while(1){ 
		if(*a == ' ' && *b == ' ') return 0;
		else return (*a == ' ' || (*a)^42 < (*b)^42) ? -1 : 1;
		a++;
		b++;
	}	*/
	while(1) { //Loop to look at entire words
		if(*a == ' ' && *b == ' ') { return 0; }
		else if (*a == ' ' || ((*a^42) < (*b^42))) { return -1; }
		else if (*b == ' ' || ((*a^42) > (*b^42))) { return 1; }
		a++; b++;
  	}


}

int compareLetter(const void* lett1, const void* lett2){
	const char* c1 = *(const char**)lett1;
	const char* c2 = *(const char**)lett2;
	return frobcmp(c1,c2);
}

void outputStuff(const char* str)
{
    while(1){
        putchar(*str); // std out, opposite of getchar
        str++;
        if (*str == ' ' || *str == EOF || *str == '\0'){
        	putchar(' ');
            return;
        }
        	
    }
}



int main(){
	// get characters from the cmd line 
	// Define EOF
	//int EOF = feof(stdin);
	// BUFFER
	size_t spaceAvailable = 1, bufferIndex = 0;
	char* buffer = (char*) malloc(sizeof(char) * spaceAvailable); // SIZE = 43 (arbitrary). Also need to cast to char* because it's void at first
	
	
	while( !feof(stdin) ){
		char c = getchar();
		if (c == EOF) break;
		// check the buffer didn't run out of space.
		if(bufferIndex == spaceAvailable){
			// Expand the amt of space multiply by 2
			// Realloc 
			spaceAvailable += 2; 
			buffer = (char*) realloc(buffer ,sizeof(char) * spaceAvailable); // Reallocating old buffer, so no new buffer
		}
		buffer[bufferIndex] = c; // put it in the buffer
		//EOF = feof(stdin); // feof can change so gotta do it again
		bufferIndex++; // on to the next char
	}
	buffer[bufferIndex] = '\0';
	bufferIndex--; // EOF: bufferIndex one too big.
	// Done: Put characters in the array.
	// TODO: Put pointers to the start of each word. The compare/sort methods will reorder the POINTERS.
	char** startIndexes = (char**) malloc(sizeof(char*) * spaceAvailable); //[spaceAvailable];
	int startindex = 0;
	//int* wordsizes = (int*) malloc(sizeof(int) * spaceAvailable);
	char* currentLine = &buffer[0]; // This is a placeholder that will make assigning pointers much easier.
	
	int i = 0;
	// First word
	for (; i < bufferIndex; i++){ // spaces initially
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
	//printf("%d\n", bufferIndex );
	// remaining words
	for (; i < bufferIndex; i++){
		
		if (buffer[i] == ' ' || buffer[i] == EOF){
			continue;
		}	
		else{
			if (buffer[i-1] == ' ' && buffer[i] != ' '){ // Criteria for next word.
				currentLine = &buffer[i];
				startIndexes[startindex] = currentLine;
				startindex++;
			}	
		}	
	}	
	/*for (;startindex++;){
		printf("%d", startindex);
	}*/
	// QUICKSORT
	qsort(startIndexes,startindex, sizeof(char*), compareLetter);
	//printf("%d", startindex);
	// OUTPUT

	for (i = 0; i < startindex; i++){
		outputStuff(startIndexes[i]);
		//fprintf(stderr, "i value: %d\n", i);
	}

	// Free everything
	free(startIndexes);
	free(buffer);
	return 0;
}	



	
