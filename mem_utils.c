/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiyahar <marimiya@sas.upenn.edu>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 03:03:31 by mmiyahar          #+#    #+#             */
/*   Updated: 2024-11-03 03:03:31 by mmiyahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_strlist(char **str)
{
	char	**temp;

	if (str)
	{
		temp = str;
		while (*temp)
		{
			free(*temp);
			temp++;
		}
		free(str);
	}
}

void	free_map(t_pos **pos, int rows)
{
	int	i;

	i = 0;
	if (pos)
	{
		while (i < rows)
			free(pos[i++]);
		free(pos);
	}
}

void	parse_line_err(char *line, t_data *data, char **values)
{
	if (line)
		free(line);
	free_strlist(values);
	free_map(data->pos, data->rows);
	malloc_err();
}

void	malloc_err(void)
{
	write(2, "Memory allocation error\n", 24);
	exit(1);
}
