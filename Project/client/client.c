#include "project.h"
;
char* username;

//Error Handler
void Error_Handler(char* msg){
	
	printf("%s: %s\n", msg, strerror(errno));
	exit(1);
}

//Helper function that helps connect the client with the server
int open_clientfd(char* IP_addr, char* port){
	
	int clientfd;
	struct addrinfo hints, *listp, *p;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
	
	//returns a linked list that sockets
	getaddrinfo(IP_addr, port, &hints, &listp);
	
	//Goes through the list until a connection is found
	for(p = listp; p != NULL; p = p->ai_next){
		
		//The case where the connection fails
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) continue;
		
		//The case where a connection is found
		if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) break;
		
		close(clientfd);
	}
	
	freeaddrinfo(listp);
	
	//If there was no connection found, return -1
	if (p == NULL) return -1;
	else return clientfd;
}

void client(int clientfd){
	
	char cmd[100];
	char msg[100];
	
	char** args;
	int argc;
	
	int i;
	int response;
	int size;
	
	int inChannel = 0;
	char curr_channel[20] = {0};
	
	while (TRUE){
		
		bzero(cmd, 100);
		bzero(msg, 100);
		//bzero(curr_channel, 20);
		
		printf("\n>>");
		
		fgets(cmd, 100, stdin);
		cmd[strlen(cmd) - 1] = '\0';
		
		argc = arg_count(cmd);
		args = getargs(cmd);
		//bzero(cmd, 100);
		
		if (ERR_CMD(args, argc, inChannel) == -1) continue;
		
		if (strcmp(args[0], "/quit") == 0){
			
			sprintf(msg, "%s %s %s", username, args[0], curr_channel);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			printf("Leaving the chat server...\n");
			break;
		}
		
		else if (strcmp(args[0], "/help") == 0){
			
			Help_Message();
		}
		
		else if (strcmp(args[0], "/leave") == 0){
			
			sprintf(msg, "%s %s %s", username, args[0], args[1]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else printf("Succefully left %s\n", args[1]);
			
			inChannel = 0;
		}
		
		else if (strcmp(args[0], "/join") == 0){
			
			sprintf(msg, "%s %s %s", username, args[0], args[1]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else{

				printf("Succefully joined %s\n", args[1]);
				strncpy(curr_channel, args[1], sizeof(args[1]));
				inChannel = 1;
			}
			
			
		}
		
		else if (strcmp(args[0], "/promote") == 0){
			
			sprintf(msg, "%s %s %s %s", username, args[0], args[1], args[2]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else printf("Succefully promoted %s\n", args[2]);
		}
		
		else if (strcmp(args[0], "/demote") == 0){
			
			sprintf(msg, "%s %s %s %s", username, args[0], args[1], args[2]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else printf("Succefully demoted %s\n", args[2]);
		}
		
		else if (strcmp(args[0], "/msg") == 0){
			
			char message[100] = {0};
			
			for (i = 2; i < argc && args[i] != NULL; i++)
				sprintf(message, "%s %s", message, args[i]);
				
			sprintf(msg, "%s %s %s %s", username, args[0], args[1], message);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else printf("You sent:\n%s: %s\n", username, message);
		}
		
		else if (strcmp(args[0], "/viewMsg") == 0){
			
			sprintf(msg, "%s %s %s", username, args[0], args[1]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else{

				int filesize;
				read(clientfd, &filesize, sizeof(int));
				char contents[filesize];
				bzero(contents, filesize);
				read(clientfd, contents, filesize);
				
				printf("\n-------------------------------- CHAT LOG --------------------------------\n");
				printf("%s", contents);
				printf("\n-------------------------------- CHAT LOG --------------------------------\n");
			}
		}
		
		else if (strcmp(args[0], "/kick") == 0){
			
			sprintf(msg, "%s %s %s %s", username, args[0], args[1], args[2]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else printf("Succefully kicked %s\n", args[2]);
		}
		
		else if (strcmp(args[0], "/ban") == 0){
			
			sprintf(msg, "%s %s %s %s", username, args[0], args[1], args[2]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else printf("Succefully banned %s\n", args[2]);
		}
		
		else if (strcmp(args[0], "/list") == 0){
			
			sprintf(msg, "%s %s %s", username, args[0], args[1]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else{

				int listSize;
				read(clientfd, &listSize, sizeof(int));
				char list[listSize];
				bzero(list, listSize);
				read(clientfd, list, listSize);
				printf("%s's members:\n", args[1]);
				write(STDIN_FILENO, list, listSize);
			}
		}
		
		else if (strcmp(args[0], "/send") == 0){

			int fd = open(args[2], O_RDWR);

			if (fd != -1)
			{	

				sprintf(msg, "%s %s %s %s", username, args[0], args[1], args[2]);
			
				size = strlen(msg);

				write(clientfd, &size, sizeof(int));
				write(clientfd, msg, strlen(msg));

				struct stat S;
				int filesize;

				stat(args[2], &S);
				filesize = S.st_size;

				char* contents = (char*)mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);

				write(clientfd, &filesize, sizeof(int));
				write(clientfd, contents, filesize);

				close(fd);

				printf("The file has been sent. %s may or may not accept.\n", args[1]);
			}

			else{

				sprintf(msg, "%s %s %s", username, args[0], "fail");
			
				size = strlen(msg);

				write(clientfd, &size, sizeof(int));
				write(clientfd, msg, strlen(msg));

				printf("The file could not be found.");
			}
		}
		
		else if (strcmp(args[0], "/recieve") == 0){
			
			sprintf(msg, "%s %s", username, args[0]);
			
			size = strlen(msg);
			
			write(clientfd, &size, sizeof(int));
			write(clientfd, msg, strlen(msg));
			
			read(clientfd, &response, sizeof(int));
			
			if (response != 0) ERR_MSGNUM(response);
			
			else{
				char c, acceptMsg[42] = {0};
				
				read(clientfd, acceptMsg, 42);
				write(STDOUT_FILENO, acceptMsg, 42);
				read(STDIN_FILENO, &c, 1);
				write(clientfd, &c, 1);
				
				if (c == 'y' || c == 'Y'){
					
					char filename[20] = {0}, filePath[30];
					int filesize;
					
					read(clientfd, filename, 20);
					read(clientfd, &filesize, sizeof(int));
					
					char fileContents[filesize];
					read(clientfd, fileContents, filesize);
					
					sprintf(filePath, "recieved/%s", filename);
					
					int fd = open(filePath, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
					write(fd, fileContents, filesize);
					
					close(fd);
				} 
			}
		}
		
		
		else 
		printf("Invalid argument. Try again. lol\n");
		
	}
}

//beginning of main
int main(int argc, char **argv) {
    
    //If the the user didn't enter the ip address and port number as command line arguments, then there will be an error
    if (argc != 4){
    
    	Error_Handler("Expected three arguments\n");
    }
    
    int clientfd;
    
    if ((clientfd = open_clientfd(argv[1], argv[2])) == -1){
    	
    	Error_Handler("Could not connect to server");
    }
    
    username = argv[3];
    
    //the client function is called
    client(clientfd);
    
    close(clientfd); 
    
    return 0;
}
//End of main.





