#include "minishell.h"




// int builting_arr (t_tools *tools, t_sep *sep)
// {
// 	static void	*builtins[6][2] = {
// 	{"echo", echo},
// 	{"cd", cd},
// 	{"pwd", pwd},
// 	{"export", export},
// 	{"unset", unset},
// 	{"env", env},
// 	};

// 	int			i;


// 	i = 0;
// 	(void) tools;
// 	while (i < 6)
// 	{
// 		if (sep->args[0])
// 		{
// 			if (!ft_strncmp(builtins[i][0], sep->args[0], ft_strlen((builtins[i][0]))))
// 				return (builtins[i][1]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }