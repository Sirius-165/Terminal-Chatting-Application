#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "str_parse.h"
#include "help.h"
#include "ERRMSG.h"
#define TRUE 1
#define MAXLINE 100
typedef struct sockaddr SA;
