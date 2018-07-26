#include <stdio.h>
#include <string.h>

int main ()
{
  const char* NATO[26] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"};

   char t0 = 'T';
   char a1 = 'a';
   char n2 = 'n';
   char g3 = 'g';
   char o4 = 'a';

   char str1[5];


   str1[0] = t0;
   str1[1] = a1;
   str1[2] = n2;
   str1[3] = g3;
   str1[4] = o4;
   int ret;

   printf("->%s<-\n", str1);
   printf("->%s<-\n", NATO[19]);

   ret = strcmp(str1, NATO[19]);


   if(ret < 0)
   {
      printf("str1 is less than str2\n");
   }
   else if(ret > 0)
   {
      printf("str2 is less than str1\n");
   }
   else
   {
      printf("str1 is equal to str2\n");
   }

   return(0);
}
