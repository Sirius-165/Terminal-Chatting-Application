#include "promote_demote.h"

int promote(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
    
    user* temp = list[i].list;
    while (strcmp(temp->username, username) != 0)
        temp = temp->next;
    
    if (temp->ispromoted == 1) return -1;
    
    temp->ispromoted = 1;
    
    return 0;
}

int isPromoted(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
    
    user* temp = list[i].list;
    while (strcmp(temp->username, username) != 0)
        temp = temp->next;
        
    return temp->ispromoted == 1;
}

int demote(channel list[], char* channel_name, char* username){
    
    int i = channel_search(list, channel_name);
    
    user* temp = list[i].list;
    while (strcmp(temp->username, username) != 0)
        temp = temp->next; 
    
    if (temp->ispromoted == 0) return -1;
    
    temp->ispromoted = 0;
    
    return 0;
}
