/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_chr_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:35:07 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/06 11:24:36 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_chr_replace(char *s, char old_c, char new_c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		if (*s == old_c)
		{
			*s = new_c;
			counter++;
		}
		s++;
	}
	return (counter);
}
