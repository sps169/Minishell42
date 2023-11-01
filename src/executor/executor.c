/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:07 by sperez-s          #+#    #+#             */
/*   Updated: 2023/11/01 22:27:06 by sperez-s         ###   ########.fr       */
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

void	executor(unsigned int size, t_command *command)
{
	unsigned int	i;
	int	ret;
	int	status;
	int	pid;
	int	pipe[2];
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
			execve(command->command[0], command->command, &env);
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
	first->next = second;
	first->command = malloc(3 * sizeof(char *));
	first->command[0] = malloc(ft_strlen("grep") * sizeof(char) + 1);
	first->command[0] = "grep";
	first->command[1] = malloc(ft_strlen("'hola'") * sizeof(char) + 1);
	first->command[1] = "'hola'";
	first->command[2] = malloc(sizeof(char));
	first->command[2] = NULL;
	second = malloc(sizeof(t_command));
	second->command = NULL;
	second->next= NULL;
	second->next= third;
	second->command = malloc(3 * sizeof(char *));
	second->command[0] = malloc(ft_strlen("cat") * sizeof(char) + 1);
	second->command[0] = "cat";
	second->command[1] = malloc(ft_strlen("myfile.txt") * sizeof(char) + 1);
	second->command[1] = "myfile.txt";
	second->command[2] = malloc(sizeof(char));
	second->command[2] = NULL;
	third = malloc(sizeof(t_command));
	third->command = NULL;
	third->next= NULL;
	third->command = malloc(3 * sizeof(char *));
	third->command[0] = malloc(ft_strlen("wc") * sizeof(char) + 1);
	third->command[0] = "wc";
	third->command[1] = malloc(ft_strlen("-l") * sizeof(char) + 1);
	third->command[1] = "-l";
	third->command[2] = malloc(sizeof(char));
	third->command[2] = NULL;
	return (first);
}

int	main(void)
{
	char *args[][3] = 
	{
		{"/bin/ls", "-l", NULL},
		{"/bin/ls", "-a", NULL},
	};


	//cat myfile.txt | grep 'my_pattern' | wc -l
	executor(2, (char ***)args);
	return  (0);
}
