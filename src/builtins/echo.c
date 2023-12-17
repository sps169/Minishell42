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


// int echo (t_tools *tools, t_sep *sep)
// {
// 	int i;
// 	int j;
// 	int n_flag;

// 	i = 1;
// 	n_flag = 0;
// 	(void) tools;

// 	while (sep->args[i] && sep->args[i][])
// }