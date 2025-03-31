#include "minishell.h"


int ft_echo(t_command *command)
{
	int i;
	
	i = 1;

	if (command->args[1] && !ft_strncmp(command->args[1], "-n", 2))
		i++;
	while (command->args[i])
	{
		ft_putstr_fd(command->args[i++], STDOUT_FILENO);
		if (command->args[i])
			ft_putchar_fd(32, STDOUT_FILENO);
	}
	if (!(command->args[1] && !ft_strncmp(command->args[1], "-n", 2)))
		ft_putchar_fd(10, STDOUT_FILENO);

	return (EXIT_SUCCESS);
}
