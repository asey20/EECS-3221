/*

# Family Name: Geller

# Given Name: David

# Section: Z

# Student Number: 214404255

# CSE Login: dgeller

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct for words
typedef struct {
	char word[101];
	int freq;
} WordArray;

//struct to place words in file
typedef struct {
	WordArray list[1000];
	char fileName[101];
	int totalWords;
} FileArray;

WordArray words[1000];
FileArray fin[101];

//qsort parameters for freq
int freqCmp(const void *a, const void *b){
	WordArray *pa = (WordArray *)a;
	WordArray *pb = (WordArray *)b; 
	
	return (pb->freq - pa->freq);
}

//qsort parameters for ascii order
int wordCmp(const void *a, const void *b){
	WordArray *pa = (WordArray *)a;
	WordArray *pb = (WordArray *)b;

	int diff = strcmp(pa->word, pb->word);
	
	if (diff == 0){
		if (pa->word > pb->word)
			diff = -1;
		else if (pa->word < pb->word)
			diff = +1;
		else
			diff = 0;
		}
	return diff;
}

int main(int argc, char * argv[]) {

	int count;
	int inList;
	int i;

	for (i = 1; i < argc; i++){
		FILE *fp;
		char data[1000];
		count = 0;
		//check if file is in command line
		if (argc < 2){
			printf("Usage: %s file is invalid!", argv[i]);
		} else {

			fp = fopen(argv[i], "r");
			
			//check if file is there
			 if (fp == NULL){
				printf("File is NULL!\n");
			} else {
				while ((fscanf(fp, "%s", data)) != EOF){
			
				inList = -1; //not in list
				
				int j; 
				//check if work is in list
				for (j = 0; j < count; j++){
					if (strcmp(words[j].word, data) == 0){
						inList = j;
					} 
				}
				//puts string in array if not there
				if (inList == -1){
					strcpy(words[count].word, data);
					words[count].freq = 1;
					count++;
				} else { //increases word freq counter
					words[inList].freq++;
					}
				}
			}
			//sorts words in ascii order using qsort
			qsort(words, count, sizeof(WordArray), wordCmp);
			//sorts words in freq order using qsort
			qsort(words, count, sizeof(WordArray), freqCmp);
			
			int k;
			
			for (k = 0; k < count; k++){
				fin[i].list[k] = words[k];
				//testing to see if sorted (ignore)
				//printf("word%d: '%s' occurs %d times.\n", k, fin[i].list[k].word, words[k].freq);
			}
			fin[i].totalWords = count;
			strcpy(fin[i].fileName, argv[i]);
			fclose(fp);

			if (fin[i].list[i].word != NULL){
				//if the list is even this is the output
				if (fin[i].totalWords%2 == 0){
					printf("File Name: '%s' Number of Words: '%d' Median Word: '%s' \n", fin[i].fileName, fin[i].totalWords, fin[i].list[count/2].word);
				}else{ //if the list is odd this is the output
					printf("File Name: '%s' Number of Words: '%d' Median Word: '%s' \n", fin[i].fileName, fin[i].totalWords, fin[i].list[(count/2 + 1)].word);
				}
			}				 
		}
		
	}
	
}	


