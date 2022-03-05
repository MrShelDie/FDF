/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:36:32 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 14:01:41 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "def.h"
#include "libft.h"
#include "get_next_line.h"
#include "parser_utils.h"

int	get_matrix_height(const char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd, TRUE);
	height = 0;
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd, FALSE);
	}
	close(fd);
	return (height);
}

int	get_matrix_width(const char *file_name)
{
	int		fd;
	int		width;
	char	*line;
	char	**tokens;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd, TRUE);
	tokens = ft_split(line, ' ');
	if (tokens)
	{
		width = 0;
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

int	is_number(const char *token)
{
	int	i;

	i = 0;
	if (token[0] == '-')
		i++;
	while (token[i])
	{
		if (!ft_isdigit(token[i]) && token[i] != '\n')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	check_line(int fd, int row_nb, int width)
{
	int		col_nb;
	int		is_first_row;
	int		was_not_number_met;
	char	*line;
	char	**tokens;

	is_first_row = row_nb == 0;
	line = get_next_line(fd, is_first_row);
	tokens = ft_split(line, ' ');
	was_not_number_met = FALSE;
	if (tokens)
	{
		col_nb = 0;
		while (tokens[col_nb] && tokens[col_nb][0] != '\n')
		{
			if (!is_number(tokens[col_nb]))
				was_not_number_met = TRUE;
			col_nb++;
		}	
	}
	if (line)
		free(line);
	if (tokens)
		ft_free_split(tokens);
	return (!was_not_number_met && col_nb == width);
}

int	check_map(const char *file_name, int height, int width)
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
