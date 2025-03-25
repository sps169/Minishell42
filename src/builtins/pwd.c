#include "minishell.h"


// int ft_pwd(t_tools *tools)
// {
//     (void) tools;
//     char * pwd;
//     pwd = getcwd(NULL, 0);
//     if (pwd == NULL)
//     {
//        perror("getcwd");
//        return (1);
//    }
//    ft_putendl_fd(pwd, STDOUT_FILENO);
//    free(pwd);
//    return (0);
// }

void ft_pwd(t_tools *tools) 
{
    char *pwd;

    tools->exit_status = 0;
    pwd = getcwd(NULL, 0);
    ft_putendl_fd(pwd, 1);
    ft_memfree(pwd);
}