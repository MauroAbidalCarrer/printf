/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:31:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/06 15:04:20 by maabidal         ###   ########.fr       */
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
# ifndef NULL_STR_MSG
#  define NULL_STR_MSG "(null)"
# endif
# if defined (__APPLE__)
#  ifndef NULL_PTR_MSG
#   define NULL_PTR_MSG "0x0"
#  endif
# else
#  ifndef NULL_PTR_MSG
#   define NULL_PTR_MSG "(nil)"
#  endif
# endif
int	ft_printf(const char *s, ...);
#endif
