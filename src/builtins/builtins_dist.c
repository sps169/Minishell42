

#include "minishell.h"


int is_builtin(t_command *command)
{
	if (!ft_strcmp(command->args[0], "echo"))
		return (1);
	if (!ft_strcmp(command->args[0], "cd"))
		return (1);
	if (!ft_strcmp(command->args[0], "pwd"))
		return (1);
	if (!ft_strcmp(command->args[0], "export"))
		return (1);
	if (!ft_strcmp(command->args[0], "unset"))
		return (1);
	if (!ft_strcmp(command->args[0], "env"))
		return (1);
	if (!ft_strcmp(command->args[0], "exit"))
		return (1);
	else 
		return (0);
}

void ft_builtin(t_command *command, t_tools *tools)
{
	if (!ft_strcmp(command->args[0], "env"))
		ft_env(command, tools);
	if (!ft_strcmp(command->args[0], "pwd"))
		ft_pwd(tools);
	if (!ft_strcmp(command->args[0], "echo"))
		ft_echo(command);
	if (!ft_strcmp(command->args[0], "exit"))
		ft_exit(tools);
	if (!ft_strcmp(command->args[0], "export"))
		ft_export(command, tools);
	if (!ft_strcmp(command->args[0], "unset"))
		ft_unset(command, tools);
	 if (!ft_strcmp(command->args[0], "cd"))
	 	ft_cd(command, tools);
}
