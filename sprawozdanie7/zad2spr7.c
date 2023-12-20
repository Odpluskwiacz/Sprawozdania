#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//Napisz program który tworzy trzy procesy, z których dwa zapisują do potoku, a trzeci odczytuje
//z niego i drukuje otrzymane komunikaty.


int main(){
    pid_t proces1, proces2, proces3;	
	//int pipe(int pip0odczyt_pip1zapis[2]);

	int pip0odczyt_pip1zapis[2];
	if (pipe(pip0odczyt_pip1zapis) == -1){
		perror("pajper"); //podręcznikowa wersja
		exit(1);
		}
	
	proces1 = fork();
	proces2 = fork();
	proces3 = fork();
	
	
	if(proces1 == 0){
		close(pip0odczyt_pip1zapis[0]); //zamykam odczyt zostaje zapis
		char dostales_mesydz[] = "Witeam jam proces 1\n";
		write(pip0odczyt_pip1zapis[1],dostales_mesydz,sizeof(dostales_mesydz));
		close(pip0odczyt_pip1zapis[1]);
		exit(0);
		}
		
	if(proces2 == 0){
		close(pip0odczyt_pip1zapis[0]); //dokładnie
		char dostales_mesydz[] = "zhakuje ci windowsa >:[ \n";
		write(pip0odczyt_pip1zapis[1],dostales_mesydz,sizeof(dostales_mesydz));
		close(pip0odczyt_pip1zapis[1]);
		exit(0);
		}
		
	if(proces3 == 0){
		close(pip0odczyt_pip1zapis[1]);
		char buffer[100]; // koszyk :>
		read(pip0odczyt_pip1zapis[0], buffer,sizeof(buffer));
		close(pip0odczyt_pip1zapis[0]);
		exit(0);
		}


	//zamykamy
	waitpid(proces1, NULL, 0);
    waitpid(proces2, NULL, 0);
    waitpid(proces3, NULL, 0);
return 0;
	}










