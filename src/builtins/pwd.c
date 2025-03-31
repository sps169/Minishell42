#include "minishell.h"

void ft_pwd(t_tools *tools) 
{
	char *pwd;

	tools->exit_status = 0;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	ft_memfree(pwd);
}