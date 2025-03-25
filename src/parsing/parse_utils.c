/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:39:33 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:59:53 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quotes(const char *str, int *j, int i)
{
	if (str[*j] == '"')
	{
		if (str[*j - 1] != ' ')
		{
			i++;
		}
		i++;
		(*j)++;
		while (str[*j] != '"')
		{
			(*j)++;
		}
	}
	return (i);
}

static int	count_valid_args(char **aux)
{
	int	i;
	int	c;

	i = 0;
	c = 0;

	if (aux[0][0] != '<' && aux[0][0] != '>')
	{
		i++;
		c++;
	}
	while (aux[i])
	{
		if (aux[i][0] != '<' && aux[i][0] != '>'
			&& aux[i - 1][0] != '<' && aux[i - 1][0] != '>')
		{
			c++;
		}
		i++;
	}
	return (c);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;
	int	j;

	i = 0;
	j = 0;
	trigger = 0;
	while (str[j])
	{
		i = process_quotes(str, &j, i);
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

char	**list_dup_after(char *s, char c)
{
	char	**pp;
	size_t	len;
	size_t	j;
	size_t	aux;

	j = 0;
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


char	**parse_args(char *s)
{
	int		i;
	int		j;
	int		c;
	char	**aux;
	char	**res;

	i = 0;
	j = 0;
	aux = split_minishell(s, ' ');
	c = count_valid_args(aux);
	res = ft_calloc(c + 1, sizeof(s));
	if (aux[0][0] != '<' && aux[0][0] != '>')
	{
		res[0] = aux[0];
		i++;
		j++;
	}
	while (aux[i])
	{
		if (aux[i][0] != '<' && aux[i][0] != '>' && aux[i - 1][0]
			!= '<' && aux[i - 1][0] != '>')
		{
			res[j] = ft_strdup(aux[i]);
			j++;
		}
		i++;
	}
	return (res);
}


