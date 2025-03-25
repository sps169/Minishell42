/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:46:51 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:08:26 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_dollar(t_tools *tools, char **aux, int *i)
{
	char	*aux2;
	char	*aux3;

	aux2 = char_to_str(tools->arg_str[(*i)++]);
	aux3 = ft_strjoin(*aux, aux2);
	free(*aux);
	*aux = aux3;
	free(aux2);
}

static int	process_env_variable(t_tools *tools, char **aux, int j, int *res)
{
	int		i;
	char	*aux2;
	char	*aux3;

	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->arg_str + j + 1, tools->envp[i],
				equal_after(tools->envp[i]) - 1) == 0
			&& after_dollar_lenght(tools->arg_str, j)
			- j == (int)equal_after(tools->envp[i]))
		{
			aux2 = ft_strdup(tools->envp[i] + equal_after(tools->envp[i]));
			aux3 = ft_strjoin(*aux, aux2);
			free(*aux);
			*aux = aux3;
			free(aux2);
			*res = equal_after(tools->envp[i]);
		}
		i++;
	}
	return (*res);
}

char	*detect_dollar(t_tools *tools)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strdup("\0");
	while (tools->arg_str[i])
	{
		i += digit_after_dollar(i, tools->arg_str);
		if (tools->arg_str[i] == '$' && tools->arg_str[i + 1] == '?')
			return (0);
		else if (tools->arg_str[i] == '$' && (tools->arg_str[i + 1]
				!= ' ' && (tools->arg_str[i + 1]
					!= '"' || tools->arg_str[i + 2] != '\0'))
			&& tools->arg_str[i + 1] != '\0')
		{
			i += loop_dollar(tools, &aux, i);
		}
		else
		{
			process_dollar(tools, &aux, &i);
		}
	}
	return (aux);
}

int	loop_dollar(t_tools *tools, char **aux, int j)
{
	int		res;
	char	*aux2;
	char	*aux3;
	int		var_length;

	res = 0;
	process_env_variable(tools, aux, j, &res);
	if (res == 0)
	{
		var_length = after_dollar_lenght(tools->arg_str, j) - j;
		aux2 = strndup(tools->arg_str + j, var_length);
		aux3 = ft_strjoin(*aux, aux2);
		free(*aux);
		*aux = aux3;
		free(aux2);
		res = var_length;
	}
	return (res);
}

char	*expansor(t_tools *tools)
{
	char	*aux;

	aux = NULL;
	tools->arg_str = expand_exit_status(tools->arg_str, tools->exit_status);
	if (tools->arg_str[dollar_after(tools->arg_str) - 2]
		!= '\'' && dollar_after(tools->arg_str) != 0
		&& tools->arg_str[dollar_after(tools->arg_str)] != '\0')
	{
		aux = detect_dollar(tools);
		free(tools->arg_str);
		tools->arg_str = aux;
	}
	tools->arg_str = delete_quotes(tools->arg_str, '\"');
	tools->arg_str = delete_quotes(tools->arg_str, '\'');
	return (tools->arg_str);
}
