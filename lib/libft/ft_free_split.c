/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:04:59 by nick              #+#    #+#             */
/*   Updated: 2022/03/04 18:52:10 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char **str_tab)
{
	int	i;

	if (!str_tab)
		return ;
	i = -1;
	while (str_tab[++i])
		free(str_tab[i]);
	free(str_tab[i]);
	free(str_tab);
}
