/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:01:40 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/15 10:49:18 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_pip	*create_pip_cell(char *cmd_pip)
{
	t_pip	*cell;

	cell = malloc(sizeof(t_pip));
	if (!cell)
		return (NULL);
	cell->cmd_pip = NULL;
	cell->prev = NULL;
	cell->next = NULL;
	cell->cmd_pip = cmd_pip;
	return (cell);
}

t_pip	*add_pip_cell(t_pip *list, char *cmd_pip, int pos)
{
	t_pip	*prec;
	t_pip	*cur;
	t_pip	*cell;
	int		i;

	cur = list;
	i = 0;
	cell = create_pip_cell(cmd_pip);
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

void	print_pip_list(t_pip *piplist)
{
	int	i;

	i = 0;
	while (piplist)
	{
		printf("| piplist->cmd_pip : %s 	\n", piplist->cmd_pip);
		piplist = piplist->next;
		i++;
	}
}

int	pipeinstr(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = inside_quote(str, i);
		if (i == (int)ft_strlen(str))
			break ;
		if (str[i] && str[i] == '\\')
			i++;
		if (i == (int)ft_strlen(str))
			break ;
		if (str[i] && str[i] == c && str[i - 1] != '\\')
			return (i);
		i++;
	}
	return (-1);
}

void	parse_pip(t_sep *list)
{
	char	**cmds;
	t_sep	*cur;
	int		j;

	cur = list;
	j = -1;
	while (cur)
	{
		cmds = NULL;
		if ((pipeinstr('|', cur->cmd_sep)) > -1)
		{
			cmds = ft_split(cur->cmd_sep, '|'); //hay que tocar cositas en este split
			while (cmds[++j])
				cur->pipcell = add_pip_cell(cur->pipcell, cmds[j], j);
			if (cmds)
				free(cmds);
		}
		cur = cur->next;
	}
}
