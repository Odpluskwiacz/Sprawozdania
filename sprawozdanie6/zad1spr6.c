#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
pid_t pidOjciec = getpid();
printf("rodzic PID %d\n", pidOjciec);

pid_t piddziecko = fork();

	if(piddziecko == 0){
		printf("Pierwsze dziecko PID %d PPID %d\n", getpid() , getppid());
		
	pid_t pidwnuczek = fork();
		if(pidwnuczek == 0){
			printf("wnuczek PID %d PPID %d\n", getpid() , getppid());
			}
		wait(NULL);
	} else if (piddziecko != 0){
			pid_t piddziecko2 = fork();
	
		if(piddziecko2 == 0) {
			printf ("Drugie dzieckoPID %d PPID %d\n", getpid() , getppid()); 
			}
		pid_t pidwnuczek2 = fork();
		if (pidwnuczek2 == 0){
			printf("Drugi wniuk PID %d PIDD %d\n", getpid() , getppid());
		} 
		wait(NULL);
	}
	wait(NULL);
    return 0;
}
//					|
//				   =|------| =
//					|      |
//					|--|   |--|
//					=  =   x  X
//

