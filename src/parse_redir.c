/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:03:19 by migonzal          #+#    #+#             */
/*   Updated: 2023/05/03 11:22:13 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char *ft_redir_out(char *s)
{
	int i = 0;
	int start = 0;
	int finish = 0;
	while ( s[i])
	{
		if (s[i] == '>')
		{
			i++;
			start = i;
			while (s[i] == ' ')
			{
				i++;
			}
			while (s[i] != ' ')
			{
				i++;
			}
			finish = i;
		}
		i++;
	}
	char *res = word_dup(s, start, finish);
	return (res);
}
