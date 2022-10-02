#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include "dir_file.h"
#include "str_parse.h"
#include "user_channel.h"
#include "promote_demote.h"
#include "msg.h"
#include "list.h"
#define LISTENQ 10
#define TRUE 1
#define MAXLINE 100
typedef struct sockaddr SA;
