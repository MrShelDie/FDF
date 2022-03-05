/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:46:55 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 15:11:49 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "def.h"
#include "libft.h"
#include "matrix.h"
#include "parser.h"
#include "parser_utils.h"
#include "get_next_line.h"

static int	get_color(const char *token)
{
	int				i;
	unsigned int	color;

	i = 0;
	while (ft_isdigit(token[i]) && token[i] && token[i] != '\n')
		i++;
	if (!token[i] || token[i] == '\n')
		return (UNDEF_COLOR);
	i += 3;
	color = 0x000000;
	while (token[i] && token[i] != '\n')
	{
		color *= 16;
		if (token[i] >= '0' && token[i] <= '9')
			color += token[i] - '0';
		else if (token[i] >= 'a' && token[i] <= 'f')
			color += token[i] - 'a' + 10;
		else
			color += token[i] - 'A' + 10;
		i++;
	}
	return (color);
}

static void	fill_point(
	t_point *point, int row_nb, int col_nb, const char *token)
{
	point->x = (float)col_nb;
	point->y = (float)row_nb;
	point->z = (float)ft_atoi(token);
	point->color = get_color(token);
}

static int	fill_line(t_point **matrix, int width, int fd, int row_nb)
{
	int		col_nb;
	char	*line;
	char	**tokens;

	if (row_nb == 0)
		line = get_next_line(fd, TRUE);
	else
		line = get_next_line(fd, FALSE);
	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		if (line)
			free(line);
		return (ERROR);
	}
	col_nb = -1;
	while (++col_nb < width)
		fill_point(&matrix[row_nb][col_nb], row_nb, col_nb, tokens[col_nb]);
	free(line);
	ft_free_split(tokens);
	return (SUCCESS);
}

static int	fill_matrix(
	t_point **matrix, int height, int width, const char *file_name)
{
	int		fd;
	int		row_nb;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	row_nb = -1;
	while (++row_nb < height)
	{
		if (!fill_line(matrix, width, fd, row_nb))
		{
			close(fd);
			return (ERROR);
		}
	}
	close(fd);
	return (SUCCESS);
}

int	parse(t_fdf *fdf, const char *file_name)
{
	fdf->height = get_matrix_height(file_name);
	fdf->width = get_matrix_width(file_name);
	if (fdf->height < 1 || fdf->width < 1)
		return (ERROR);
	if (!check_map(file_name, fdf->height, fdf->width))
		return (ERROR);
	fdf->matrix = alloc_matrix(fdf->height, fdf->width);
	if (!fdf->matrix)
		return (ERROR);
	if (!fill_matrix(fdf->matrix, fdf->height, fdf->width, file_name))
	{
		free_matrix(fdf->matrix, fdf->height);
		return (ERROR);
	}
	return (SUCCESS);
}
