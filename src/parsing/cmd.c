/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:33:25 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:58:22 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

char	*first_command(char *str)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	i = 0;
	j = 0;
	if (!str)
	{
		printf("No hay comando");
		return (NULL);
	}
	len = ft_strlen_first_word(str) + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	i = skip_spaces(str, i);
	while (str[i] != ' ' && str[i] != '\0')
		res[j++] = str[i++];
	res[j] = '\0';
	printf("%s\n", res);
	printf("%d\n", i);
	return (res);
}

int	validate_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && str[i + 1] == ' ' && str[i + 2] == '|')
		{
			fprintf(stderr, "Error: Invalid syntax `| |`\n"); ///OJO
			return (0);
		}
		i++;
	}
	return (1);
}


int	ft_strlen_first_word(char *str)
{
	int	i;
	int	cont;

	cont = 0;
	i = 0;

	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
	{
		i++;
		cont++;
	}
	return (cont);
}

char	*arg_quote(char *str)
{
	int		i;
	char	**res;

	i = 0;
	res = ft_split(str, '"');
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	return (0);
}
