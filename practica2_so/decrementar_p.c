#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

struct timeval start;
struct timeval end;
int bytes;
char buffer[sizeof(float)];

float time_diff(struct timeval *start, struct timeval *end){
	return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void decrementar_num_p(int num,float time, int inicial){
	if(num>0){
		if(gettimeofday(&start,NULL)!=0){
			perror("Error en gettimeofday");
			exit(1);
		}
		if(fork() == 0){
			if(gettimeofday(&end,NULL)!=0){
				perror("Error en gettimeofday");
				exit(1);
			}
			float t_time = time_diff(&start,&end);
			time += t_time; 
			printf("Proceso pid: %d, Tiempo CS: %f,  Proceso: %d,  Numero: %d\n",getpid(), t_time, num, num);
			decrementar_num_p(num-1,time,inicial);
			exit(0);
		}else{
			wait(NULL);
		}
	}else{
		float avrg = time/inicial; 
		printf("\nTiempo transcurrido de CS promedio: %f\n",avrg);
	}
}

void decrementar_num(int num){
	decrementar_num_p(num,0.0,num);
}


int main(int argc, char *argv[]){
	if(argc!=2){
		perror("Modo de uso ./decremento_p [num]\n  num = Numero a ingresar\n funcion: gettimeofday");
		return 0;
	}
	int num = atoi(argv[1]);
	decrementar_num(num);
	return 0;
}
