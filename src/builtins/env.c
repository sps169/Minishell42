#include "minishell.h"


int env(t_tools *tools, t_sep *sep)
{
    int i;

	(void) sep;
    i = 0;
    while (tools->envp[i])
    {
        ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}