/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 03:01:13 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 03:01:13 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	realloc_map(t_data *data, int *allocated_rows)
{
	void	*new_ptr;
	size_t	new_size;

	*allocated_rows *= 2;
	new_size = sizeof(t_pos *) * (*allocated_rows);
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free_map((*data).pos, (*data).rows);
		malloc_err();
	}
	ft_memcpy(new_ptr, (*data).pos, new_size / 2);
	free((*data).pos);
	(*data).pos = new_ptr;
}

int	hex_to_int(const char *hex_str)
{
	int	result;
	int	digit;

	if (!hex_str)
		return (0xFFFFFF);
	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
	{
		hex_str += 2;
	}
	result = 0;
	while (*hex_str)
	{
		if (*hex_str >= '0' && *hex_str <= '9')
			digit = *hex_str - '0';
		else if (*hex_str >= 'a' && *hex_str <= 'f')
			digit = *hex_str - 'a' + 10;
		else if (*hex_str >= 'A' && *hex_str <= 'F')
			digit = *hex_str - 'A' + 10;
		else
			break ;
		result = result * 16 + digit;
		hex_str++;
	}
	return (result);
}

int	count_strings(char **strlist)
{
	int	count;

	count = 0;
	while (strlist[count])
		count++;
	return (count);
}

void	parse_line(char *line, t_data *data)
{
	char	**values;
	char	**nums;
	int		i;

	values = ft_split(line, ' ');
	if (!values)
		parse_line_err(line, data, values);
	(*data).cols = count_strings(values);
	(*data).pos[(*data).rows] = malloc(sizeof(t_pos) * ((*data).cols));
	if (!(*data).pos[(*data).rows])
		parse_line_err(line, data, values);
	i = -1;
	while (++i < (*data).cols)
	{
		nums = ft_split(values[i], ',');
		if (!nums)
			parse_line_err(line, data, values);
		(*data).pos[(*data).rows][i].x = i;
		(*data).pos[(*data).rows][i].y = (*data).rows;
		(*data).pos[(*data).rows][i].z = ft_atoi(nums[0]);
		(*data).pos[(*data).rows][i].color = (int)hex_to_int(nums[1]);
		free_strlist(nums);
	}
	free_strlist(values);
}

void	getmap(int fd, t_data *data)
{
	char	*line;
	int		allocated_rows;

	(*data).rows = 0;
	allocated_rows = 10;
	(*data).pos = malloc(sizeof(t_pos *) * allocated_rows);
	if (!(*data).pos)
		malloc_err();
	line = get_next_line(fd, data);
	while (line)
	{
		if ((*data).rows >= allocated_rows)
			realloc_map(data, &allocated_rows);
		parse_line(line, data);
		free(line);
		(*data).rows++;
		line = get_next_line(fd, data);
	}
}
