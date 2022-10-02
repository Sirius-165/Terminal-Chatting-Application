#ifndef PROMOTE_DEMOTE
#define PROMOTE_DEMOTE

#include "user_channel.h"
#include <string.h>

int promote(channel list[], char* channel_name, char* username);
int isPromoted(channel list[], char* channel_name, char* username);
int demote(channel list[], char* channel_name, char* username);

#endif
