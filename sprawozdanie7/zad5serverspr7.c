//Zmodyfikować poprzedni program, tak, by kolejka utworzona przez klienta była
//dwukierunkowa, klient publiczną kolejką powinien przesyłać nazwę stworzonej przez siebie
//kolejki. Dalsza wymiana komunikatów powinna odbywać się poprzez kolejkę stworzoną przez
//klienta. Klient kolejką tą powinien wysyłać polecenia, zadaniem serwera jest wykonywanie tych
//poleceń i odsyłanie wyników.
//server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER 1024

int main(){
		const char *server_fifo = "/tmp/server_fifo";
		char client_fifo[BUFFER];
		mkfifo(client_fifo, 0666);
	
		int server_fd = open(server_fifo, O_RDWR);

	
		while (1) {
			if(read(server_fd, client_fifo, BUFFER)>0){
			int client_fd = open(client_fifo, O_RDWR);
			char komenda[BUFFER];
			if(read(client_fd,komenda,BUFFER)>0){
			FILE *cmd_output = popen(komenda, "r"); //to to
			char wiaderko[BUFFER];
			while (fgets(wiaderko, BUFFER, cmd_output) != NULL){
				write(client_fd, wiaderko, strlen(wiaderko));
				}
				pclose(cmd_output);
				}
			}
		}
	close(server_fd);
	unlink(server_fifo);
	
	return 0;
	}
