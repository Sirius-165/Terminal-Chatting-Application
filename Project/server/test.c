#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int search_dir(char* dir, char* key){
	
	DIR* streamp;
	struct dirent* dirp;
	
	streamp = opendir(dir);
	
	while ((dirp = readdir(streamp)) != NULL){
		printf("%s   %s\n", key, dirp->d_name);
		if (strcmp(key, dirp->d_name) == 0){
			
			closedir(streamp);
			return 1;
		}
	}
		
	closedir(streamp);
	return 0;
}

int main(){
	
	if (search_dir("logs/users/sara", "ghazi.txt")) printf("TRUE\n");
	else printf("False!!\n");

	return 0;
}
