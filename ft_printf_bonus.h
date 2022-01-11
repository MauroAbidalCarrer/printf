/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:31:48 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/10 21:14:13 by maabidal         ###   ########.fr       */
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
typedef unsigned long long	t_ul;
typedef struct format
{
	char	sfi[3];//sign flag indices 0 = #, 1 = ' ' , 2 = +
	char	pf;//precision flag
	char	conv;//est egale a 'S' si il faut imprimer une partie de s, a csupdixX% i il faut faire une convertion, a 0 si c la fin.
	unsigned short		fo_p;//format precision
	unsigned short		fl_p;//flag precision
	char	rev_fo_p;
}	t_format;

t_format	new_f();
int		ft_printf(const char *s, ...);
t_format	parse_format(char **str);
int		put_chars(char c, int nb, int *ws);
int		ft_cont(char c, char *s);
//cspdiuxX%

//LA CONVERSTION % NE PEUT ETRE PRECEDEE QUE PAR UN %

//# = ajouter 0x, juste ecrire 0 si n = 0. Valable pour x,X.
//  = ecrire ' ' si n >= 0. Valable pour p,i,d. 
//+ = ecrire + si n >= 0. Valable pour p,i,d.

//IL PEUT Y AVOIR AUTANT DE sf QUE POSSIBLE AU DEBUT DU FORMAT
//IL NE PEUT PAS Y AVOIR DE sf APRES UNE PRECISION
//SEUL LES sf VALABLES SONT PRIS EN COMPTE(ex:si il y % +d , + est pris en compte, %#  +X, # et pris em compte
//LES ESPACES SONT IGNOREES Si il y un +-_-

//- = mettre les espaces de la fo_p a droite si la str est trop petite(foncionne avec toute le conv)
//0 = mettre des zero a gauche si conv = 's' ou 'c' alors on met des espaces. Valable pour u,d,i,x,X,P.
//. = comme 0, sauf que si precision et nombre = 0, alors, rien ecrire.

//SI AUCUNE PRECISION N'EST FOURNIE APRES UN pf, LA PRECISION EST DE 0
//SI IL Y A UN . ALORS LES 0 QUI SUIVENT SONT CONSIDERES COMME UN PRECISION ET NON DES pf
//IL NE PEUT PAS Y AVOIR UN - APRES UNE PRECISION (puisque - fonctionne comme fo_p a lenvers)
//	LA PREMIERE PRECISION PEUT COMMENCER PAR 0(nigga bruuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuh)
//	DONC SI IL N'Y A PAS UN AUTRE pf APRES UNE PRECISION QUI COMMENCE PAR 0, ALORS LE 0 EST UN pf
//IL NE PEUT PAS Y AVOIR DE pf APRES UN .(mais la fl_p peut etre egale a 0)
//IL NE PEUT PAS Y AVOIR DE pf APRES fl_p(mais la fl_p peut etre egale a 0)
//UNE CONVERSION MARQUE TOUJOURS LA FIN D'UN FORMAT

//COMBINAISONS VALIDES:
//sf|fo_p|pf|fl_p|conv	(%#015.12d)
//fo_p|pf|fl_p|conv	(%032.3x)
//pf|fl_p|conv		(%015d)
//pf|conv		(%0s)
//fo_p|conv		(%900u)
//conv			(%%)
//pf|sf|conv		(%00-0-0-0 p)
//pf|sf|fl_p|conv	(%----  +123p)
//sf|pf|conv		(% +#.d)
//pf|sf|conv		(%0+d)(ne foncitionne pas avec . comme pf)
//sf|pf|sf|conv		(% -+d)
//pf|sf|pf|conv		(%0 0X)
//pf|sf|pf|fl_p|conv	(%-+-123s)
//sf|pf|sf|fl_p|conv	(%+0#321u)

//COMBINAISON INVALIDES:
//#015-12d
//..
//00123+d
//34-d
//34%

//ORDRE DE LECTURE:
//PASSER DES FLAGS
//PASSER UNE PRECISION
//PASSER DES FLAGS
//PASSER UNE PRECISION
#endif
