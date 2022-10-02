#include "list.h"

void list(channel chnl[], char* channel_name, int connfd){
	
	int i = channel_search(chnl, channel_name);
	int num = 1;
	char userList[200] = {0};
	int size;

	user* temp = chnl[i].list;

	while (temp != NULL){

		if (temp->ispromoted == 1)
			sprintf(userList, "%s%d - @%s\n", userList,num, temp->username);
		else
			sprintf(userList, "%s%d - %s\n", userList,num, temp->username);

		temp = temp->next;
		num++;
	}

	size = strlen(userList);
	write(connfd, &size, sizeof(int));
	write(connfd, userList, size);
}