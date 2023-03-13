#include <stdio.h>
#include <stdlib.h>

int ft_isdigit(int c);

int ft_atoi(const char *str)
{
	int i;
	int s;
	int res;


	i = 0;
	s = 1;
	res = 0;
	
		if (str[0] == '-')
		{
			s *= -1;
			i++;
		}

	while (str[i] != '\0' && ft_isdigit(str[i]))
//	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res *s);
}


