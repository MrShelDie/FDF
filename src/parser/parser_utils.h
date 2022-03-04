/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 22:49:39 by nick              #+#    #+#             */
/*   Updated: 2022/03/04 23:34:29 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include <fcntl.h>

# include "def.h"
# include "libft.h"
# include "get_next_line.h"

int	get_matrix_height(const char *file_name);
int	get_matrix_width(const char *file_name);
int	is_number(const char *token);
int	check_line(int fd, int row_nb, int width);
int	check_map(const char *file_name, int height, int width);

#endif
