/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:49:39 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 17:38:36 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define COLOR_STR_SIZE 8

int		check_line(int fd, int row_nb, int width);
int		fill_line(t_point **matrix, int width, int fd, int row_nb);

#endif
