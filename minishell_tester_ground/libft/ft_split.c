#include "libft.h"

static int	numwords(char const *s, char c)
{
	int	cur;
	int	word_num;

	cur = 0;
	word_num = 0;
	while (s[cur] != 0)
	{
		if (s[cur] != c && (s[cur + 1] == c || s[cur + 1] == 0))
			word_num++;
		cur++;
	}
	return (word_num);
}

static int	split_words(char **result, char const *s, char c, int word)
{
	int		start_cur;
	int		end_cur;

	end_cur = 0;
	start_cur = 0;
	while (s[end_cur])
	{
		if (s[end_cur] == c || s[end_cur] == 0)
			start_cur = end_cur + 1;
		if (s[end_cur] != c && (s[end_cur + 1] == c || s[end_cur + 1] == 0))
		{
			result[word] = malloc(sizeof(char) * (end_cur - start_cur + 2));
			if (!result[word])
			{
				while (--word >= 0)
					free(result[word]);
				return (0);
			}
			ft_strlcpy(result[word], (s + start_cur), end_cur - start_cur + 2);
			word++;
		}
		end_cur++;
	}
	result[word] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	result = malloc(sizeof(char *) * (numwords(s, c) + 1));
	if (!result)
		return (0);
	if (!split_words(result, s, c, 0))
		return (free(result), NULL);
	return (result);
}

/*#include <stdio.h>
int main()
{
	char *to_split = "hello word";
	char spilt = ' ';

	char **r = ft_split(to_split, spilt);
	if(r == NULL)
	{
		printf("error\n");
		return 1;
	}

	printf("the spilted string is : %s\n", r[0]);
	free(r[0]);
	free(r[1]);
	free(r);
	return 0;
}*/