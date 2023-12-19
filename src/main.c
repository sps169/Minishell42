/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:42:59 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/19 12:42:47 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int set_built(t_sep *sep)
// {
// 	static void *arr_built[6][2] = {

	
// 	{"echo", echo},
// 	{"cd", cd},
// 	{"pwd", pwd},
// 	{"export", export},
// 	{"unset", unset},
// 	{"env", env},
// 	};
// 	int i;
// 	i = 0;

// 	while (i < 6)
// 	{
// 		if (sep->args[0])
// 		{
// 			if (!ft_strncmp(arr_built[i][0], sep->args[0], ft_strlen((arr_built[i][0]))))
// 				return (int)(arr_built[i][1]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int init_tools(t_tools *tools)
// {
// 	tools->arg_str = NULL;
// 	tools->reset = 0;
// 	tools->sep = NULL;
// 	parse_envp(tools);

// }

// int minishell_loop(t_tools *tools)
// {
// 	char *aux;

// 	tools->arg_str = readline("MINISHEL$");
// 	aux = ft_strtrim(tools->arg_str, " ");
// 	free(tools->arg_str);
// 	if (!tools->arg_str)
// 	{
// 		ft_putendl_fd("exit", STDOUT_FILENO);
// 		exit(EXIT_SUCCESS);
// 	}
// 	if (tools->arg_str[0] == '\0')
// 		return (reset_tools(tools)); //HACER FUNCION
// 	add_history(tools->arg_str);
// 	if (!count_quotes(tools->arg_str))
// 		return (ft_error()); // HACER FUNCION
// 	tools->sep = parser(tools->arg_str);
// 	//ENCHUFAR EXECUTOR

// }





int	main(int argc, char **argv, char **envp)
{
	t_tools *tools = (t_tools *)ft_calloc(1, sizeof(t_tools));
	t_command *sep;


	if (argc != 1 || argv[1])
	{
		printf("Este programa no acepta argumentos inútil\n");
		exit(0);
    }
	tools->envp = arrdup(envp);
	find_pwd(tools);
	char *str ="echo -n buenas tardes caballero";
	sep = parser(str);
	
	echo(tools, sep);
	

	// printf("Actual PWD: %s\n", tools->pwd);
	// printf("Old PWD: %s\n", tools->old_pwd);

	

	 //print_list(sep);


	


	return (0);
}
//char *expansor(t_tools *tools, char *str)
