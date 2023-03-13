/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:44:37 by migonzal          #+#    #+#             */
/*   Updated: 2023/03/02 10:00:15 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
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


/*
 * Variables globales
 */
char	**g_envs;
pid_t	g_pid;
int		g_error;
int		g_status;
int		g_tester;




/*
 * Estructuras
 */

typedef struct s_sep
{
	char				*cmd_sep;
	struct s_sep		*prev;
	struct s_sep		*next;
	struct s_pip		*pipcell;
}					t_sep;

typedef struct s_pip
{
	char				*cmd_pip;
	struct s_pip		*prev;
	struct s_pip		*next;
}					t_pip;

typedef struct s_redir
{
	char			*out1;
	char			*out2;
	char			*in;
	int				sstdout;
	int				sstderr;
	int				sstdin;
	int				end;
	int				i;
	char			*name;
	char			*value;
}				t_redir;

typedef struct s_copy
{
	t_sep		*list;
	char		**cmd_sep;
	char		*wc;
	char		**args;
	char		*cmd;
	int			i;
	int			j;
	t_redir		redir;
	char		**tmp;
	char		*arg;
}				t_copy;

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
 * free_parsing
 */

void		free_cmdarg(t_copy *copy);
void		free_list_pip(t_pip *pipcell);
void		free_list(t_sep *list);

/*
 *	args.c
 */

int			init_malloc_args(t_copy *copy, size_t i);
int			args_quoting(t_copy *copy, int j, size_t i);
int			args_redir_env(t_copy *copy, int j, size_t i);
void		copy_arg(t_copy *copy, size_t i, int j);
char		*args(t_copy *copy, size_t i, int j);

/*
 * cmd.c
 */
int			init_value_name(t_copy *copy);
int			cmd_quoting(t_copy *copy, int j);
int			cmd_redir_env(t_copy *copy, int j);
char		*cmd(t_copy *copy, int j);
char		*parsing(char *whole_cmd, t_copy *copy);

/*
 * d_quote.c
 */

int			d_quote(t_copy *copy, int j);
int			quote_util(t_copy *copy, int j, size_t i);
int			d_quote_arg(t_copy *copy, size_t i, int j);
int			quote_util_redir(t_copy *copy, char *str, int std, int j);
int			d_quote_redir(t_copy *copy, char *str, int std);

/*
 * error.c
 */
int			ft_error_token(char *msg, char c, int i, char *str);
int			error_msg(char *str, int i, char c);
int			error_exit(char *str, char *msg);
void		error_ambiguous(char *name);

/*
 * options.c
 */
int			options_special_case(char *arg, t_copy *copy);
void		ft_copy_tmp(t_copy *copy, char **tmp, size_t j);
int			init_options_after(t_copy *copy, size_t i);
int			init_options_before(t_copy *copy, int j, int i);
int			options(t_copy *copy, size_t i, size_t j);

/*
 * redir.out.c
 */
void		redir_in_util(t_copy *copy, int i);
int			redir_quoting(t_copy *copy, int i, char *file);
int			redir_out_error(t_copy *copy, int i);
int			redir_out(t_copy *copy, int i);

/*
 * redir.c
 */
int			create_file_out2(t_copy *copy);
int			create_file_in(t_copy *copy);
int			create_file(t_copy *copy, int type);
int			redir_in(t_copy *copy, int i);
int			redirection(t_copy *copy, int i);

/*
 * s_quote.c
 */
int			quote_error(char c);
int			s_quote(t_copy *copy);
int			s_quote_arg(t_copy *copy, size_t i);
int			s_quote_redir(t_copy *copy, char *str);

/*
 * syntax_error.c
 */
int			inside_quote(char *str, int i);
int			syntax_error_redir(char *str, char c);
int			syntax_error_newline(char *str);
int			syntax_error_go(char *str, int i, char c);
int			syntax_error(char *str, char c, int i);

/*
 *varenv_utils.c
 */
char		*remalloc_cmdargs(t_copy *copy, char *value, char *str);
char		*remalloc_redir(t_copy *copy, char *value, char *str);
void		env_copy(t_copy *copy, int arg, int i, char *value);
int			status_env(t_copy *copy, int arg, int i);
int			no_value(t_copy *copy, char *value);

/*
 * varenv.c
 */
int			multiple_dollars(t_copy *copy, int arg, int i);
int			find_name(t_copy *copy, int i, char **name);
int			env(t_copy *copy, int arg, int i, int space);
void		env_redir_ambig(t_copy *copy, int space);
int			env_redir(t_copy *copy, int std, int spce);

#endif // !MINISHELL_H
