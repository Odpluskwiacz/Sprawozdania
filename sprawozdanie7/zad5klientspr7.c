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
	//unikalna nazwa
	snprintf(client_fifo, BUFFER,"/tmp/server_fifo_%d", getpid());
	
	
	mkfifo(client_fifo, 0666);
	
	int server_fd = open(server_fifo, O_RDWR);
	
	//na serwer
	write(server_fd, client_fifo, strlen(client_fifo) + 1); 

	int client_fd = open(client_fifo, O_RDWR);
	char komenda[BUFFER];
	while(1){
		printf("Podaj polecenie q aby zakończyć jak quit");
		fgets(komenda, BUFFER, stdin);
		if (komenda[0] == 'q') {
			break ; // wolność
			}
		write(client_fd, komenda, strlen(komenda)); // przesyłam do wiersza
		char wiaderko[BUFFER];
		while(read(client_fd, wiaderko, BUFFER) >0){
			printf("%s", wiaderko);
			}
		}
	// kończ waść wstydu oszczędź	
	close(client_fd);
	unlink(client_fifo);
	close(server_fd);
	
	return 0;
	}
