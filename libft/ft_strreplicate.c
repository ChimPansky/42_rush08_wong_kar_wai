/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:12:10 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/05 11:28:59 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Create a String consisting of Length len only containing Character c */
char	*ft_strreplicate(char c, size_t len)
{
	char	*result;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (len)
	{
		while (len--)
			result[len] = c;
	}
	return (result);
}
