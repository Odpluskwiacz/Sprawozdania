#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER 1024

int main() {
    const char *server_fifo = "/tmp/server_fifo";

	char client_fifo[BUFFER];
	mkfifo(client_fifo, 0666);
	
	
	int server_fd = open(server_fifo, 0_WRONLY);
	write(server_fd, client_fifo, 0_RDONLY);

	//odbieranie
	char wiaderko[BUFFER];
	while(read(client_fd, wiaderko, BUFFER)>0){
			printf("%s", wiaderko);
		}

	close(client_fd);
	unlink(client_fifo);
	close(server_fd);



return 0;
}
