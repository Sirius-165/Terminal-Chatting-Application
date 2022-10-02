all: server

server: dir_file.o promote_demote.o str_parse.o user_channel.o server.o msg.o list.o
	gcc -g -o server dir_file.o promote_demote.o str_parse.o user_channel.o server.o msg.o list.o -lpthread
	
dir_file.o: dir_file.c
	gcc -g -c dir_file.c

promote_demote.o: promote_demote.c
	gcc -g -c promote_demote.c

str_parse.o: str_parse.c
	gcc -g -c str_parse.c

user_channel.o: user_channel.c
	gcc -g -c user_channel.c

server.o: server.c
	gcc -g -c server.c

msg.o: msg.c
	gcc -g -c msg.c

list.o: list.c
	gcc -g -c list.c