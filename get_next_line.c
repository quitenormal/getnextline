/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjirapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:13:03 by yjirapin          #+#    #+#             */
/*   Updated: 2022/06/21 18:49:36 by yjirapin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Hello everyone. I am coding. Look ma */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

/* Set up the buffer to be of size BUFFER_SIZE
*/
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	/* Starting out with rd_bytes = 1 for every call*/
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		/* Here, we call the function read to get
		the buff variable populated. */
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		/*read returns -1 if there is an error so
		the buff variable is free and the execution
		is returned to the calling function.*/
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		/*add \0 to the end of each buff size str*/
		buff[rd_bytes] = '\0';
		/*take buff and append it to left_str*/
		left_str = ft_strjoin(left_str, buff);
		/*left_str is now old_left_str + buff plus \0*/
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;
/* check if fd is less than zero
or if buffer size is 0 or smaller */
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
/*Here, is a recursive function
left_str is recursively read until null is reached.
*/
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_getme_aline(left_str);
	left_str = ft_new_left_str(left_str);
	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("testme1.txt", O_RDONLY);
	fd2 = open("testme2.txt", O_RDONLY);
	fd3 = open("testme3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

