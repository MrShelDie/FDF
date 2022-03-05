/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:46:55 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 13:09:21 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_utils.h"

t_point	**alloc_matrix(int height, int width)
{
	t_point	**matrix;
	int		i;

	matrix = (t_point **)malloc(sizeof(t_point *) * height);
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!matrix[i])
			break ;
		i++;
	}
	if (i < height)
	{
		while (i >= 0)
		{
			free(matrix[i]);
			i--;
		}
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

void	free_matrix(t_point **matrix, int height)
{
	int	i;

	if (!matrix)
		return ;
	i = -1;
	while (++i < height)
		free(matrix[i]);
	free(matrix);
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
	{
		matrix[row_nb][col_nb].x = (float)col_nb;
		matrix[row_nb][col_nb].y = (float)row_nb;
		matrix[row_nb][col_nb].z = (float)ft_atoi(tokens[col_nb]);
	}
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
