/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrpad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:07:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/08 18:54:09 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Right Pad a String <s> with a character <cpad> to reach a certain
	size <target_size>*/
char	*ft_strrpad(char *src, char padding, size_t target_size, bool free_src)
{
	size_t	s_len;
	char	*result;

	s_len = ft_strlen(src);
	if (s_len >= target_size)
		return (src);
	result = malloc(sizeof(char) * (target_size + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, src, s_len + 1);
	while (s_len < target_size)
		result[s_len++] = padding;
	result[s_len] = '\0';
	if (free_src)
		free(src);
	return (result);
}
