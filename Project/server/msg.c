#include "msg.h"

void msg(char* username, channel chnl[], char* channel_name, char* msg){
	
	char message[100] = {0};
	char path[20] = {0};
	
	sprintf(message, "%s: %s\n", username, msg);
	
	int i = channel_search(chnl, channel_name);
	
	lseek(chnl[i].fd, 0, SEEK_END);
	
	write(chnl[i].fd, message, strlen(message));
}

int viewMsg(int fd, char* username, char* path, channel chnl[]){
	
	char chnl_file[20] = {0};
	char fullPath[50] = {0};
	char contents[100] = {0};
	char user_dir[50] = {0};
	char user_file[50] = {0};
	struct stat S;
	int size;
	
	sprintf(chnl_file, "%s.txt", path);
	sprintf(fullPath, "logs/channels/%s", chnl_file);

	sprintf(user_dir, "logs/user/%s", username);
	sprintf(user_file, "%s.txt", path);
	
	if (search_dir("logs/channels", chnl_file) || search_dir(user_dir, user_file)){
		
		if (search_dir("logs/channels", chnl_file)){
			
			int i = channel_search(chnl, path);
			lseek(chnl[i].fd, 0, SEEK_SET);
			
			stat(fullPath, &S);
			size = S.st_size;
			
			read(chnl[i].fd, contents, size);
		}
		else{
			char userPath[20] = {0};
			sprintf(userPath, "logs/users/%s/%s.txt", username, path);
			
			int FD = open(userPath, O_RDWR);
			
			stat(userPath, &S);
			size = S.st_size;
			
			read(FD, contents, size);
		}
		
		write(fd, &size, sizeof(int));
		write(fd, contents, size);
		
		return 0;
	}
	
	return -1;	
}

void PM(char* msg, char* sender, char* reciever){
	
	int fd;
	char filePath[50] = {0};
	char user_dir[50] = {0};
	char filename[50] = {0};
	sprintf(filePath, "logs/users/%s/%s.txt", reciever, sender);
	sprintf(user_dir, "logs/users/%s", reciever);
	sprintf(filename, "%s.txt", sender);
	
	if (search_dir(user_dir, sender)){
	
		fd = open(filePath, O_RDWR);
		lseek(fd, 0, SEEK_END);
		write(fd, msg, strlen(msg));
	}
	else{
		fd = open(filePath, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
		write(fd, msg, strlen(msg));
	}	
	
	close(fd);
	return;
}

int viewPM(int fd, char* username, char* path){

	char user_dir[50] = {0};
	char user_file[50] = {0};
	char contents[100] = {0};
	struct stat S;

	sprintf(user_dir, "logs/user/%s", username);
	sprintf(user_file, "%s.txt", path);

	if (search_dir(user_dir, user_file) == 1){

		char userPath[20] = {0};
		sprintf(userPath, "logs/users/%s/%s.txt", username, path);
			
		int FD = open(userPath, O_RDWR);
			
		stat(userPath, &S);
		int size = S.st_size;
			
		read(FD, contents, size);

		write(fd, &size, sizeof(int));
		write(fd, contents, size);
		
		return 0;
	}

	return -1;
}