/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlpad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:07:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/09 09:52:49 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Left Pad a String <s> with a character <cpad> to reach a certain
	size <target_size>*/
char	*ft_strlpad(char *src, char padding, size_t target_size, bool free_src)
{
	size_t	src_len;
	size_t	i;
	char	*result;

	src_len = ft_strlen(src);
	i = 0;
	if (src_len >= target_size)
		return (src);
	result = malloc(sizeof(char) * (target_size + 1));
	if (!result)
		return (NULL);
	while (i < target_size - src_len)
		result[i++] = padding;
	ft_strlcpy(result + i, src, src_len + 1);
	if (free_src)
		free(src);
	return (result);
}
