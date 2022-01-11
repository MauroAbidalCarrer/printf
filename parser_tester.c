#include<stdio.h>
#include"ft_printf_bonus.h"

void	print_format(t_format f)
{
	printf("\nf.conv = '%c'\nf.pf = '%c'\nf.fl_p = %d\nf.sfi = {%d, %d, %d}\nf.fo_p = %d\nf.rev = '%c'\n\n", 
			f.conv, f.pf, f.fl_p, f.sfi[0], f.sfi[1], f.sfi[2], f.fo_p, f.rev_fo_p);
}

int	test(char *format, int valid)
{
	char *save = format;
	t_format f = parse_format(&format);
	if ((f.conv != 0) != valid)
	{
		printf("testing \"%s\"\n", save);
		if (valid)
			printf("should be valid\n");
		else
			printf("sould not be valid\n");
		printf("ERROR-----------------------------------\n");
		print_format(f);
		printf("rest = \"%s\"\n", format);
		printf("ERROR-----------------------------------\n\n");
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
				"%-9.3d",
				NULL
			};
	int	errors = 0;
	for (int i = 0; invalid_formats[i]; i++)
		errors += test(invalid_formats[i], 0);
	for (int i = 0; valid_formats[i]; i++)
		errors += test(valid_formats[i], 1);
	printf("%d errors encounterd.\n", errors);
}
