/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:25:18 by migonzal          #+#    #+#             */
/*   Updated: 2023/05/08 14:03:41 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


t_redir *create_redir(char *redir)
{
	t_redir *cell;

	cell = malloc(sizeof(t_redir));
	if (!cell)
		return (NULL);
	cell -> in = list_dup_after(redir, '<');
	cell -> out = list_dup_after(redir, '>');
	cell -> cmd = redir;
	return (cell);
}

t_sep	*create_cell(char *cmd_sep)
{
	t_sep	*cell;

	cell = malloc(sizeof(t_sep));
	if (!cell)
		return (NULL);
	cell -> prev = NULL;
	cell -> next = NULL;
	cell -> args = parse_args(cmd_sep);
	cell -> flags = list_dup_after(cmd_sep, '-');
	cell -> redir = create_redir(cmd_sep);
	cell -> cmd_sep = cmd_sep;
	return (cell);
}

t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos)
{
	t_sep	*prec;
	t_sep	*cur;
	t_sep	*cell;
	int		i;

	cur = list;
	i = 0;
	cell = create_cell(cmd_sep);
	if (list == NULL)
		return (cell);
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (list);
}

void	print_list(t_sep *list)
{
	int	i;

	i = 0;
	int j = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", list->cmd_sep);
		while(list->args[j])
		{
			printf("| list->args : %s            \n", list->args[j]);
			j++;
		}
		j = 0;
		while(list->flags[j])
		{
			printf("| list->flags : %s            \n", list->flags[j]);
			j++;
		}
		j = 0;
		while(list->redir->in[j])
		{
			printf("| list->redir->in : %s            \n", list->redir->in[j]);
			j++;
		}
		j = 0;
		while(list->redir->out[j])
		{
			printf("| list->redir->out : %s            \n", list->redir->out[j]);
			j++;
		}
		j = 0;
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}
