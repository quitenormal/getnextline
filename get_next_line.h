/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjirapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:05:46 by yjirapin          #+#    #+#             */
/*   Updated: 2022/06/22 16:13:12 by yjirapin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*ft_read4myman(int fd, char *mainman);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *mainman, char *buff);
size_t	ft_strlen(char *s);
char	*ft_getme_myline(char *mainman);
char	*ft_new_mainman(char *mainman);

#endif
