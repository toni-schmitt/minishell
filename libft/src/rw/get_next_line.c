/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:34:18 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/03 19:19:27 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

/* Duplicates string str starting from start for len bytes */
static char	*ft_gnlsubstr(char const *s, unsigned long start, size_t len)
{
	char	*substr;
	size_t	str_len;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (str_len == 0)
		return (NULL);
	substr = malloc((len + 1) * sizeof(*substr));
	if (substr == NULL)
		return (NULL);
	while (start < str_len && len--)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

/* Returns line until newline or line if no nl is found */
char	*ft_get_return(char **line)
{
	char	*ret;
	char	*tmp;
	char	*line_buf;
	int		i;

	i = 0;
	line_buf = *line;
	while (line_buf[i] != '\n' && line_buf[i])
		i++;
	if (line_buf[i] == '\n')
	{
		ret = ft_gnlsubstr(line_buf, 0, i + 1);
		tmp = ft_strdup(&(line_buf[i + 1]));
		ft_free((void *)line);
		if (tmp == NULL)
			return (ft_free((void *)&ret));
		*line = tmp;
		if ((*line)[0] == '\0')
			ft_free((void *)line);
	}
	else
		ret = ft_append(line, NULL);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*line[10240];
	char		*buffer;
	ssize_t		bytes_read;

	bytes_read = TRUE;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
	if (buffer == NULL)
		return (NULL);
	while (bytes_read > 0 && ft_strchr(line[fd], '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		line[fd] = ft_append(&line[fd], buffer);
		if (line[fd] == NULL)
			return (ft_free((void *)&buffer));
	}
	ft_free((void *)&buffer);
	if (bytes_read < 0 || (bytes_read == 0 && line[fd] == NULL))
		return (ft_free((void *)&line[fd]));
	return (ft_get_return(&line[fd]));
}
