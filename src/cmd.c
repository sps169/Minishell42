/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:33:25 by migonzal          #+#    #+#             */
/*   Updated: 2023/04/12 12:52:10 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *first_command(char *str)
{
	int i;
	int j;
	char *res;
	int cont;


	i = 0;
	j = 0;
	cont = 0; 
	res = malloc(sizeof(char) * (ft_strlen_first_word(str) + 1));

	if (!str)
	{
		printf("No hay comando");
		return (0);
	}
	while (str[i] == ' ')
	{
		i++;
	}
	while (str[i] != ' ')
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	printf("%s\n", res);
	printf("%d\n", i);
	return (res);

}


char *arg_quote(char *str)
{
	int i = 0;
	char **res = ft_split(str, '"');
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	return (0);
}
