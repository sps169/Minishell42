#include "minishell.h"



static void	unset_variable(t_tools *tools, char *name)
{
	int i = 0;
	int j = 0;
	int len = ft_strlen(name);
	char **new_envp;

	while (tools->envp[i])
		i++;

	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return;

	i = 0;
	while (tools->envp[i])
	{
		if (!(ft_strncmp(tools->envp[i], name, len) == 0 && tools->envp[i][len] == '='))
		{
			new_envp[j] = tools->envp[i];
			j++;
		}
		else
		{
			free(tools->envp[i]);
		}
		i++;
	}
	new_envp[j] = NULL;

	free(tools->envp);
	tools->envp = new_envp;
}

void	ft_unset(t_tools *tools)
{
	int i = 1; 

	if (!tools->command->args[i])
		return;

	tools->exit_status = 0;

	while (tools->command->args[i])
	{
		unset_variable(tools, tools->command->args[i]);
		i++;
	}
}