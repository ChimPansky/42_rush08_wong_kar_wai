/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_signed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:09:49 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/03 00:20:59 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_signed(int n, char *base)
{
	char	*pos_conversion;
	char	*result;
	int		neg;
	long	nb;

	neg = 0;
	nb = (long)n;
	if (nb < 0)
	{
		neg = 1;
		nb *= -1;
	}
	pos_conversion = ft_itoa_base_unsigned(nb, base);
	if (!neg)
		return (pos_conversion);
	result = ft_strjoin("-", pos_conversion);
	free(pos_conversion);
	if (!result)
		return (NULL);
	return (result);
}
