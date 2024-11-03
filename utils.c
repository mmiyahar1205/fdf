/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 03:01:28 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 03:01:28 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX)
			return (-1);
		if (result * sign < INT_MIN)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

char	*get_next_line(int fd, t_data *data)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	line = (char *)malloc(1);
	if (!line)
		return (free_map((*data).pos, (*data).rows), NULL);
	line[0] = '\0';
	if (buffer[0] != '\0')
	{
		i = find_nextline(buffer);
		if (find_nextline(buffer) != -1)
			return (line = append_line(line, buffer, i, data),
				clean_buff(buffer, i), line);
		line = append_line(line, buffer, ft_strlen(buffer), data);
		if (!line)
			return (free_map((*data).pos, (*data).rows), NULL);
		buffer[0] = '\0';
	}
	line = read_file(fd, line, buffer, data);
	if (!line || line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
