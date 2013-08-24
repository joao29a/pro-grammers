#include <stdio.h>
#include <stdlib.h>
#include <cstring>

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

long long int caralha5(long long int n, long long int m){
	//printf("%lld %lld\n", n, m);
	if(m==0){
		return n + 1;
	}
	if(m == 1){
		return n + 2;
	}
	if(m == 2) {
		return 2*n+3;
	}
	int i;
	long long int x = 1;
	for(i=0; i<=n; i++) {
		x = caralha5(x, m-1);
		if(x < 0) break; else printf("%lld\n", x);
	}
	return x;
/*
	if(m == 0){

		return ++n; // DOUBLE CHECKED

	}else if(n==0 && m >= 1){

		return caralha5(1,m-1); // DOUBLE CHECKED

	}else if(n > 0 && m > 0){

		return caralha5(caralha5(n-1,m),m-1); 
		// BRAIN FUCK // IMPOSIBLU DE SER CHECADO
	}
*/
}

int main(){
	char *p = readSTDIN();
	char *punch = strtok(p, "\n");
	int i = 0;
	int size = atoi(punch);
	punch = strtok(NULL, "\n");
	while(punch != NULL && i != size) {
		int n, m;
		sscanf(punch,"%d %d",&n,&m);
		i++;   
		printf("%lld\n", caralha5(n,m));
		punch = strtok(NULL, "\n");
	}
	return 0;
}
