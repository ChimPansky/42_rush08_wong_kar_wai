/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:33 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/02 14:12:10 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, bool free_s1, bool free_s2)
{
	char	*result;

	result = ft_strjoin((const char *)s1, (const char *)s2);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (result);
}
