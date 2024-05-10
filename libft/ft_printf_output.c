/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:23:29 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/28 13:17:36 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	output_percent(int fd, const char **format)
{
	int			bytes_written;
	const char	*first_perc_ind;

	first_perc_ind = *format;
	bytes_written = 0;
	while (**format == ' ')
		(*format)++;
	if (**format == '%')
	{
		bytes_written = write(fd, "%", 1);
		(*format)++;
	}
	else
		*format = first_perc_ind;
	return (bytes_written);
}

int	output_conversion(int fd, t_format conf, va_list args)
{
	int		bytes_written;
	char	*result;

	bytes_written = 0;
	result = NULL;
	if (conf.type == 'c')
		return (output_c(fd, conf, args));
	else if (conf.type == 's')
	{
		result = va_arg(args, char *);
		result = ft_iif_ptr_f(result != NULL, ft_strdup, result, "(null)");
	}
	else if (ft_strchr("diuxXp", conf.type))
		result = convert_diuxxp(conf.type, args);
	if (result)
		result = manipulate_s(result, conf);
	if (result)
	{
		bytes_written += write(fd, result, ft_strlen(result));
		free(result);
	}
	return (bytes_written);
}

int	output_c(int fd, t_format conf, va_list args)
{
	int		c;
	int		bytes_written;
	char	*spad;

	c = va_arg(args, int);
	bytes_written = 0;
	if (conf.width)
	{
		spad = ft_strreplicate(' ', conf.width - 1);
		if (!spad)
			return (0);
		if (!(conf.flags & F_MINUS))
			bytes_written += write(fd, spad, conf.width - 1);
	}
	bytes_written += write(fd, &c, 1);
	if (conf.width && (conf.flags & F_MINUS))
		bytes_written += write(fd, spad, conf.width - 1);
	if (conf.width)
		free(spad);
	return (bytes_written);
}

int	output_regular(int fd, const char **format)
{
	size_t	i;
	int		bytes_written;

	i = 0;
	while (*(*format + i) && *(*format + i) != '%')
		i++;
	if (i > 0)
	{
		bytes_written = write(fd, *format, i);
		(*format) += i;
		return (bytes_written);
	}
	(*format)++;
	return (0);
}
