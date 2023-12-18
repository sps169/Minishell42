/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:25:18 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/18 02:09:40 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	locate_redir(char **redir, int *type) {
	char	quote;

	quote = 0;
	while (**redir)
	{
		if (quote == '"' || quote == '\'')
		{
			if (**redir == quote)
				quote = 0;
		}
		else
		{
			if (**redir == '"' || **redir == '\'')
				quote = **redir;
			else
			{
				if (**redir == '>' && **redir + 1 && **redir + 1 == '>')
				{
					**redir++;
					*type = 3;
					break;
				}
				else if (**redir == '>')
				{
					*type = 1;
					break;
				}
				if (**redir == '<' && **redir + 1 && **redir + 1 == '<')
				{
					**redir++;
					*type = 2;
					break;
				}
				else if (**redir == '<')
					*type = 0;
					break;
			}
		}
		**redir++;
	}
	return (quote == 0);
}

t_redir *create_redir_list(char *redir)
{
	//< > << >> or error
	//search_icon, analize_icon, search_arg, analize_arg
	int		type;
	char	*file;
	t_redir	*curr;
	t_redir	*first;
	t_redir	*aux;

	curr = NULL;
	first = NULL;
	aux = NULL;
	while (redir)
	{
		if (!locate_redir(&redir, &type))
			return (NULL);
		file = !locate_redir_file(&redir);
		if (!file)
			return (NULL);
		aux = create_redir_node(file, type);
		if (!first)
		{
			first = aux;
			curr = aux;
		}
		else
		{
			curr->next = aux;
			curr = curr->next;
		}
	}
	return (first);
}

t_command	*create_cell(char *cmd_sep)
{
	t_command	*cell;

	cell = malloc(sizeof(t_command));
	if (!cell)
		return (NULL);
	cell -> next = NULL;
	cell -> args = parse_args(cmd_sep);
	cell -> redir = create_redir_list(cmd_sep);
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
	cell->prev = prec;
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
	//	while(list->flags[j])
	//	{
	//		printf("| list->flags : %s            \n", list->flags[j]);
	//		j++;
	//	}
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
