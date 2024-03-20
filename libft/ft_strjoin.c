#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joining;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joining = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joining)
		return (NULL);
	ft_strlcpy(joining, s1, s1_len + 1);
	ft_strlcpy((joining + s1_len), s2, s2_len + 1);
	return (joining);
}

/*
#include <stdio.h>
int main ()
{
	char *s1 = "hello";
	char *s2 = "word";

	char res = ft_strjoin(s1,s2);
	printf("the string res : ", res);
}*/