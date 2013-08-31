// http://kknd.wordpress.com/2011/08/23/cadeias-de-markov-exemplo-pratico/
//
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


typedef struct
{
   double m[21][21];
} M21x21;

int _max;

//Multiplica matrizes 20x20: a*b = c
// TODO: trocar por Strassen
M21x21 m_mul(M21x21 a, M21x21 b, int tam = _max + 1)
{
   M21x21 c;
   memset(c.m, 0, sizeof(c.m));
   for (int i = 0; i < tam; i++)
      for (int j = 0; j < tam; j++)
         for (int k = 0; k < tam; k++)
            c.m[i][j] += a.m[i][k] * b.m[k][j];
   return c;
}

// Retorna a^n = b.
// Não precisa tratar n=0.
M21x21 m_exp(M21x21 a, int n)
{
   M21x21 b;
   if (n == 1)
      return a;
   else if (n % 2 == 0)
   {
      b = m_exp(a, n / 2);
      b = m_mul(b, b);
      return b;
   }
   else
   {
      b = m_exp(a, (n - 1) / 2);
      b = m_mul(b, b);
      return (m_mul(b, a));
   }
}

int main(){
   char *p = readSTDIN();
   char *punch = strtok(p, "\n");
   while(punch != NULL) {
      M21x21 mt;
      int ev1;
      int ev2;
      int at;
      int d;
      sscanf(punch,"%d %d %d %d",&ev1,&ev2,&at,&d);
      if(ev1==0 & ev2==0 & at==0 & d==0){
         return 0;
      }

      ev1 = 1 + (ev1 - 1) / d; // ceil
      ev2 = 1 + (ev2 - 1) / d; // ceil
      d = 1;
      double pg = at / 6.0; // probabilidade de ganho
      double pp = 1 - pg; // probabilidade de perda
      _max = ev1 + ev2; // Energia vital final do ganhador
      memset(mt.m, 0, sizeof(mt.m));
      mt.m[0][0] = 1.0; mt.m[_max][_max] = 1.0;
      for (int i = 1; i < _max; i++)
         mt.m[i][i - 1] = pp, mt.m[i][i + 1] = pg;
      mt = m_exp(mt, 1000);

      printf("%0.1f\n", mt.m[ev1][_max]*100);
      punch = strtok(NULL, "\n");
   }
   return 0;
}
