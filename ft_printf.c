/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:56:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/05 19:02:55 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdarg.h>
#include<limits.h>
#ifndef BD
# define BD "0123456789"
#endif
#ifndef BHU
# define BHL "0123456789abcdef"
#endif
#ifndef BHU
# define BHU "0123456789ABCDEF"
#endif
#define ABS(Value) (Value > 0 ? Value : -Value)
#if defined __LINUX__
# define NULL_MSG "(nil)"
#else
# define NULL_MSG "(null)"
#endif

typedef unsigned long long t_ul;

int	put_str(char *str)
{
	int	i;

	if (str == NULL)
		return (put_str(NULL_MSG));
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
}

int	put_unb(t_ul n, char *base, int base_len)
{
	char	buffer[20 + 2];
	int	nb_len;
	t_ul	nb;

	nb_len = 1;
	nb = n;
	while (nb >= base_len)
	{
		nb /= base_len;
		nb_len++;
	}
	buffer[nb_len] = 0;
	nb = n;
	while (--nb_len >= 0)
	{
		buffer[nb_len] = base[nb % base_len];
		nb /= base_len;
	}
	return (put_str(buffer));
}

int	put_snb(long n, char *base, int base_len)
{
	char	buffer[10 + 2];
	int	nb_len;
	long	nb;

	nb_len = (n < 0) + 1;
	nb = ABS(n);
	while (nb >= base_len)
	{
		nb /= base_len;
		nb_len++;
	}
	buffer[nb_len] = 0;
	*buffer = '-';
	nb = ABS(n);
	n = (n < 0);
	while (--nb_len >= n)
	{
		buffer[nb_len] = base[nb % base_len];
		nb /= base_len;
	}
	return (put_str(buffer));
}

int	put_var(char c, va_list list)
{
	if (c == 's')
		return (put_str(va_arg(list, char *)));
	if (c == 'u')
		return (put_unb((t_ul)va_arg(list, unsigned int), BD, 10));
	if (c == 'p')
		return (put_str("0x") + put_unb(va_arg(list, t_ul), BHL, 16));
	if (c == 'i' || c == 'd')
		return (put_snb(va_arg(list, int), BD, 10));
	if (c == 'x')
		return (put_unb(va_arg(list, unsigned int), BHL, 16));
	if (c == 'X')
		return (put_unb(va_arg(list, unsigned int), BHU, 16));
	if (c == '%')
		return (write(1, "%", 1));
	if (c == 'c')
	{
		c = (char)va_arg(list, int);
		return (write(1, &c, 1));
	}
	return (-3);
}

int	ft_printf(const char * s, ...)
{
	va_list	list;
	int	count;
	int	w_size;

	if (s == NULL)
		return (-1);
	count = 0;
	va_start(list, s);
	while (*s)
	{
		w_size = -4;
		if (*s == '%' && s[1] != 0)
			w_size = put_var(s[1], list);
		if (w_size == -1 || w_size == -2)
		{
			va_end(list);
			return (-1);
		}
		s += w_size != -3 && w_size != -4;
		if (w_size == -3 || w_size == -4)
			w_size = write(1, s, 1);
		count += w_size;
		s++;
	}
	va_end(list);
	return (count);
}
