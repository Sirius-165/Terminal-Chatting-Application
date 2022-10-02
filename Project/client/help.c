//Project By: Ghazi and Samar
//help.c
//contain function for '/help'
#include "help.h"

#define SWITCH Errmsg_Label

//Shows a list of all commands and their descriptions
void Help_Message(){
	
	printf("\n<Syntax> | <Example> | <Description>\n\n\n");

	printf("./client <server IP> <Server Port> <username> | ./client 127.0.0.1 6667 csuser | This command connects the client with the server as the username given in the command.\n\n");

	printf("/join #<Channel Name> | /join #cs223 | Allows the client to join the channel given in the command.\n\n");

	printf("/msg #<Channel Name> <Message> | /msg #cs223 Hello, Class! | Sends a message to a channel.\n\n");

	printf("/viewMsg #<Channel Name> | /viewMsg #cs223 | Shows the chat log in the requested channel.\n\n");

	printf("/leave #<Channel Name> | /leave #cs223 | Allows the client to leave the channel.\n\n");

	printf("/kick #<Channel Name> <Username> | /kick #cs223 csuser | Allows the client to kick a user from the channel. This command can only be done by an operator.\n\n");

	printf("/ban #<Channel Name> <Username> | /ban #cs223 csuser | The command is similar to kick, but the user is not allowed in the channel again unless they are unbanned.\n\n");

	printf("/promote #<Channel Name> <Username> | /promote #cs223 csuser | Upgrades a regular user into an operator. This command can only be done by an operator.\n\n");

	printf("/demote #<Channel Name> <Username> | /demote #cs223 csuser | Downgrades an operator into a regular user. This command can only be done by an operator.\n\n");

	printf("/list #<Channel Name> | /list #cs223 | Shows all the current members that are in the channel.\n\n");
	
	printf("/help | /help | Lists all the commands.\n\n");

	printf("/quit | /quit | Terminates the program.\n\n");
}
