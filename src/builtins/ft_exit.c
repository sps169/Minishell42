#include "minishell.h"


// void	free_tools(t_tools *tools)
// {
// 	ft_free_arr(tools->paths);
// 	ft_free_arr(tools->envp);
// 	free(tools->arg_str);
// 	//Limpiar t_command
// 	free(tools->pwd);
// 	free(tools->old_pwd);
// }

// int is_str_digit(char *str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// void code_exit(char **str)
// {
// 	int exit_code;

// 	if  (!str[1])
// 		exit_code = 0;
// 	else if (is_str_digit(str[1]))
// 		exit_code = ft_atoi(str[1]);
// 	else
// 	{
// 		ft_putstr_fd("minishell: exit ", STDERR_FILENO);
// 		ft_putstr_fd(str[1], STDERR_FILENO);
// 		ft_putstr_fd(": nummeric argument required\n", STDERR_FILENO);
// 		exit_code = 255;
// 	}
// 	free(str);
// 	exit(exit_code);
// }

// int ft_exit(t_tools *tools)
// {
// 	char **str;

// 	ft_putendl_fd("exit", STDERR_FILENO);
// 	if (tools->command->args[1] && tools->command->args[2])
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	str = arrdup(tools->command->args);
// 	free_tools(tools);
// 	code_exit(str);
// 	return (EXIT_SUCCESS);
// }

static int	check_exit_args(t_tools *tools);


int	ft_exit(t_tools *tools)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	tools->exit_status = check_exit_args(tools);
	if (tools->exit_status != 1)
	{
		exit(tools->exit_status);
	}
	ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	check_exit_args(t_tools *tools)
{
	int	i;

	if (tools->command->args[1] && tools->command->args[2])
		return (1);
	if (tools->command->args[1])
	{
		i = -1;
		while (tools->command->args[1][++i])
		{
			if (!ft_isdigit(tools->command->args[1][i]))
			{
				printf("exit: %s: numeric argument required\n",
						tools->command->args[1]);
				return (2);
			}
		}
		return (ft_atoi(tools->command->args[1]));
	}
	return (0);
}