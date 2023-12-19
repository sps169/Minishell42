#include "minishell.h"




int (*builting_arr(char *str))(t_tools *tools)
{
	static void *builtins[7][2] =  {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"export", export},
	{"unset", unset},
	{"env", env},
	{"exit", ft_exit},
	};
	int	i;

	i = 0;
	while (i<7)
	{
		if (str)
		{
			if(!ft_strncmp(builtins[i][0], str, ft_strlen(builtins[i][0])))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}