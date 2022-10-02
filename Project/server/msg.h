#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "user_channel.h"

void msg(char* username, channel chnl[], char* channel_name, char* msg);
int viewMsg(int fd, char* username, char* path, channel chnl[]);
void PM(char* msg, char* sender, char* reciever);
int viewPM(int fd, char* username, char* path);
