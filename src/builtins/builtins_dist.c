

#include "minishell.h"




int built_comprobation(t_tools *tools)
{
	if (!ft_strncmp(tools->command->args[0], "echo", 4))
		return (1);
	if (!ft_strncmp(tools->command->args[0], "cd", 2))
		return (1);
	if (!ft_strncmp(tools->command->args[0], "pwd", 3))
		return (1);
	if (!ft_strncmp(tools->command->args[0], "export", 6))
		return (1);
	if (!ft_strncmp(tools->command->args[0], "unset", 4))
		return (1);
	if (!ft_strncmp(tools->command->args[0], "env", 3))
		return (1);
	if (!ft_strncmp(tools->command->args[0], "exit", 4))
		return (1);
	else 
		return (0);
}


void ft_builtin(t_tools *tools)
{
	if (!ft_strncmp(tools->command->args[0], "env", 3))
		ft_env(tools);
	if (!ft_strncmp(tools->command->args[0], "pwd", 3))
		ft_pwd(tools);
	if (!ft_strncmp(tools->command->args[0], "echo", 4))
		ft_echo(tools);
	if (!ft_strncmp(tools->command->args[0], "exit", 4))
		ft_exit(tools);
	// if (!ft_strncmp(tools->command->args[0], "cd", 2))
	// 	//ft_cd(tools);
	// if (!ft_strncmp(tools->command->args[0], "export", 6))
	// 	//ft_export(tools);
	// if (!ft_strncmp(tools->command->args[0], "unset", 4))
	// 	//ft_unset(tools);
}


// int (*builting_arr(char *str))(t_tools *tools)
// {
// 	static void *builtins[7][2] =  {
// 	{"echo", echo},
// 	{"cd", cd},
// 	{"pwd", pwd},
// 	{"export", export},
// 	{"unset", unset},
// 	{"env", env},
// 	{"exit", ft_exit},
// 	};
// 	int	i;

// 	i = 0;
// 	while (i<7)
// 	{
// 		if (str)
// 		{
// 			if(!ft_strncmp(builtins[i][0], str, ft_strlen(builtins[i][0])))
// 				return (builtins[i][1]);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }