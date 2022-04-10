/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:36:32 by nick              #+#    #+#             */
/*   Updated: 2022/04/10 15:44:28 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fdf.h"
#include "libft.h"
#include "parser_utils.h"
#include "get_next_line.h"

static int	is_color(const char *token)
{
	int	i;

	if (ft_strncmp(token, "0x", 2) != 0 && ft_strncmp(token, "0X", 2) != 0)
		return (false);
	i = 2;
	while (token[i] && token[i] != '\n')
	{
		if ((token[i] >= '0' && token[i] <= '9')
			|| (token[i] >= 'a' && token[i] <= 'f')
			|| (token[i] >= 'A' && token[i] <= 'F')
		)
			i++;
		else
			break ;
	}
	return (i <= COLOR_STR_SIZE);
}

static int	is_number(const char *token)
{
	int	i;
	int	error;

	error = 0;
	ft_atoi(token, &error);
	if (error)
		return (false);
	i = 0;
	if (token[0] == '-')
		i++;
	while (token[i] && token[i] != '\n')
	{
		if (!ft_isdigit(token[i]))
			break ;
		i++;
	}
	if (!token[i] || token[i] == '\n')
		return (true);
	if (token[i] == ',' && is_color(&token[i + 1]))
		return (true);
	return (false);
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
	was_not_number_met = false;
	col_nb = 0;
	if (tokens)
	{
		while (tokens[col_nb] && tokens[col_nb][0] != '\n')
		{
			if (!is_number(tokens[col_nb]))
				was_not_number_met = true;
			col_nb++;
		}	
	}
	if (line)
		free(line);
	if (tokens)
		ft_free_split(tokens);
	return (!was_not_number_met && col_nb == width);
}
