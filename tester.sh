#gcc -Wall -Wextra -Werror ft_printf_utils_bonus.c ft_printf_bonus.c shower.c;
make bonus;
make clean;
gcc -Wall -Werror -Wextra shower.c -L. -lftprintf
./a.out my > my;
./a.out > og;
diff -e my og
