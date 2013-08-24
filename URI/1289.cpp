#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

#define BUF_SIZE 102400
char buffer[BUF_SIZE];
size_t contentSize = 1;

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

float probabilidade(int n, float prob, int j){
	int i, exp;
	float result = 0;
	for (i = 0; i < 500; i++){
		exp = n*i+j-1;
		result += pow(1-prob,exp)*prob;
	}
	return result;
}

int main(){
	char *p = readSTDIN();
	char *punch = strtok(p, "\n");
	punch = strtok(NULL,"\n");
	int i, j;
	float prob;
	while(punch != NULL){
		int n;
		sscanf(punch,"%d %f %d",&i,&prob,&j);
		printf("%.4f\n",probabilidade(i,prob,j));
		punch = strtok(NULL, "\n");
	}
	return 0;
}
