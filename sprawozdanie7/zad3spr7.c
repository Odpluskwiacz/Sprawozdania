#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//Napisz programy realizujące następujące potoki:
//ls|wc
//finger | cut -d' ' -f1
//ls -l | grep ^d | more a)
//ps –ef| tr -s ' ' :| cut -d: -f1 |sort| uniq -c |sort n
//cat /etc/group | head -5 > grupy.txt
int main(int argc, char* argv[]){
	
	pid_t proces1, proces2, proces3;// proces4, proces5;
	pid_t pidgrep;
	int pip0odczyt_pip1zapis[2];
	int pipsupport[2];
	pipe(pipsupport);
	
	if (pipe(pip0odczyt_pip1zapis) == -1){
		perror("pajper"); //podręcznikowa wersja
		exit(1);
		}
	
	proces1 = fork();
	
	switch(proces1 = fork()){
		case 0:
			close(pip0odczyt_pip1zapis[0]);
			dup2(pip0odczyt_pip1zapis[1],1);
			execvp("ls" , argv);
			perror("ls");
			exit(1);									//system("ls -l"); chcesz tego użyćdu
		 default: {
			 close(pip0odczyt_pip1zapis[1]);
			 dup2(pip0odczyt_pip1zapis[0], 0);
			 execlp("wc", "wc", NULL); // musi być null bo inaczej źle
			 perror("wc");
			 exit(1);
			 } 
		} 
	waitpid(proces1, NULL, 0); //zamykamy
	
	
	switch(proces2 = fork()){
		case 0:
			close(pip0odczyt_pip1zapis[0]);
			dup2(pip0odczyt_pip1zapis[1],1);
			execvp("finger", argv);
			perror("finger");
			exit(1);
		default: {
			close(pip0odczyt_pip1zapis[1]); //zamykasz zapis
			dup2(pip0odczyt_pip1zapis[0],0);  //formatujesz odczyt na wersję LINUX
			execlp("cut", "cut", "-d' '", "-f1" , NULL);
			perror("cut");
			exit(1);
			}
		}
	waitpid(proces2, NULL, 0); //kończymy
	
	
	
	
	
	switch(proces3 = fork()){
		case 0:
			close(pipsupport[1]);
			close(pipsupport[0]);
			close(pip0odczyt_pip1zapis[0]);
			dup2(pip0odczyt_pip1zapis[1],1);
			execlp("ls", "ls", "-l", NULL); //cvp ma problem z zbyt wieloma argumentami w tym "-l"
			perror("cut");
			exit(1);
		default:{
			switch(pidgrep = fork()){
					case 0:
						close(pip0odczyt_pip1zapis[1]);
						close(pipsupport[0]);
						dup2(pip0odczyt_pip1zapis[0], 0);
						dup2(pipsupport[1], 1);
						execlp("grep", "grep", "-d", NULL);
						perror("grep");
						exit(1);
					default:{
						close(pip0odczyt_pip1zapis[0]);
						close(pipsupport[1]);
						dup2(pip0odczyt_pip1zapis[1], 1);
						dup2(pipsupport[0], 0);
						execlp("more", "more", NULL);
						perror("more");
						exit(1);
						}
				}
			}
		}
	waitpid(proces3, NULL, 0);
	waitpid(pidgrep, NULL, 0);
return 0;	// koniec części a)
}
