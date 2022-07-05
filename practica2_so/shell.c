#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
void imprimir();

int main(){
	char option[200];
	int fd[2];
	int pid;
	char *token;
	char *command;
	char *tokens[20];
	pipe(fd);
	while(1){
		printf("SHELL>>");
		scanf(" %199[^\n]", (char*) &option);
		if(strcmp(option,"exit") == 0){
			break;
		}
		token = strtok(option," ");
		command = (char*)malloc(sizeof(token));
		strcpy(command,token);
		if((pid = fork()) == 0){ //hijo
			close(STDOUT);
			dup(fd[1]);
			if(token!=NULL){
				int cont = 0;
				while(token!=NULL){ //obtiene los tokens del comando
					tokens[cont++] = token;
					token = strtok(NULL," ");				
				}
				tokens[cont] = NULL;
			}else{
				tokens[0] = command;
				tokens[1] = NULL; 
			}
			close(fd[0]);
			close(fd[1]);
			if(execvp(command,tokens)==-1){
				exit(1);
			}
			exit(0);
		}else{	//padre
			int status =-1;
			int stat = -1;
			if(waitpid(pid,&status,0)>0 && status == 0){
				imprimir(fd[0]);
			}else{
				printf("Error al intentar ejecutar el comando : %s\n",command);
			}
		}
		free(command);
	}
	close(STDIN);
	close(STDOUT);
	printf("Saliendo...\n");	
	return 0;
}

void imprimir(int fd){
	int bytes;
	int stat = -1;
	int p;
	if((p =fork())==0){
		close(STDIN);			
		char valor[1024];
		while((bytes = read(fd,&valor,1024))>0){
			write(STDOUT,valor,bytes);
			if(bytes < 1024){
				break;
			}
		}
		exit(0);
	}else{
		wait(NULL);
	}
}
