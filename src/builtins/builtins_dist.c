

#include "minishell.h"




int built_comprobation(t_tools *tools)
{
	if (!ft_strcmp(tools->command->args[0], "echo"))
		return (1);
	if (!ft_strcmp(tools->command->args[0], "cd"))
		return (1);
	if (!ft_strcmp(tools->command->args[0], "pwd"))
		return (1);
	if (!ft_strcmp(tools->command->args[0], "export"))
		return (1);
	if (!ft_strcmp(tools->command->args[0], "unset"))
		return (1);
	if (!ft_strcmp(tools->command->args[0], "env"))
		return (1);
	if (!ft_strcmp(tools->command->args[0], "exit"))
		return (1);
	else 
		return (0);
}


void ft_builtin(t_tools *tools)
{
	if (!ft_strcmp(tools->command->args[0], "env"))
		ft_env(tools);
	if (!ft_strcmp(tools->command->args[0], "pwd"))
		ft_pwd(tools);
	if (!ft_strcmp(tools->command->args[0], "echo"))
		ft_echo(tools);
	if (!ft_strcmp(tools->command->args[0], "exit"))
		ft_exit(tools);
	if (!ft_strcmp(tools->command->args[0], "export"))
		ft_export(tools);
	if (!ft_strcmp(tools->command->args[0], "unset"))
		ft_unset(tools);
	 if (!ft_strcmp(tools->command->args[0], "cd"))
	 	ft_cd(tools);
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