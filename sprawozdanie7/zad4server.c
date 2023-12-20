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

    // Utwórz ogólnodostępną kolejkę FIFO dla serwera
	mkfifo(server_fifo, 0666);

    printf("Serwer: Oczekiwanie na klienta...\n");

    int server_fd = open(server_fifo, O_RDONLY);
 
    char client_fifo[BUFFER];

    while (1) {
        // Czekaj na     zgłoszenie klienta w nieskończoność
        if (read(server_fd, client_fifo, BUFFER) > 0) {
            // Otwórz kolejkę klienta
            int client_fd = open(client_fifo, O_WRONLY);

            // Wykonaj polecenie ls i przekieruj wynik do kolejki klienta
            FILE *ls_output = popen("ls", "r");
            char buffer[BUFFER];
			while (fgets(buffer, MAX_BUF, ls_output) != NULL) {
                write(client_fd, buffer, strlen(buffer));
            }
            pclose(ls_output);

            // posptzątaj
            close(client_fd);
        }
    }

    // posprzątaj
    close(server_fd);
    unlink(server_fifo);

    return 0;
}
