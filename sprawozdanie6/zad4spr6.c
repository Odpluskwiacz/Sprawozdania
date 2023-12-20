#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int zombie;	 //pytaine do zadania  czym się różni int od pid_t 
	printf("jestem czlowiekiem\n");
	for(int i = 0; i < 3; i++) { // 3 zombiaki + były czlowiek
		zombie = fork();	
	}
    
    if (zombie == 0){
    sleep(4);       
    printf("moozg\n");
    }

 
return 0;
}
//  |jestem człowiekiem
//	| 
//	|--|--|--|
//	|  |  |  |
//  Mooozg
//
