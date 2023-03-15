/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:04:58 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/15 10:49:41 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_value_name(t_copy *copy)
{
	copy->redir.value = NULL;
	copy->redir.name = NULL;
	copy->redir.name = malloc(sizeof(char) * ft_strlen(copy->wc) + 1);
	if (!(copy->redir.name))
		return (-1);
	return (0);
}

int	cmd_quoting(t_copy *copy, int j)
{
	while (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
	{
		while (copy->wc[copy->i] == '"')
		{
			j = d_quote(copy, j);
			if (j == -1)
				return (-1);
		}
		while (copy->wc[copy->i] == '\'')
		{
			j = s_quote(copy);
			if (j == -1)
				return (-1);
		}
	}
	if (copy->wc[copy->i] == '\\')
		copy->i++;
	return (j);
}

int	cmd_redir_env(t_copy *copy, int j)
{
	if (copy->wc[copy->i] && copy->wc[copy->i] == '$'
		&& (copy->i == 0 || copy->wc[copy->i -1] != '\\'))
	{
		if (copy->wc[copy->i + 1] == '\\')
			copy->cmd[++copy->j] = copy->wc[copy->i];
		else
			j = env(copy, 0, 0, 1);
	}
	if ((copy->wc[copy->i] == '>' || copy->wc[copy->i] == '<')
		&& (copy->i == 0 || copy->wc[copy->i -1] != '\\'))
			j = redirection(copy, 0);
	return (j);
}

char	*cmd(t_copy *copy, int j)
{
	while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
	{
		j = -2;
		if ((copy->wc[copy->i] == '1' || copy->wc[copy->i] == '2')
			&& copy->wc[copy->i + 1] == '>'
			&& (!copy->cmd[0] || copy->wc[copy->i - 1] == ' '))
			copy->i++;
		j = cmd_quoting(copy, j);
		j = cmd_redir_env(copy, j);
		if ((copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] != '\\')
			&& (copy->cmd[0] || (!copy->cmd[0] && (copy->wc[copy->i - 1] == '"'
						|| copy->wc[copy->i - 1] == '\'') && (copy->wc
						[copy->i - 2] == '"' || copy->wc[copy->i - 2] == '\''
						|| j == 1))))
			break ;
		if (copy->i < (int)ft_strlen(copy->wc) && ((copy->wc[copy->i] == '$'
					&& (copy->i == 0 || copy->wc[copy->i - 1] == '\\'))
				|| (copy->wc[copy->i] != '$' && j == -2)))
			copy->cmd[++copy->j] = copy->wc[copy->i];
		if (copy->i < (int)ft_strlen(copy->wc))
			copy->i++;
	}
	copy->cmd[copy->j + 1] = 0;
	return (copy->cmd);
}

char	*parsing(char *whole_cmd, t_copy *copy)
{
	copy->i = 0;
	copy->j = -1;
	copy->cmd = NULL;
	copy->args = NULL;
	copy->redir.sstdout = 1;
	copy->redir.sstderr = 2;
	copy->redir.sstdin = 1;
	copy->redir.out1 = NULL;
	copy->redir.out2 = NULL;
	copy->redir.in = NULL;
	copy->wc = whole_cmd;
	g_error = 0;
	copy->cmd = malloc(sizeof(char) * (ft_strlen(copy->wc) + 1));
	if (!(copy->cmd) || !(copy->wc))
		return (NULL);
	copy->cmd[0] = 0;
	while (copy->wc[copy->i] && copy->wc[copy->i] == ' ')
		copy->i++;
	if (cmd(copy, 0) == NULL || g_error == -1)
		return (NULL);
	copy->args = (char **)malloc(sizeof(char *) * 1);
	if (!(copy->args) || options(copy, 1, 0) == -1)
		return (NULL);
	return (copy->cmd);
}
