/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:45:32 by vvilensk          #+#    #+#             */
/*   Updated: 2024/03/04 19:11:19 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	string_extend(t_string *string, size_t new_len)
{
	char	*new;
	size_t	new_capacity;

	if (new_len < string->capacity)
		return (SUCCESS);
	new_capacity = string->capacity;
	while (new_capacity <= new_len)
		new_capacity *= 2;
	new = malloc(sizeof(char) * new_capacity);
	if (!new)
		return (!SUCCESS);
	ft_memcpy(new, string->buf, string->capacity * sizeof(char));
	free(string->buf);
	string->buf = new;
	string->capacity = new_capacity;
	return (SUCCESS);
}

int	string_add_str(t_string *string, const char *appendix)
{
	size_t	append_len;

	if (!appendix || !*appendix)
		return (SUCCESS);
	append_len = ft_strlen(appendix);
	if (string_extend(string, string->len + append_len) != SUCCESS)
		return (!SUCCESS);
	ft_memcpy(string->buf + string->len, appendix, append_len + 1);
	string->len = string->len + append_len;
	return (SUCCESS);
}

int	string_add_chr(t_string *string, char appendix)
{
	if (!appendix)
		return (SUCCESS);
	if (string_extend(string, string->len + 1) != SUCCESS)
		return (!SUCCESS);
	string->buf[string->len] = appendix;
	string->buf[string->len + 1] = '\0';
	string->len++;
	return (SUCCESS);
}
