/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:21:06 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/03 00:31:44 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_unsigned(size_t n, char *base)
{
	char	*str;
	size_t	base_len;
	size_t	len;

	base_len = ft_strlen(base);
	len = ft_get_int_order_base(n, base_len);
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
