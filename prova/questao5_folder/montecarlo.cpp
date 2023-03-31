
#include <time.h>
#include <math.h>
#include <iostream>

#define ITERATIONS 100000

int main(){

 int pi=0;
 srand((unsigned)time(NULL)); 
 for (int i=0;i<ITERATIONS; i++){
   double x,y;
   x = (rand()%2) -1;
   y = (rand()%2) -1;
   if (x*x+y*y<=1)
      pi++;
 }

 std::cout<<pi*4.0/ITERATIONS;

 return 0;

}