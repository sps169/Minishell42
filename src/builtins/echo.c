/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:39:54 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 18:05:37 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_tools *tools)
{
	int	i;

	i = 1;
	if (tools->command->args[1]
		&& !ft_strncmp(tools->command->args[1], "-n", 2))
		i++;
	while (tools->command->args[i])
	{
		ft_putstr_fd(tools->command->args[i++], STDOUT_FILENO);
		if (tools->command->args[i])
			ft_putchar_fd(32, STDOUT_FILENO);
	}
	if (!(tools->command->args[1]
			&& !ft_strncmp(tools->command->args[1], "-n", 2)))
		ft_putchar_fd(10, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
