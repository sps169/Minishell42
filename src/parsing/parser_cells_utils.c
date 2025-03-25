/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cells_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:05:15 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 16:32:15 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_node(char *file, int type, int *status)
{
	t_redir	*node;

	node = NULL;
	node = malloc(sizeof(t_redir));
	if (!node)
	{
		free(file);
		*status = -1;
		return (NULL);
	}
	node->file = NULL;
	node->fd = -1;
	node->type = -1;
	node->next = NULL;
	node->file = file;
	node->type = type;
	return (node);
}

void	cleanse_redir_list(t_redir *redir)
{
	t_redir	*next;

	if (!redir)
		return ;
	while (redir)
	{
		next = redir;
		free(next->file);
		redir = next->next;
		free(next);
	}
}

t_command	*create_cell(char *cmd_sep)
{
	t_command	*cell;
	int			status;

	status = 0;
	cell = malloc(sizeof(t_command));
	if (!cell)
		return (NULL);
	cell -> next = NULL;
	cell -> args = parse_args(cmd_sep);
	cell -> redir = create_redir_list(cmd_sep, &status);
	cell -> cmd_sep = cmd_sep;
	if (status == -1)
	{
		//free things ()
		return (NULL);
	}
	return (cell);
}

t_command	*add_cell(t_command *list, char *cmd_sep)
{
	t_command	*cur;
	t_command	*cell;

	cur = list;
	cell = create_cell(cmd_sep);
	if (list == NULL)
		return (cell);
	while (cur->next)
		cur = cur->next;
	cur->next = cell;
	return (list);
}






