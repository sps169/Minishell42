/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:39:33 by migonzal          #+#    #+#             */
/*   Updated: 2023/05/11 12:57:55 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char *word_dup_after(char *s, char c, int i)
{
	int start = 0;
	int finish = 0;


	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			start = i;
			while(s[i] == ' ')
				i++;
			while (s[i] != ' ' && s[i])
				i++;
		finish = i;
		break;
		}
		i++;
	}
	char * res = word_dup(s, start, finish);
	return (res);

}

int dup_after_pos(char *s, char c, int num)
{
	int i = num;


	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			break;
		}
		i++;
	}
	return (i);

}

char *word_dup_before(char *s, char c)
{
	int i;
	int start = 0;
	int finish = 0;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i--;
			finish = i;
			while(s[i] == ' ')
				i--;
			while (s[i] != ' ' && s[i])
				i--;
		start = i;
		break ;
		}
		i++;
	}
	char * res = word_dup(s, start, finish);
	return (res);
}

char **list_dup_after(char* s, char c)
{
	char **pp;
	size_t len;
	size_t j;
	size_t aux;

	if (!s)
		return (NULL);
	len = count_tokens(s, c);
	if (len == 0)
		return (NULL);
	pp = ft_calloc(len +1, sizeof(s));
	if (!pp)
		return (NULL);
	aux = 0;
	while (j < len)
	{
		pp[j] = word_dup_after(s, c, aux);
		if (!pp[j])
			return (ft_free_matrix(pp));
		aux = dup_after_pos(s, c, aux);
		j++;
	}
	return (pp);
}


char **parse_args(char *s)
{
	int i;
	int j;
	int c;
	char **aux = split_minishell(s, ' ');
	char **res;

	i = 0;
	j = 0;
	c = 0;

	if (aux[0][0] != '<' && aux[0][0] != '>'  && aux[0][0] != '-')
	{
		i++;
		c++;
	}
	while (aux[i])
	{
		if (aux[i][0] != '<' && aux[i][0] != '>'  && aux[i][0] != '-' && aux[i-1][0] != '<' && aux[i-1][0] != '>' && aux[i-1][0] != '-')
		{
			c++;
		}
		i++;
	}
	i = 0;

	res = ft_calloc(c +1, sizeof(s));
	if (aux[0][0] != '<' && aux[0][0] != '>'  && aux[0][0] != '-')
	{
		
		res[0] = aux[0];
		i++;
		j++;
		
	}
	while (aux[i])
	{
		if (aux[i][0] != '<' && aux[i][0] != '>'  && aux[i][0] != '-' && aux[i-1][0] != '<' && aux[i-1][0] != '>' && aux[i-1][0] != '-')
		{
			res[j] = ft_strdup(aux[i]);
			//printf("Dentro de res[j] %s\n", res[j]);
			j++;
			
		}
		i++;
	}
	return (res);

}

void ft_free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char **arrdup(char **arr)
{
	char **aux;
	size_t i;

	i = 0;
	while(arr[i] != NULL)
		i++;
	aux = ft_calloc(sizeof(char*), i +1);
	if(!aux)
		return (NULL);
	i = 0;
	while(arr[i] != NULL)
	{
		aux[i] = ft_strdup(arr[i]);
		if(aux[i] == NULL)
		{
			ft_free_arr(aux);
			return(aux);
		}
		i++;
	}
	return (aux);


}
