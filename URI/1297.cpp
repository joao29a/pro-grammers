#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <float.h>
#include <cmath>

#define BUF_SIZE 10240
char *buffer;

double doFunction(int* p,int* q, int k,double x){
    printf("aki\n");
    double pRes =0;
    double qRes =0;
    for(int i = 0; i < k; i++){
        pRes += p[i]*pow(x,i);
        printf("%d\n%f\n",p[i],pRes);
    }
    for(int i = 0; i < k; i++){
        qRes += q[i]*pow(x,i);
    }
    if(qRes == 0)
        return DBL_MAX;
    else
        return (pRes/qRes);
}

void loopLer(int k, int** vet){
    /*for(int i = 0; i < k; i++){
      sscanf(buffer,"%d %s\n",&(*vet[i]),buffer);
      printf("%d %s\n",(*vet[i]),buffer);
      }*/
    //char *temp = (char*)malloc(sizeof(char)*BUF_SIZE);
    //strcpy(buffer,temp);
    char * p = std::strtok (buffer," ");
    int i = 0;
    while (p!=0)
    {
        if (i > k) return;
        sscanf(p,"%[0-9]",p);
        (*vet[i]) = atoi(p);
        printf("%d\n",(*vet[i]));
        p = strtok(NULL," ");
        i++;
    }
    printf("aki\n");
}

int main(){
    int cont = 1;
    int w,d,a,k;
    int *p1,*p2;
    int *q1,*q2;
    buffer = (char*)malloc(sizeof(char)*BUF_SIZE);
    int size;
    while (fgets(buffer,BUF_SIZE,stdin) != NULL){
        if (cont == 1){
            sscanf(buffer,"%d %d %d %d",&w,&d,&a,&k);
            k = k + 1;
            p1 = (int*)malloc(sizeof(int)*k);
            q1 = (int*)malloc(sizeof(int)*k);
            p2 = (int*)malloc(sizeof(int)*k);
            q2 = (int*)malloc(sizeof(int)*k);
        }
        else if (cont == 2){
            loopLer(k,&p1);
        }
        else if (cont == 3){
            loopLer(k,&q1);
        }
        else if (cont == 4){
            loopLer(k,&p2);
        }
        else if (cont == 5){
            loopLer(k,&q2);
            cont = 0;
            printf("%f\n",doFunction(p1,q1,k,2));
            free(p1);
            free(p2);
            free(q1);
            free(q2);
        }
        //buffer[0]='\0';
        cont++;
    }
    return 0;
}
