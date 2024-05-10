/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:53:43 by tkasbari          #+#    #+#             */
/*   Updated: 2023/11/23 12:57:10 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_splitted(char **splitted)
{
	char	**to_free;

	if (!splitted)
		return ;
	to_free = splitted;
	while (*splitted)
	{
		free(*splitted);
		splitted++;
	}
	ft_free_and_null((void **)&to_free);
}
