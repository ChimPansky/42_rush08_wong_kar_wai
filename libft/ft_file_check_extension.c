/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_check_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:07:02 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/05 12:48:20 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_file_check_extension(char *file_path, char *ext_to_check)
{
	char	*file_ext;

	if (!file_path)
		return (false);
	file_ext = ft_file_get_extension(file_path);
	if (!file_ext && !ext_to_check)
		return (true);
	if (!file_ext || !ext_to_check)
		return (false);
	return (!ft_strcmp(file_ext, ext_to_check));
}
