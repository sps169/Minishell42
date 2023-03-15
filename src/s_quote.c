/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:16:08 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/15 10:49:12 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_error(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n'", 2);
	g_status = 1;
	g_error = -1;
	return (-1);
}

int	s_quote(t_copy *copy)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (quote_error('\''));
	if (copy->wc[copy->i + 1] == '\'' && (copy->wc[copy->i + 2] == ' '
			|| copy->wc[copy->i + 2] == '\0'))
		copy->cmd[++copy->j] = '\0';
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '\'')
		copy->cmd[++copy->j] = copy->wc[copy->i];
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '\'')
		return (quote_error('\''));
	copy->i++;
	return (-2);
}

int	s_quote_arg(t_copy *copy, size_t i)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (quote_error('\''));
	if (copy->wc[copy->i + 1] == '\'' && (copy->wc[copy->i + 2] == ' '
			|| copy->wc[copy->i + 2] == '\0'))
		copy->args[i][++copy->j] = '\0';
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '\'')
		copy->args[i][++copy->j] = copy->wc[copy->i];
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '\'')
		return (quote_error('\''));
	copy->i++;
	return (1);
}

int	s_quote_redir(t_copy *copy, char *str)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (quote_error('\''));
	if ((copy->wc[copy->i + 1] == '\'' && copy->wc[copy->i +2] == ' ') && !str)
	{
		str[copy->redir.i] = ' ';
		str[copy->redir.i +1] = 0;
		copy->i = copy->i +2;
		return (-1);
	}
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '\'')
		str[++copy->redir.i] = copy->wc[copy->i];
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '\'')
		return (quote_error('\''));
	str[copy->redir.i +1] = 0;
	copy->i++;
	if (copy->wc[copy->i] != ' ')
		return (1);
	return (-1);
}
