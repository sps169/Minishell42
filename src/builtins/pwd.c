#include "minishell.h"


int pwd(t_tools *tools)
{
   ft_putendl_fd(tools->pwd, STDOUT_FILENO);
    return (0);
}