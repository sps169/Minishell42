# include "minishell.h"


char *detect_dollar(t_tools *tools, char *str)
{
	int		i;
	char	*aux;
	char	*aux1;
	char	*aux2;

	i = 0;
	aux = ft_strdup("\0");
	while(str[i])
	{
		i += digit_after_dollar(i, str);
                if (str[i] == '$' && str[i + 1] == '?')
                    //j += funcion_interrogacion
                else if (str[i] == '$' && (str[i + 1] != ' ' &&
                        (str[i + 1] != '"' || str[i + 2] != '\0')) &&
                        str[i + 1] != '\0')
                 // j += funcion que maneja el expansor
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
    if (ft_strncmp(str + j))
  }
}



