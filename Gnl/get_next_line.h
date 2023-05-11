/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:01:40 by migonzal          #+#    #+#             */
/*   Updated: 2023/04/13 09:47:41 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define FD_SIZE 1024

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

//int		ft_strlen(char *s);
int		ft_search(char *s, int c);
//char	*ft_strdup(char *s);
//char	*ft_strjoin(char *s1, char *s2);
//char	*ft_substr(char *s, int start, int len);
char	*get_next_line(int fd);

#endif
