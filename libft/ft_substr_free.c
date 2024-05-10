/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:07 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/04 19:54:47 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_free(char *s, unsigned int start, size_t len, int to_free)
{
	char	*result;

	result = ft_substr((const char *)s, start, len);
	if (!result)
		return (NULL);
	if (to_free)
		free(s);
	return (result);
}
