#include"ft_printf_bonus.h"
#include<stdio.h>

static void	putdigit(long n)
{
	if (n >= 10)
		putdigit(n / 10);
char c = '0' + n % 10;
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		write(1, "-", 1);
		putdigit(-((long)n));
	}
	else
		putdigit((long)n);
	write(1, "\n", 1);
}

void	printf_putnbr(int n)
{
	printf("%d\n", n);
}

int	main(int ac, char **av)
{
	int (*print)(const char *,  ...);
	void (*putnbr) (int n);
	if (ac >= 2 && av[1][0] == 'm' && av[1][1] == 'y')
	{
		print = &ft_printf;
		putnbr = &ft_putnbr;
	}
	else
	{
		putnbr = &printf_putnbr;
		print = &printf;
	}
//simple tests
	putnbr(print("simple %s", "tests:\n\n"));
	putnbr(print("yes\n", NULL));
	putnbr(print("NULL string = %s\n", NULL));
	putnbr(print("32 int = %d\n", 32));
	putnbr(print("32 int = %i\n", 32));
	putnbr(print("32 in hexa lower case = %x\n", 32));
	putnbr(print("32 in hexa upper case = %X\n", 32));
	putnbr(print("0 in HDL = %X\n", 32));
	putnbr(print("adress 123 = %p\n", 123));
	putnbr(print("negative number = %d\n", -123));
	putnbr(print("negative number = %i\n", -123));
	putnbr(print("%p\n", NULL));
//limits
	putnbr(print("lints%s\n", ":\n"));
	putnbr(print("unsigned long long max = %p\n", 9223372036854775807));
	putnbr(print("int max = %d\n", 2147483647));
	putnbr(print("int max = %i\n", 2147483647));
	putnbr(print("int min = %d\n", -2147483648));
	putnbr(print("int min = %i\n", -2147483648));
	putnbr(print("unsigned int max = %u\n", 4294967295));
	putnbr(print("unsigned int max = %x\n", 4294967295));
	putnbr(print("unsigned int max = %X\n", 4294967295));
	putnbr(print("0 = %d\n", 0));
//flags combinations
	putnbr(print("flag combinations:\n",  42));
	putnbr(print("%#015.12d\n",  42));
	putnbr(print("%#015.0000d\n",  42));
	putnbr(print("%032.3x\n",  42));
	putnbr(print("%032.3x\n",  42));
	putnbr(print("%0s\n", "salut ca va?"));
	putnbr(print("%90u\n", 42));
	putnbr(print("%%\n"));
	putnbr(print("%%00-0-0-0  p (32100) = \"%00-0-0-0  p\"\n", 32100));
	putnbr(print("%00-0-0-0  p\n", NULL));
	putnbr(print("%%----  +23p (3524) = %----  +23p\n", 3524));
	putnbr(print("%% +.d = \"% +#.d\"\n", 0));
	putnbr(print("%0+d\n", 120));
	putnbr(print("% -+d\n", 120));
	putnbr(print("% -+d\n", -120));
	putnbr(print("%0 0X\n", 120));
	putnbr(print("%0 0X\n", 0));
	putnbr(print("%-+-23s\n", "mewicclair"));
	putnbr(print("%023s\n", "mewicclair"));
	putnbr(print("%-+-23s\n", NULL));
	putnbr(print("%%+0#32u = %+0#32u\n", 0));
	putnbr(print("%%+032d = %+032d\n", 92));
	putnbr(print("%%+032s = %+032s\n", "sale"));
	putnbr(print("%%+0#32u = %+0#32u\n", 100));
	putnbr(print("%%-+012d = %-+012d\n", 22));
	putnbr(print("%%-+.12d = %-+.12d\n", 22));
	putnbr(print("%%-+015.12d = %-+015.12d\n", 22));
	putnbr(print("\n"));
//multiple fomats
	putnbr(print("multiple formats:\n"));
	putnbr(print("yes%12s, %%% +d% indeddededed\n", NULL, 32, -47));
	putnbr(print("yes%12s, %% +d% indeddededed\n", NULL, 32, -47));
	putnbr(print("%%%%%%%%%%%%%%%\n"));
	putnbr(print("\%s%s%w%%%%\n", "salut", "ca va?", "ata koi?"));
}
