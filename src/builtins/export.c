/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:25:21 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:06:07 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		printf("%s\n", tools->envp[i]);
		i++;
	}
}

static void	update_existing_env(char **envp, int i, char *name, char *value)
{
	free(envp[i]);
	envp[i] = ft_strjoin(name, "=");
	envp[i] = ft_strjoin(envp[i], value);
}

static void	add_new_env_entry(t_tools *tools, int i, char *name, char *value)
{
	tools->envp = realloc(tools->envp, (i + 2) * sizeof(char *));
	tools->envp[i] = ft_strjoin(name, "=");
	tools->envp[i] = ft_strjoin(tools->envp[i], value);
	tools->envp[i + 1] = NULL;
}

void	add_or_update_env(t_tools *tools, char *var)
{
	char	*name;
	char	*value;
	int		i;

	name = get_env_name(var);
	value = get_env_value(var);
	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], name, ft_strlen(name)) == 0
			&& tools->envp[i][ft_strlen(name)] == '=')
		{
			update_existing_env(tools->envp, i, name, value);
			free(name);
			free(value);
			return ;
		}
		i++;
	}
	add_new_env_entry(tools, i, name, value);
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
		i = 1;
		while (tools->command->args[i])
		{
			add_or_update_env(tools, tools->command->args[i]);
			i++;
		}
	}
}
