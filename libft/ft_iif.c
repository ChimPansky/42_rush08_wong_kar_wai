/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iif.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 07:31:10 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/06 11:00:57 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Norminette says "No" to ternary operators? Inline-IF to the rescue!
	Function that returns <true_val> or <false_val> based on <condition>
	Usage: new_page = ft_iif((line_no % 100) == 1, 1, 0);
*/
int	ft_iif_int(int condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	else
		return (false_val);
}

void	*ft_iif_ptr(int condition, void *true_val, void *false_val)
{
	if (condition)
		return (true_val);
	else
		return (false_val);
}

void	*ft_iif_ptr_f(int cond, char *(*f)(const char *), void *v1, void *v2)
{
	if (cond)
		return (f(v1));
	else
		return (f(v2));
}
