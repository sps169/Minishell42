#include "minishell.h"

// void print_lines(int i, char **str, int out)
// {
// 	while (str[i])
// 	{
// 		ft_putstr_fd(str[i++], out);
// 		if (str[i])
// 			ft_putchar_fd(' ', out);
// 	}
// }


// int ft_echo (t_tools *tools)
//  {
//  	int i;
// 	int j;
//  	int n_flag;

//  	i = 1;
// 	j = 0;
//  	n_flag = 0;
//  	(void) tools;

//  	while (tools->command->args[i] && tools->command->args[i][0] == '-'
// 		&& tools->command->args[i][1] == 'n')
//         {
// 			j = 1;
// 			while (tools->command->args[i][j] == 'n')
// 				j++;
// 			if (tools->command->args[i][j] == '\0')
// 				n_flag = 1;
// 			else
// 				break;
// 			i++;
//         }

//         print_lines(i, tools->command->args, STDOUT_FILENO);
//         if (n_flag == 0)
//           ft_putchar_fd('\n', STDOUT_FILENO);
//         return (EXIT_SUCCESS);
//  }


int ft_echo(t_command *command)
{
	int	i;
//	int	n_flag;

	i = 1;
//	n_flag = 0;

	if (command->args[1] && !ft_strncmp(command->args[1], "-n", 2))
		i++;
	while (command->args[i])
	{
		ft_putstr_fd(command->args[i++], STDOUT_FILENO);
		if (command->args[i])
			ft_putchar_fd(32, STDOUT_FILENO);
	}
	if (!(command->args[1] && !ft_strncmp(command->args[1], "-n", 2)))
		ft_putchar_fd(10, STDOUT_FILENO);

	return (EXIT_SUCCESS);
}
