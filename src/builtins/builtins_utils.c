#include "minishell.h"


void ft_free_list(t_env **list)
{
	t_env *tmp;

	while(*list)
	{
		tmp = (*list)->next;
		ft_memfree((*list)->var_name);
		ft_memfree((*list)->value_var);
		ft_memfree(*list);
		*list = tmp;
	}
	*list = NULL;
}

void change_path(t_tools *tools)
{
	char *aux;

	aux = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = aux;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
}

int check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~' || c == '=' || c == '-' || c == '?' || c == '&'
		|| c == '*');
}
