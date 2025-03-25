/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:38:01 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:03:28 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_comprobation(t_tools *tools)
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

void	ft_builtin(t_tools *tools)
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
