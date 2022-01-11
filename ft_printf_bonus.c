/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:56:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/11 14:35:17 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include "ft_printf_bonus.h"


//just writes the src if format.conv is 0
//sign = -1 si n < 0, 0 si n == 0, 1 si n > 0
int	put_str(char *src, t_format f, int *wc)
{
	int	w_size;
	int	len;
	int	fo_len;

	if (src == NULL)
		return (put_str(NULL_STR_MSG, f, wc));
	len = (f.conv == 'c');
	while (f.conv != 'c' &&  src[len])
		len++;
	fo_len = f.fo_p - (len + (f.fl_p -len) * (f.fl_p > len));
	if (!f.rev_fo_p && put_chars(' ', fo_len, wc))
		return (1);
	if (ft_cont(f.pf , ".0") && put_chars('0', f.fl_p - len, wc))
		return (1);
	w_size = write(1, src, len);
	*wc += w_size;
	if (w_size < len)
	{
		if (w_size == -1)
			*wc = -1;
		return (1);
	}
	if (f.rev_fo_p && put_chars(' ', fo_len, wc))
		return (1);
	return (0);
}

//max len = 19
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

//if the number is neg and it should be signed, f.conv = d, else it's u,x,X or p
//in this vontext, conv peut etre egale a u,d(le nombre est forcement negatif),p,x,X
int	put_num(t_ul n, t_format f, int *wc)
{
	char	buffer[1 + 2 + 19 + 1];
	int offset;

	if (f.conv == 'p' && n == 0)
		return (put_str(NULL_PTR_MSG, f, wc));
	//write sign
	*buffer = 0;
	if (f.conv == 'd')
		*buffer = '-';
//printf("0 = %d, 1 = %d, 2 = %d\n",  f.sfi[0], f.sfi[1], f.sfi[2]);
//printf("result = '%c'\n", " +"[f.sfi[2] != 0]);
	if ((f.sfi[1] ||f.sfi[2]) && f.conv != 'd')
		*buffer = " +"[f.sfi[2] != 0];
	buffer[*buffer != 0] = '0';
	buffer[(*buffer != '0') + 1] = 'x';
	offset = (*buffer != '0') + 2 * (f.conv == 'p' || (ft_cont(f.conv, "xX") && *f.sfi));
	if (ft_cont(f.conv, "du"))
		fill_num_buffer(n, BD, 10, buffer + offset);
	else if (f.conv == 'p' || f.conv == 'x')
		fill_num_buffer(n, BHL, 16, buffer + offset);
	else
		fill_num_buffer(n, BHU, 16, buffer + offset);
	if (f.pf == '.' && f.fl_p == 0)
		*buffer = 0;
	return (put_str(buffer, f, wc));
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
		return (put_str(va_arg(list, char *), f, wc));
	if (f.conv == '%')
		return (put_str("%", new_f(), wc));
	c = (char)va_arg(list, int);
	return (put_str(&c, f, wc));
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		wc;
	t_format	f;

	if (s == NULL)
		return (-1);
	wc = 0;
	va_start(list, s);
	while (*s)
	{
		f = parse_format((char **)&s);
		if (f.conv && put_var(f, list, &wc))
			break;
		if (!f.conv && put_chars(*(s++), 1, &wc))
			break;
	}
	va_end(list);
	return (wc);
}
