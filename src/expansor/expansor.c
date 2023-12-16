# include "minishell.h"




char *expansor(t_tools *tools, char *str)
{
	char *aux;

	//aux = NULL;
	

	//if (str[dollar_after(str) -2] != '\'' && dollar_after(str) != 0
	//	&& str[dollar_after(str)] != '\0')
		//{
			aux = detect_dollar(tools, str);
			free(str);
			str = aux;
		//}
	//	str = delete_quotes(str, '\"');
	//	str = delete_quotes(str, '\'');

		return (str);
}


char *detect_dollar(t_tools *tools, char *str)
{
	int		i;
	char	*aux;
	char	*aux2;
	char	*aux3;

	i = 0;
	aux = ft_strdup("\0");
	while(str[i])
	{
		i += digit_after_dollar(i, str);
                if (str[i] == '$' && str[i + 1] == '?')
                    return (0);
                else if (str[i] == '$' && (str[i + 1] != ' ' &&
                        (str[i + 1] != '"' || str[i + 2] != '\0')) &&
                        str[i + 1] != '\0')
						{
                  			i += loop_dollar(tools, str, &aux, i);
						}
                else 
                {
                  aux2 = char_to_str(str[i++]);
                  aux3 = ft_strjoin(aux, aux2);
                  free(aux);
                  aux = aux3;
                  free(aux2);
                }
                  
              
	}
        return (aux);

}


int loop_dollar(t_tools *tools, char *str, char **aux, int j)
{
  int i;
  int res;
  char *aux2;
  char *aux3;

  i = 0;
  res = 0;
  while (tools-> envp[i])
  {
    if (ft_strncmp(str + j+ 1, tools->envp[i],
		equal_after(tools->envp[i]) -1) == 0 
		&& after_dollar_lenght(str, j) - j == (int) equal_after(tools->envp[i]))
	{
		aux2 = ft_strdup(tools->envp[i] + equal_after(tools->envp[i]));
		aux3 = ft_strjoin(*aux, aux2);
		free(*aux);
		*aux = aux3;
		free(aux2);
		res = equal_after(tools->envp[i]);
	}
	i++;
  }
  if (res == 0)
	res = after_dollar_lenght(str, j) -j;
return (res);
}



