#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX (1 << 22)
#define ACCESS (1 << 28)

int main(void)
{
   int *v = new int[MAX], *u = new int[MAX];
   register int i, limit, k;
   double start, stop;
   FILE *fp = fopen("trace.log","w");
   int logsize = 0, logstride = 0, stride, j, size;

   for (size = 1; size <= MAX; size *= 2) {
      for (stride = 1; stride <= size; stride = stride*2) {
         for (i=0; i<size; i+=stride) {
            v[i] = (i+stride) % size;
         }
         for (i=0; i<MAX; i++) u[i] = 0;
         limit = (ACCESS >> logsize)<<logstride;
         k = 0;
         start = (double)clock()/CLOCKS_PER_SEC;
         for (i=0; i<limit; i++) {
            do {
               k = v[k];
            } while (k!=0);
         }
         stop = (double)clock()/CLOCKS_PER_SEC;
         fprintf(fp, "%d\t%d\t%lf\n", size*sizeof(v[0]), stride*sizeof(v[0]), stop-start);
         logstride++;
      }
      logsize++;
      logstride = 0;
   }
   
   fclose(fp);
   printf("Value: %d\n", u[random()%MAX]);
   return 0;
}
