/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:25:34 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 17:03:15 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"
#include "parser.h"
#include "parser_utils.h"
#include "get_next_line.h"

static int	get_matrix_height(const char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd, true);
	height = 0;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd, false);
	}
	close(fd);
	return (height);
}

static int	get_matrix_width(const char *file_name)
{
	int		fd;
	int		width;
	char	*line;
	char	**tokens;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd, true);
	tokens = ft_split(line, ' ');
	width = 0;
	if (tokens)
	{
		while (tokens[width] && tokens[width][0] != '\n')
			width++;
	}
	close(fd);
	if (line)
		free(line);
	if (tokens)
		ft_free_split(tokens);
	return (width);
}

static int	check_map(const char *file_name, int height, int width)
{
	int	fd;
	int	row_nb;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	row_nb = -1;
	while (++row_nb < height)
	{
		if (!check_line(fd, row_nb, width))
		{
			close(fd);
			return (ERROR);
		}
	}
	close(fd);
	return (SUCCESS);
}

static int	fill_matrix(t_fdf *fdf, int height,
	int width, const char *file_name)
{
	int		fd;
	int		row_nb;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	row_nb = -1;
	while (++row_nb < height)
	{
		if (!fill_line(fdf, width, fd, row_nb))
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
	fdf->map_height = get_matrix_height(file_name);
	fdf->map_width = get_matrix_width(file_name);
	if (fdf->map_height < 1 || fdf->map_width < 1)
		return (ERROR);
	if (!check_map(file_name, fdf->map_height, fdf->map_width))
		return (ERROR);
	fdf->matrix_3d = alloc_matrix_3d(fdf->map_height, fdf->map_width);
	if (!fdf->matrix_3d)
		return (ERROR);
	fdf->matrix_2d = alloc_matrix_2d(fdf->map_height, fdf->map_width);
	if (!fdf->matrix_2d)
	{
		free_matrix_3d(fdf->matrix_3d, fdf->map_height);
		return (ERROR);
	}
	if (!fill_matrix(fdf, fdf->map_height, fdf->map_width, file_name))
	{
		free_matrix_3d(fdf->matrix_3d, fdf->map_height);
		free_matrix_2d(fdf->matrix_2d, fdf->map_height);
		return (ERROR);
	}
	return (SUCCESS);
}
