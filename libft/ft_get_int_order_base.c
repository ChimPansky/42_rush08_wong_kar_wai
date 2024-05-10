/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_int_order_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:19:37 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/03 00:20:06 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_int_order_base(size_t nb, size_t base_len)
{
	size_t	ord;

	ord = 1;
	while (nb / base_len != 0)
	{
		ord++;
		nb /= base_len;
	}
	return (ord);
}
