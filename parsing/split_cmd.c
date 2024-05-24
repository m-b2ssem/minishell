#include "../minishell.h"

static int	numwords(char const *s, char c)
{
	int	cur;
	int	word_num;

	cur = 0;
	word_num = 0;
	while (s[cur] != '\0')
	{
		if (s[cur] != c && (s[cur + 1] == c || s[cur + 1] == '\0'))
			word_num++;
		cur++;
	}
	return (word_num);
}

void	free_word(int word, char **result)
{
	while (--word >= 0)
		free(result[word]);
}

static void	init_split_vars(int *start_cur, int *end_cur, t_quote_status *stat)
{
	*end_cur = 0;
	*start_cur = 0;
	*stat = NO_QUOTE;
}

static int	split_words(char **result, char const *s, char c, int word)
{
	int				start_cur;
	int				end_cur;
	t_quote_status	quote;

	init_split_vars(&start_cur, &end_cur, &quote);
	while (s[end_cur] != '\0')
	{
		quote = get_quote_status(s[end_cur], quote);
		if (s[end_cur] == c && quote == NO_QUOTE)
			start_cur = end_cur + 1;
		if (s[end_cur] != c && (s[end_cur + 1] == c || s[end_cur + 1] == '\0')
			&& quote == NO_QUOTE)
		{
			while (s[start_cur] != '\0' && is_space(s[start_cur]))
				start_cur++;
			result[word] = malloc(sizeof(char) * (end_cur - start_cur + 2));
			if (!result[word])
				return (free_word(word, result), 0);
			ft_strlcpy(result[word], (s + start_cur), end_cur - start_cur + 2);
			word++;
		}
		end_cur++;
	}
	result[word] = NULL;
	return (1);
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (numwords(s, c) + 1));
	if (!result)
		return (NULL);
	if (!split_words(result, s, c, 0))
		return (free(result), NULL);
	return (result);
}
