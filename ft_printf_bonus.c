/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:56:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/12 19:13:04 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include "ft_printf_bonus.h"

int	put_str(char *src, t_format f, int *wc, int off)
{
	int		len;
	int		fo_len;
	char	*zero_flag_src;
	int		zero_len;

	if (src == NULL)
		return (put_str(NULL_STR_MSG, f, wc, 0));
	len = ft_cont(0, src);
	if (f.conv == 's' && f.pf == '.' && f.fl_p < len)
		len = f.fl_p;
	fo_len = f.fo_p - (len + (f.fl_p - len) * (f.fl_p > len));
printf("fo_len before = %d\n", fo_len);
	//fo_len -= off * (f.pf == '.');
printf("fo_len after = %d\n", fo_len);
printf("f.fo_p after = %d\n", f.fo_p);
	zero_flag_src = ZEROS;
	zero_len = f.fl_p - len + off * (f.pf == '.');
	if (ft_cont(f.conv, "cs"))
		zero_flag_src = SPACES;
	if ((!f.rev_fo_p && put_chars(SPACES, fo_len, wc))
		|| put_chars(src, off, wc)
		|| ((ft_cont(f.pf, "0."))
			&& put_chars(zero_flag_src, zero_len, wc))
		|| put_chars(src + off, len - off, wc)
		|| (f.rev_fo_p && put_chars(SPACES, fo_len, wc)))
		return (1);
	return (0);
}

void	fill_num_buffer(t_ul n, char *base, int base_len, char *buffer)
{
	int		nb_len;
	t_ul	nb;

	nb_len = 1;
	nb = n;
	while (nb >= (unsigned int)base_len)
	{
		nb /= base_len;
		nb_len++;
	}
	buffer[nb_len] = 0;
	while (--nb_len >= 0)
	{
		buffer[nb_len] = base[n % base_len];
		n /= base_len;
	}
}

//max len = 19
int	put_num(t_ul n, t_format f, int *wc)
{
	char	buffer[1 + 2 + 19 + 1];
	int		offset;

	if (f.conv == 'p' && n == 0)
		return (put_str(NULL_PTR_MSG, f, wc, 0));
	*buffer = 0;
	if (f.conv == '-')
		*buffer = '-';
	if ((f.sfi[1] || f.sfi[2]) && (ft_cont(f.conv, "+p")))
		*buffer = " +"[f.sfi[2] != 0];
	buffer[*buffer != 0] = '0';
	buffer[(*buffer != '0') + 1] = 'x';
	if (f.conv == 'X')
		buffer[(*buffer != '0') + 1] = 'X';
	offset = (*buffer != '0');
	offset += 2 * (f.conv == 'p' || (ft_cont(f.conv, "xX") && *f.sfi && n));
	if (ft_cont(f.conv, "-+u"))
		fill_num_buffer(n, BD, 10, buffer + offset);
	else if (f.conv == 'p' || f.conv == 'x')
		fill_num_buffer(n, BHL, 16, buffer + offset);
	else
		fill_num_buffer(n, BHU, 16, buffer + offset);
	if (f.pf == '.' && f.fl_p == 0 && n == 0)
		buffer[ft_cont(*buffer, "+ ")] = 0;
	return (put_str(buffer, f, wc, offset));
}

int	put_var(t_format f, va_list list, int *wc)
{
	long	nb;
	char	c;

	if (f.conv == 'd')
	{
		nb = (long)va_arg(list, int);
		if (nb >= 0)
			f.conv = '+';
		else
		{
			nb = -nb;
			f.conv = '-';
		}
		return (put_num((t_ul)nb, f, wc));
	}
	if (f.conv == 'p')
		return (put_num(va_arg(list, t_ul), f, wc));
	if (ft_cont(f.conv, "uxX"))
		return (put_num(va_arg(list, unsigned int), f, wc));
	if (f.conv == 's')
		return (put_str(va_arg(list, char *), f, wc, 0));
	if (f.conv == '%')
		return (put_str("%", f, wc, 0));
	c = (char)va_arg(list, int);
	return (put_str(&c, f, wc, 0));
}

int	ft_printf(const char *s, ...)
{
	va_list		list;
	int			wc;
	t_format	f;
	int			i;

	if (s == NULL)
		return (-1);
	wc = 0;
	va_start(list, s);
	while (*s)
	{
		i = -1;
		while (++i < (int) sizeof(t_format))
			((unsigned char *)&f)[i] = 0;
		f = parse_format((char **)&s, f);
		if (f.conv && put_var(f, list, &wc))
			break ;
		if (!f.conv && put_chars((char *)s++, 1, &wc))
			break ;
	}
	va_end(list);
	return (wc);
}
