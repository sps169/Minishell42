/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cells_utils_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:11:18 by migonzal          #+#    #+#             */
/*   Updated: 2025/03/25 17:40:06 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_and_type(char *redir, int *i, char *quote, int *type)
{
	if (*quote == '"' || *quote == '\'')
	{
		if (redir[*i] == *quote)
			*quote = 0;
	}
	else
	{
		if (redir[*i] == '"' || redir[*i] == '\'')
			*quote = redir[*i];
		else
		{
			if (redir[*i] == '>' && redir[*i + 1] && redir[*i + 1] == '>')
			{
				*i = *i + 1;
				*type = 3;
			}
			else if (redir[*i] == '>')
				*type = 1;
			else if (redir[*i] == '<' && redir[*i + 1] && redir[*i + 1] == '<')
			{
				*i = *i + 1;
				*type = 2;
			}
			else if (redir[*i] == '<')
				*type = 0;
		}
	}
}

static t_redir	*process_redir(char *redir, int *i, int type, int *status)
{
	char	*file;
	t_redir	*node;

	file = locate_redir_file(redir, i, status);
	node = create_redir_node(file, type, status);
	if (!file)
		return (NULL);
	if (!node)
	{
		return (NULL);
	}
	return (node);
}


int	locate_redir(char *redir, int *i)
{
	char	quote;
	int		type;

	quote = 0;
	type = -1;

	while (redir[*i] && type == -1)
	{
		update_quote_and_type(redir, i, &quote, &type);
		*i = *i + 1;
	}
	return (type);
}



t_redir	*create_redir_list(char *redir, int *status)
{
	int		i;
	t_redir	*curr;
	t_redir	*first;
	int		type;
	t_redir	*node;

	i = 0;
	curr = NULL;
	first = NULL;

	while (redir[i])
	{
		type = locate_redir(redir, &i);
		if (type == -1)
			return (first);
		node = process_redir(redir, &i, type, status);
		if (!node)
		{
			cleanse_redir_list(first);
			return (NULL);
		}

		if (!first)
		{
			first = node;
			curr = node;
		}
		else
		{
			curr->next = node;
			curr = curr->next;
		}
	}
	return (first);
}