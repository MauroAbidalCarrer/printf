/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:31:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/06 12:47:37 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include<stdio.h>
# include<unistd.h>
# include<stdarg.h>
# include<limits.h>
# ifndef BD
#  define BD "0123456789"
# endif
# ifndef BHU
#  define BHL "0123456789abcdef"
# endif
# ifndef BHU
#  define BHU "0123456789ABCDEF"
# endif
# define ABS(Value) (Value > 0 ? Value : -Value)
# if defined (__APPLE__)
#  define NULL_STR_MSG "(nil)"
# else
#  define NULL_STR_MSG "(null)"
# endif
# if defined (__APPLE__)
#  define NULL_PTR_MSG "(null)"
# else
#  define NULL_PTR_MSG "(nil)"
# endif
int	ft_printf(const char *s, ...);
#endif
