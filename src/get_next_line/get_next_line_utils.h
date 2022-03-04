/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:21:29 by nick              #+#    #+#             */
/*   Updated: 2022/03/04 23:22:31 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

# include "get_next_line.h"

void		init_res(t_result *res);
t_gnl_list	*new_list(void);
void		free_list_elem(t_gnl_list *elem);
t_gnl_list	*push_back_list(t_gnl_list *elem);
void		free_list(t_gnl_list **list);

#endif
