
#include "minishell.h"

int	count_words(const char *str, char c)
{
	int i;
	int trigger;
	int j;

	i = 0;
	j = 0;
	trigger = 0;
	while (str[j])
	{
		if (str[j]== '"')
		{
			if(str[j-1] != ' ')
			{
				i++;
			}
			i++;
			j++;
			while(str[j] != '"')
			{
				j++;
			}
		}
		if (str[j] != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (str[j] == c)
			trigger = 0;
		j++;
	}
	return (i);
}

char	*word_dup(const char *str, int start, int finish)
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

char		**ft_split_aux(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;
	printf("Número de palabras: %d\n", count_words(s, c));

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{

		if (s[i] != c  && index < 0)
		{
			printf("Valor de i: %c\n", s[i]);
			index = i;
		}
		if( s[i] == '"')
		{
			if (s[i - 1] != ' ')
			{
				split[j++] = word_dup(s, index, i);
				index = -1;
			}
			i++;
			index = i;
			while(s[i]!= '"')
			{
				i++;
			}
			split[j++] = word_dup(s, index, i);
			index = -1;
			i++;
			printf("Valor de index: %d\n", index);
		}
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
