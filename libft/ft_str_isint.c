/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:57:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/07 10:38:36 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_sign(char **s, int *neg_mult)
{
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*neg_mult = -1;
		(*s)++;
	}
}

int	ft_str_isint(char *s, int *target)
{
	bool	isnum;
	int		neg_mult;
	long	result;

	*target = 0;
	neg_mult = 1;
	result = 0;
	isnum = false;
	handle_sign(&s, &neg_mult);
	while (*s)
	{
		if (ft_isdigit(*s))
		{
			result = result * 10 + *s - '0';
			if ((neg_mult == -1 && (result * neg_mult) < INT_MIN)
				|| (neg_mult == 1 && result > INT_MAX))
				return (0);
			isnum = true;
		}
		else
			return (false);
		s++;
	}
	*target = result * neg_mult;
	return (isnum);
}
