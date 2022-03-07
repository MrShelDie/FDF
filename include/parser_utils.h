/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:49:39 by nick              #+#    #+#             */
/*   Updated: 2022/03/06 14:08:36 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define COLOR_STR_SIZE 8

int	check_line(int fd, int row_nb, int width);
int	fill_line(t_point_3d **matrix_3d, int width, int fd, int row_nb);

#endif
