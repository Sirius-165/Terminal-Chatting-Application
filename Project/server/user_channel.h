#ifndef USER_CHANNEL
#define USER_CHANNEL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 10

typedef struct User{
    
    char* username;
    struct User* next;
    int ispromoted;
    
}user;

typedef struct Banned{
    
    char* username;
    struct Banned* next;
    
}banned;

typedef struct Channel{
    
    char* channel_name;
    user* list;
    banned* Blist;
    int fd;
    
}channel;

/* Channel Functions */
channel* init();
int channel_search(channel list[], char* channel_name);
int isChannelEmpty(channel chnl[], char* channel_name);
void channel_insert(channel list[], char* channel_name);

/* User Functions */
void user_insert(channel list[], char* channel_name, char* username);
void user_remove(channel list[], char* channel_name, char* username);
int user_search(channel list[], char* channel_name, char* username);

/* Banned Users Functions */
void banned_insert(channel list[], char* channel_name, char* username);
int banned_search(channel list[], char* channel_name, char* username);

/* Debug Functions */
void list_channel(channel list[]);
void banned_list(channel list[], char* channel_name);
void list_users(channel list[], char* channel_name);

#endif
