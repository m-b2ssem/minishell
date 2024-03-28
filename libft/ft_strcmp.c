#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *(unsigned char *)s1 == *(unsigned char *)s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*#include <stdio.h>

int main () {
   char str1[15];
   char str2[15];
   int ret;

   strcpy(str1, "abcdef");
   strcpy(str2, "ABCDEF");

   ret = ft_strcmp(str1, str2,);

   if(ret < 0) {
      printf("str1 is less than str2");
   } else if(ret > 0) {
      printf("str2 is less than str1");
   } else {
      printf("str1 is equal to str2");
   }
   
   return(0);

	//if Return value < 0 then it indicates str1 is less than str2.
	//if Return value > 0 then it indicates str2 is less than str1.
	//if Return value = 0 then it indicates str1 is equal to str2.
}*/