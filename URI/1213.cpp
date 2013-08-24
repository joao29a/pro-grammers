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

int ones(int n){
   int res = 1;
   int i = 1;
   while(res != 0){
      res = ((((res%n) * (10%n) % n) % n )+ (1 % n))%n;
      i++;
   }
   return i;
}

int main(){
	char *p = readSTDIN();
	char *punch = strtok(p, "\n");
	while(punch != NULL) {
                int n;
		sscanf(punch,"%d",&n);
		printf("%d\n",ones(n));
	        punch = strtok(NULL, "\n");
	}
	return 0;
}
