#include "minishell.h"


int env(t_tools *tools)
{
    int i;

    i = 0;
    while (tools->envp[i])
    {
        ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}