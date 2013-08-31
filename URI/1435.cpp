#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

#define BUF_SIZE 1024
char buffer[BUF_SIZE];
size_t contentSize = 1;

int *matriz;

char* readSTDIN(){
	char *content = (char*) malloc(sizeof(char) * BUF_SIZE);
	if(content == NULL)
	{
		perror("Failed to allocate content");
		exit(1);
	}

	content[0] = '\0'; 

	while(fgets(buffer, BUF_SIZE, stdin))
	{
		char *old = content;
		contentSize += strlen(buffer);
		content = (char*) realloc(content, contentSize);
		if(content == NULL)
		{
			perror("Failed to reallocate content");
			free(old);
			exit(2);
		}
		strcat(content, buffer);
	}
	return content;
}

void alocarMatriz(int tamanho){
	matriz = (int*) malloc (sizeof(int)*tamanho*tamanho);
}

void incrementarMatriz(int inicio, int tamanho, int n, int tamanhoMaisRealAinda){
	int i,j;
	if (tamanho < 1)
		return;
	for (i = inicio; i < inicio+tamanho; i++)
		for (j = inicio; j < inicio+tamanho; j++)
			matriz[i*tamanhoMaisRealAinda+j] = n;
	incrementarMatriz(++inicio,tamanho-2,++n,tamanhoMaisRealAinda);
}

void calcularMatriz(char* punch){
	int tamanho = atoi(punch);
	while (punch != NULL){
		alocarMatriz(tamanho);
		int i,j;
		int n = 1;
		incrementarMatriz(0,tamanho,n,tamanho);
		for (i = 0; i < tamanho; i++){
			for (j = 0; j < tamanho; j++){
				if (j == tamanho-1)
					printf("%3d\n",matriz[i*tamanho+j]);
				else printf("%3d ",matriz[i*tamanho+j]);
			}
		}
		punch = strtok(NULL,"\n");
		tamanho = atoi(punch);
		if (tamanho == 0) return;
		printf("\n");
	}
}

int main(){
	char *p = readSTDIN();
	char *punch = strtok(p, "\n");
	calcularMatriz(punch);
	return 0;
}
