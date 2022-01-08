#include<stdio.h>
#include"ft_printf_bonus.h"


//contains char
int	cont(char c, char *s)
{
	return (c == *s || (s[1] && cont(c, s + 1)));
}

t_format	new_format()
{
	t_format f;

	f.sfi[0] = -1;
	f.sfi[1] = -1;
	f.sfi[2] = -1;
	f.conv = 0;
	f.pf = 0;
	f.fl_p = 0;
	f.fo_p = 0;
	return (f);
}

int	i_in(char c, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

int	parse_precision(char *s, int i, t_format *f)
{
	int	n;

	if (i == -1)
		return (-1);
	if (!cont(s[i], "0123456789"))
		return (i);
	n = 0;	
	while(cont(s[i], "0123456789"))
	{
		n *= 10;
		n += s[i++] - '0';
	}
//printf("f->pf = %c, cond = %d\n", f->pf, (f->pf != 0));
	if (f->pf != 0)
		f->fl_p = n;
	else
		f->fo_p = n;
	return (i);
}

int	parse_flags(char *s, int i, t_format *f)
{
	int	j;

	if (i == -1)
		return (-1);
	while (cont(s[i], FLAGS))
	{
		//update sf
		if (cont(s[i], SF))
		{
			f->sfi[i_in(s[i], SF)] = i;
			//verifier la validite
			if (f->fo_p || f->fl_p)
				return (-1);
		}
		else if (!(s[i] == '0' && f->pf))
		{
			if (f->pf == '.'
				|| (s[i] == '-' && f->fo_p)
				|| f->fl_p)
				return (-1);
			if (s[i] == '0')
			{
				j = i + 1;
				while (cont(s[j], "0123456789"))
					j++;
				if (s[j] == '.')
					return (i + 1);
			}
			f->pf = s[i];
		}
		//update pf
		i++;
	}
	return (i);
}

t_format	parse_format(char **str)
{
	int		i;
	t_format	f;
	char	*s;

	f = new_format();
	s = *str;
	if (*s != '%')
		return (f);
	if (s[1] == '%')
	{
		f.conv = '%';
		*str += 2;
		return (f);
	}
	i = 1;
	//first flags
	i = parse_flags(s, i, &f);
	//format precision
	i = parse_precision(s, i, &f);
	//second flags
	i = parse_flags(s, i, &f);
	//flag precision
	i = parse_precision(s, i, &f);
	if (i == -1 || !cont(s[i], "cspdiuxX"))
		return (f);
	f.conv = s[i];
	*str += i + 1;
	return (f);
}

void	print_format(t_format f)
{
		printf("\nf.conv = '%c'\nf.pf = '%c'\nf.fl_p = %d\nf.sfi = {%d, %d, %d}\nf.fo_p = %d\n\n", 
			f.conv, f.pf, f.fl_p, f.sfi[0], f.sfi[1], f.sfi[2], f.fo_p);
}

int	test(char *format, int valid)
{
	t_format f;
	char *oui = parse_format(format, &f);
	printf("testing \"%s\"\n", format);
	if (f.conv)
	{
		if (!valid)
			printf("ERROR-----------------------------------\n");
		print_format(f);
		printf("rest = \"%s\"\n", oui);
		if (!valid)
			printf("ERROR-----------------------------------\n\n");
		else
			printf("-----------------------------------------\n\n");
	}
	else
	{
		if (valid)
			printf("ERROR-----------------------------------\n");
		printf("Invalid format\n");
		if (valid)
			printf("ERROR-----------------------------------\n\n");
		else
			printf("-----------------------------------------\n\n");
	}
	return (valid != (f.conv != 0));
}

int	main()
{
	char *invalid_formats[]	=
			{
				"%#015-12d",
				"%..",
				"%00123+d",
				"%34-d",
				"%34%",
				NULL
			};
	char	*valid_formats[]	=
			{
				"%#015.12d",
				"%032.3x",
				"%015d",
				"%0s",
				"%900u"
				"%%",
				"%00-0-0-0  p",
				"%----  +123p",
				"% +#.d",
				"%0+d",
				"% -+d",
				"%0 0X",
				"%-+-123s",
				"%+0#321u",
				NULL
			};
	int	errors = 0;
	printf("Testing invalid formats.\n\n");
	for (int i = 0; invalid_formats[i]; i++)
		errors += test(invalid_formats[i], 0);
	printf("\nTesting valid fomats.\n");
	for (int i = 0; valid_formats[i]; i++)
		errors += test(valid_formats[i], 1);
	printf("%d errors encounterd.\n", errors);
}
