/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:13:58 by tkasbari          #+#    #+#             */
/*   Updated: 2023/10/28 13:17:19 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_format_flags(const char **format, t_format *conf);
static void	set_format_length(const char **format, t_format *conf);

int	set_config(const char **format, t_format *conf)
{
	const char	*percent_pos;

	conf->flags = 0;
	conf->width = 0;
	conf->prec = -1;
	conf->type = 0;
	percent_pos = *format - 1;
	set_format_flags(format, conf);
	set_format_length(format, conf);
	if (!ft_strchr(S_CONVERSIONS, **format))
	{
		conf->type = 0;
		*format = percent_pos;
		return (0);
	}
	conf->type = **format;
	(*format)++;
	return (1);
}

static void	set_format_flags(const char **format, t_format *conf)
{
	while (ft_strchr(S_FLAGS, **format))
	{
		if (**format == '#' && !(conf->flags & F_HASH))
			conf->flags += F_HASH;
		if (**format == '0' && !(conf->flags & F_ZERO))
			conf->flags += F_ZERO;
		if (**format == '-' && !(conf->flags & F_MINUS))
			conf->flags += F_MINUS;
		if (**format == ' ' && !(conf->flags & F_SPACE))
			conf->flags += F_SPACE;
		if (**format == '+' && !(conf->flags & F_PLUS))
			conf->flags += F_PLUS;
		(*format)++;
	}
}

static void	set_format_length(const char **format, t_format *conf)
{
	while (ft_isdigit(**format))
	{
		conf->width *= 10;
		conf->width += **format - '0';
		(*format)++;
	}
	if (**format == '.')
	{
		conf->prec = 0;
		(*format)++;
		while (**format == '0')
			(*format)++;
		while (ft_isdigit(**format))
		{
			conf->prec *= 10;
			conf->prec += **format - '0';
			(*format)++;
		}
	}
}
