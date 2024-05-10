/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:09:22 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/05 20:30:15 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	chose_output(int fd, int *prted, const char **fmt, va_list args);

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	printed = ft_vdprintf(STDOUT_FILENO, format, args);
	va_end(args);
	return (printed);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		printed;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	printed = ft_vdprintf(fd, format, args);
	va_end(args);
	return (printed);
}

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int	printed;

	printed = 0;
	while (*format && printed != -1)
		chose_output(fd, &printed, &format, args);
	return (printed);
}

int	ft_write(int fd, char *s, int nbytes, int *printed)
{
	int	bytes_written;

	bytes_written = 0;
	bytes_written = write(fd, s, nbytes);
	if (bytes_written == -1)
		*printed = -1;
	else
		*printed += bytes_written;
	return (bytes_written);
}

static void	chose_output(int fd, int *prted, const char **fmt,	va_list args)
{
	t_format	conf;
	const int	already_printed = *prted;

	if (**fmt == '%')
	{
		(*fmt)++;
		if (!(**fmt))
		{
			if (*prted)
				ft_write(fd, "%", 1, prted);////////////////7
			else
				*prted = -1;
			return ;
		}
		*prted += output_percent(fd, fmt);
		if (*prted == already_printed)
		{
			if (set_config(fmt, &conf))
				*prted += output_conversion(fd, conf, args);
			else
				*prted += output_percent(fd, fmt);
		}
	}
	else
		*prted += output_regular(fd, fmt);
}
