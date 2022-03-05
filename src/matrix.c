/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:45:27 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 14:04:57 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "def.h"
#include "matrix.h"

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
