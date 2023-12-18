#include "minishell.h"

void print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}


int echo (t_tools *tools, t_sep *sep)
 {
 	int i;
 	int n_flag;

 	i = 1;
 	n_flag = 0;
 	(void) tools;

 	while (sep->args[i])
        {
          if (sep->args[1][0] == '-' && sep->args[1][1] == 'n') //TERRORISMO AQUI, NO OLVIDAR
              n_flag = 1;
          i++;
        }
        print_lines(i, sep->args, STDOUT_FILENO);
        if (n_flag == 1)
          ft_putchar_fd('\n', STDOUT_FILENO);
        return (EXIT_SUCCESS);
 }