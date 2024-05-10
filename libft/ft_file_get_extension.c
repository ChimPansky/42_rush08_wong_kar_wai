/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_get_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:09:40 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/05 20:12:14 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_file_get_extension(char *file_path)
{
	if (!file_path)
		return (NULL);
	return (ft_strrchr(file_path, '.'));
}

// char	*ft_file_get_extension(char *file_path)
// {
// 	char	*ext;
// 	char	*point_pos;

// 	if (!file_path)
// 		return (NULL);
// 	ext = ft_calloc(sizeof(char), 6);
// 	if (!ext)
// 		return (NULL);
// 	point_pos = ft_strrchr(file_path, '.');
// 	if (point_pos)
// 		ft_strlcpy(ext, point_pos + 1, 6);
// 	return (ext);
// }
