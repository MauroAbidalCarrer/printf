/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:26:57 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/12 15:47:59 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"ft_printf_bonus.h"

int	put_chars(char *src, int nb, int *wc)
{
	int	w_size;
	int	len;
	int	count;

	len = ft_cont(0, src);
	while (nb > 0)
	{
		count = len * (len <= nb) + nb * (nb < len);
		w_size = write(1, src, count);
		*wc += w_size;
		if (w_size == -1)
			*wc = -1;
		if (w_size < count)
			return (1);
		nb -= w_size;
	}
	return (0);
}

//ft_contains char, if c == 0, returns len
int	ft_cont(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (i * (c == 0));
}

int	parse_precision(char *s, int i, t_format *f)
{
	int	n;

	if (i == -1)
		return (-1);
	if (!ft_cont(s[i], "0123456789"))
		return (i);
	n = 0;
	while (ft_cont(s[i], "0123456789"))
	{
		n *= 10;
		n += s[i++] - '0';
	}
	if (f == NULL)
		return (i);
	if (f->pf == '.' || (f->pf == '0' && f->rev_fo_p != '-'))
		f->fl_p = n;
	else
		f->fo_p = n;
	return (i);
}

int	parse_flags(char *s, int i, t_format *f)
{
	while (i != -1 && ft_cont(s[i], FLAGS))
	{
		f->sfi[0] = (f->sfi[0] || s[i] == '#');
		f->sfi[1] = (f->sfi[1] || s[i] == ' ');
		f->sfi[2] = (f->sfi[2] || s[i] == '+');
		if (ft_cont(s[i], "#+ ") && (f->fo_p || f->fl_p))
			return (-1);
		if (ft_cont(s[i], "0.-") && !(s[i] == '0' && f->pf))
		{
			if (f->pf == '.' || f->fl_p || (s[i] == '-' && f->fo_p))
				return (-1);
			if (s[i] == '0' && s[parse_precision(s, i + 1, NULL)] == '.')
				return (i + 1);
			if (s[i] != '-')
				f->pf = s[i];
			else
				f->rev_fo_p = '-';
		}
		i++;
	}
	return (i);
}

t_format	parse_format(char **str, t_format f)
{
	int		i;

	if (**str != '%')
		return (f);
	if ((*str)[1] == '%')
	{
		f.conv = '%';
		*str += 2;
		return (f);
	}
	i = 1;
	i = parse_flags(*str, i, &f);
	i = parse_precision(*str, i, &f);
	i = parse_flags(*str, i, &f);
	i = parse_precision(*str, i, &f);
	if (i == -1 || !ft_cont((*str)[i], "cspdiuxX"))
		return (f);
	f.conv = (*str)[i];
	if (f.conv == 'i')
		f.conv = 'd';
	*str += i + 1;
	return (f);
}
