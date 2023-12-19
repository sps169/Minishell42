/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2023/12/19 20:43:29 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanse_pipe_list(t_pipe *first)
{
	//todo
}

t_pipe	*create_pipe_list(int size)
{
	t_pipe	*first;
	t_pipe	*prev;
	t_pipe	*current;
	int		i;

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
				cleanse_pipe_list(first);
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

int	open_files(char *input, char *output, int heredoc, int append)
{
	int	iflags;
	int	oflags;
	int	ifd;
	int	ofd;

	iflags = 0;
	oflags = 0;
	iflags = O_RDONLY;
	oflags = O_RDWR | O_CREAT | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP | S_IROTH;
	if (append)
		oflags = oflags | O_APPEND;
	if (input)
	{
		ifd = open(input, iflags);
		if (ifd == -1)
			return (0);
		dup2(ifd, STDIN_FILENO);
		close(ifd);
	}
	if (output)
	{
		ofd = open(output, oflags);
		if (ofd == -1)
			return (0);
		dup2(ofd, STDOUT_FILENO);
		close(ofd);
	}
	return (1);
}

static int	get_command_list_size(t_command *list)
{
	int	i;

	i = 0;
	while(list)
	{
		list = list->next;
	}
	return (i);
}

void	executor(t_tools *tools)
{
	unsigned int	i, j;
	int	status;
	int child_status;
	int	pid;
	t_pipe	*ps;
	t_pipe	*prev_pipe;
	int	size;

	i = 0;
	status = 0;
	prev_pipe = NULL;
	size = get_command_list_size(tools->command);
	if (size < 1)
		return ;
	ps = create_pipe_list(get_command_list_size());
	if (!ps)
		return;
	if (!open_files(command->input, command->next->next->output, command->heredoc, command->next->next->append))
		return;
	while (i < size)
	{
		if (i != size - 1)
			pipe(ps->pipe);
		pid = fork();
		if (pid == 0)
		{
			// printf("Access to file: %i\n", access(ft_strjoin("/bin/", ft_split(command->command, ' ')[0]), F_OK | X_OK));
			if (i != size -1)
			{
				dup2(ps->pipe[1],STDOUT_FILENO);
				close(ps->pipe[0]);
				close(ps->pipe[1]);
			}
			if (i != 0)
			{
				dup2(prev_pipe->pipe[0], STDIN_FILENO);
				close(prev_pipe->pipe[0]);
			}
			execve(ft_strjoin("/bin/", ft_split(command->command, ' ')[0]), ft_split(command->command, ' '), env);
			printf("???? errno = %i\n", errno);
			return;
		} else {
			if (i != size - 1) {
				close(ps->pipe[1]);
				if (prev_pipe)
					close(prev_pipe->pipe[0]);
			} else {
				close(ps->pipe[0]);
			}
		}
		i++;
		if (command) {
			command = command->next;
		}
		if (ps) {
			prev_pipe = ps;
			ps = ps->next;
		}
	}
	j = 0;
	waitpid(pid, &child_status, 0);
		// printf("Node %i exit status is: %i\n", j, child_status % 128);

}
