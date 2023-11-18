/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2023/11/18 17:16:51 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor_basic(unsigned int size, char ***commands)
{
	unsigned int	i;
	int	ret;
	int	status;
	int	pid;
	(void) commands;
	char *command[] = {"/bin/ls", "-l", NULL};
	char	*env = getenv("PATH");

	i = 0;
	ret = 0;
	status = 0;
	printf("Environment:\n%s\n", env);
	printf("Parent process started\n");
	while (i < size)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("Child[%i] process started\n", i);
			execve("/bin/ls", command, &env);
			printf("????\n");
			return;
		}
		printf("Parent process waiting\n");
		ret = waitpid(pid, &status, 0);
		if (ret == -1)
			printf("[Parent] Error\n");
		if (ret == pid)
			printf("Child[%i] process finished\n", i);
		i++;
		ret = 0;
	}
}

void	executor(unsigned int size, t_command *command, char *env[])
{
	unsigned int	i;
	int	status;
	int	pid;
	int save;
	int	p[2];

	i = 0;
	status = 0;
	save = -1;
	while (i < size)
	{
		if (i != size - 1)
			pipe(p);
		pid = fork();
		if (pid == 0)
		{
			// printf("Access to file: %i\n", access(ft_strjoin("/bin/", ft_split(command->command, ' ')[0]), F_OK | X_OK));
			if (i != size -1)
			{
				close(STDOUT_FILENO);
				dup(p[1]);//,STDOUT_FILENO);
				close(p[0]);
				close(p[1]);
			}
			if (i != 0)
			{
				close(STDIN_FILENO);
				dup(save);
				close(save);
			}
			execve(ft_strjoin("/bin/", ft_split(command->command, ' ')[0]), ft_split(command->command, ' '), env);
			printf("???? errno = %i\n", errno);
			return;
		} else {
			if (i != size - 1) {
				close(p[1]);
				save = p[0];
			} else
				close(p[0]);
		}
		i++;
		if (command) {
			command = command->next;
		}
	}
	while (pid != wait(&status));
}

t_command *create_command_list()
{
	t_command	*first;
	t_command	*second;
	t_command	*third;


	first = NULL;
	second = NULL;
	third = NULL;
	first = malloc(sizeof(t_command));
	first->command = NULL;
	first->next = NULL;
	first->command = malloc(ft_strlen("cat myfile.txt"));
	first->command = "cat myfile.txt";
	second = malloc(sizeof(t_command));
	second->command = NULL;
	second->next= NULL;
	second->command = malloc(ft_strlen("sort"));
	second->command = "sort";
	third = malloc(sizeof(t_command));
	third->command = NULL;
	third->next= NULL;
	third->command = malloc(ft_strlen("wc -l"));
	third->command = "wc -l";
	first->next = second;
	second->next = third;
	return (first);
}

int	main(int argc, char *argv[], char *envp[])
{
	//compilation: gcc -I../../include executor.c ../../Libft/*.c
	//cat myfile.txt | sort | wc -l
	executor(3, create_command_list(), envp);
	return  (0);
}
