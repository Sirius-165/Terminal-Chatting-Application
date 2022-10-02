#include "project.h"

channel* chnl;

//SIGINT handler
void sigint_handler(){
	
	printf(" Terminating the program...\n");
	exit(0);
}

//Error Handler
void Error_Handler(char* msg){
	
	printf("%s: %s\n", msg, strerror(errno));
	exit(1);
}

// a helper function to recieve connection requests from the client
int open_listenfd(char* port){
	int listenfd, opt_val = 1;
	struct addrinfo hints, *listp, *p;
	
	//reserve needed amount of memory for list
	memset(&hints, 0, sizeof(struct addrinfo));
	
	// accept a connection
	hints.ai_socktype = SOCK_STREAM; 
	// ^^ with a specfied IP address and port number  
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
	
	//gets the needed IP address info
	getaddrinfo(NULL, port, &hints, &listp);
	
	//goes through list until a connection that can be binded to is found
	for(p = listp ; p ; p->ai_next){
		
		//check if socket failed
		if(listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol) < 0){
			continue;
		}
		
		//prevents bind error for 'used addresses'
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt_val, sizeof(int));
		
		//bind descriptor to the correct address
		if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0){
			break;	//bind was successful
		}
		
		//bind failed ; next loop iteration checks the next address
		close(listenfd);
	}
	
	freeaddrinfo(listp);
	
	//no valid addresses were found
	if(p == NULL){
		return -1;
	}
	
	//change socket to be ready to recieve connections
	
	if(listen(listenfd, LISTENQ) < 0){
		close(listenfd);
		return -1;
	}
	
	return listenfd;	
}

// server operation 
void server(int connfd){

	//channel* chnl = init();
	
	char cmd[100];
	static char reciever[20] = {0};
	static char filename[50] = {0};
	static char* contents;
	static int size;
	int err_num, i;
	
	char** args;
	int argc;
	
	while (TRUE){
		
		bzero(cmd, 100);
		
		read(connfd, &size, sizeof(int));
		read(connfd, cmd, size);
		
		argc = arg_count(cmd);
		args = getargs(cmd);
		//bzero(cmd, 100);
		
		if (strcmp(args[1], "/quit") == 0){
			
			if (user_search(chnl, args[2], args[0]) != -1)
				user_remove(chnl, args[2], args[0]);
			
			close_all(chnl);
			
			close(connfd);
			break;
		}
		
		else if (strcmp(args[1], "/leave") == 0){
		
			printf("leave err: ");
			
			if (channel_search(chnl, args[2]) == -1){
				
				err_num = 1; //no such channel
				
				printf("1\n");
			}
			
			else if (user_search(chnl, args[2], args[0]) == 0){
				
				err_num = 2; //no user in channel
				
				printf("2\n");
			}
			
			else{
				user_remove(chnl, args[2], args[0]);
				err_num = 0; //success
				
				printf("0\n");
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/join") == 0){
			
			printf("join err: ");
			
			if (channel_search(chnl, args[2]) == -1){
				
				err_num = 0;
				channel_insert(chnl, args[2]);
				user_insert(chnl, args[2], args[0]);
				
				printf("0\n");
			}
			
			else if (banned_search(chnl, args[2], args[0]) == 1){
				
				err_num = 3; //the user is banned
				
				printf("3\n");
			}
			
			else if (user_search(chnl, args[2], args[0]) == 1){
				
				err_num = 4; //the user is already in the channel
				
				printf("4\n");
			}
			
			else{
				
				user_insert(chnl, args[2], args[0]);
				err_num = 0; //success
				
				printf("0\n");
			}
			
			//printf("%s has joined %s\n", args[0], args[2]);
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/promote") == 0){
			
			printf("promote err: ");
			
			if (channel_search(chnl, args[2]) == -1){
				
				err_num = 1; //no such channel
				printf("1\n");
			}
			
			else if (user_search(chnl, args[2], args[3]) == 0){
				
				err_num = 2; //no user in channel
				printf("2");
			}
			
			else if (isPromoted(chnl, args[2], args[0]) == 0){
				
				err_num = 5; //a non operator cannot promote/demote
				printf("5\n");
			}
			
			else if (isPromoted(chnl, args[2], args[3]) == 1){
				
				err_num = 6; //the user is already promoted
				printf("6\n");
			}
			
			else{
				
				promote(chnl, args[2], args[3]);
				err_num = 0; //success
				
				printf("success\n");
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/demote") == 0){
		
			printf("demote err: ");
			
			if (channel_search(chnl, args[2]) == -1){
				
				err_num = 1; //no such channel
				
				printf("1\n");
			}
			
			else if (user_search(chnl, args[2], args[3]) == 0){
				
				err_num = 2; //no user in channel
				
				printf("2\n");
			}
			
			else if (isPromoted(chnl, args[2], args[0]) == 0){
				
				err_num = 5; //a non operator cannot promote, demote, kick, ban
				
				printf("5\n");
			}
			
			else if (isPromoted(chnl, args[2], args[3]) == 0){
				
				err_num = 7; //the user is already demoted
				
				printf("7\n");
			}
			
			else{
				
				demote(chnl, args[2], args[3]);
				err_num = 0; //success
				
				printf("0\n");
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/msg") == 0){

			char message[100] = {0};
		
			if (args[2][0] == '#'){
				
				if (channel_search(chnl, args[2]) == -1){
				
					err_num = 1; //no such channel
				
					printf("1\n");
				}
				
				else{


					for (i = 3; i < argc && args[i] != NULL; i++)
						sprintf(message, "%s %s", message, args[i]);

					msg(args[0], chnl, args[2], message);
					err_num = 0;
					
					printf("0\n");
				}
			}

			else{

				for (i = 3; i < argc && args[i] != NULL; i++)
						sprintf(message, "%s %s", message, args[i]);

				PM(message , args[0], args[2]);
				err_num = 0;
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		else if (strcmp(args[1], "/viewMsg") == 0){
			
			if (args[2][0] == '#'){
				
				if (channel_search(chnl, args[2]) == -1){
				
					err_num = 1; //no such channel
				
					printf("1\n");
				}
				
				else{
						
					char filename[20] = {0};
					sprintf(filename, "%s.txt", args[2]);
					if (search_dir("logs/channels", filename) == 0){

						err_num = 9; //Could not find chat log
						printf("9\n");
					}

					else{

						err_num = 0;
						write(connfd, &err_num, sizeof(int));
						viewPM(connfd, args[0], args[2]);
					
						printf("0\n");

						continue;
					}
				}
			}
			
			else{

				char userPath[50] = {0};
				char userdir[50] = {0};
				sprintf(userPath, "%s.txt", args[2]);
				sprintf(userdir, "logs/users/%s", args[0]);
				if (search_dir(userdir, userPath) == 0){

					err_num = 9; //Could not find chat log
					printf("9\n");
				}

				else{

					err_num = 0;
					write(connfd, &err_num, sizeof(int));
					viewMsg(connfd, args[0], args[2], chnl);
					
					printf("0\n");

					continue;
				}
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/kick") == 0){
		
			printf("kick err: ");
			
			if (channel_search(chnl, args[2]) == -1){
				
				err_num = 1; //no such channel
				
				printf("1\n");
			}
			
			else if (user_search(chnl, args[2], args[3]) == 0){
				
				err_num = 2; //no user in channel
				
				printf("2\n");
			}
			
			else if (isPromoted(chnl, args[2], args[0]) == 0){
				
				err_num = 5; //a non operator cannot promote, demote, kick, ban
				
				printf("5\n");
			}
			
			else{
				
				user_remove(chnl, args[2], args[3]);
				err_num = 0; //success
				
				printf("0\n");
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/ban") == 0){
		
			printf("ban err: ");
			
			if (channel_search(chnl, args[2]) == -1){
				
				err_num = 1; //no such channel
				
				printf("1\n");
			}
			
			else if (user_search(chnl, args[2], args[3]) == 0){
				
				err_num = 2; //no user in channel
				
				printf("2\n");
			}
			
			else if (isPromoted(chnl, args[2], args[0]) == 0){
				
				err_num = 5; //a non operator cannot promote, demote, kick, ban
				
				printf("5\n");
			}
			
			else{
				
				banned_insert(chnl, args[2], args[3]);
				err_num = 0; //success
				
				printf("0\n");
			}
			
			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/list") == 0){
			
			if (channel_search(chnl, args[2]) == -1){

				err_num = 1;
				printf("1\n");
			}
			/*
			else if (isChannelEmpty(chnl, args[2]) == 0){

				err_num = 10; //the channel is empty
				printf("10\n");
			}
*/
			else{
				err_num = 0;
				printf("0\n");

				write(connfd, &err_num, sizeof(int));

				list(chnl, args[2], connfd);

				continue;
			}

			write(connfd, &err_num, sizeof(int));
		}
		
		else if (strcmp(args[1], "/send") == 0){
			

			if (strcmp(args[2], "fail") != 0){

				read(connfd, &size, sizeof(int));
				read(connfd, contents, size);
				strncpy(reciever, args[2], strlen(args[2]));
				strncpy(filename, args[3], strlen(args[3]));

				printf("usrname: %s   reciever: %s   file: %s\n", args[0], reciever, filename);
			}
		}
		
		else if (strcmp(args[1], "/recieve") == 0){
			
			printf("usrname: %s   reciever: %s   file: %s\n", args[0], reciever, filename);
			if (strcmp(reciever, args[0]) == 0){
			
				err_num = 0;
				write(connfd, &err_num, sizeof(int));
				
				char c;
				write(connfd, "Are you sure you accept this file? (Y/N): ", 42);
				read(connfd, &c, 1);
				
				if (c == 'y' || c == 'Y'){
				
					if (1/*fork() == 0*/){
						
						write(connfd, filename, strlen(filename));
						write(connfd, &size, sizeof(int));
						write(connfd, contents, size);
						//exit(0);
					}
					
					bzero(reciever, 20);
					bzero(filename, 50);
				}
			}
			
			else{
				err_num = 8; //Cannot recieve a file not intended for you
				write(connfd, &err_num, sizeof(int));
			}
			
		}
	}
}



void* thread(void* argv){

	int connfd = *((int*)argv);

	pthread_detach(pthread_self());
	free(argv);

	server(connfd);
	close(connfd);

	return NULL;

}

// server main
int main(int argc, char *argv[]){

	chnl = init();

	if (argc != 2){
    
    	    Error_Handler("Expected two arguments\n");
    	}
    
        if (signal(SIGINT, sigint_handler) == SIG_ERR){
    
    	    Error_Handler("SIGINT error.");
        }	
	
	int listenfd, *connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	char client_hostname[MAXLINE], client_port[MAXLINE];
	pthread_t tid;
	
	bzero(client_hostname, MAXLINE);
	bzero(client_port, MAXLINE);

	listenfd = open_listenfd(argv[1]);
    
	while (1) {
		clientlen = sizeof(struct sockaddr_storage); 

		connfd = (int*)malloc(sizeof(int));
		
		//accept func.
		*connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        	
        getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        	
        //connection message
        printf("The server has connected to client %s %s \n", client_hostname, client_port);
        	
        pthread_create(&tid, NULL, thread, connfd);
    }
    
	exit(0);
}
