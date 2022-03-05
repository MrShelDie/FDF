/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:24:33 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 13:55:13 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO DELETE
#include <stdio.h>

#include "def.h"
#include "libft.h"
#include "parser.h"
#include "matrix.h"

static int	check_args(int argc, char **argv)
{
	size_t	file_name_len;

	if (argc != 2)
		return (ERROR);
	file_name_len = ft_strlen(argv[1]);
	if (file_name_len < 4)
		return (ERROR);
	if (ft_strncmp(&argv[1][file_name_len - 4], ".fdf", 5) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (!check_args(argc, argv))
		return (0);
	if (!parse(&fdf, argv[1]))
		return (0);

	for (int i = 0; i < fdf.height; i++)
	{
		for (int j = 0; j < fdf.width; j++)
			printf("%3d", (int)(fdf.matrix[i][j].z));
		printf("\n");
	}

	free_matrix(fdf.matrix, fdf.height);
	
	return (0);
	// Изометрическое проецирование
	// Рисование
}
