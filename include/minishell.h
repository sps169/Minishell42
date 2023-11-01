/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:45:35 by migonzal          #+#    #+#             */
/*   Updated: 2023/11/01 19:34:00 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ui.h"
# include "executor.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_redir
{
	char				*cmd;
	char				**out;
	char				**in;

}	t_redir;

typedef struct s_sep
{
	char				*cmd_sep;
	struct s_sep		*prev;
	struct s_sep		*next;
	char				**args;
	char				**flags;
	t_redir				*redir;

}					t_sep;

typedef struct s_pip
{
	char				*cmd_pip;
	struct s_pip		*prev;
	struct s_pip		*next;
}					t_pip;



/*
 * Parser_cells
 */

t_sep		*create_cell(char *cmd_sep);
t_sep		*add_cell(t_sep *t_list, char *cmd_sep, int pos);
void		print_list(t_sep*list);

/*
 * Parser_pip
 */

t_pip		*create_pip_cell(char *cmd_pip);
t_pip		*add_pip_cell(t_pip *list, char *cmd_pip, int pos);
void		print_pip_list(t_pip *piplist);
int			pipeinstr(char c, char *str);
void		parse_pip(t_sep *list);

/*
 * cmd.c
 */

char *first_command(char *str);
int	ft_strlen_first_word(char *str);
char *arg_quote(char *str);

/*
 * split minishell
 */

void	*ft_free_matrix(char **mtx);
char **split_minishell(char *s, char z);
size_t count_tokens(char *s, char z);
char *cross_string(char *s, size_t *i, char z);
char *get_end_str(char *s, char c, size_t *len, int count, char z);
size_t count_string(char *s, char z);




/*
 * parse_utils
 */
char	*word_dup(char *str, int start, int finish);
char *word_dup_after(char *s, char c, int i);
char *word_dup_before(char *s, char c);
int	count_words(const char *str, char c);
char **list_dup_after(char* s, char c);
int dup_after_pos(char *s, char c, int num);
char **parse_args(char *s);

t_sep *parser(char *s);

#endif
