/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:45:27 by nick              #+#    #+#             */
/*   Updated: 2022/03/07 10:41:16 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fdf.h"

t_point_3d	**alloc_matrix_3d(int height, int width)
{
	t_point_3d	**matrix_3d;
	int		i;

	matrix_3d = (t_point_3d **)malloc(sizeof(t_point_3d *) * height);
	if (!matrix_3d)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix_3d[i] = (t_point_3d *)malloc(sizeof(t_point_3d) * width);
		if (!matrix_3d[i])
			break ;
		i++;
	}
	if (i < height)
	{
		while (i >= 0)
		{
			free(matrix_3d[i]);
			i--;
		}
		free(matrix_3d);
		return (NULL);
	}
	return (matrix_3d);
}

void	free_matrix_3d(t_point_3d **matrix_3d, int height)
{
	int	i;

	if (!matrix_3d)
		return ;
	i = -1;
	while (++i < height)
		free(matrix_3d[i]);
	free(matrix_3d);
}
