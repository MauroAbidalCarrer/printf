/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:31:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/12 15:52:16 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
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
# ifndef FLAGS
#  define FLAGS "0-.#+ "
# endif
# ifndef CONVS
#  define CONVS "cspdiuxX"
# endif 
# ifndef SF
#  define SF "# +"
# endif 
# ifndef ZEROS
#  define ZEROS "0000000000"
# endif 
# ifndef SPACES
#  define SPACES "          "
# endif 

typedef unsigned long long	t_ul;
//sign flag indices 0 = #, 1 = ' ' , 2 = +
//precision flag
//a csupdixX% i il faut faire une convertion, a 0 si c la fin.
//format precision
//flag precision
typedef struct format
{
	char				sfi[3];
	char				pf;
	char				conv;
	unsigned short		fo_p;
	unsigned short		fl_p;
	char				rev_fo_p;
}	t_format;

int			ft_printf(const char *s, ...);
t_format	parse_format(char **str, t_format f);
int			put_chars(char *src, int nb, int *ws);
int			ft_cont(char c, char *s);
#endif
