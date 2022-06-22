/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjirapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:39:51 by yjirapin          #+#    #+#             */
/*   Updated: 2022/06/22 15:27:20 by yjirapin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* This function returns the size of str */
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
The ft_strchr() function returns a pointer to the first occurrence
 of the character c in the string s.
*/
char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
/* The function ft_strjoin is actually a helper function
where memory is first allocated to the
static variable mainman if mainman is empty.
It is also where the mainman variable is swapped out
with a memory-allocated str variable. (The original mainman
is freed then the str variable is returedd as a longer
string called mainman)
*/

char	*ft_strjoin(char *mainman, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!mainman)
	{
		mainman = (char *)malloc(1 * sizeof(char));
		mainman[0] = '\0';
	}
	if (!mainman || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(mainman) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (mainman)
		while (mainman[++i] != '\0')
			str[i] = mainman[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(mainman) + ft_strlen(buff)] = '\0';
	free(mainman);
	return (str);
}
/*****************************
The function ft_getmyline takes the
static variable mainman as input
and returns a string to be put into
the variable line.
1) If mainman's first char is NULL then,
return the string NULL.
2) If each character in mainman is not null or
a new line character then count i.
3) i is now the number of characters in mainman
excluding the newline.
4) So now we know what the value of i is.
Let's set up the str variable (allocating memory)
to be 2 bytes larger than i to accomodate i = 0 and
the newline character.
5) Quit if you can't get enough memory
	allocated.
6) mainman value is put into str variable.
7)	For the last character of mainman check if it is a new line.
	If it is a newline, then put the newline into str and
	increment i as well. Finally, set the last character
	to \0 and return str. Note that str memory (or line)
	is not yet free. It can't be free because line is
	needed as the return varilable.
*/
char	*ft_getme_myline(char *mainman)
{
	int		i;
	char	*str;

	i = 0;
	if (!mainman[i])
		return (NULL);
	while (mainman[i] && mainman[i] != '\n')
		i++;

	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (mainman[i] && mainman[i] != '\n')
	{
		str[i] = mainman[i];
		i++;
	}
	if (mainman[i] == '\n')
	{
		str[i] = mainman[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* The function ft_new_mainman takes mainman as input
and free it before returning a NULL or a string.
Without this function, there will be memory leaks.
1) Starting with i = 0, find the i where there is
 a newline or null. i is now the length of mainman.
2) If the last char of mainman is null,
 then just free mainman and return.
YYY
3) If the last char of mainman is newline,
 then there is more work to do.
4) If mainman length is more than i then, there
is a part of the text beyond the newline. This part
will need to be kept in str (which will require memory).
5) The memory allocated to str is, therefore,
char size x ft_strlen(mainman) - i + 1.
6) Increment i by 1. This is the position of first character
in mainman which follows the newline.
7) Using j as index (starting with 0), str is populated
with the rest of mainman followed by \0.
8) The used mainman is finally free (not needed anymore).
9) str is returned (as the new mainman actually)
*/
char	*ft_new_mainman(char *mainman)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (mainman[i] && mainman[i] != '\n')
		i++;
	if (!mainman[i])
	{
		free(mainman);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(mainman) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (mainman[i])
		str[j++] = mainman[i++];
	str[j] = '\0';
	free(mainman);
	return (str);
}
