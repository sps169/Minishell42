/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:39:29 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:03:44 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_change_oldpwd_env(t_tools *tools);
static void	ft_change_pwd_env(t_tools *tools);

void	ft_cd(t_tools *tools)
{
	char	*path;

	path = NULL;
	if (tools->command->args[1] && tools->command->args[2])
	{
		printf("cd: too many arguments\n");
		tools->exit_status = 1;
		return ;
	}
	ft_change_oldpwd_env(tools);
	if (tools->command->args[1])
		path = ft_strdup(tools->command->args[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
	{
		perror("cd");
		tools->exit_status = 1;
	}
	else
	{
		tools->exit_status = 0;
	}
	ft_memfree(path);
	ft_change_pwd_env(tools);
}

static void	ft_change_oldpwd_env(t_tools *tools)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("OLDPWD=", path);
	add_or_update_env(tools, to_send);
	ft_memfree(to_send);
	ft_memfree(path);
}

static void	ft_change_pwd_env(t_tools *tools)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("PWD=", path);
	add_or_update_env(tools, to_send);
	ft_memfree(to_send);
	ft_memfree(path);
}
