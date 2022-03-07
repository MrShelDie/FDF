/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:24:33 by nick              #+#    #+#             */
/*   Updated: 2022/03/07 14:13:51 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include "parser.h"
#include "render.h"

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
	fdf.mlx_ptr = mlx_init();
	if (!fdf.mlx_ptr)
	{
		free_matrix_3d(fdf.matrix_3d, fdf.height);
		return (0);
	}
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!fdf.win_ptr)
	{
		free_matrix_3d(fdf.matrix_3d, fdf.height);
		return (0);
	}

	for (int i = 0; i < 100000000; i++);
	render(&fdf);

	mlx_loop(fdf.mlx_ptr);
	free_matrix_3d(fdf.matrix_3d, fdf.height);
	return (0);


	// for (int i = 0; i < fdf.height; i++)
	// {
	// 	for (int j = 0; j < fdf.width; j++)
	// 	{
	// 		printf("%3d", (int)(fdf.matrix_3d[i][j].z));
	// 		if (fdf.matrix_3d[i][j].color != UNDEF_COLOR)
	// 			printf(",%x", (int)(fdf.matrix_3d[i][j].color));
	// 	}
	// 	printf("\n");
	// }

}