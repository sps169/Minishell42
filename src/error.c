/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:30 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/15 10:49:37 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_token(char *msg, char c, int i, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (c == 'n')
		ft_putstr_fd("newline\'\n", 2);
	else if (str[i + 1] == c || (i > 0 && str[i - 1] == c))
	{
		ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\'', 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\'', 2);
		ft_putchar_fd('\n', 2);
	}
	g_status = 2;
	return (-1);
}

int	error_msg(char *str, int i, char c)
{
	ft_error_token("syntax error near unexpected token ", c, i, str);
	g_status = 2;
	return (-1);
}

int	error_exit(char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (errno != 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	g_error = -1;
	g_status = 1;
	return (-1);
}

void	error_ambiguous(char *name)
{
	ft_putstr_fd("minishell: $", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	g_error = -1;
	g_status = 1;
}
