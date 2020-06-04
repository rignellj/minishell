/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:57:34 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/12 14:24:29 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char			ft_check_type(char c)
{
	char		*array;
	int			i;
	char		d;

	array = "cspdiouxXfba%";
	i = 0;
	while (array[i] != '\0')
	{
		d = array[i];
		if (c == d)
		{
			array = NULL;
			return (d);
		}
		++i;
	}
	array = NULL;
	return (0);
}

int				ft_len_format(char *f, unsigned int *i)
{
	unsigned int	j;

	j = 1;
	while (f[*i + j] && ft_check_type(f[*i + j]) != f[*i + j])
		j++;
	return (j);
}

void			ft_form_struct(t_format *f, char *format,
				unsigned i, unsigned j)
{
	char	c;

	ft_put_zero(f);
	if (!(f->s_str = ft_strsub(format, i, j)))
		exit(-1);
	f->format = f->s_str[ft_strlen(f->s_str) - 1];
	c = f->format;
	f->len = which_len(f);
	f->dot = (ft_strchr(f->s_str, '.') ? 1 : 0);
	f->minus = (ft_strchr(f->s_str, '-') ? 1 : 0);
	f->space = (ft_strchr(f->s_str, ' ') ? 1 : 0);
	f->plus = (ft_strchr(f->s_str, '+') ? 1 : 0);
	f->hash = (ft_strchr(f->s_str, '#') ? 1 : 0);
	f->prec = f->dot ? ft_if_precision_diouxs(f) : 0;
	f->width = ft_check_if_width(f);
	f->zero = (f->minus || (f->dot && (c == 'd' || c == 'i' || c == 'o' ||
		c == 'u' || c == 'x' || c == 'X'))) ? 0 : iszero(f);
}

int				ft_check_error(char *format)
{
	int		i;
	int		percent;
	int		specifier;

	i = 1;
	percent = 0;
	specifier = 0;
	while (format[i])
	{
		if (format[i] == '%')
			percent = 1;
		if (ft_check_type(format[i]))
			specifier = 1;
		i++;
	}
	if (!percent && !specifier)
		if (format[0] == '%' && !specifier)
			return (0);
	return (1);
}

int				ft_printf(const char *format, ...)
{
	va_list			ap;
	unsigned int	i;
	unsigned int	j;
	t_format		f;
	int				ret;

	va_start(ap, format);
	i = 0;
	ret = 0;
	while (format[i] && ft_check_error((char*)format))
	{
		j = 1;
		if (format[i] == '%')
		{
			j = ft_len_format((char*)format, &i);
			ft_form_struct(&f, (char*)format, i + 1, j);
			ret += diouxf(&f, ap, 1) - 1;
			i += j + 1;
		}
		else
			write(1, &format[i++], 1);
		ret++;
	}
	va_end(ap);
	return (ret);
}
