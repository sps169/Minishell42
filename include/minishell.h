/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:45:35 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/16 18:54:51 by sperez-s         ###   ########.fr       */
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
	char			*file;
	int				type; //0 in 1 out 2 heredoc 3 append
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				*cmd_sep;
	struct s_sep		*next;
	char				**args;
	t_redir				*redir;
	int					return_val;

}					t_command;

typedef struct s_pip
{
	char				*cmd_pip;
	struct s_pip		*prev;
	struct s_pip		*next;
}					t_pip;

typedef struct s_tools
{
	char	**paths;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
}					t_tools;

/*
 * Parser_cells
 */

t_command		*create_cell(char *cmd_sep);
t_command		*add_cell(t_command *t_list, char *cmd_sep, int pos);
void		print_list(t_command *list);

/*
 * Parser_pip
 */

t_pip		*create_pip_cell(char *cmd_pip);
t_pip		*add_pip_cell(t_pip *list, char *cmd_pip, int pos);
void		print_pip_list(t_pip *piplist);
int			pipeinstr(char c, char *str);
void		parse_pip(t_command *list);

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
void ft_free_arr(char **arr);
char **arrdup(char **arr);

t_command *parser(char *s);

/*
 * parse_envp
 */
 int     find_pwd(t_tools *tools);
 char *find_path(char **envp);
 int parse_envp(t_tools *t_tools);

 /*
  *  parser_var
  */
int     get_char_pos(char *s, char c);
char	*get_left_str(char *str);
char	*get_right_str(char *str);
int 	if_var(char *str);
int 	if_ass_str(char **table);

/*
 * quotes_aux.c
 */

 size_t quotes_lenght(char *str);
 char    *delete_quotes(char *str, char c);


/*
 *	expansor.c
 */
char *detect_dollar(t_tools *tools, char *str);


/*
 *	expansor_utils.c
 */
size_t dollar_after(char *str);
char *char_to_str(char c);
int digit_after_dollar(int j, char *str);



#endif
