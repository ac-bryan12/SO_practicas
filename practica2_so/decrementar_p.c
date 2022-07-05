#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

#define STDIN 0
#define STDOUT 1

struct timeval start;
struct timeval end;
struct timeval end_parent;
int bytes;
char buffer[sizeof(float)];

float time_diff(struct timeval *start, struct timeval *end){
	return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void decrementar_num(int num,float time){
	int c_num = num-1;
	pid_t pid;
	if(c_num>0){
		if(gettimeofday(&start,NULL)!=0){
			perror("Error en gettimeofday");
			exit(1);
		}
		if((pid=fork()) == 0){
			if(gettimeofday(&end,NULL)!=0){
				perror("Error en gettimeofday");
				exit(1);
			}
			float t_time = time_diff(&start,&end);
			time += t_time; 
			printf("Proceso pid: %d, Tiempo CS: %f,  Proceso: %d,  Numero: %d\n",getpid(), t_time, c_num, c_num);
			decrementar_num(c_num,time);
		}else{
			wait(NULL);
		}
	}else{
		printf("Tiempo trasncurrido de Context Swicth: %f\n",time);
	}
}

int main(int argc, char *argv[]){
	if(argc!=2){
		perror("Modo de uso ./decremento_p [num]\n  num = Numero a ingresar");
		return 0;
	}
	int num = atoi(argv[1]);
	float tiempo_ini = 0.0;
	decrementar_num(num,tiempo_ini);
	return 0;
}
