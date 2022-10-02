#ifndef DIR_FILE
#define DIR_FILE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "user_channel.h"

int search_dir(char* dir, char* key);
void make_user_dir(char* username);
void close_all(channel chnl[]);
void send_file(int connfd, char* filename);

#endif
