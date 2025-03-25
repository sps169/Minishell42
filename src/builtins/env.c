#include "minishell.h"



void	ft_env(t_tools *tools)
{
	int i = 0;

	if (tools->command->args[1])
	{
		printf("env: %s: No such file or directory\n", tools->command->args[1]);
		tools->exit_status = 127;
		return ;
	}
	while (tools->envp[i])
	{
		printf("%s\n", tools->envp[i]);
		i++;
	}
	tools->exit_status = 0;
}

