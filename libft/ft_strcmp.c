/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strings.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vvilensk <vilenskii.v@gmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/09/04 12:19:36 by vvilensk		  #+#	#+#			 */
/*   Updated: 2023/09/04 12:37:29 by vvilensk		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;

	if (s1 == s2)
		return (SUCCESS);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
