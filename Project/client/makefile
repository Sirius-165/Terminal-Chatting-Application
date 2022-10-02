all: client

client: client.o str_parse.o help.o ERRMSG.o
	gcc -g -o client client.o str_parse.o help.o ERRMSG.o
	
client.o: client.c
	gcc -g -c client.c

str_parse.o: str_parse.c
	gcc -g -c str_parse.c

help.o: help.c
	gcc -g -c help.c

ERRMSG.o: ERRMSG.c
	gcc -g -c ERRMSG.c
