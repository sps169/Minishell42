/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:44:26 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:06:34 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_envp_entries(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	is_matching_variable(char *env_entry, char *name, int len)
{
	return (ft_strncmp(env_entry, name, len) == 0 && env_entry[len] == '=');
}

static void	unset_variable(t_tools *tools, char *name)
{
	int		i;
	int		j;
	int		len;
	char	**new_envp;

	len = ft_strlen(name);
	i = count_envp_entries(tools->envp);
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return ;
	i = 0;
	j = 0;
	while (tools->envp[i])
	{
		if (!is_matching_variable(tools->envp[i], name, len))
			new_envp[j++] = tools->envp[i];
		else
			free(tools->envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	free(tools->envp);
	tools->envp = new_envp;
}

void	ft_unset(t_tools *tools)
{
	int	i;

	i = 0;
	if (!tools->command->args[i])
		return ;
	tools->exit_status = 0;
	while (tools->command->args[i])
	{
		unset_variable(tools, tools->command->args[i]);
		i++;
	}
}
