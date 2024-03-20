char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurrence;

	last_occurrence = 0;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
		{
			last_occurrence = (char *)s;
		}
		s++;
	}
	if ((char) c == '\0')
	{
		return ((char *)s);
	}
	return ((char *)last_occurrence);
}

/*
#include <stdio.h>

int main () {
   const char str[] = "Hello word";
   const char ch = 'o';
   char *ret;

   ret = ft_strrchr(str, ch);

   printf("String after is \n", ret);
   
   return(0);
}*/