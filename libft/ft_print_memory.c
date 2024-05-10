/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:43:25 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/28 16:53:25 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_substr(char *s, size_t offset, size_t len)
{
	size_t	i;
	char	c;

	i = 0;
	while (i < len)
	{
		c = *(s + offset + i);
		if (ft_isprint(c))
			ft_printf("%c", c);
		else
			ft_printf(".");
		i++;
	}
	ft_printf("\n");
}

void	print_spaces(size_t nbytes)
{
	size_t	spaces;
	size_t	i;

	i = 0;
	spaces = nbytes % 2;
	spaces += (nbytes * 2);
	spaces += (nbytes / 2);
	while (i++ < spaces)
		ft_printf(" ");
}

void	*ft_print_memory_width(void *addr, size_t size, size_t width)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (i % width == 0)
			ft_printf("%.16x: ", (size_t)(addr + i));
		if (!addr)
		{
			ft_printf("\n");
			return (addr);
		}
		ft_printf("%02x", *((char *)addr + i));
		if (i % 2 == 1 || i % width == width - 1)
			ft_printf(" ");
		if (i % width != width - 1 && i == size - 1)
			print_spaces((width - 1) - (i % width));
		if (i % width == width - 1 || i == size - 1)
			print_substr((char *)addr, i - (i % width), i % width + 1);
		i++;
	}
	return (addr);
}

void	*ft_print_memory(void *addr, size_t size)
{
	ft_print_memory_width(addr, size, 16);
	return (addr);
}
