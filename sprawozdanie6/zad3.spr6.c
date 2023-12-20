#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

// wypluwa proces od 0 do 30 a każdy z nich ponumerowany jest swoją PID mam problem każdy proces jest "wypluwany o + więcej niż powinien" popraw z świeżą głową


void lista(int ilosc, int x){
	for(int i =0; i< ilosc; i++){
		printf("      ");
		printf("Proces %d\n", x);
	}
	
}

void rekurencja(int od, int doo) { // nie wolno "do"
    if (od >= doo) {
        return;
    }

    pid_t pidzadanie = fork();

    if (pidzadanie == 0) {
        lista(od + 1, getpid());
        rekurencja(od + 1, doo);
        _exit(0);  
    } else if (pidzadanie > 0) {
        wait(NULL); 
    }
}


int main () {
srand(time(NULL));
int r =  rand() % 30;
	printf("------Początek Listy------\n");
	rekurencja(1,r);
	printf("------Koniec Listy------\n");
return 0;	
}
//coraz mniej lubie c; bez pomocy się nie dało
