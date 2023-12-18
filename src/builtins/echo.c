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
	int j;
 	int n_flag;

 	i = 1;
	j = 0;
 	n_flag = 0;
 	(void) tools;

 	while (sep->args[i] && sep->args[i][0] == '-'
		&& sep->args[i][1] == 'n')
        {
			j = 1;
			while (sep->args[i][j] == 'n')
				j++;
			if (sep->args[i][j] == '\0')
				n_flag = 1;
			else
				break;
			i++;
        }

        print_lines(i, sep->args, STDOUT_FILENO);
        if (n_flag == 0)
          ft_putchar_fd('\n', STDOUT_FILENO);
        return (EXIT_SUCCESS);
 }