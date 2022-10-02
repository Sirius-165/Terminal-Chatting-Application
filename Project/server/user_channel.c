#include "user_channel.h"

int curr = 0;

channel* init(){
    
    channel* Channel_list = (channel*)malloc(sizeof(channel) * MAX);
    int i;
    for (i = 0; i < MAX; i++){
        
        Channel_list[i].list = NULL;
        Channel_list[i].Blist = NULL;
        Channel_list[i].channel_name = (char*)calloc(30, sizeof(char));
        Channel_list[i].fd = -1;
    }
        
    return Channel_list;
}

int channel_search(channel list[], char* channel_name){
    
    int i = 0;
    for (; i < curr; i++){
        
        if (strcmp(list[i].channel_name, channel_name) == 0)
            return i;
    }
    return -1;
}

int isChannelEmpty(channel chnl[], char* channel_name){

    int i;
    if ((i = channel_search(chnl, channel_name)) == -1) return 0;

    else return chnl[i].list == NULL;
}

void channel_insert(channel list[], char* channel_name){
    
    if (curr == MAX){
        printf("can't exceed max\n");
        return;
    }
    
    strncpy(list[curr].channel_name, channel_name, strlen(channel_name));
    
    char path[20] = {0};
    sprintf(path, "logs/channels/%s.txt", channel_name);
    list[curr].fd = open(path, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    
    curr++;
}

void user_insert(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
        
    user* newUser = (user*)malloc(sizeof(user));
    
    newUser->username = (char*)calloc(30, sizeof(char));
    strncpy(newUser->username, username, strlen(username));
    
    make_user_dir(username);
    
    newUser->next = NULL;
    
    if (list[i].list == NULL){
        
        list[i].list = newUser;
        list[i].list->ispromoted = 1;
        return;
    }
    
    user* temp = list[i].list;
    while (temp->next != NULL)
        temp = temp->next;
    
    temp->next = newUser;
    newUser->ispromoted = 0;
}

void user_remove(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
    
    if (strcmp(list[i].list->username, username) == 0){
        
        if (list[i].list->next == NULL)
            list[i].list = NULL;
        
        else{
            
            user* temp = list[i].list;
            list[i].list = list[i].list->next;
            free(temp);
        }
        
        return;
    }
    
    user* temp = list[i].list;
    while (temp != NULL){
        
        if (strcmp(temp->next->username, username) == 0){
            
            user* temp2 = temp->next;
            temp->next = (temp->next)->next;
            
            free(temp2);
            
            return;
        }
        
        temp = temp->next;
    }
}

int user_search(channel list[], char* channel_name, char* username){
    
    int i;
    if ( (i= channel_search(list, channel_name)) == -1) return -1;
    
    user* temp = list[i].list;
    while (temp != NULL){
        
        if (strcmp(temp->username, username) == 0)
            return 1;
        
        temp = temp->next;
    }
    
    return 0;
}

void banned_insert(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
    user_remove(list, channel_name, username);
    
    banned* newUser = (banned*)malloc(sizeof(banned));
    
    newUser->username = (char*)calloc(30, sizeof(char));
    strncpy(newUser->username, username, strlen(username));
    
    newUser->next = NULL;
    
    if (list[i].Blist == NULL){
        
        list[i].Blist = (user*)newUser;
        return;
    }
    
    banned* temp = list[i].Blist;
    while (temp->next != NULL)
        temp = temp->next;
    
    temp->next = newUser;
    
}

//int banned_remove(channel list[], int name, int key);
int banned_search(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
    
    banned* temp = list[i].Blist;
    while (temp != NULL){
        
        if (strcmp(temp->username, username) == 0)
            return 1;
        
        temp = temp->next;
    }
    
    return 0;
}

/* Debugging functions */
void list_channel(channel list[]){
    
    int i;
    printf("Listing channels:\n");
    for (i = 0; i < curr; i++)
        printf("%d - %s\n", i + 1, list[i].channel_name);
        
    printf("\n");
}

void list_users(channel list[], char* channel_name){
    
    int i = channel_search(list, channel_name);
    int num = 1;
    
    user* temp = list[i].list;
    while (temp != NULL){
        
        if (isPromoted(list, channel_name, temp->username) == 1)
            printf("%d - @%s\n", num, temp->username);
        else
            printf("%d - %s\n", num, temp->username);
            
        num++;
        temp = temp->next;
        
    }
     printf("\n");
}

void banned_list(channel list[], char* channel_name){
    
    int i = channel_search(list, channel_name);
    int num = 1;
    
    user* temp = list[i].Blist;
    while (temp != NULL){
        
        printf("%d - %s\n", num, temp->username);
        
        num++;
        temp = temp->next;
    }
     printf("\n");
}
