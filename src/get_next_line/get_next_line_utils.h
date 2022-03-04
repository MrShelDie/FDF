/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:21:29 by nick              #+#    #+#             */
/*   Updated: 2022/03/05 00:10:45 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

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

void		init_res(t_result *res);
t_gnl_list	*new_list(void);
void		free_list_elem(t_gnl_list *elem);
t_gnl_list	*push_back_list(t_gnl_list *elem);
void		free_list(t_gnl_list **list);

#endif
