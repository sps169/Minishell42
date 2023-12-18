/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2023/12/18 20:19:48 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	cleanse_pipe_list(t_pipe *first)
// {
// 	//todo
// }

// t_pipe	*create_pipe_list(int size)
// {
// 	t_pipe	*first;
// 	t_pipe	*prev;
// 	t_pipe	*current;
// 	int		i;

// 	first = NULL;
// 	prev = NULL;
// 	current = NULL;
// 	i = 0;
// 	if (size > 0)
// 	{
// 		first = malloc(sizeof(t_pipe));
// 		if (!first)
// 			return (NULL);
// 		first->next = NULL;
// 		current = first;
// 		while (i < size - 1)
// 		{
// 			prev = current;
// 			current = malloc(sizeof(t_pipe));
// 			if (!current)
// 			{
// 				cleanse_pipe_list(first);
// 				return (NULL);
// 			}
// 			current->next = NULL;
// 			prev->next = current;
// 			prev = current;
// 			i++;
// 		}
// 	}
// 	return (first);
// }

// int	open_files(char *input, char *output, int heredoc, int append)
// {
// 	int	iflags;
// 	int	oflags;
// 	int	ifd;
// 	int	ofd;

// 	iflags = 0;
// 	oflags = 0;
// 	iflags = O_RDONLY;
// 	oflags = O_RDWR | O_CREAT | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP | S_IROTH;
// 	if (append)
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

// void	executor(unsigned int size, t_command *command, char *env[])
// {
// 	unsigned int	i, j;
// 	int	status;
// 	int child_status;
// 	int	pid;
// 	t_pipe	*ps;
// 	t_pipe	*prev_pipe;

// 	i = 0;
// 	status = 0;
// 	prev_pipe = NULL;
// 	ps = create_pipe_list(size);
// 	if (!ps)
// 		return;
// 	if (!open_files(command->input, command->next->next->output, command->heredoc, command->next->next->append))
// 		return;
// 	while (i < size)
// 	{
// 		if (i != size - 1)
// 			pipe(ps->pipe);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			// printf("Access to file: %i\n", access(ft_strjoin("/bin/", ft_split(command->command, ' ')[0]), F_OK | X_OK));
// 			if (i != size -1)
// 			{
// 				dup2(ps->pipe[1],STDOUT_FILENO);
// 				close(ps->pipe[0]);
// 				close(ps->pipe[1]);
// 			}
// 			if (i != 0)
// 			{
// 				dup2(prev_pipe->pipe[0], STDIN_FILENO);
// 				close(prev_pipe->pipe[0]);
// 			}
// 			execve(ft_strjoin("/bin/", ft_split(command->command, ' ')[0]), ft_split(command->command, ' '), env);
// 			printf("???? errno = %i\n", errno);
// 			return;
// 		} else {
// 			if (i != size - 1) {
// 				close(ps->pipe[1]);
// 				if (prev_pipe)
// 					close(prev_pipe->pipe[0]);
// 			} else {
// 				close(ps->pipe[0]);
// 			}
// 		}
// 		i++;
// 		if (command) {
// 			command = command->next;
// 		}
// 		if (ps) {
// 			prev_pipe = ps;
// 			ps = ps->next;
// 		}
// 	}
// 	j = 0;
// 	waitpid(pid, &child_status, 0);
// 		// printf("Node %i exit status is: %i\n", j, child_status % 128);

// }

// t_command *create_command_list(char *input_path, char *output_path, int heredoc, int append)
// {
// 	t_command	*first;
// 	t_command	*second;
// 	t_command	*third;

// 	first = NULL;
// 	second = NULL;
// 	third = NULL;
// 	first = malloc(sizeof(t_command));
// 	first->command = NULL;
// 	first->next = NULL;
// 	first->command = malloc(ft_strlen("head -n 3"));
// 	first->command = "head -n 3";
// 	if (input_path)
// 	{
// 		first->input = malloc(ft_strlen(input_path));
// 		first->input = input_path;
// 	}
// 	else
// 		first->input = NULL;
// 	first->output = NULL;
// 	first->heredoc = 0;
// 	first->append = 0;
// 	second = malloc(sizeof(t_command));
// 	second->command = NULL;
// 	second->next= NULL;
// 	second->command = malloc(ft_strlen("tail -n 1"));
// 	second->command = "tail -n 2";
// 	second->input = NULL;
// 	second->output = NULL;
// 	second->heredoc = 0;
// 	second->append = 1;
// 	third = malloc(sizeof(t_command));
// 	third->command = NULL;
// 	third->next= NULL;
// 	third->command = malloc(ft_strlen("wc -l"));
// 	third->command = "wc -l";
// 	third->input = NULL;
// 	if (output_path)
// 	{
// 		third->output = malloc(ft_strlen(output_path));
// 		third->output = output_path;
// 	}
// 	else
// 		third->output = NULL;
// 	third->heredoc = 0;
// 	third->append = 1;
// 	first->next = second;
// 	second->next = third;
// 	return (first);
// }

// int	main(int argc, char *argv[], char *envp[])
// {
// 	//compilation: gcc -I../../include executor.c ../../Libft/*.c
// 	//cat myfile.txt | sort | wc -l
// 	//cat myfile.txt | awk '{count++} END {print count}'
// 	//top
// 	char *input = malloc(ft_strlen("myfile.txp"));
// 	input = "myfile.txp";
// 	char *output = NULL; // malloc(ft_strlen("out.txt"));
// 	output = NULL; //out.txt;
// 	executor(3, create_command_list(input, output, 1, 0), envp);
// 	return  (0);
// }
