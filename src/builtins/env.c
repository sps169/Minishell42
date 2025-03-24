#include "minishell.h"


// int env(t_tools *tools)
// {
//     int i;

//     i = 0;
//     while (tools->envp[i])
//     {
//         ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
//         i++;
//     }
//     return (0);
// }


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

