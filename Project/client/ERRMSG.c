#include "ERRMSG.h"

int ERR_CMD(char** args, int argc, int inChannel){

	
	if (strcmp(args[0], "/quit") == 0){
		
		if (argc != 1){
			
			printf("Expected only one argument.\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/help") == 0){
		
		if (argc != 1){
			
			printf("Expected only one argument.\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/leave") == 0){
		
		if (argc != 2){
			
			printf("Expected two arguments.\n");
			return -1;
		}
		
		if (args[1][0] != '#'){
			
			printf("Invalid channel name. Channels start with \'#\'\n");
			return -1;
		}
		
		if (inChannel == 0){
			
			printf("Can't leave a channel when you are not in one. Try joining one!\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/join") == 0){
		
		if (argc != 2){
			
			printf("Expected two arguments.\n");
			return -1;
		}
		
		if (args[1][0] != '#'){
			
			printf("Invalid channel name. Channels start with \'#\'\n");
			return -1;
		}
		
		if (inChannel == 1){
			
			printf("Can't join a channel when you are already in one. Try leaving first.\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/promote") == 0){
		
		if (argc != 3){
			
			printf("Expected three arguments.\n");
			return -1;
		}
		
		if (args[1][0] != '#'){
			
			printf("Invalid channel name. Channels start with \'#\'\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/demote") == 0){
		
		if (argc != 3){
			
			printf("Expected three arguments.\n");
			return -1;
		}
		
		if (args[1][0] != '#'){
			
			printf("Invalid channel name. Channels start with \'#\'\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/msg") == 0){
		
		if (argc <= 2){
			
			printf("Expected at least three arguments.\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/viewMsg") == 0){
		
		if (argc != 2){
			
			printf("Expected two arguments.\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/kick") == 0){
		
		if (argc != 3){
			
			printf("Expected three arguments.\n");
			return -1;
		}
		
		if (args[1][0] != '#'){
			
			printf("Invalid channel name. Channels start with \'#\'\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/ban") == 0){
		
		if (argc != 3){
			
			printf("Expected three arguments.\n");
			return -1;
		}
		
		if (args[1][0] != '#'){
			
			printf("Invalid channel name. Channels start with \'#\'\n");
			return -1;
		}
	}
	
	else if (strcmp(args[0], "/list") == 0){
		
		if (argc != 2){
			
			printf("Expected two arguments.\n");	
			return -1;
		}	
	}
	
	return 0;
}

void ERR_MSGNUM(int num){
	
	switch(num){
		
		case 1:
			printf("There is no such channel.\n");
			break;
		case 2:
			printf("There is no such user in the channel.\n");
			break;
		case 3:
			printf("This user has been banned.\n");
			break;
		case 4:
			printf("You are alreday in the channel.\n");
			break;
		case 5:
			printf("a non operator cannot promote, demote, kick, ban.\n");
			break;
		case 6:
			printf("The user is alreday promoted.\n");
			break;
		case 7:
			printf("The user is alreday demoted.\n");
			break;
		case 8:
			printf("You cannot recieve a file that is not intended for you.\n");
			break;
		case 9:
			printf("Could not find channel/user chat log.\n");
			break;
		case 10:
			printf("The channel is empty.\n");
			break;
		default:
			break;
	}
}
