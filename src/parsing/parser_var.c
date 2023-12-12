#include "minishell.h"



char *get_right_str(char *str)
{
    char *res;
    int i = 0;
    int pos = get_char_pos(str, '=');
    int lon_str = ft_strlen(str);
    int lon = ft_strlen(str) - pos;

    res = ft_calloc(lon, sizeof(char));
    i = pos+1;
    int j = 0;
    while (i < lon_str)
    {
        res[j] = str[i];
        i++;
        j++;
    }
    res[i] = '\0';
    return (res);
}

char *get_left_str(char *str)
{
    char *res;
    int i;
    int pos;

    pos = get_char_pos(str, '=');
    res = ft_calloc(pos, sizeof(char));
    i = 0;

    while(i < pos)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);

}


int get_char_pos(char *s, char c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (i);

        i++;
    }   
    return (0);
}


int if_var(char *str)
{
    char *aux;
    int len;

    len = ft_strlen(str);

    aux = ft_strchr(str, '=');

    if (aux != NULL && (aux == str || str[0] != '\"' || str[len-1] != '\"'))
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int if_ass_str(char **table)
{
    int i;


    i = 0;

    while(table[i])
    {
        if (if_var(table[i]))
            i++;
        else
            return(0);
    }
    return (1);
}







