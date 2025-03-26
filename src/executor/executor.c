/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2025/03/26 17:40:32 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int find_command_in_route(t_command *command, char *path) {
	char	*joined;
	int		found;

	found = 0;
	joined = ft_strjoin(path, command->args[0]);
	if (access(joined, R_OK | X_OK) != -1)
	{
		free(command->args[0]);
		command->args[0] = joined;
		found = 1;
	}
	else 
		free(joined);
	return (found);
}

int	fill_command_from_env(t_command *command, t_tools *tools)
{
	int		found;
	int		i;

	if (is_builtin(command))
		return (0);
	found = 0;
	i = 0;
	while (tools->paths[i] && !found)
	{
		if (access(command->args[0], R_OK | X_OK) != -1)
			found = 1;
		else
		{
			found = find_command_in_route(command, tools->paths[i]);
			i++;
		}
	}
	if (found == 0)
	{
		printf("%s: command not found\n", command->args[0]);
		return (-1);
	}
	errno = 0;
	return (0);
}

static int get_command_list_size(t_command *list)
{
	int i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

static void handle_status(int status, t_tools *tools)
{
	if (WIFEXITED(status))
		tools->exit_status = WEXITSTATUS(status);
	if (tools && tools->exit_status == 127)
		printf("%s: command not found\n", tools->command->args[0]);
	if (g_signal == S_SIGINT_CMD)
		tools->exit_status = 130;
	g_signal = S_BASE;
}


static void run_command(t_command *command, t_tools *tools) 
{
	if (redir_setup(command) == 0)
	{
		if (is_builtin(command))
		{
			ft_builtin(command, tools);
		}
		else
		{
			execve(command->args[0], command->args, tools->envp);
		}
	}
}

static void run_builtin_in_parent_process(t_command *command, t_tools *tools)
{
	int	stdin_fd;
	int	stdout_fd;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	run_command(command, tools);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}

static int exec_single_command(t_command *command, t_tools *tools)
{
	int	pid;
	int	status;

	if (is_builtin(command))
	{
		run_builtin_in_parent_process(command, tools);
		return (0);
	}
	if (fill_command_from_env(command, tools) == -1)
		return -1;
	g_signal = S_CMD;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		run_command(command, tools);
		return (-1);
	}
	else if(pid > 0) {
		waitpid(pid, &status, 0);
		handle_status(status, tools);
	} else {
		return -1;
	}
	return status;
}

static t_pipe *obtain_related_pipe_from_list(t_pipe *ps, unsigned int pos, int is_prev)
{
	t_pipe			*curr_pipe;
	unsigned int	i;

	curr_pipe = ps;
	i = 1;
	if (!is_prev)
		i = 0;
	while (i < pos && curr_pipe) {
		curr_pipe = curr_pipe->next;
		i++;
	}
	if (pos == 0 && is_prev)
		return NULL;
	return curr_pipe;

}

static int piped_command_child (t_command *curr_command, t_pipes_command pipes, t_tools *tools, unsigned int i)
{
	signal(SIGINT, SIG_DFL);
	if (curr_command->next)//not last
	{
		dup2(pipes.curr->pipe[1], STDOUT_FILENO);
		close(pipes.curr->pipe[0]);
		close(pipes.curr->pipe[1]);
	}
	if (i != 0)//not first
	{
		dup2(pipes.prev->pipe[0], STDIN_FILENO);
		close(pipes.prev->pipe[0]);
	}
	if (is_builtin(curr_command) && ft_strcmp(curr_command->args[0],"exit") == 0)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	run_command(curr_command, tools);
	if (is_builtin(curr_command))
	{
		close(STDOUT_FILENO);
		exit(0);
	}
	return (-1);
}

static int exec_piped_command(t_pipe *ps, t_tools *tools, t_command *curr_command, unsigned int i)
{
	int	pid;
	int child_status;
	t_pipes_command pipes;

	pipes.prev = obtain_related_pipe_from_list(ps, i, 1);
	pipes.curr = obtain_related_pipe_from_list(ps, i, 0);
	if (fill_command_from_env(curr_command, tools) != -1) {

			if (curr_command->next != NULL) //dont make new pipe at last command
				pipe(pipes.curr->pipe);
			pid = fork();
			if (pid == 0)
				return (piped_command_child(curr_command, pipes, tools, i));
			else
			{
				if (curr_command->next != NULL) //not last
					close(pipes.curr->pipe[1]);
				if (pipes.prev)
					close(pipes.prev->pipe[0]);
				waitpid(pid, &child_status, 0);		
				handle_status(child_status, tools);
			}
		}
		return (0);
}

static int exec_compound_command(t_tools *tools, unsigned int size)
{
	t_pipe *ps;
	unsigned int i;
	t_command *curr_command;

	i = 0;
	ps = create_pipe_list(size);
	if (!ps)
	{
		write(2, "ERROR: Could't create pipe list\n", 33);
		return (-1);
	}
	curr_command = tools->command;
	while (i < size)
	{
		if (exec_piped_command(ps, tools, curr_command, i) != 0)
			return (1);
		if (curr_command)
			curr_command = curr_command->next;
		i++;
	}
	cleanse_pipe_list(&ps);
	return (0);
}

int executor(t_tools *tools)
{
	unsigned int size;

	size = get_command_list_size(tools->command);
	if (size < 1)
	{
		printf("ERROR: empty command list\n");
		return (0);
	}
	if (size == 1)
		return (exec_single_command(tools->command, tools));
	return (exec_compound_command(tools, size));
}
