#include "dir_file.h"

int search_dir(char* dir, char* key){
	
	DIR* streamp;
	struct dirent* dirp;
	
	streamp = opendir(dir);
	
	while ((dirp = readdir(streamp)) != NULL){
	
		if (strcmp(key, dirp->d_name) == 0){
			
			closedir(streamp);
			return 1;
		}
	}
		
	closedir(streamp);
	return 0;
}

void make_user_dir(char* username){
	
	char path[20] = {0};
	
	sprintf(path, "logs/users/%s", username);
	
	mkdir(path, 0777);
}

void close_all(channel chnl[]){
	
	int i = 0;
	
	while (chnl[i].fd != -1){
	
		close(chnl[i].fd);
		i++;
	}
}

void send_file(int connfd, char* filename){
	
	int fd = open(filename, O_RDWR);
	struct stat S;
	int size;
	
	stat(filename, &S);
	size = S.st_size;
	
	char* content = (char*)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	
	if (fork() == 0){

		read(fd, content, size);
		
		write(connfd, filename, strlen(filename));
		write(connfd, &size, sizeof(int));
		write(connfd, content, size);
		exit(0);
	}
	
	close(fd);
}
