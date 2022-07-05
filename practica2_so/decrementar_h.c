#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>

int num;
sem_t sem;
float t_time;
pthread_t *hilos;
struct timeval start;
struct timveal end;

void *decrementar(void *args){
	sem_wait(&sem);
	num--;
	printf("Hilo %d, Numero: %d\n",num,num);
	sem_post(&sem);
}

int main(int argc,char argv[]){
	if(argc!=2){
		perror("Modo de uso ./decremento_p num\n  num: Numero entero");
		return 0;
	}
	int c_num = atoi(argv[1]);
	sem_init(&sem,0,1);
	while(c_num){
	}
}




