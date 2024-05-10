/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manipulations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:13:03 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/09 09:37:35 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*apply_precision(char *s, int prec, char type);
static char	*apply_flags(char *s, int flags, char type);
static char	*apply_min_width(char *s, t_format conf);

char	*convert_diuxxp(char conv, va_list args)
{
	char			*result;
	unsigned int	arg_uxx;

	result = NULL;
	if (ft_strchr("di", conv))
		result = ft_itoa(va_arg(args, int));
	else if (ft_strchr("uxX", conv))
	{
		arg_uxx = va_arg(args, unsigned int);
		if (conv == 'u')
			result = ft_itoa_base_unsigned(arg_uxx, S_BASE_U);
		else if (conv == 'x')
			result = ft_itoa_base_unsigned(arg_uxx, S_BASE_HEX);
		else if (conv == 'X')
			result = ft_itoa_base_unsigned(arg_uxx, S_BASE_HEXL);
	}
	else if (conv == 'p')
	{
		result = va_arg(args, void *);
		if (!result)
			result = ft_strdup("(nil)");
		else
			result = ft_itoa_base_unsigned((size_t)result, S_BASE_HEX);
	}
	return (result);
}

char	*manipulate_s(char	*s, t_format conf)
{
	char	*result;

	result = s;
	if (conf.prec >= 0)
		result = apply_precision(result, conf.prec, conf.type);
	if (result && conf.type == 'p' && ft_strncmp(result, "(nil)", 5))
		result = add_prefix(result, "0x");
	if (result)
		result = apply_flags(result, conf.flags, conf.type);
	if (result && conf.width)
		result = apply_min_width(result, conf);
	return (result);
}

static char	*apply_precision(char *s, int prec, char type)
{
	char	*result;
	char	*to_free;

	result = s;
	to_free = s;
	if (type == 's')
		result = apply_precision_s(result, prec);
	else if (ft_strchr("diuxX", type)
		|| (type == 'p' && ft_strncmp(result, "(nil)", 5)))
	{
		if (prec == 0 && *result == '0')
			*result = '\0';
		else if (prec > 0)
		{
			if (ft_strchr("di", type) && *result == '-'
				&& ft_strlen(result) < (size_t)prec + 1)
				result = pad_negative(result, '0', prec + 1, 1);
			else
				result = ft_strlpad(result, '0', prec, true);
		}
	}
	if (!result)
		free(to_free);
	return (result);
}

static char	*apply_flags(char *s, int flags, char type)
{
	char	*result;
	char	*positive;

	result = s;
	if (flags & F_HASH)
	{
		if (ft_strchr("xX", type) && *s != '0')
		{
			if (type == 'x')
				result = add_prefix(result, "0x");
			else
				result = add_prefix(result, "0X");
		}
	}
	if (((flags & F_PLUS) || (flags & F_SPACE))
		&& ft_strchr("di", type) && *result != '-')
	{
		positive = ft_iif_ptr((flags & F_PLUS), "+", " ");
		result = add_prefix(result, positive);
	}
	return (result);
}

static char	*apply_min_width(char *s, t_format conf)
{
	char	*result;
	char	*to_free;

	to_free = s;
	result = s;
	if (conf.flags & F_MINUS)
		result = ft_strrpad(result, ' ', conf.width, true);
	else if (ft_strchr("diupxX", conf.type)
		&& conf.flags & F_ZERO && conf.prec < 0)
	{
		if (ft_strchr("di", conf.type)
			&& *s == '-' && ft_strlen(result) < conf.width)
			result = pad_negative(result, '0', conf.width, 1);
		else
			result = ft_strlpad(result, '0', conf.width, true);
	}
	else
		result = ft_strlpad(result, ' ', conf.width, true);
	if (!result)
		free(to_free);
	return (result);
}
