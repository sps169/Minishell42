/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip_extra_spaces_before.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:51:13 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/02 10:04:40 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	follow_env(int v, char *whole_cmd)
{
	v--;
	while (whole_cmd[v] && whole_cmd[v] != ' ')
	{
		if (whole_cmd[v] == '$' && whole_cmd[v - 1] != '\\')
			return (1);
		v--;
	}
	return (0);
}

int	add_space_before_condition(char *whole_cmd, int v)
{
	if (follow_env(v, whole_cmd) || whole_cmd[v - 1] == '"' || whole_cmd
		[v - 1] == '\'' || whole_cmd[v - 1] == '/' || whole_cmd[v - 1]
		== '@' || whole_cmd[v - 1] == ',' || whole_cmd[v - 1] == '['
		|| whole_cmd[v - 1] == ']' || (whole_cmd[v - 1] == ' '
			&& whole_cmd[v - 2] == '\\'))
		return (1);
	return (0);
}

int	add_space_before_util(char *whole_cmd, int v, char *tmp)
{
	if (whole_cmd[v + 1] == ' ' && ft_only_spaces(tmp))
		return (-1);
	while (whole_cmd[v] && whole_cmd[v] != '$' && whole_cmd[v - 1] != '\\')
		v--;
	if (whole_cmd[v - 1] == ' ' && ft_only_spaces(tmp))
		return (-1);
	return (v);
}

static int	add(char *whole_cmd, char *copy, char **new, int v)
{
	int	j;

	j = 0;
	if (v == -1)
	{
		if (copy)
			free(copy);
		return (-1);
	}
	if (add_space_before_condition(whole_cmd, v) == 1)
	{
		while (copy[j])
		{
			(*new)[0] = ' ';
			(*new)[j + 1] = copy[j];
			j++;
		}
		(*new)[j + 1] = '\0';
	}
	return (1);
}

int	add_space_before(char *tmp, char *whole_cmd, int v, char **new)
{
	int		i;
	char	*copy;

	i = 0;
	copy = NULL;
	copy = ft_strdup(*new);
	v--;
	if (tmp[i] == ' ')
	{
		v = add_space_before_util(whole_cmd, v, tmp);
		if (add(whole_cmd, copy, new, v) == -1)
			return (-1);
	}
	if (copy)
		free(copy);
	return (1);
}
