/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:23:47 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 17:33:05 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_unclosed_quotes(t_tools *tools, int *in_dquote, int *in_squote)
{
	int i;

	i = 0;
	while (tools->arg_str[i])
	{
		if (tools->arg_str[i] == '"' && !(*in_squote))
			*in_dquote = !(*in_dquote);
		else if (tools->arg_str[i] == '\'' && !(*in_dquote))
			*in_squote = !(*in_squote);
		i++;
	}
}

static void	read_line_and_trim(t_tools *tools)
{
	char	*aux;

	tools->arg_str = readline("minishell? ");
	if (!tools->arg_str)
	{
		ft_putendl_fd("No line read, exit minishell", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	aux = ft_strtrim(tools->arg_str, " ");
	free(tools->arg_str);
	tools->arg_str = aux;
}

static void	handle_multiline_quotes(t_tools *tools, int *in_dquote, int *in_squote)
{
	char *aux;
	char *next_line;

	while (*in_dquote || *in_squote)
	{
		next_line = readline(*in_dquote ? "dquote> " : "quote> ");
		if (!next_line)
		{
			ft_putendl_fd("No line read, exit minishell", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		aux = ft_strjoin(tools->arg_str, "\n");
		free(tools->arg_str);
		tools->arg_str = ft_strjoin(aux, next_line);
		free(aux);
		free(next_line);

		*in_dquote = 0;
		*in_squote = 0;
		handle_unclosed_quotes(tools, in_dquote, in_squote);
	}
}

static int	process_user_input(t_tools *tools)
{
	int	in_dquote;
	int	in_squote;

	in_dquote = 0;
	in_squote = 0;

	read_line_and_trim(tools);

	if (tools->arg_str[0] == '\0')
	{
		reset_tools(tools);
		return (0);
	}
	if (!validate_pipes(tools->arg_str))
	{
		reset_tools(tools);
		return (0);
	}

	handle_unclosed_quotes(tools, &in_dquote, &in_squote);
	handle_multiline_quotes(tools, &in_dquote, &in_squote);

	return (1);
}

int	minishell_loop(t_tools *tools)
{
	while (1)
	{
		if (g_signal == S_SIGINT)
			tools->exit_status = 1;

		if (!process_user_input(tools))
			continue ;

		add_history(tools->arg_str);
		expansor(tools);
		tools->command = parser(tools->arg_str);
		executor(tools);
		reset_tools(tools);
	}
	return (1);
}