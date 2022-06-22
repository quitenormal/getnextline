/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjirapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:13:03 by yjirapin          #+#    #+#             */
/*   Updated: 2022/06/22 20:46:07 by yjirapin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

/*ft_read4myman is a function that takes a file descriptor
and mainman as input and returns a string
1) Set up the buff variable to be of size BUFFER_SIZE + 1
using malloc. (+1 is for the ending /0)
Note that we check if memory allocation
is successful.
2) Starting out with read_bytes = 1 (just so that
it will enter the read while loop at least once)
3) ft_strchr is used to check if there a newline
in mainman. If there is not a newline in mainman or
if read_bytes is not 0 then we keep on going.
4) If there is no newline in mainman and the read_bytes isn't
zero, then the file is read into the variable buff.
5) Read quits if an error is encountered.
In other words, read returns -1 if there is an error in which case
	the buff variable is free and the execution
	is returned to the calling function.
6) After a successful read, the read_bytes is changed to the
number of bytes read into buff.
7) \0 is added to the end of the buff variable with
buff[read_bytes] = '\0';
8) Then mainman gets appended with the string in buff
using the str_join function.
9) Step 3 - 8 is repeated until mainman contains a newline
or until read_bytes = 0 (which means that we're at the
end of the file).
10) memory for buff variable is freed and mainman is returned.
Note that mainman is a static variable so it
doesn't get reset.
*/

char	*ft_read4myman(int fd, char *mainman)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(mainman, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		mainman = ft_strjoin(mainman, buff);
	}
	free(buff);
	return (mainman);
}
/* ---------------------------------------
The function get_next_line takes only the file descriptor
as an input and returns a string which is the "next line
of text in that file".
1) If fd is less than zero
or if buffer size is 0 or smaller
then 0 is returned
2) Using a static variable mainman that doesn't get reset
 (sort of like a global variable
except that it's not), the mainman is a series of buffer
sized string appended together until a new line is found.
3) The function read4myman is used to
read the file and put a string into a variable.
The static variable mainman is passed into this function
and ask it to put the values return into the same static
variable.
4) line variable is the value of mainman up to the newline
character.
5) The static varilable mainman is stripped off the first
part up to the first newline character and returned
as the remaining part. */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*mainman;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	mainman = ft_read4myman(fd, mainman);
	if (!mainman)
		return (NULL);
	line = ft_getme_myline(mainman);
	mainman = ft_new_mainman(mainman);
	return (line);
}

/*
int	main(void) {
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("testme1.txt", O_RDONLY);
	fd2 = open("testme2.txt", O_RDONLY);
	fd3 = open("testme3.txt", O_RDONLY);
	i = 1;
	while (i < 7){
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
	//	line = get_next_line(fd2);
	//	printf("line [%02d]: %s", i, line);
	//	free(line);
	//	line = get_next_line(fd3);
	//	printf("line [%02d]: %s", i, line);
	//	free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */
