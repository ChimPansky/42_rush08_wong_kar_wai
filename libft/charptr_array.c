/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charptr_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:37:15 by vvilensk          #+#    #+#             */
/*   Updated: 2024/03/04 19:11:31 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	charptr_array_expand(t_charptr_array *arr, size_t new_sz)
{
	size_t	new_cap;
	char	**new_buf;

	if (new_sz < arr->cap)
		return (SUCCESS);
	new_cap = arr->cap;
	while (new_sz >= new_cap)
		new_cap *= 2;
	new_buf = malloc(sizeof(char *) * new_cap);
	if (!new_buf)
		return (!SUCCESS);
	ft_memcpy(new_buf, arr->buf, sizeof(char *) * arr->cap);
	free(arr->buf);
	arr->buf = new_buf;
	arr->cap = new_cap;
	return (SUCCESS);
}

int	charptr_array_init(t_charptr_array *arr)
{
	arr->sz = 0;
	arr->cap = 0;
	arr->buf = malloc(sizeof(char *) * STR_ARR_INIT_CAP);
	if (!arr->buf)
		return (!SUCCESS);
	arr->cap = STR_ARR_INIT_CAP;
	return (SUCCESS);
}

int	charptr_array_add_allocated_str(t_charptr_array *arr, char **str)
{
	if (!*str)
		return (SUCCESS);
	if (charptr_array_expand(arr, arr->sz + 1) != SUCCESS)
		return (SUCCESS);
	arr->buf[arr->sz] = *str;
	arr->sz++;
	arr->buf[arr->sz] = NULL;
	*str = NULL;
	return (SUCCESS);
}

int	charptr_array_dup_and_add_str(t_charptr_array *arr, const char *str)
{
	char	*cpy;
	int		ret;

	if (!str)
		return (SUCCESS);
	cpy = ft_strdup(str);
	if (!cpy)
		return (!SUCCESS);
	ret = charptr_array_add_allocated_str(arr, &cpy);
	if (ret != SUCCESS)
		return (free(cpy), !SUCCESS);
	return (SUCCESS);
}

void	charptr_array_destroy(t_charptr_array *arr)
{
	while (arr->sz)
		free(arr->buf[--arr->sz]);
	free(arr->buf);
	arr->cap = 0;
}

/*
void	charptr_array_print(t_charptr_array *arr)
{
	size_t	i;

	i = 0;
	if (!arr)
	{
		ft_printf("{NULL}");
		return ;
	}
	if (arr->sz == 0)
	{
		ft_printf("{EMPTY}");
		return ;
	}
	while (i < arr->sz)
		ft_printf("%s\n", arr->buf[i++]);
}
*/
