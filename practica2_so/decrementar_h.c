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
struct timeval end;

float time_diff(struct timeval *start, struct timeval *end){
	return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void *decrementar(void *args){
	sem_wait(&sem);
	num--;
	gettimeofday(&end,NULL);
	float time_h = time_diff(&start,&end);
	t_time += time_h;
	sem_post(&sem);
	printf("Hilo %ld,  Tiempo CS hilo: %f   Numero: %d\n",pthread_self(),time_h,num);
	return (void*)0;
}

int main(int argc,char *argv[]){
	if(argc!=2){
		perror("Modo de uso ./decremento_h num\n  num: Numero entero\n  funcion: gettimeofday");
		return 0;
	}
	int c_num = atoi(argv[1]);
	num = atoi(argv[1]);
	sem_init(&sem,0,1);
	hilos = malloc(c_num * sizeof(pthread_t));
	for(int i = 0; i<c_num-1;i++){
		gettimeofday(&start,NULL);
		pthread_create(&hilos[i],NULL,decrementar,NULL);
	}
	for(int i = 0;i<c_num-1;i++){
		pthread_join(hilos[i],NULL);
	}
	float avrg = t_time/c_num;
	printf("\nTiempo transcurrido de CS promedio: %f\n",avrg);
	
	
}




