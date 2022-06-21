/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjirapin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:39:51 by yjirapin          #+#    #+#             */
/*   Updated: 2022/06/21 19:18:04 by yjirapin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	---------
*	GET_LINE
*	---------
*	Extracts the line (ending in either line break and `\0` or only `\0` in EOF)
*	from static variable.
*	PARAMETERS
*	#1. The pointer to the cumulative static variable from previous runs of get_next_line.
*	RETURN VALUES
*	The string with the full line ending in a line break (`\n`) + (`\0`).
*/


#include "get_next_line.h"

/***********************
ft_strlen will wow you with a beautiful output that is size_t.
You only need to input a string and wa-lah!
*/

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

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
/*if left_str is null
then just allocate one byte and
put \0 in it.*/
	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	/* returning str which is left_str+buff plus \0*/
	return (str);
}
/*
*	ft_getme_aline
*	Stores in the cumulative static variable the new updated variable with whatever
*	is left from the original variable after the line is extracted.
*	PARAMETERS
*	The pointer to the cumulative static variable from previous runs of get_next_line.
*	RETURN VALUES
*	The new updated string which contains whatever is left from the original static variable value after extracting the
*	line.
*/

char	*ft_getme_aline(char *left_str)
{
	int		i;
	char	*str;

	i = 0;
	/*stop and go back if left_str[i] is NULL*/
	if (!left_str[i])
		return (NULL);
	/* while left_str[i] is not null and it is not a new line
	increment i*/
	while (left_str[i] && left_str[i] != '\n')
		i++;
	/*
	So now we know what the value of i is.
	Let's set up the str variable (allocating memory)
	to be 2 bytes larger than i to accomodate i = 0 and
	the end of line character.
	*/
	str = (char *)malloc(sizeof(char) * (i + 2));
	/* Quit if you can't get enough memory
	allocated. */
	if (!str)
		return (NULL);
	/* Now put left_str into str (up to i characters)
	*/
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	/* For the last character if it is a new line,
	put it in str. Otherwise let it be \0 and
	return str. */
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* ----------------------------------------------------------------
*	ft_new_left_str
*	Stores in the cumulative static variable the new updated variable with whatever
*	is left from the original, minus the line extracted.
*	PARAMETERS
*	#1. The pointer to the cumulative static variable from previous runs of get_next_line.
*	RETURN VALUES
*	The new updated string with whatever is left from the original static, minus the
*	line extracted.
*/

char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	/*finding the i where left_str ends or is null*/
	while (left_str[i] && left_str[i] != '\n')
		i++;
	/* If left_str[i] is null, then it means we are done.
	Don't forget to free left_str*/
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	/* The last char is going to be \0 */
	str[j] = '\0';
	free(left_str);
	return (str);
}
