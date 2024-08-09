/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2024/08/09 20:09:51 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanse_pipe_list(t_pipe **first)
{
	t_pipe *current;
	t_pipe *next;

	if (!first || !*first)
		return;
	current = *first;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

t_pipe *create_pipe_list(int size)
{
	t_pipe *first;
	t_pipe *prev;
	t_pipe *current;
	int i;

	first = NULL;
	prev = NULL;
	current = NULL;
	i = 0;
	if (size > 0)
	{
		first = malloc(sizeof(t_pipe));
		if (!first)
			return (NULL);
		first->next = NULL;
		current = first;
		while (i < size - 1)
		{
			prev = current;
			current = malloc(sizeof(t_pipe));
			if (!current)
			{
				cleanse_pipe_list(&first);
				return (NULL);
			}
			current->next = NULL;
			prev->next = current;
			prev = current;
			i++;
		}
	}
	return (first);
}

int	get_commands_from_env(t_tools *tools)
{
	t_command	*current_command;
	char		*curr_path;
	int			found;
	int			i;
	char	*tmp;

	current_command = tools->command;
	while (current_command)
	{
		i = 0;
		found = 0;
		while (tools->paths[i] && !found)
		{
			curr_path = tools->paths[i];
			if (access(ft_strjoin(curr_path, current_command->args[0]), R_OK | X_OK) != -1)
			{
				found = 1;
				tmp = current_command->args[0];
				current_command->args[0] = ft_strjoin(curr_path, current_command->args[0]);
				free(tmp);
				tmp = current_command->cmd_sep;
				current_command->cmd_sep = ft_strjoin(curr_path, current_command->cmd_sep);
				free(tmp);
			}
			i++;
		}
		if (found == 0)
		{
			printf("%s: command not found\n", current_command->args[0]);
			return (-1);
		}
		current_command = current_command->next;
	}
	return (0);
}

// int open_files(t_tools *tools)
// {
// 	t_redir *curr_redir;
// 	int iflags;
// 	int oflags;
// 	int ifd;
// 	int ofd;

// 	curr_redir = tools->command->redir;
// 	iflags = O_RDONLY;
// 	oflags = O_RDWR | O_CREAT | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP | S_IROTH;
	
// 	while (curr_redir)
// 	{
// 		if (curr_redir->type == 0)
// 		{
// 			curr_redir->fd = open(curr_redir->file, iflags);
// 			if (curr_redir->fd == -1)
// 				return (-1);
// 		}

// 		curr_redir = curr_redir->next;
// 	}
// 	if (tools->command
// 			->redir.)
// 		oflags = oflags | O_APPEND;
// 	if (input)
// 	{
// 		ifd = open(input, iflags);
// 		if (ifd == -1)
// 			return (0);
// 		dup2(ifd, STDIN_FILENO);
// 		close(ifd);
// 	}
// 	if (output)
// 	{
// 		ofd = open(output, oflags);
// 		if (ofd == -1)
// 			return (0);
// 		dup2(ofd, STDOUT_FILENO);
// 		close(ofd);
// 	}
// 	return (1);
// }

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

void executor(t_tools *tools)
{
	unsigned int size;
	t_pipe *ps;
	unsigned int i;
	int child_status;
	int pid;
	t_pipe *prev_pipe;
	t_command *curr_command;

	i = 0;
	prev_pipe = NULL;
	size = get_command_list_size(tools->command);
	if (size < 1)
		return;
	ps = create_pipe_list(size);
	if (size > 1 && !ps)
		return;
	if (get_commands_from_env(tools) != 0)
		return;
	curr_command = tools->command;
	while (i < size)
	{
		if (i != size - 1)
			pipe(ps->pipe);
		pid = fork();
		if (pid == 0)
		{
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
			execve(curr_command->args[0], curr_command->args, tools->envp);
			printf("???? errno = %i\n", errno);
			return;
		}
		else
		{
			if (i != size - 1)
			{
				close(ps->pipe[1]);
				if (prev_pipe)
					close(prev_pipe->pipe[0]);
			}
			else
			{
				close(ps->pipe[0]);
			}
		}
		i++;
		if (curr_command)
		{
			curr_command = curr_command->next;
		}
		if (ps)
		{
			prev_pipe = ps;
			ps = ps->next;
		}
	}
	waitpid(pid, &child_status, 0);
}
