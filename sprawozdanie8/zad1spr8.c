
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

//https://pl.wikipedia.org/wiki/Problem_producenta_i_konsumenta
//https://pl.wikipedia.org/wiki/Semafor_(informatyka)
//gcc -Wall -o "%e" "%f" -pthread

int buffer[BUFFER_SIZE];
int in = 0, out = 0; // "w" "z" nie czytelne
int cyklp = 0, cyklc =0;

sem_t mutex, empty,full;

void *producent(void *arg){
	int jablko = 1;
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in] = jablko;
		printf("dodaje %d jablek dla miejsca %d\n",jablko,in);
		in = (in + 1) % BUFFER_SIZE; //zwiększa aktualne in nie przekraczając 5
		
		sem_post(&mutex);
		sem_post(&full);
		
		jablko++;
		
		sleep(1); // opóźnienie
		
		cyklp++;
		
		if(cyklp >= 10){
			printf("producent zakończył prace\n");
			pthread_exit(NULL);
			}
		}
	}
void *consument(void *arg){
	int jablko;
	
	while(1) {
		sem_wait(&full);
		sem_wait(&mutex);
		
		jablko = buffer[out];
		printf("pobieram %d jablek dla miejsca %d\n", jablko, out);
		out = (out +1) % BUFFER_SIZE;
		
		sem_post(&mutex);
		sem_post(&empty);
		
		sleep(2); // śpij dłużej
		
		cyklc++;
		
		if(cyklc >= 10){
			printf("consument zakończył prace\n");
			pthread_exit(NULL);
			}
		}
	}


int main(){
	pthread_t producentT , consumentT;//T jak thread
	sem_init(&mutex, 0,1);
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full,0,0);
	
	pthread_create(&producentT, NULL, producent,NULL);
	pthread_create(&consumentT, NULL, consument,NULL);
	
	
	pthread_join(producentT, NULL);
	pthread_join(consumentT, NULL);
	
	//porządki 
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	
return 0;
	}
