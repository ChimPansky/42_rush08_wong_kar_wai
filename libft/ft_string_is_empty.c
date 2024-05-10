/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:14:43 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/04 19:50:54 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_string_is_empty(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str++))
			return (false);
	}
	return (true);
}
