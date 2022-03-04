/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:05:44 by gannemar          #+#    #+#             */
/*   Updated: 2022/03/04 23:22:49 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct s_buff
{
	char	arr[BUFFER_SIZE];
	size_t	next_char_idx;
	ssize_t	readed_left;
}	t_buff;

typedef struct s_gnl_list
{
	char				arr[BUFFER_SIZE];
	size_t				len;
	struct s_gnl_list	*next;
}	t_gnl_list;

typedef struct s_result
{
	char	*arr;
	size_t	size;
}	t_result;


char	*get_next_line(int fd, int is_new_file);

#endif