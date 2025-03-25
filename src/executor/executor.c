/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2025/03/25 18:51:53 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




static int	check_command_list(t_tools *tools)
{
	unsigned int	size;

	size = get_command_list_size(tools->command);
	if (size < 1)
	{
		printf("ERROR: empty command list\n");
		return (0);
	}
	return (size);
}

static	t_pipe *initialize_pipes(unsigned int size)
{
	t_pipe	*ps;

	ps = create_pipe_list(size);
	if (!ps)
	{
		write(2, "ERROR: Couldn't create pipe list\n", 33);
		return (NULL);
	}
	return (ps);
}

static int	setup_and_run_command( unsigned int i, unsigned int size, t_pipe *ps, t_pipe *prev_pipe, t_command *curr_command, t_tools *tools)
{
	int	pid;

	if (i != size - 1)
		pipe(ps->pipe);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (i != size - 1)
		{
			dup2(ps->pipe[1], STDOUT_FILENO);
			close(ps->pipe[0]);
			close(ps->pipe[1]);
		}
		if (i != 0)
		{
			dup2(prev_pipe->pipe[0], STDIN_FILENO);
			close(prev_pipe->pipe[0]);
		}
		run_command(curr_command, tools);
		exit(-1);
	}
	return (pid);
}

static void	execute_commands(unsigned int size, t_pipe *ps, t_tools *tools)
{
	unsigned int	i;
	int				child_status;
	t_pipe			*prev_pipe;
	t_command		*curr_command;

	i = 0;
	prev_pipe = NULL;
	curr_command = tools->command;

	while (i < size)
	{
		if (fill_command_from_env(curr_command, tools) != -1)
		{
			int pid = setup_and_run_command(i, size, ps, prev_pipe, curr_command, tools);
			if (i != size - 1)
				close(ps->pipe[1]);
			if (prev_pipe)
				close(prev_pipe->pipe[0]);
			waitpid(pid, &child_status, 0);
			handle_status(child_status, tools);
		}
		curr_command = curr_command->next;
		prev_pipe = ps;
		ps = ps->next;
		i++;
	}
}

int	executor(t_tools *tools)
{
	unsigned int	size;
	t_pipe			*ps;

	size = check_command_list(tools);
	ps = initialize_pipes(size);
	if (size == 0)
		return (0);
	if (size == 1)
		return (exec_single_command(tools->command, tools));
	if (!ps)
		return (-1);
	execute_commands(size, ps, tools);
	return (0);
}