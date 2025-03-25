#include "minishell.h"




static void	print_env(t_tools *tools)
{
	int i = 0;

	while (tools->envp[i])
	{
		printf("%s\n", tools->envp[i]);
		i++;
	}
}


void	add_or_update_env(t_tools *tools, char *var)
{
	char *name = get_env_name(var);
	char *value = get_env_value(var);
	int i = 0;

	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], name, ft_strlen(name)) == 0 && tools->envp[i][ft_strlen(name)] == '=')
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strjoin(name, "=");
			tools->envp[i] = ft_strjoin(tools->envp[i], value);
			free(name);
			free(value);
			return;
		}
		i++;
	}

	tools->envp = realloc(tools->envp, (i + 2) * sizeof(char *));
	tools->envp[i] = ft_strjoin(name, "=");
	tools->envp[i] = ft_strjoin(tools->envp[i], value);
	tools->envp[i + 1] = NULL;
	free(name);
	free(value);
}

void	ft_export(t_tools *tools)
{
	int	i;

	tools->exit_status = 0;

	if (tools->command->args[1] == NULL)
	{
		print_env(tools);
	}
	else
	{
		i = 1; // Iniciar en 1 para omitir el nombre del comando
		while (tools->command->args[i])
		{
			add_or_update_env(tools, tools->command->args[i]);
			i++;
		}
	}
}
