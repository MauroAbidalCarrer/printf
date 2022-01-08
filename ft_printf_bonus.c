/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:56:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/08 21:31:07 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

typedef unsigned long long	t_ul;

int	put_str(char *str)
{
	int	i;

	if (str == NULL)
		return (put_str(NULL_STR_MSG));
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
}

int	put_unb(t_ul n, char *base, int base_len, char *flag)
{
	char	buffer[20 + 2];
	int		nb_len;
	t_ul	nb;

	if (n == 0 && (*flag == ))
		return (put_str(NULL_PTR_MSG));
	nb_len = 1;
	nb = n;
	while (nb >= (unsigned int)base_len)
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
	if (add_0x)
		return (put_str("0x") + put_str(buffer));
	return (put_str(buffer));
}

int	put_snb(long n, char *base, int base_len, int sign_op)
{
	char	buffer[10 + 2];
	int		nb_len;
	long	nb;

	nb_len = (n < 0 || sign_op) + 1;
	nb = n;
	if (nb < 0)
		nb = -nb;
	while (nb >= base_len)
	{
		nb /= base_len;
		nb_len++;
	}
	buffer[nb_len] = 0;
	*buffer = "-+"[n < 0];
	nb = n;
	if (nb < 0)
		nb = -nb;
	n = (n < 0);
	while (--nb_len >= n || sign_op)
	{
		buffer[nb_len] = base[nb % base_len];
		nb /= base_len;
	}
	return (put_str(buffer));
}

int	put_var(, va_list list)
{
	if (c == 's')
		return (put_str(va_arg(list, char *)));
	if (c == 'u')
		return (put_unb((t_ul)va_arg(list, unsigned int), BD, 10, 0));
	if (c == 'p')
		return (put_unb((t_ul)va_arg(list, void *), BHL, 16, 1));
	if (c == 'i' || c == 'd')
		return (put_snb(va_arg(list, int), BD, 10));
	if (c == 'x')
		return (put_unb(va_arg(list, unsigned int), BHL, 16, 0));
	if (c == 'X')
		return (put_unb(va_arg(list, unsigned int), BHU, 16, 0));
	if (c == '%')
		return (write(1, "%", 1));
	if (c == 'c')
	{
		c = (char)va_arg(list, int);
		return (write(1, &c, 1));
	}
	return (-3);
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		count;
	int		w_size;

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
			break ;
		s += (w_size != -3 && w_size != -4);
		if (w_size == -3 || w_size == -4)
			w_size = write(1, s, 1);
		count += w_size;
		s++;
	}
	va_end(list);
	if (w_size == -1 || w_size == -2)
		return (-1);
	return (count);
}
