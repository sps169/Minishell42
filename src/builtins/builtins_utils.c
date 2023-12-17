#include "minishell.h"

void change_path(t_tools *tools)
{
	char *aux;

	aux = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = aux;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
}