/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjirapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:39:51 by yjirapin          #+#    #+#             */
/*   Updated: 2022/06/22 19:17:32 by yjirapin         ###   ########.fr       */
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
 0 is returned if the str itself is empty or if a match
 is never found.
 If c is \0 then the address of the
 last character in str is returned which is &str[ft_strlen(str)].
 Otherwise, i is used as an index and each character is
 compared to c one-by-one until a match is found which
 will result in the address, &str[i], being returned.
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
is freed then the str variable is returned as a longer
string which is then called mainman)
The love story:
1) If mainman is empty, give mainman the memory size of
one char and put /0 in mainman.
2) If neither mainman nor buff is null, we are going to
need a bigger boat. The temp variable called str is used.
3) First we give str as much memory as needed which is
enough for a string length of mainman plus buff.
4) Now let's return str right into mainman.
I don't think we used mainman's staticness in this function.
But time will come when his royal staticness shall be
required.
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
The function ft_getme_myline takes the
static variable mainman as input
and returns a substring that ends
with a new line character.
1) If mainman's first char is NULL then,
return NULL.
2) Find out the length of the first substring that ends with
a newline character by walking through each character in mainman
which is not null until we find the first
new line character using the counter i.
3) i is now the number of characters in mainman up to
the first newline character
(or the number of all characters in mainman).
4) So now we know what the value of i is.
Let's set up the substr variable (allocating memory)
to be 2 bytes larger than i to accomodate i = 0 and
the newline character.
5) Quit if you can't get enough memory
	allocated.
6) mainman value is put into substr variable.
7)	For the last character of mainman check if it is a new line.
	If it is a newline, then put the newline into substr.
	(according to FR #3)
Functional requirement #3:
The returned line should include the terminating \n character
except if the end of file was reached and does not
end with a \n character.
8. Finally, increment i by 1 then set the last character
	of str to \0 before returning substr
	(which is going to be called line).
Note: In C if you use character array as string,
 you need to put '\0' at the end.
 There is no separate string type in C.
Also, note that the memory allocation for substr will
(or the variable line in the calling function)
is not yet free. It can't be free because substr is
needed as the return varilable. Whoever calls main
will have to free the memory for the line variable*/

char	*ft_getme_myline(char *mainman)
{
	int		i;
	char	*substr;

	i = 0;
	if (!mainman[i])
		return (NULL);
	while (mainman[i] && mainman[i] != '\n')
		i++;
	substr = (char *)malloc(sizeof(char) * (i + 2));
	if (!substr)
		return (NULL);
	i = 0;
	while (mainman[i] && mainman[i] != '\n')
	{
		substr[i] = mainman[i];
		i++;
	}
	if (mainman[i] == '\n')
	{
		substr[i] = mainman[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/* The function ft_new_mainman takes mainman as input
and frees memory for the used mainman variable before
setting the new mainman variable to the remaining
text (with corresponding memory allocation)
or returning a NULL. The new (shorter) mainman is to be
used in the next call to get_next_line (because
mainman is a static variable and it's freaky).
Without this function, the next line
get_next_line function call will be wrong.
1) Starting with i = 0, find the position
 i where there is the first newline character.
2) If the ith char of mainman is null,
 then there is nothing more to do
 just free mainman and return NULL for the new mainman.
3) Else the ith char of mainman is newline
and there is more work to do.
4) If mainman length is more than i then, there
is a part of the text beyond the newline. This part
will need to be kept in str (which will require memory).
5) The memory allocated to str is, therefore,
char size x ft_strlen(mainman) - i + 1.
6) Increment i by 1. "i + 1" is the position of first character
in mainman which follows the newline.
7) Using j as index (starting with 0), str is populated
with the rest of mainman followed by \0.
8) The used mainman is finally free (not needed anymore).
9) str is returned (as the new mainman, actually)
Note: In C if you use character array as string,
 you need to put '\0' at the end.
 There is no separate string type in C.
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
