#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

#define BUF_SIZE 102400000
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

int toDecimal(char *bin) {
	int dec = 0;
	while(*bin != '\0') {
		dec = dec << 1;
		if(*bin == '1') {
			dec = dec | 1;
		}
		bin++;	
	}
	return dec;
}

int calcMMC(int a, int b) {
	int min = a < b ? a: b, max = a > b ? a: b, med = sqrt(max), i;
	if( a == b ) return 1;
	for(i=2; i<=med && i<=min; i++) {
		if(a%i == 0 && b%i == 0) return 1;
	}
	return 0;
}

int main(){
	char *p = readSTDIN(), *punch = strtok(p, "\n");
	int i = 1, num1, num2, tam = atoi(punch);
	punch = strtok(NULL, "\n");
	while(tam >= i) {
		num1 = toDecimal(punch);
		punch = strtok(NULL, "\n");
		num2 = toDecimal(punch);
		if(calcMMC(num1, num2) == 1) {
			printf("Pair #%d: All you need is love!\n", i);
		} else {
			printf("Pair #%d: Love is not all you need!\n", i);
		}
		i++;
		punch = strtok(NULL, "\n");
	}
	
}
