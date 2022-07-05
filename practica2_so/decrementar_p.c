#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

#define STDIN 0
#define STDOUT 1

struct timeval start;
struct timeval end;
int fd[2];

float time_diff(struct timeval *start, struct timeval *end){
	return (end->tv_ec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void decrementar(int num){
	int c_num = num-1;
	if(num<0){
		gettimeofday(&start, NULL);
		int pid = fork();
		if(pid == 0){
			close(fd[0]);
			gettimeofday(&end,NULL);
			float c_time = time_diff(&start,end);
			printf("Proceso pid: %d, ");
			close(fd[1]);
		}else{
			wait(NULL);
		}
	}else{
		printf("Tiempo CS transcurrido : %f\n", elapsed_time);
	}
}

int main(int argc, char *argv[]){
	if(argc!=2){
		perror("Modo de uso ./decremento_p [num]\n  *num = Numero a ingresar");
		return 0;
	}
	int num = atoi(argv[1]);
	if(pipe(fd) == -1){
		perror("Fallo al crear el pipe");
		return -1;
	}
	decrementar(num);
	return 0;
}
