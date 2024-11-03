#include "fdf.h"

void malloc_err(t_data *data, t_pos *pos)
{
    if(pos != NULL)
        free(pos);
    if(data != NULL)
        free(data);
    exit(1);
}

void *ft_realloc(void *ptr, size_t new_size) 
{
    void *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        free(ptr);
        exit(MALLOC_ERR);
    }
    ft_memcpy(new_ptr, ptr, new_size);
    free(ptr);
    return (new_ptr);
}

void realloc_map(t_pos ***pos, int *allocated_rows) 
{
    *allocated_rows *= 2;
    *pos = ft_realloc(*pos, sizeof(t_pos *) * (*allocated_rows));
    if (!*pos)
        exit(MALLOC_ERR);
}

int hex_to_int(const char *hex_str) {
    // If the string starts with "0x" or "0X", skip the first two characters
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        hex_str += 2;
    }

    int result = 0;
    while (*hex_str) {
        int digit;
        if (*hex_str >= '0' && *hex_str <= '9')
            digit = *hex_str - '0';
        else if (*hex_str >= 'a' && *hex_str <= 'f')
            digit = *hex_str - 'a' + 10;
        else if (*hex_str >= 'A' && *hex_str <= 'F')
            digit = *hex_str - 'A' + 10;
        else
            break;
        result = result * 16 + digit;
        hex_str++;
    }
    return result;
}

void parse_line(char *line, t_pos ***pos, int row_count, int *col_count)
{
    char **values;
    
    values = ft_split(line, ' ');
    if (!values)
    {
        free(line);
        free_map(*pos, row_count);
        exit(MALLOC_ERR);
    }
    *col_count = 0;
    while (values[*col_count])
        (*col_count)++;
    (*pos)[row_count] = malloc(sizeof(t_pos) * (*col_count));
    if (!(*pos)[row_count]) {
        while(*values)
            free(*values++);
        free(values);
        free_map(*pos, row_count);
        exit(MALLOC_ERR);
    }
    for (int i = 0; i < *col_count; i++) {
        char **nums = ft_split(values[i], ',');
        
        (*pos)[row_count][i].x = i;
        (*pos)[row_count][i].y = row_count;
        (*pos)[row_count][i].z = ft_atoi(nums[0]);
        if(nums[1])
            (*pos)[row_count][i].color = (int)hex_to_int(nums[1]);
        else
            (*pos)[row_count][i].color = 0xFFFFFF;
        free(nums[0]);
        if (nums[1])
            free(nums[1]);
        free(values[i]);
    }
    free(values);
}

void getmap(int fd, t_pos ***pos, int *rows, int *cols)
{
    char *line;
    int row_count;
    int allocated_rows;

    row_count = 0;
    allocated_rows = 10;
    *pos = malloc(sizeof(t_pos *) * allocated_rows);
    if (!*pos)
        exit(MALLOC_ERR);
    while ((line = get_next_line(fd))) {
        if (row_count >= allocated_rows)
            realloc_map(pos, &allocated_rows);
        parse_line(line, pos, row_count, cols);
        free(line);
        row_count++;
    }
    *rows = row_count;
}

int	ft_atoi(const char *str) 
{
	int		sign;
	long	result;

    sign = 1;
    result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+') {
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9') {
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX)
			return (-1);
		if (result * sign < INT_MIN)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

void free_map(t_pos **pos, int rows) 
{
    int i;

    i = 0;
    if (pos) {
        while(i < rows)
            free(pos[i++]);
        free(pos);
    }
}

