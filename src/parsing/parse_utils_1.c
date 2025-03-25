
#include "minishell.h"

char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}


char	*word_dup_after(char *s, char c, int i)
{
	int		start;
	int		finish;
	char	*res;

	start = 0;
	finish = 0;


	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			start = i;
			while (s[i] == ' ')
				i++;
			while (s[i] != ' ' && s[i])
				i++;
			finish = i;
			break ;
		}
		i++;
	}
	res = word_dup(s, start, finish);
	return (res);

}

int	dup_after_pos(char *s, char c, int num)
{
	int	i;

	i = num;


	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);

}

char	*word_dup_before(char *s, char c)
{
	int		i;
	int		start;
	int		finish;
	char	*res;

	start = 0;
	finish = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i--;
			finish = i;
			while (s[i] == ' ')
				i--;
			while (s[i] != ' ' && s[i])
				i--;
			start = i;
			break ;
		}
		i++;
	}
	res = word_dup(s, start, finish);
	return (res);
}

