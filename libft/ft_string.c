/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:46:38 by vvilensk          #+#    #+#             */
/*   Updated: 2024/03/04 19:53:20 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	string_init_fixed_cap(t_string *string, size_t init_capacity)
{
	string->buf = malloc(sizeof(char) * init_capacity);
	if (!string->buf)
		return (!SUCCESS);
	string->buf[0] = '\0';
	string->capacity = init_capacity;
	string->len = 0;
	return (SUCCESS);
}

int	string_init(t_string *string, char *content)
{
	const size_t	cont_sz = ft_strlen(content);
	size_t			init_cap;

	init_cap = T_STRING_INIT_CAPACITY;
	while (init_cap < cont_sz)
		init_cap *= 2;
	if (string_init_fixed_cap(string, init_cap) != SUCCESS)
		return (!SUCCESS);
	return (string_add_str(string, content));
}

void	string_init_with_allocated(t_string *string, char *allocated)
{
	string->buf = allocated;
	string->len = ft_strlen(allocated);
	string->capacity = string->len + 1;
}

void	string_destroy(t_string *string)
{
	if (string)
		free(string->buf);
}
