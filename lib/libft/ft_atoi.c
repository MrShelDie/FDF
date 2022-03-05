/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:34:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/03/05 17:11:30 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

static void	ft_skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
}

static	int	ft_get_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (1);
	}
	if (**str == '+')
		(*str)++;
	return (0);
}

static long int	ft_str_to_num(const char **str, int *ndigit)
{
	long int	num;

	num = 0;
	while (ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		(*ndigit)++;
		(*str)++;
	}
	return (num);
}

int	ft_atoi(const char *str, int *error)
{
	int			is_neg;
	int			ndigit;
	long int	num;

	num = 0;
	is_neg = 0;
	ndigit = 0;
	ft_skip_spaces(&str);
	is_neg = ft_get_sign(&str);
	num = ft_str_to_num(&str, &ndigit);
	if (error)
	{
		if (ndigit > 10 || num > (long int)is_neg + INT_MAX)
			*error = 1;
	}
	if (is_neg)
		num *= -1;
	return ((int)num);
}
