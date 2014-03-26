/*
 * Без имени.c
 * 
 * Copyright 2014 Lex <lex22@ubuntu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/param.h>
#include <stdlib.h>
#include <sys/types.h>
#define MAX_FILE_LENGTH  1000


int checkStringMatch(char* toSearch, char* pattern);

char* switchToLower(char* string);
// Processes a file, printing any lines in that file that match the given search pattern
void processfile(char* filename, char* pattern );
// Checks for possible options and returns the number of enabled options
int checkoptions(char** argv);

int optionn = 0;

int checkoptions(char** argv){
	int numOptions = 0;
	if(checkStringMatch(argv[1], "-n") || checkStringMatch(argv[2], "-n")){
		optionn = 1;
		numOptions++;
	}      
	return numOptions;
}

void processfile(char* filename, char* pattern){
	FILE* f = fopen(filename, "r");// r - only for reading
	// If the file doesn't exist - error
	if(!f){
		printf("error \n");
		return;
	}
	char* line = (char*)malloc(MAX_FILE_LENGTH * sizeof(char)); 
	int lineNum = 1;                         
	while(!feof(f)){  // check the end of file   
		line = fgets(line, MAX_FILE_LENGTH, f);// gets the next line
		// if the line is non-null
		if(line){
			if(optionn){
					if(checkStringMatch(line, pattern)){
						printf("%d %s %s", lineNum*optionn, filename, line);
						}
					}
					lineNum++;
			}
	}
	fclose(f);      
	free(line);
}

int checkStringMatch(char* toSearch, char* pattern){
	char* exists = strstr(toSearch, pattern);
	if(exists){
		return 1;
	}
	return 0;
}

char* switchToLower(char* str){       
	char* newString = (char*)malloc(sizeof(char)*strlen(str));
	//Iterate each letter to lowercase
	int i;
	for(i = 0; str[i]; i++){
		newString[i]=tolower(str[i]);           
	}
	return newString;
}

int main(int argc, char**argv){
	if(argc < 3){
		fputs("Write search word and at least 1 file.\n", stderr);
		return 1;
	}
	int numoptions = checkoptions(argv);
	char* pattern = argv[numoptions+ 1];
	int i;
	for(i = numoptions + 2; i < argc; i++){
		char* filename = argv[i];
		processfile(filename, pattern);         
	}
	return 0;
}

