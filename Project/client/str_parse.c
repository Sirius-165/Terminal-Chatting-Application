//Project By: Ghazi and Samar
//str_parse.c
//utility functions to parse a string; will not be directly called by user 
#include "str_parse.h"

//Returns the number of arguments
int arg_count(char* cmd){
	
	//state keeps track if the string is in a word or space
	int state = 0;
	int argc = 0;
	int i = 0;
	
	//Goes through the string and counts the number of arguments
	while(*(cmd + i) != '\0'){
		
		if (*(cmd + i) == ' ') state = 0;
		
		else if (state == 0){
			
			state = 1;
			argc++;
		}
		
		i++;
	}
	
	//return the argument count
	return argc;
}

//tokenises all the arguments and returns them in an array of strings
char** getargs(char cmd[]){
    
    //Gets the argument count by using arg_count
    int i, argc = arg_count(cmd);
    
    //Allocates memory for the array and each of its indexes
    char** args = malloc((argc + 1) * sizeof(char*));
    for (i = 0; i < argc; i++) args[i] = (char*)malloc(100);
    
    i = 0;
    char* token = strtok(cmd, " ");
    
    //Goes through the string and tokenises all the arguments
    while (token != NULL){
        
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    
    args[i] = NULL;
    
    //Returns the array of arguments 
    return args;
}
