/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:29:21 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 00:09:12 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "def.h"

t_point	**alloc_matrix(int height, int width);
void	free_matrix(t_point **matrix, int height);
int		parse(t_fdf *fdf, const char *file_name);

#endif
