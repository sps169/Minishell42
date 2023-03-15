/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:44:43 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/15 10:49:34 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdarg(t_copy *copy)
{
	int	i;

	i = 0;
	if (copy ->cmd)
		free(copy->cmd);
	if (copy->args)
	{
		while (copy->args[i])
		{
			free(copy->args[i]);
			i++;
		}
		free(copy->args);
	}
	if (copy->redir.out1)
		free(copy->redir.out1);
	if (copy->redir.out2)
		free(copy->redir.out2);
	if (copy->redir.in)
		free(copy->redir.in);
	copy->cmd = NULL;
	copy->args = NULL;
	copy->redir.out1 = NULL;
	copy->redir.out2 = NULL;
	copy->redir.in = NULL;
}

void	free_list_pip(t_pip *pipcell)
{
	t_pip	*tmp;

	if (pipcell == NULL)
		return ;
	while (pipcell)
	{
		if (pipcell->cmd_pip)
			free(pipcell->cmd_pip);
		tmp = pipcell;
		pipcell = pipcell->next;
		free(tmp);
	}
	pipcell = NULL;
}

void	free_list(t_sep *list)
{
	t_sep	*tmp;

	if (list == NULL)
		return ;
	while (list)
	{
		if (list->cmd_sep)
			free(list->cmd_sep);
		free_list_pip(list->pipcell);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	list = NULL;
}
