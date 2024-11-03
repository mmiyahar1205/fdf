/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <mmiyahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:43 by mmiyahar          #+#    #+#             */
/*   Updated: 2024/09/30 20:16:19 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

int	find_nextline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	clean_buff(char *buffer, int i)
{
	int	count;

	count = 0;
	i++;
	while (buffer[i])
		buffer[count++] = buffer[i++];
	buffer[count] = '\0';
}

char	*append_line(char *line, char *buffer, int i, t_data *data)
{
	char	*newline;
	size_t	line_len;
	size_t	j;
	int		count;

	line_len = ft_strlen(line);
	newline = (char *)malloc(line_len + i + 2);
	if (!newline)
		return (free(line), free_map((*data).pos, (*data).rows), NULL);
	j = -1;
	while (++j < line_len)
		newline[j] = line[j];
	count = -1;
	while (++count <= i)
		newline[line_len + count] = buffer[count];
	newline[line_len + i + 1] = '\0';
	free(line);
	return (newline);
}

char	*read_file(int fd, char *line, char *buffer, t_data *data)
{
	int	byteread;
	int	i;

	byteread = read(fd, buffer, BUFFER_SIZE);
	while (byteread > 0)
	{
		buffer[byteread] = '\0';
		i = find_nextline(buffer);
		if (i != -1)
		{
			line = append_line(line, buffer, i, data);
			if (!line)
				return (NULL);
			return (clean_buff(buffer, i), line);
		}
		line = append_line(line, buffer, byteread, data);
		if (!line)
			return (NULL);
		buffer[0] = '\0';
		byteread = read(fd, buffer, BUFFER_SIZE);
	}
	if (byteread == -1)
		return (buffer[0] = '\0', free(line), NULL);
	return (line);
}
