/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:25:18 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/19 12:36:05 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	locate_redir(char *redir, int *i)
{
	char	quote;
	int		type;

	quote = 0;
	type = -1;
	while (redir[*i] && type == -1)
	{
		if (quote == '"' || quote == '\'')
		{
			if (redir[*i] == quote)
				quote = 0;
		}
		else
		{
			if (redir[*i] == '"' || redir[*i] == '\'')
				quote = redir[*i];
			else
			{
				if (redir[*i] == '>' && redir[*i + 1] && redir[*i + 1] == '>')
				{
					*i = *i + 1;
					type = 3;
				}
				else if (redir[*i] == '>')
					type = 1;
				else if (redir[*i] == '<' && redir[*i + 1] && redir[*i + 1] == '<')
				{
					*i = *i + 1;
					type = 2;
				}
				else if (redir[*i] == '<')
					type = 0;
			}
		}
		*i = *i + 1;
	}
	return (type);
}

static char	*locate_redir_file(char *redir, int *i, int *status)
{
	char	quote;
	char	*word_start;
	char	*file;
	size_t	length;

	quote = 0;
	word_start = NULL;
	length = 0;
	file = NULL;
	while(redir[*i] && (redir[*i] == ' ' || redir[*i] == '\t' || redir[*i] == '\n'))
		*i = *i + 1;
	if (redir[*i] && (redir[*i] == '\\' || redir[*i] == '<' || redir[*i] == '>'))
	{
		*status = -1;
		return (NULL);
	}
	word_start = redir + *i;
	while (redir[*i] && word_start)
	{
		if (quote == '"' || quote == '\'')
		{
			if (redir[*i] == quote)
			{
				*i = *i + 1;
				length++;
				break;
			}
		}
		else
		{
			if (redir[*i] == '"' || redir[*i] == '\'')
			{
				if (word_start == NULL)
					word_start = redir + *i;
				quote = redir[*i];
			}
			else
			{
				if (redir[*i] == ' ' || redir[*i] == '\t' || redir[*i] == '\n' || redir[*i] == '<' || redir[*i] == '>')
					break;
			}
		}
		length++;
		*i = *i + 1;
	}
	if (length == 0)
	{
		*status = -1;
		return (NULL);
	}
	file = ft_calloc(1, sizeof(char) * length + 1);
	if (!file)
	{
		*status = -1;
		return (NULL);
	}
	if (ft_strlcpy(file, word_start, length + 1) < length)
	{
		free(file);
		*status = -1;
		return (NULL);
	}
	return (file);
}

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
	while (redir) {
		next = redir;
		free(next->file);
		redir = next->next;
		free(next);
	}
}

t_redir *create_redir_list(char *redir, int *status)
{
	int		type;
	int		i;
	char	*file;
	t_redir	*curr;
	t_redir	*first;
	t_redir	*aux;

	curr = NULL;
	first = NULL;
	aux = NULL;
	file = NULL;
	i = 0;
	type = -1;
	while (redir[i])
	{
		type = locate_redir(redir, &i);
		if (type == -1)
			return (first);
		file = locate_redir_file(redir, &i, status);
		if (!file)
		{
			cleanse_redir_list(first);
			return (NULL);
		}
		aux = create_redir_node(file, type, status);
		if (!aux)
		{
			cleanse_redir_list(first);
			return (NULL);
		}
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

t_command	*add_cell(t_command *list, char *cmd_sep, int pos)
{
	t_command	*cur;
	t_command	*cell;
	int		i;

	cur = list;
	i = 0;
	cell = create_cell(cmd_sep);
	if (list == NULL)
		return (cell);
	while (i < pos)
	{
		i++;
		cur = cur->next;
	}
	cell->next = cur;
	return (list);
}

void	print_list(t_command *list)
{
	int	i;
	t_redir *curr;

	i = 0;
	int j = 0;
	curr = NULL;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", list->cmd_sep);
		j = 0;
		while(list->args[j])
		{
			printf("| list->args : %s            \n", list->args[j]);
			j++;
		}
		curr = list->redir;
		while(curr)
		{
			printf("| list->redir->file : \"%s\"          \n", curr->file);
			printf("| list->redir->type : %i          \n", curr->type);
			curr = curr->next;
		}
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}
