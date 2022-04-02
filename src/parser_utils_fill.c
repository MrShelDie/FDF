/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:46:55 by nick              #+#    #+#             */
/*   Updated: 2022/04/02 22:20:18 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "fdf.h"
#include "libft.h"
#include "parser_utils.h"
#include "get_next_line.h"

static int	get_color(const char *token)
{
	int	i;
	int	color;

	i = 0;
	if (token[i] == '-')
		i++;
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

static void	fill_point(t_fdf *fdf, int row_nb,
	int col_nb, const char *token)
{
	fdf->matrix_3d[row_nb][col_nb].x = (float)col_nb;
	fdf->matrix_3d[row_nb][col_nb].y = (float)row_nb;
	fdf->matrix_3d[row_nb][col_nb].z = (float)ft_atoi(token, NULL);
	if (abs(fdf->matrix_3d[row_nb][col_nb].z) > fdf->height_max)
		fdf->height_max = abs(fdf->matrix_3d[row_nb][col_nb].z);
	fdf->matrix_3d[row_nb][col_nb].color = get_color(token);
}

int	fill_line(t_fdf *fdf, int width, int fd, int row_nb)
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
		fill_point(fdf, row_nb, col_nb, tokens[col_nb]);
	free(line);
	ft_free_split(tokens);
	return (SUCCESS);
}
