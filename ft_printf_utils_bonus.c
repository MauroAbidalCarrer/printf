/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:26:57 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/10 20:01:46 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>

#include"ft_printf_bonus.h"
//ft_contains char
int	ft_cont(char c, char *s)
{
	return (c == *s || (s[1] && ft_cont(c, s + 1)));
}

int	put_chars(char c, int nb, int *wc)
{
	int	w_size;

	while (nb > 0)
	{
		w_size = write(1, &c, 1);
		*wc += w_size;
		if (w_size == -1)
			*wc = -1;
		if (w_size < 1)
			return (1);
		nb--;
	}
	return (0);
}


t_format	new_f()
{
	t_format f;

	f.sfi[0] = 0;
	f.sfi[1] = 0;
	f.sfi[2] = 0;
	f.conv = 0;
	f.pf = 0;
	f.fl_p = 0;
	f.fo_p = 0;
	f.rev_fo_p = 0;
//printf("%c\n", f.rev_fo_p);
	return (f);
}

int	parse_precision(char *s, int i, t_format *f)
{
	int	n;

	if (i == -1)
		return (-1);
	if (!ft_cont(s[i], "0123456789"))
		return (i);
	n = 0;	
	while(ft_cont(s[i], "0123456789"))
	{
		n *= 10;
		n += s[i++] - '0';
	}
	if (f->pf != 0)
		f->fl_p = n;
	else
		f->fo_p = n;
	return (i);
}

int	parse_flags(char *s, int i, t_format *f)
{
	int	j;

	while (i != -1 && ft_cont(s[i], FLAGS))
	{
		f->sfi[0] = f->sfi[0] || s[i] == '#';
		f->sfi[1] = f->sfi[1] || s[i] == ' ';
		f->sfi[2] = f->sfi[2] || s[i] == '+';
		if (ft_cont(s[i], "#+ ") && (f->fo_p || f->fl_p))
			return (-1);
		if (ft_cont(s[i], "0.-") && !(s[i] == '0' && f->pf))
		{
			if (f->pf == '.'|| f->fl_p || (s[i] == '-' && f->fo_p))
				return (-1);
			if (s[i] == '0')
			{
				j = i + 1;
				while (ft_cont(s[j], "0123456789"))
					j++;
				if (s[j] == '.')
					return (i + 1);
			}
			if (s[i] != '-')
				f->pf = s[i];
			else
				f->rev_fo_p = '-';
		}
		i++;
	}
	return (i);
}

t_format	parse_format(char **str)
{
	int		i;
	t_format	f;

	f = new_f();
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
